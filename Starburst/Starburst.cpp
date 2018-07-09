#include "Starburst.h"
#include <iostream>

Starburst::Starburst(cv::Point2f _center):center(_center) {};
Starburst::Starburst() {};
void Starburst::calculate( cv::Mat &image,const int rayCount,const int treshold) const
{

    std::vector<cv::Point2f> contourPoints;
    const cv::Size size =  image.size();
    const cv::Point2f center(size.height/2,size.width/2);
    const float  angleStep = 360 / rayCount;
    const float maxRadius = center.x;

    const int radiusStep = 1; //bo to sa i tak i tak piksele wiec przekskauje zawsze po pelnej wartosci piksela







    std::vector<cv::Point2f> edgePoints;
    edgePoints.reserve(100);

    cv::Mat draw = image.clone();
    cvtColor(draw,draw,cv::COLOR_GRAY2BGR);
    float angle = 0*PI_180;
    for( int ray=0; ray<rayCount; ray++,angle+=angleStep* PI_180)
    {
        for(int radius =0; radius<maxRadius; radius++)
        {
            const cv::Point2f pixel (center.x + radius*sin(angle) , center.y + radius*cos(angle) );
            const cv::Scalar color(image.at<uchar>(pixel));
            if(color.val[0]<treshold)//zamiast robic treshold na pale to moze jakos procentowa zmiana od ostatniego?
            {
                cv::drawMarker(draw,pixel,cv::Scalar(255,0,0),cv::MarkerTypes::MARKER_STAR,1,1,8);
            }
            else
            {

                cv::drawMarker(draw,pixel,cv::Scalar(255,255,0),cv::MarkerTypes::MARKER_CROSS,10,1,8);
                edgePoints.emplace_back(pixel);
                break;

            }


        }

    }

    cv::circle(draw,center,2,cv::Scalar(10,255,0));

//Wyslij jeszcze raz promienie z katem 50d dla kazdego punktu koncowego
    cv::Mat draw2 = image.clone();
    cvtColor(draw2,draw2,cv::COLOR_GRAY2BGR);

    cv::Point2f point = edgePoints[0];
    for (cv::Point2f point : edgePoints)
    {
        for( float angle = 0; angle<2*CV_PI; angle+=50* PI_180)
        {
            for(int radius =0; radius<maxRadius; radius++)
            {
                const cv::Point2f pixel (point.x + radius*sin(angle) , point.y + radius*cos(angle) );
                const cv::Scalar color(image.at<uchar>(pixel));

                if(color.val[0]<treshold)
                {
                       cv::drawMarker(draw2,pixel,cv::Scalar(0,0,0),cv::MarkerTypes::MARKER_STAR,1,1,8);
                }
                else
                {

                     cv::drawMarker(draw2,pixel,cv::Scalar(255,255,0),cv::MarkerTypes::MARKER_CROSS,10,1,8);
                    break;
                }


            }
        }

    }

        imshow("aaa",draw);


        imshow("aaa2",draw2);


}
void shotRay(const int degree)
{


}
