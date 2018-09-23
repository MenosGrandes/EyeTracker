#include "Starburst.h"
#include <stdlib.h>


Starburst::Starburst(cv::Point2f _center): center(_center) {};
Starburst::Starburst() {};



void Starburst::calculate(const cv::Mat& image, const int rayCount, const int treshold, const int currentRadius) const
{
#ifdef DEBUG
    cv::Mat debugDraw = image.clone();
    cvtColor(debugDraw, debugDraw, cv::COLOR_GRAY2BGR);
    cv::Mat debugDraw2 = image.clone();
    cvtColor(debugDraw2, debugDraw2, cv::COLOR_GRAY2BGR);
#endif
    cv::Point2f center(image.cols / 2, image.rows / 2);
    std::vector<IntensityAndPoint> intensityAndPoint_v;
    intensityAndPoint_v.reserve(1000);
    float angleStep = (360 / rayCount) * PI_180;
#ifdef DEBUG
    cv::circle(debugDraw, center, 5, cv::Scalar(10, 255, 0));
#endif
    const int minimumCandidates = 5;
    ////////////////////////////////
    cv::Point2f pixel;

    int colorOfPixel1,colorOfPixel2;
    for (float angle = 0; angle < 2 * CV_PI; angle += angleStep)
    {
        const cv::Point2f distance(currentRadius * cos(angle), currentRadius * sin(angle));
        pixel = center + distance; // (center.x + distance.x,center.y + distance.y); //p.x p.y
        colorOfPixel1 = image.at<uchar>(pixel); // pixel_value1
        while (1)
        {
            pixel += distance; // 129 - 130

	    if (pixel.x >= image.cols || pixel.y >= image.rows || pixel.x < 0 || pixel.y < 0)
            {
                break;
            }
		

           colorOfPixel2= image.at<uchar>(pixel);
	    if (colorOfPixel2 - colorOfPixel1   > treshold && colorOfPixel2 < 100)
            {
                const cv::Point2f edgePoint = pixel - distance / 2; // ( pixel.x - distance.x/2,pixel.y - distance.y/2);
#ifdef DEBUG
                debug::drawMarker(debugDraw, edgePoint, cv::Scalar(255, 255, 0));
                debug::drawLine(debugDraw, center, edgePoint, cv::Scalar(200, 100, 100));
#endif
                intensityAndPoint_v.emplace_back(colorOfPixel2 - colorOfPixel1 , edgePoint);
                break;
            }
	    colorOfPixel1 = colorOfPixel2;
        }
    }

    if (intensityAndPoint_v.size() < minimumCandidates)
    {
        std::cerr << "Not enought candidates to do RASNAC";
    }

    ///////////////////
    const int angleSpread = 100 * PI_180;
    angleStep = 50 * PI_180;

    for (const IntensityAndPoint newCenter : intensityAndPoint_v)
    {
        const float angleNormal = atan2(center.y - newCenter.point.y, center.x - newCenter.point.x);
        const float newAngleStep = angleStep * (2 / newCenter.intensity);
        cv::Point2f pixel;

        for (double angle = angleNormal - angleSpread / 2 + 0.00001; angle < angleNormal + angleSpread; angle += newAngleStep)
        {
            const cv::Point2f distance(currentRadius * cos(angle), currentRadius * sin(angle));
            pixel = newCenter.point + distance; // (center.x + distance.x,center.y + distance.y);
            colorOfPixel1 = image.at<uchar>(pixel);
            while (1)
            {
                pixel += distance; //cv::Point2f(pixel.x + distance.x,pixel.y + distance.y);

                if (pixel.x > image.cols || pixel.y > image.rows || pixel.x < 0 || pixel.y < 0)
                {
                    break;
                }
   		colorOfPixel2 = image.at<uchar>(pixel);

                if (colorOfPixel2 - colorOfPixel1  > treshold && colorOfPixel2 <100 )
                {
                    const cv::Point2f edgePoint = pixel - distance / 2; // ( pixel.x - distance.x/2,pixel.y - distance.y/2);
#ifdef DEBUG
                    debug::drawMarker(debugDraw2, edgePoint, cv::Scalar(255, 255, 0));
                    debug::drawLine(debugDraw2, newCenter.point, edgePoint, cv::Scalar(200, 100, 100));
#endif
                    intensityAndPoint_v.emplace_back(colorOfPixel2 - colorOfPixel1, edgePoint);
                    break;
                }
		colorOfPixel1 = colorOfPixel2;
            }
        }
    }

#ifdef DEBUG
    imshow("initial", debugDraw);
    imshow("second", debugDraw2);
#endif


   

//fit_ellipse(intensityAndPoint_v


}
