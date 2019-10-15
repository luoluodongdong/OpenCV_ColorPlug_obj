//
//  ImageProcessUtils.hpp
//  OpenCVTest000
//
//  Created by 曹伟东 on 2019/1/26.
//  Copyright © 2019年 曹伟东. All rights reserved.
//

#ifndef myOpenCVUtils_h
#define myOpenCVUtils_h

#ifdef check
    #define OS_X_STUPID_CHECK_MACRO check
    #undef check
#endif

#ifdef __cplusplus
#undef NO
#undef YES
//#import <opencv2/opencv.hpp>
#include <opencv2/opencv.hpp>
#endif

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/objdetect.hpp"
//#include "opencv2/core/core.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/videoio.hpp"



#include <iostream>
#include <stdio.h>

#ifdef OS_X_STUPID_CHECK_MACRO
    #define check OS_X_STUPID_CHECK_MACRO
    #undef OS_X_STUPID_CHECK_MACRO
#endif

using namespace std;
using namespace cv;

class myOpenCVUtils {
    
    
public:
    /* 图像转灰度*/
    //Mat imageToGray(String inputImageFullPath);
    /* 图像均值滤波*/
    //Mat imageBlur(String inputImageFullPath);
    /*显示图像*/
    //void showImage(String inputImageFullPath);
    
    /*SOURCE FILE PATH*/
    //String resorcesFilePath;
    /*FACE DETECTION*/
    //void facedetectTest();
    /*EDGE DETECTION*/
    //void adgeDetection();
    /*CREAT MASK*/
    //void creatMaskTest();
    /*dft图像傅立叶转换*/
    //void dftTest();
    /*DETECT BLOB*/
    //void detectBlobTest();
    /*DRAWING*/
    //void drawingTest();
    /*recover motion_out_of_focus image with motion blur distortion*/
    //void recoverImageWithMBD();
    /*recover out_of_focus image*/
    //void recoverDefocusImage();
    /*screenshot test*/
    void screenshotTest(Mat img);
};

#endif /* ImageProcessUtils_h */
