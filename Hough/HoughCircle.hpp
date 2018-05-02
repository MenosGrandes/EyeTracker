#ifndef HOUGHCIRCLE_HPP
#define HOUGHCIRCLE_HPP
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "../Helpers/const.hpp"
#include <string>
#include <iostream>
class HoughCircle
{

public:
    void  execute(cv::Mat &mat,int min,int max,int treshold,std::vector<cv::Point3f> &circles) const
    {
        std::vector<cv::Mat> hough_spaces(max);
        for(int i=0; i<max; ++i)
        {
            hough_spaces[i] = cv::Mat::zeros(mat.rows,mat.cols,mat.type());
        }
        for(int x=0; x<mat.rows; ++x)
        {
            for(int y=0; y<mat.cols; ++y)
            {
                if(mat.at<const uchar>(x,y) == 255)
                {
                    for(int radius=min; radius<max; ++radius)
                    {
                        for(int theta = 0; theta<360; ++theta)
                        {
                            const int a = x - radius * lookup::cosArray[theta];//+ 0.5f;
                            const int b = y - radius * lookup::sinArray[theta]; //+ 0.5f;
                            if(a >= 0 && a <hough_spaces[radius].rows && b >= 0 && b<hough_spaces[radius].cols)                             {
                                hough_spaces[radius].at<uchar>(a,b)++;
                            }


                        }
                    }
                }
            }
        }
        for(int radius=min; radius<max; ++radius)
        {
            double min_f,max_f;
            cv::Point min_loc,max_loc;
            cv::minMaxLoc(hough_spaces[radius],&min_f,&max_f,&min_loc,&max_loc);
            if(max_f>=treshold)
            {
                circles.emplace_back(cv::Point3f(max_loc.x,max_loc.y,radius));
                debug::showImage(std::to_string(radius).c_str(),hough_spaces[radius]);

            }
        }
        circles.shrink_to_fit();

    }
    void  execute2(cv::Mat &mat,int min,int max,int treshold,std::vector<cv::Point3f> &circles,int kernelSize) const
    {

        cv::Mat sobelX,sobelY;
        Sobel(mat, sobelX, CV_32F, 1, 0, kernelSize, 1, 0, cv::BORDER_REPLICATE);
        Sobel(mat, sobelY, CV_32F, 0, 1, kernelSize, 1, 0, cv::BORDER_REPLICATE);
        //cv::Canny(mat,mat,100,200,kernelSize,false);
        debug::showImage("sobelX",sobelX);
        debug::showImage("SobelY",sobelY);
        debug::showImage("MAT",mat);
        cv::Mat magnitudeMap,angleMap;
	magnitudeMap = cv::Mat::zeros(mat.rows,mat.cols,mat.type());
	angleMap = cv::Mat::zeros(mat.rows,mat.cols,mat.type());
        std::vector<cv::Mat> hough_spaces(max);
        for(int i=0; i<max; ++i)
        {
            hough_spaces[i] = cv::Mat::zeros(mat.rows,mat.cols,mat.type());
        }
        for(int x=0; x<mat.rows; ++x)
        {
            for(int y=0; y<mat.cols; ++y)
            {

                const float magnitude = sqrt(sobelX.at<uchar>(x,y)*sobelX.at<uchar>(x,y)+sobelY.at<uchar>(x,y)*sobelY.at<uchar>(x,y));
                const float theta= atan2(sobelY.at<uchar>(x,y),sobelX.at<uchar>(x,y)) * 180/CV_PI;
                magnitudeMap.at<uchar>(x,y) = magnitude;
                if(magnitude > 225)//mat.at<const uchar>(x,y) == 255)
                {
                    for(int radius=min; radius<max; ++radius)
                    {

                        const int a = x - radius * cos(theta);//lookup::cosArray[static_cast<int>(theta)];//+ 0.5f;
                        const int b = y - radius * sin(theta);//lookup::sinArray[static_cast<int>(theta)]; //+ 0.5f;
                        if(a >= 0 && a <hough_spaces[radius].rows && b >= 0 && b<hough_spaces[radius].cols)                             {
                            hough_spaces[radius].at<uchar>(a,b)+=10;
                        }


                    }
                }
            }
        }
        debug::showImage("magnitude",magnitudeMap);
        for(int radius=min; radius<max; ++radius)
        {
            double min_f,max_f;
            cv::Point min_loc,max_loc;
            cv::minMaxLoc(hough_spaces[radius],&min_f,&max_f,&min_loc,&max_loc);
            if(max_f>=treshold)
            {
                circles.emplace_back(cv::Point3f(max_loc.x,max_loc.y,radius));
                // debug::showImage(std::to_string(radius).c_str(),hough_spaces[radius]);

            }
        }
        circles.shrink_to_fit();




    }

};
#endif

