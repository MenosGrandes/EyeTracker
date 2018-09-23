#include "opencv2/opencv.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "time/timer.cpp"
#include "Hough/Hough.cpp"
#include "Hough/HoughCircle.hpp"
#include "Hough/HoughLine.hpp"
#include "Hough/HoughCircleTBB.hpp"
#include "Hough/HoughCircleGradient.hpp"
#include <unistd.h>
#include "Starburst/Starburst.cpp"

void runHough()
{
    Clock clock;
    cv::Mat gray;
    {
        int bright = 10;
        cvNamedWindow("video");
        cvCreateTrackbar("brightness", "video", &bright, 255, NULL);
        cv::Mat frame = imread("3.jpg", cv::IMREAD_COLOR)    ;
        cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        cv::Mat hough_accum = frame.clone();//(frame.size,frame.type());
        const int treshold = 1;
        int maxValue = 100;
        int minValue = 35;
        std::vector<cv::Point3f> circles(1000);
        const int kernelSize = 5;
        double start = clock.getTime();//CLOCK();
        Hough<HoughCircleTBB> hough;
        hough.calculate(gray, minValue, maxValue, treshold, circles, kernelSize);
        const double dur = clock.getTime() - start;
        std::cout << std::to_string(dur).c_str() << std::endl;

        //////////////
        for (auto circle : circles)
        {
            cv::circle(hough_accum, cv::Point2f(circle.x, circle.y), circle.z, cv::Scalar(255, 0, 0), 1, 2, 0);
            cv::circle(hough_accum, cv::Point2f(circle.x, circle.y), 1, cv::Scalar(0, 255, 0), 1, 2, 0);
        }

        imshow("hough_space", hough_accum);
        cv::waitKey(0); //break;
    }
}
	





void runStarburst()
{
	const int numberOfImages = 7;
//	for( int i=0;i<numberOfImages;i++)
//	{
		std::stringstream ss;
		ss<<"images/"<<numberOfImages<<".png";
    Starburst starburst;
    cv::Mat image = imread(ss.str(), cv::IMREAD_COLOR);
    cvtColor(image, image, cv::COLOR_BGR2GRAY);
    Clock clock;
    double start = clock.getTime();
    const int rayCount = 20;
    const int treshold = 10;
    const int currentRadius = 6;
    starburst.calculate(image, rayCount, treshold, currentRadius);



    const double dur = clock.getTime() - start;
    std::cout << dur << std::endl;
    //imshow("edges", image);
    cv::waitKey(0); //break;
    ss.str("");
//	}
}


int main()
{
    lookup::buildArray();
    runStarburst();
    //runHough();
    return 0;
}
