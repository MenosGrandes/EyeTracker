#include "Starburst.h"
#include <iostream>
#include <stdlib.h>
Starburst::Starburst(cv::Point2f _center):center(_center) {};
Starburst::Starburst() {};



void Starburst::calculate( const cv::Mat &image,const int rayCount,const int treshold,const int currentRadius) const
{
    cv::Mat draw = image.clone();
    cvtColor(draw,draw,cv::COLOR_GRAY2BGR);
    cv::Mat draw2 = image.clone();
    cvtColor(draw2,draw2,cv::COLOR_GRAY2BGR);

    cv::Point2f center(image.cols/2,image.rows/2);

    
    std::vector<IntensityAndPoint> intensityAndPoint_v;
    intensityAndPoint_v.reserve(1000);
    float angleStep = 360/rayCount;

    cv::circle(draw,center,5,cv::Scalar(10,255,0));





    const int minimumCandidates = 5;
    ////////////////////////////////
    cv::Point2f pixel;

    for(int angle =0; angle<360; angle+=angleStep)
    {

        const cv::Point2f distance (currentRadius*cos(angle),currentRadius*sin(angle));

        pixel= center + distance;// (center.x + distance.x,center.y + distance.y);
        const cv::Scalar colorOfPixel (image.at<uchar>(pixel));
        while(1)
        {
            pixel+=  distance;//cv::Point2f(pixel.x + distance.x,pixel.y + distance.y);
            if(pixel.x >image.cols || pixel.y >image.rows || pixel.x < 0 || pixel.y <0)
            {
                break;
            }
            const cv::Scalar differenceInColors=static_cast<const cv::Scalar>(image.at<uchar>(pixel)) - colorOfPixel;

           if(static_cast<int>((differenceInColors)[0]) > treshold)
            {
                const cv::Point2f edgePoint = pixel - distance/2;// ( pixel.x - distance.x/2,pixel.y - distance.y/2);
                debug::drawMarker(draw,edgePoint,cv::Scalar(255,255,0));
                debug::drawLine(draw,center,edgePoint,cv::Scalar(200,100,100));
                intensityAndPoint_v.emplace_back(static_cast<int>(differenceInColors[0]), edgePoint);
                break;

            }
        }
    }
    if(intensityAndPoint_v.size() < minimumCandidates)
    {
        std::cerr<<"Not enought candidates to do RASNAC";
    }
/*
///////////////////
const int angleSpread = 100*PI_180;
    angleStep = 50;
    for(const IntensityAndPoint newCenter : intensityAndPoint_v)
    {
	//IntensityAndPoint newCenter = intensityAndPoint_v[0];
        const float angleNormal = atan2(center.y - newCenter.point.y, center.x - newCenter.point.x);
	std::cout<<angleStep<<" "<<newCenter.intensity<<std::endl;
	const float newAngleStep = angleStep*(20/newCenter.intensity); 

	std::cout<<newAngleStep<<std::endl;
        cv::Point2f pixel;
        for(float angle=angleNormal -angleSpread/2 +0.001;angle<angleNormal+ angleSpread/2;angle+=newAngleStep) //)
        {
            const cv::Point2f distance (currentRadius*cos(angle),currentRadius*sin(angle));
            pixel= newCenter.point + distance;// (newCenter.x + distance.x,newCenter.y + distance.y);
            const cv::Scalar colorOfPixel (image.at<uchar>(pixel));
            while(1)
            {
                pixel+=  distance;//cv::Point2f(pixel.x + distance.x,pixel.y + distance.y);
                if(pixel.x >image.cols || pixel.y >image.rows || pixel.x < 0 || pixel.y <0)
                {
                    break;
                }
		const cv::Scalar differenceInColors=static_cast<const cv::Scalar>(image.at<uchar>(pixel)) - colorOfPixel;

                if(differenceInColors[0] > treshold)
                {
                    const cv::Point2f edgePoint = pixel - distance/2;// ( pixel.x - distance.x/2,pixel.y - distance.y/2);
                    debug::drawMarker(draw2,edgePoint,cv::Scalar(255,255,0));
                    debug::drawLine(draw2,newCenter.point,edgePoint,cv::Scalar(200,100,100));
		    intensityAndPoint_v.emplace_back(static_cast<int>(differenceInColors[0]), edgePoint);
                    break;

                }
            }
        }

    }
*/
    imshow("initial",draw);
    imshow("second",draw2);



}
void shotRay(const int degree)
{


}
