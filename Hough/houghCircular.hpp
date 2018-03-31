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

    std::vector<cv::Point3f > calculate(cv::Mat &mat,int min,int max)
    {
        if(max>mat.rows)
        {
            max = mat.rows-3;
        }
        std::cout<<"min : "<<min <<"max" << max<<std::endl;
        std::vector<cv::Point3f> circles(100);
        circles.reserve(10000);
        std::vector<cv::Mat> hough_spaces(max*2);
        for(int i=min; i<max*2; ++i)
        {
            hough_spaces[i] = cv::Mat::zeros(mat.rows,mat.cols,mat.type());
        }
        // const int sz[3] = {mat.rows,mat.cols,max-min};
        //cv::Mat L(3,sz, CV_8UC(1), cv::Scalar::all(0));
        for(int x=0; x<mat.rows; ++x)
        {

            for(int y=0; y<mat.cols; ++y)
            {

                if(mat.at<uchar>(x,y) == 255) {
                    for(int radius=min; radius<max; ++radius)
                    {
                        std::cout<<radius<<"radius"<<std::endl;
                        for(int theta = 0; theta<360; ++theta)
                        {
                            const float a= x - radius * cos(theta * PI_180);
                            const float b=y- radius *sin(theta * PI_180);
                            //if(a <0 || a >= mat.rows || b < 0 || b >= mat.cols){
			    hough_spaces[radius].at<uchar>(a,b)++;
			   // }
                            //L.at<uchar>(a,b,radius)+=1;
                        }
                    }
                }
            }


        }
/*
        const int treshold = 20;
        for(int radius=(max - min); radius<max; ++radius)
        {
            for(int x=mat.rows; x<mat.rows; ++x)
            {
                for(int y=mat.cols; y<mat.rows; ++y)
                {
                    if(hough_spaces[radius].at<uchar>(x,y) >treshold)
                    {
                        std::cout<<"CIRCLE"<<std::endl;
                        circles.emplace_back(cv::Point3f(x,y,radius));
                    }
                }

            }
        }
	*/
        //cv::Mat current_space = L.subm
        imshow("i",hough_spaces[4]);

        /*
            for(int radius = min; radius< max; ++radius )
            {
                cv::Mat &hough_space = hough_spaces[radius-min];
                hough_space.create(mat.rows,mat.cols,mat.type());


                for(int x=0; x<mat.cols; ++x)
                {

                    for(int y=0; y<mat.rows; ++y)
                    {
                        if(mat.at<uchar>(x,y) == 255)
                        {
                            //accum_circle(hough_space,cv::Point2i(y,x),radius);

        	    }
                    }
                }
            imshow("i",hough_space);//hough_space);

            const int treshold = 5 *radius;
                for(int x=0; x<hough_space.cols; ++x)
                {

                    for(int y=0; y<hough_space.rows; ++y)
                    {
                        if(hough_space.at<uchar>(x,y) > treshold)
                        {

                            circles.emplace_back(cv::Point3f(x,y,radius));
                        }
                    }
                }
            }*/
        circles.shrink_to_fit();
        return circles;

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
        if(position.x < 0 || position.x >= image.cols ||
                position.y < 0 || position.y >= image.rows)
        {
            return;
        }
        image.at<uchar>(position.x,position.y)++;
    }


};

#endif
