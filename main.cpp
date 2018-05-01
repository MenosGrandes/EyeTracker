#include "opencv2/opencv.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "time/timer.cpp"
#include "Hough/Hough.cpp"
#include "Hough/HoughCircle.hpp"
#include "Hough/HoughLine.hpp"
using namespace cv;

#define DEBUG
int main(int, char**)
{
    lookup::buildArray();
    Clock clock;
    Hough<HoughCircle> hough;

    /*

    VideoCapture cap(0); // open the default camera
        if(!cap.isOpened())  // check if we succeeded
        {
            std::cout<<"NO CAMERA"<<std::endl;
            return -1;
        }
      */
    Mat gray;
    namedWindow("edges",1);

//namedWindow( "Connected Components", 1 );
 //   createTrackbar( "Threshold", "Connected Components", &threshval, 255, on_trackbar );
        //on_trackbar(threshval, 0);


    {

int bright = 10;
   
 cvNamedWindow("video");
    
cvCreateTrackbar("brightness", "video", &bright, 255, NULL);
       Mat frame = imread("3.jpg",cv::IMREAD_COLOR)	;

        cvtColor(frame, gray, COLOR_BGR2GRAY);
        Mat hough_accum = frame.clone();//(frame.size,frame.type());

        GaussianBlur(gray,gray, Size(9,9), 2, 2);

	Mat edges, dx, dy;
	const int kernelSize = 5;
	Sobel(gray, dx, CV_16S, 1, 0, kernelSize, 1, 0, BORDER_REPLICATE);
    	Sobel(gray, dy, CV_16S, 0, 1, kernelSize, 1, 0, BORDER_REPLICATE);
	imshow("SobelX",dx);
	imshow("Sobely",dy);
	//Canny(dx, dy, edges, std::max(1, cannyThreshold / 2), cannyThreshold, false);	
 	Canny(gray,gray,100,200,kernelSize);
        const double start = clock.getTime();//CLOCK();
        const int treshold = 150;
        std::vector<cv::Point3f> circles (1000);
	hough.calculate(gray,0,100,treshold,circles);
        for(auto circle : circles)
        {
            cv::circle(hough_accum,cv::Point2f(circle.x,circle.y),circle.z,cv::Scalar(255,0,0),1,2,0);
        }

        const double dur = clock.getTime()- start;
        
	std::cout<<std::to_string(dur).c_str()<<std::endl;
        imshow("edges", gray);
        imshow("hough_space",hough_accum);
        
	waitKey(0); //break;
    }
    return 0;
}


