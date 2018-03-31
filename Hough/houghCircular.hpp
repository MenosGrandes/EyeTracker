#ifndef HOUGH_HPP
#define HOUGH_HPP
#include <opencv2/core/core.hpp>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
//#include "../precompiled/CompileTimeAngle.hpp"


#include <iostream>
#include <vector>
#define PI_180 CV_PI / 180


template <typename Function>
class Hough
{
private:
    Function * function;
public:
    Hough():function(new Function()) {};

    ~Hough()
    {
        delete function;
    };

    std::vector<cv::Point3f > calculate(cv::Mat &mat,int min,int max,int treshold) const
    {
        if(max>mat.rows)
        {
            max = std::min(mat.cols ,mat.rows)/2;
        }
//        std::cout<<"min : "<<min <<"max" << max<<std::endl;
        std::vector<cv::Point3f> circles(100);
        circles.reserve(100);
        std::vector<cv::Mat> hough_spaces(max);
        for(int i=0; i<max; ++i)
        {
            hough_spaces[i] = cv::Mat::zeros(mat.rows,mat.cols,mat.type());
        }
//	std::cout<<mat.rows<<" "<<mat.cols<<std::endl;
        // const int sz[3] = {mat.rows,mat.cols,max-min};
        //cv::Mat L(3,sz, CV_8UC(1), cv::Scalar::all(0));
        for(int x=0; x<mat.rows; ++x)
        {

            for(int y=0; y<mat.cols; ++y)
            {

                if(mat.at<uchar>(x,y) == 255)
                {
                    for(int radius=min; radius<max; ++radius)
                    {
                        for(int theta = 0; theta<360; ++theta)
                        {
                            const int a = floor(x - radius * cos(theta * PI_180));//radius * cos can be precomputed and used multiple times
                            const int b = floor(y - radius * sin(theta * PI_180));
                            if(a <0 || a >= hough_spaces[radius].rows ||
                             b < 0 || b >= hough_spaces[radius].cols)
                            {
                                break;
                            }
                            hough_spaces[radius].at<uchar>(a,b)++;

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
            if(max_f>treshold)
            {
                circles.emplace_back(cv::Point3f(max_loc.x,max_loc.y,radius));
            }
        }
        circles.shrink_to_fit();
        return circles;

    }

};

#endif
