#ifndef HOUGHCIRCLE_HPP
#define HOUGHCIRCLE_HPP
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "../Helpers/const.hpp"
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
                            const int a = floor(x - radius * lookup::cosArray[theta]);//bin cos(theta * PI_180));//radius * cos can be precomputed and used multiple times
                            const int b = floor(y - radius * lookup::sinArray[theta]);//sin(theta * PI_180));
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
    }
};
#endif

