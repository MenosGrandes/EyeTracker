#include "opencv2/opencv.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "time/timer.cpp"
#include "Hough/houghCircular.hpp"
using namespace cv;


int main(int, char**)
{

    Clock clock;
    Hough<int> hough;

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




    //for(;;)
    {

        Mat frame = imread("1.jpg",cv::IMREAD_COLOR)	;
//	Mat frame;
// cap >> frame; // get a new frame from camera

        cvtColor(frame, gray, COLOR_BGR2GRAY);
        Mat hough_accum = frame.clone();//(frame.size,frame.type());

        GaussianBlur(gray,gray, Size(9,9), 0, 0);
        Canny(gray,gray,100,150,3);
        const double start = clock.getTime();//CLOCK();
        const int treshold = 20;
        const std::vector<cv::Point3f> circles = hough.calculate(gray,40,100,treshold);
        for(auto circle : circles)
        {
            cv::circle(hough_accum,cv::Point2f(circle.x,circle.y),circle.z,cv::Scalar(255,0,0),1,2,0);
        }

        const double dur = clock.getTime()- start;
        //putText(gray,std::to_string(dur).c_str(),cv::Point(100,100),cv::FONT_HERSHEY_PLAIN,2,cv::Scalar(0,0,0,255));
        std::cout<<std::to_string(dur).c_str()<<std::endl;
        imshow("edges", gray);
        imshow("hough_space",hough_accum);
        waitKey(0); //break;
    }
    return 0;
}


