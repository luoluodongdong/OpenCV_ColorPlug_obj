//
//  creat_mask.cpp
//  OpenCVTest000
//
//  Created by 曹伟东 on 2019/1/29.
//  Copyright © 2019年 曹伟东. All rights reserved.
//
#import "myOpenCVUtils.h"


Mat src, img1, mask, finalpic;

Point point;
vector<Point> pts;
int drag = 0;
int var = 0;
int flag = 0;

void mouseHandler(int event, int x, int y, int, void*)
{
    
    if (event == EVENT_LBUTTONDOWN && !drag)
    {
        if (flag == 0)
        {
            if (var == 0)
                img1 = src.clone();
            point = Point(x, y);
            circle(img1, point, 2, Scalar(0, 0, 255), -1, 8, 0);
            pts.push_back(point);
            var++;
            drag  = 1;
            
            if (var > 1)
                line(img1,pts[var-2], point, Scalar(0, 0, 255), 2, 8, 0);
            
            imshow("Source", img1);
        }
    }
    
    if (event == EVENT_LBUTTONUP && drag)
    {
        imshow("Source", img1);
        drag = 0;
    }
    
    if (event == EVENT_RBUTTONDOWN)
    {
        flag = 1;
        img1 = src.clone();
        
        if (var != 0)
        {
            polylines( img1, pts, 1, Scalar(0,0,0), 2, 8, 0);
        }
        
        imshow("Source", img1);
    }
    
    if (event == EVENT_RBUTTONUP)
    {
        flag = var;
        finalpic = Mat::zeros(src.size(), CV_8UC3);
        mask = Mat::zeros(src.size(), CV_8UC1);
        
        vector<vector<Point> > vpts;
        vpts.push_back(pts);
        fillPoly(mask, vpts, Scalar(255, 255, 255), 8, 0);
        bitwise_and(src, src, finalpic, mask);
        imshow("Mask", mask);
        imshow("Result", finalpic);
        imshow("Source", img1);
    }
    
    if (event == EVENT_MBUTTONDOWN)
    {
        pts.clear();
        var = 0;
        drag = 0;
        flag = 0;
        imshow("Source", src);
    }
}

void myOpenCVUtils::creatMaskTest(){
    //CommandLineParser parser(argc, argv, "{@input | ../data/lena.jpg | input image}");
    //parser.about("This program demonstrates using mouse events\n");
    //parser.printMessage();
    cout << "\n\tleft mouse button - set a point to create mask shape\n"
    "\tright mouse button - create mask from points\n"
    "\tmiddle mouse button - reset\n";
    String input_image = resorcesFilePath+"/data_pic/lena.jpg";//parser.get<String>("@input");
    
    src = imread(input_image);
    
    if (src.empty())
    {
        printf("Error opening image: %s\n", input_image.c_str());
        return;
    }
    
    namedWindow("Source", WINDOW_AUTOSIZE);
    setMouseCallback("Source", mouseHandler, NULL);
    imshow("Source", src);
    waitKey(0);
    
    destroyAllWindows();
}
