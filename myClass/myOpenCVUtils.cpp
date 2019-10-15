//
//  ImageProcessUtils.cpp
//  OpenCVTest000
//
//  Created by 曹伟东 on 2019/1/26.
//  Copyright © 2019年 曹伟东. All rights reserved.
//

//#include <stdio.h>

#import "myOpenCVUtils.h"

/* 图像转灰度*/
Mat myOpenCVUtils::imageToGray(String inputImageFullPath){
    cv::Mat gray;
    Mat input=imread(inputImageFullPath).clone();
    cvtColor(input,gray,cv::COLOR_BGR2GRAY);

    return gray;
}

/* 图像均值滤波*/
Mat myOpenCVUtils::imageBlur(String inputImageFullPath){
    Mat output;
    Mat input = imread(inputImageFullPath).clone();
    blur(input,output,Size(7,7));
    
    return output;
}

/*显示图像*/
void myOpenCVUtils::showImage(String inputImageFullPath){
    
    cv::namedWindow("Image", cv::WINDOW_NORMAL);
    
    //这里要填写你要显示的图片路径
    Mat input = cv::imread(inputImageFullPath);
    
    cv::imshow("Image", input);
    
    cv::waitKey(0);
    
    //cv::(&input);
    
    cv::destroyWindow("Image");
    //cvDestroyWindow("image");
}




