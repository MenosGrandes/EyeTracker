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
using namespace cv;

#include "Starburst/Starburst.cpp"
//#define GRADIENT_TBB
#define GRADIENT

using namespace cv;

void runHough()
{
    Clock clock;


    cv::Mat gray;
    {

        int bright = 10;

        cvNamedWindow("video");

        cvCreateTrackbar("brightness", "video", &bright, 255, NULL);
        Mat frame = imread("3.jpg",cv::IMREAD_COLOR)	;


        cvtColor(frame, gray, COLOR_BGR2GRAY);
        Mat hough_accum = frame.clone();//(frame.size,frame.type());

        GaussianBlur(gray,gray, Size(9,9), 2, 2);
	cv::Sobel(gray,gray,CV_16S,1,0);	
        const int treshold = 1;
        int maxValue = 40;
        std::vector<cv::Point3f> circles (1000);
     

const int kernelSize = 5;
const int cannyThreshold = 200;
	cv::Mat dx,dy;
//	cv::Sobel(gray, dx, CV_16S, 1, 0, kernelSize, 1, 0, BORDER_REPLICATE);

//	cv::Sobel(gray, dy, CV_16S, 0, 1, kernelSize, 1, 0, BORDER_REPLICATE);

//	cv::Canny(dx, dy, gray, std::max(1, cannyThreshold / 2), cannyThreshold, false);
	imshow("canny",gray);	
//	hough.calculate(gray,30,45,treshold,circles,dy,dx);


double start = clock.getTime();//CLOCK();
#ifdef GRADIENT_TBB
        Hough<HoughCircleTBB> hough;
        hough.calculate(gray,minValue,maxValue,treshold,circles,kernelSize);
#endif
#ifdef HOUGH_OPENCV
        /// Apply the Hough Transform to find the circles
        cv::HoughCircles( gray, circles, CV_HOUGH_GRADIENT, 1, gray.rows/8, 200,60, 0, 200 );

        /// Draw the circles detected
        for( size_t i = 0; i < circles.size(); i++ )
        {
            Point center((circles[i].x), (circles[i].y));
            int radius = (circles[i].z);
            // circle center
            circle( hough_accum, center, 3, Scalar(0,255,0), -1, 8, 0 );
            // circle outline
            circle( hough_accum, center, radius, Scalar(0,0,255), 3, 8, 0 );
        }
#endif
        const double dur = clock.getTime()- start;
        std::cout<<std::to_string(dur).c_str()<<std::endl;
//////////////
        for(auto circle : circles)
        {
            cv::circle(hough_accum,cv::Point2f(circle.x,circle.y),circle.z,cv::Scalar(255,0,0),1,2,0);
            cv::circle(hough_accum,cv::Point2f(circle.x,circle.y),1,cv::Scalar(0,255,0),1,2,0);
        }
        imshow("edges", gray);
        imshow("hough_space",hough_accum);
        waitKey(0); //break;
    }
}






void runStarburst(){
Starburst starburst;

cv::Mat image = imread("3.jpg",cv::IMREAD_COLOR);
cvtColor(image,image,COLOR_BGR2GRAY);
starburst.calculate(image,20,55);


        imshow("edges", image);
        waitKey(0); //break;
 


}
int main()
{
runStarburst();
runHough();



return 0;
}
