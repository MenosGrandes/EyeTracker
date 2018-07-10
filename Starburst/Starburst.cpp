#include "Starburst.h"
#include <iostream>

Starburst::Starburst(cv::Point2f _center):center(_center) {};
Starburst::Starburst() {};
void Starburst::calculate( cv::Mat &image,const int rayCount,const int treshold) const
{
    cv::Mat draw = image.clone();
    cvtColor(draw,draw,cv::COLOR_GRAY2BGR);
    cv::Mat draw2 = image.clone();
    cvtColor(draw2,draw2,cv::COLOR_GRAY2BGR);

    const cv::Size size =  image.size();
    const cv::Point2f center(size.height/2,size.width/2);
    const float maxRadius = center.x;


    std::vector<cv::Point2f> edgePoints;
    edgePoints.reserve(100);


    float angle = 0*PI_180;
    float angleStep = 360/rayCount;
    cv::Point2f previousPixel;


    for( int ray=0; ray<rayCount; ray++,angle+=angleStep* PI_180)
    {
        for(int radius =0; radius<maxRadius; radius+=1)
        {
            const cv::Point2f pixel (center.x + radius*sin(angle) , center.y + radius*cos(angle) );
            const cv::Scalar color(image.at<uchar>(pixel));
            if(color.val[0]>treshold)
            {

                debug::drawMarker(draw,previousPixel,cv::Scalar(255,255,0));
                debug::drawLine(draw,center,previousPixel,cv::Scalar(200,100,100));
                edgePoints.emplace_back(previousPixel);
                break;
            }
            else
            {
                previousPixel = pixel;
            }
        }
    }
    cv::circle(draw,center,2,cv::Scalar(10,255,0));

    angleStep=50;
    angle=0;
    for(cv::Point2f edgePoint : edgePoints)
    {
        for( int ray=0; ray<rayCount; ray++,angle+=angleStep* PI_180)
        {
            for(int radius =0; radius<maxRadius; radius++)
            {
                const cv::Point2f pixel (edgePoint.x + radius*sin(angle) , edgePoint.y + radius*cos(angle) );
                const cv::Scalar color(image.at<uchar>(pixel));
                if(color.val[0]>treshold)
                {
                    debug::drawMarker(draw2,previousPixel,cv::Scalar(255,255,0));
                    debug::drawLine(draw2,edgePoint,previousPixel,cv::Scalar(200,100,100));
                    edgePoints.emplace_back(pixel);
                    break;
                }
		else
		{
		previousPixel = pixel;
		}
            }
        }
    }

    std::cout<<edgePoints.size()<<std::endl;
    imshow("initial",draw);
    imshow("second",draw2);



}
void shotRay(const int degree)
{


}
