//
//  screenshot.cpp
//  OpenCVTest000
//
//  Created by 曹伟东 on 2019/2/17.
//  Copyright © 2019年 曹伟东. All rights reserved.
//

#import "myOpenCVUtils.h"

void myOpenCVUtils::screenshotTest(Mat img){
    //string filename = resorcesFilePath+"/data_pic/lena.jpg";
    //Mat img = imread(filename);
    if( img.empty() )
    {
        //help();
        //printf("Cannot read image file: %s\n", filename.c_str());
        return ;
    }
    //imshow("Source", img);
    
    //cv::Rect rect1();
    Mat imageROI=img(cv::Rect(436,560,200,200));
    
    Mat output;
    
    imageROI.copyTo(output);
    
    //imshow("Output", output);
    
    waitKey(0);
    
    destroyAllWindows();
    
}
