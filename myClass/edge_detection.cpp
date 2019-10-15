//
//  edge_detection.cpp
//  OpenCVTest000
//
//  Created by 曹伟东 on 2019/1/29.
//  Copyright © 2019年 曹伟东. All rights reserved.
//

#import "myOpenCVUtils.h"


int edgeThresh = 1;
int edgeThreshScharr=1;

Mat image, gray, blurImage, edge1, edge2, cedge;

const char* window_name1 = "Edge map : Canny default (Sobel gradient)";
const char* window_name2 = "Edge map : Canny with custom gradient (Scharr)";

// define a trackbar callback
static void onTrackbar(int, void*)
{
    blur(gray, blurImage, Size(3,3));
    
    // Run the edge detector on grayscale
    Canny(blurImage, edge1, edgeThresh, edgeThresh*3, 3);
    cedge = Scalar::all(0);
    
    image.copyTo(cedge, edge1);
    imshow(window_name1, cedge);
    
    /// Canny detector with scharr
    Mat dx,dy;
    Scharr(blurImage,dx,CV_16S,1,0);
    Scharr(blurImage,dy,CV_16S,0,1);
    Canny( dx,dy, edge2, edgeThreshScharr, edgeThreshScharr*3 );
    /// Using Canny's output as a mask, we display our result
    cedge = Scalar::all(0);
    image.copyTo(cedge, edge2);
    imshow(window_name2, cedge);
}

void myOpenCVUtils::adgeDetection(){
    //help();
    //CommandLineParser parser(argc, argv, keys);
    string filename = resorcesFilePath+"/data_pic/fruits.jpg";
    
    image = imread(filename, IMREAD_COLOR);
    
    if(image.empty())
    {
        printf("Cannot read image file: %s\n", filename.c_str());
        //help();
        return;
    }
    imshow("Source Image", image);
    
    cedge.create(image.size(), image.type());
    cvtColor(image, gray, COLOR_BGR2GRAY);
    
    // Create a window
    namedWindow(window_name1, 1);
    namedWindow(window_name2, 1);
    
    // create a toolbar
    createTrackbar("Canny threshold default", window_name1, &edgeThresh, 100, onTrackbar);
    createTrackbar("Canny threshold Scharr", window_name2, &edgeThreshScharr, 400, onTrackbar);
    
    // Show the image
    onTrackbar(0, 0);
    
    // Wait for a key stroke; the same function arranges events processing
    waitKey(0);
    
    destroyAllWindows();
}

