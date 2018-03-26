#ifndef HOUGH_HPP
#define HOUGH_HPP
#include <opencv2/core/core.hpp>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"



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

    void calculate(cv::Mat &mat,int min,int max)
    {
        std::vector<cv::Mat> hough_spaces(max - min);
        for(int i = min; i< max; ++i )
        {
            cv::Mat &hough_space = hough_spaces[i-min];
            hough_space.create(mat.rows,mat.cols,mat.type());


            for(int x=0; x<mat.cols; ++x)
            {

                for(int y=0; y<mat.rows; ++y)
                {
                    if(mat.at<uchar>(x,y) == 255)
                    {
                        accum_circle(hough_space,cv::Point2i(x,y),i);
                    }
                }
            }
            const int treshold = 5 *i;
            for(int x=0; x<hough_space.cols; ++x)
            {

                for(int y=0; y<hough_space.rows; ++y)
                {
                    if(hough_space.at<uchar>(x,y) > treshold)
                    {

			cv::circle(mat,cv::Point2i(x,y),i,cv::Scalar(0,0,255),3,8,0);							
//draw circle;
//std::cout<<"CIRCLE!";
                    }

                }


            }

        }


    }
private :

    void accum_circle(cv::Mat & image,const cv::Point2i &position,unsigned int radius)//image &image, const cv::point2i &position, unsigned int radius)
    {
        int f = 1 - radius;
        int ddf_x = 1;
        int ddf_y = -2 * radius;
        int x = 0;
        int y = radius;

        accum_pixel(image, cv::Point2i(position.x, position.y + radius));
        accum_pixel(image, cv::Point2i(position.x, position.y - radius));
        accum_pixel(image, cv::Point2i(position.x + radius, position.y));
        accum_pixel(image, cv::Point2i(position.x - radius, position.y));

        while(x < y)
        {
            if(f >= 0)
            {
                y--;
                ddf_y += 2;
                f += ddf_y;
            }

            x++;
            ddf_x += 2;
            f += ddf_x;

            accum_pixel(image, cv::Point2i(position.x + x, position.y + y));
            accum_pixel(image, cv::Point2i(position.x - x, position.y + y));
            accum_pixel(image, cv::Point2i(position.x + x, position.y - y));
            accum_pixel(image, cv::Point2i(position.x - x, position.y - y));
            accum_pixel(image, cv::Point2i(position.x + y, position.y + x));
            accum_pixel(image, cv::Point2i(position.x - y, position.y + x));
            accum_pixel(image, cv::Point2i(position.x + y, position.y - x));
            accum_pixel(image, cv::Point2i(position.x - y, position.y - x));
        }
    }
    void accum_pixel(cv::Mat &image, const cv::Point2i &position)
    {
        /* bounds checking */
        if(position.x < 0 || position.x >= image.rows ||
                position.y < 0 || position.y >= image.cols)
        {
            return;
        }
        image.at<uchar>(position.x,position.y)++;
    }


};

#endif
