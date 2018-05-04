#include "opencv2/opencv.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "time/timer.cpp"
#include "Hough/Hough.cpp"
#include "Hough/HoughCircle.hpp"
#include "Hough/HoughLine.hpp"
using namespace cv;

#define DEBUG
#define GRADIENT
int main(int, char**)
{
    lookup::buildArray();
    Clock clock;
    Hough<HoughCircle> hough;


    cv::Mat gray;
    {

        int bright = 10;

        cvNamedWindow("video");

        cvCreateTrackbar("brightness", "video", &bright, 255, NULL);
        Mat frame = imread("5.jpg",cv::IMREAD_COLOR)	;


        cvtColor(frame, gray, COLOR_BGR2GRAY);
        Mat hough_accum = frame.clone();//(frame.size,frame.type());

        GaussianBlur(gray,gray, Size(9,9), 2, 2);

//        Mat edges, dx, dy;
        const int kernelSize = 5;
        const double start = clock.getTime();//CLOCK();
        const int treshold = 100;
        const int minValue = 30;
        const int maxValue = 100;
        std::vector<cv::Point3f> circles (1000);
#ifndef GRADIENT

        Canny(gray,gray,100,200,kernelSize);

        hough.calculate(gray,minValue,maxValue,treshold,circles);
        for(auto circle : circles)
        {
            cv::circle(hough_accum,cv::Point2f(circle.x,circle.y),circle.z,cv::Scalar(255,0,0),1,2,0);

            cv::circle(hough_accum,cv::Point2f(circle.x,circle.y),1,cv::Scalar(0,255,0),1,2,0);
        }


#endif
#ifndef NO_GRADIENT

        HoughCircle h_circle;
        h_circle.execute2(gray,minValue,maxValue,treshold,circles,kernelSize);
        for(auto circle : circles)
        {
            cv::circle(hough_accum,cv::Point2f(circle.x,circle.y),circle.z,cv::Scalar(255,0,0),1,2,0);

            cv::circle(hough_accum,cv::Point2f(circle.x,circle.y),1,cv::Scalar(0,255,0),1,2,0);


        }
#endif

        //   std::cout<<std::to_string(dur).c_str()<<std::endl;
        imshow("edges", gray);
        imshow("hough_space",hough_accum);

        waitKey(0); //break;
    }
    return 0;
}


