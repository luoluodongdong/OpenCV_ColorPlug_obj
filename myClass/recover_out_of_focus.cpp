//
//  recover_out_of_focus.cpp
//  OpenCVTest000
//
//  Created by 曹伟东 on 2019/1/30.
//  Copyright © 2019年 曹伟东. All rights reserved.
//

#import "myOpenCVUtils.h"

//void calcPSF(Mat& outputImg, Size filterSize, int R);
//void fftshift(const Mat& inputImg, Mat& outputImg);
//void filter2DFreq(const Mat& inputImg, Mat& outputImg, const Mat& H);
//void calcWnrFilter(const Mat& input_h_PSF, Mat& output_G, double nsr);

const String keys2 =
"{help h usage ? |             | print this message   }"
"{image          |original.JPG | input image name     }"
"{R              |53           | radius               }"
"{SNR            |5200         | signal to noise ratio}"
;

int R = 10;//parser.get<int>("R");
int snr2 = 452;//parser.get<int>("SNR");

Mat imgIn2;
const char* recoveWinName2 = "Recover Image";



//! [calcPSF]
void calcPSF2(Mat& outputImg, Size filterSize, int R)
{
    Mat h(filterSize, CV_32F, Scalar(0));
    Point point(filterSize.width / 2, filterSize.height / 2);
    circle(h, point, R, 255, -1, 8);
    Scalar summa = sum(h);
    outputImg = h / summa[0];
}
//! [calcPSF]

//! [fftshift]
void fftshift2(const Mat& inputImg, Mat& outputImg)
{
    outputImg = inputImg.clone();
    int cx = outputImg.cols / 2;
    int cy = outputImg.rows / 2;
    Mat q0(outputImg, Rect(0, 0, cx, cy));
    Mat q1(outputImg, Rect(cx, 0, cx, cy));
    Mat q2(outputImg, Rect(0, cy, cx, cy));
    Mat q3(outputImg, Rect(cx, cy, cx, cy));
    Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);
}
//! [fftshift]

//! [filter2DFreq]
void filter2DFreq2(const Mat& inputImg, Mat& outputImg, const Mat& H)
{
    Mat planes[2] = { Mat_<float>(inputImg.clone()), Mat::zeros(inputImg.size(), CV_32F) };
    Mat complexI;
    merge(planes, 2, complexI);
    dft(complexI, complexI, DFT_SCALE);
    
    Mat planesH[2] = { Mat_<float>(H.clone()), Mat::zeros(H.size(), CV_32F) };
    Mat complexH;
    merge(planesH, 2, complexH);
    Mat complexIH;
    mulSpectrums(complexI, complexH, complexIH, 0);
    
    idft(complexIH, complexIH);
    split(complexIH, planes);
    outputImg = planes[0];
}
//! [filter2DFreq]

//! [calcWnrFilter]
void calcWnrFilter2(const Mat& input_h_PSF, Mat& output_G, double nsr)
{
    Mat h_PSF_shifted;
    fftshift2(input_h_PSF, h_PSF_shifted);
    Mat planes[2] = { Mat_<float>(h_PSF_shifted.clone()), Mat::zeros(h_PSF_shifted.size(), CV_32F) };
    Mat complexI;
    merge(planes, 2, complexI);
    dft(complexI, complexI);
    split(complexI, planes);
    Mat denom;
    pow(abs(planes[0]), 2, denom);
    denom += nsr;
    divide(planes[0], denom, output_G);
}
//! [calcWnrFilter]

// define a trackbar callback
static void onTrackbar2(int, void*)
{
    
    
    Mat imgOut;
    
    //! [main]
    // it needs to process even image only
    Rect roi = Rect(0, 0, imgIn2.cols & -2, imgIn2.rows & -2);
    
    //Hw calculation (start)
    Mat Hw, h;
    calcPSF2(h, roi.size(), R);
    calcWnrFilter2(h, Hw, 1.0 / double(snr2));
    //Hw calculation (stop)
    
    // filtering (start)
    filter2DFreq2(imgIn2(roi), imgOut, Hw);
    // filtering (stop)
    //! [main]
    
    imgOut.convertTo(imgOut, CV_8U);
    normalize(imgOut, imgOut, 0, 255, NORM_MINMAX);
    //imwrite("result.jpg", imgOut);
    //在图片上写文字
    string rStr=format("R:%.3d",R);
    string snrStr=format("SNR:%.4d",snr2);
    putText(imgOut,rStr,Point(5,40),FONT_HERSHEY_SIMPLEX,0.5,Scalar(255,23,0),1,8);
    putText(imgOut,snrStr,Point(5,60),FONT_HERSHEY_SIMPLEX,0.5,Scalar(255,23,0),1,8);
    imshow(recoveWinName2, imgOut);
}

void myOpenCVUtils::recoverDefocusImage(){
    
    
    string strInFileName = resorcesFilePath+"/data_pic/text_defocus.jpg";//parser.get<String>("image");
    
    imgIn2 = imread(strInFileName, IMREAD_GRAYSCALE);
    if (imgIn2.empty()) //check whether the image is loaded or not
    {
        cout << "ERROR : Image cannot be loaded..!!" << endl;
        return ;
    }
    
    //show source input image
    imshow("Source Image", imgIn2);
    
    //creat output of recover image window
    namedWindow(recoveWinName2,1);
    
    // create a toolbar
    createTrackbar("R:", recoveWinName2, &R, 50, onTrackbar2);
    createTrackbar("SNR:", recoveWinName2, &snr2, 1000, onTrackbar2);
    
    // Show the image
    onTrackbar2(0, 0);
    
    // Wait for a key stroke; the same function arranges events processing
    waitKey(0);
    
    destroyAllWindows();
}

