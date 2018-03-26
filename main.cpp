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
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
    {
        std::cout<<"NO CAMERA"<<std::endl;
        return -1;
    }
    Mat gray;
    namedWindow("edges",1);
   for(;;)
    {

        const double start = clock.getTime();//CLOCK();
     //   Mat frame = imread("2.jpg",cv::IMREAD_COLOR)	;
	Mat frame;      
  cap >> frame; // get a new frame from camera
       
	 cvtColor(frame, gray, COLOR_BGR2GRAY);
        GaussianBlur(gray,gray, Size(9,9), 0, 0);
        Canny(gray,gray,100,150,3);
   //     std::vector<Vec3f> circles;
/*        HoughCircles(gray,circles,HOUGH_GRADIENT,2,gray.rows/4,200,100);
        for( size_t i = 0; i < circles.size(); i++ )
        {
            Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);
// draw the circle center
            circle( frame, center, 3, Scalar(0,255,0), -1, 8, 0 );
// draw the circle outline
            circle( frame, center, radius, Scalar(0,0,255), 3, 8, 0 );
*/
        

	hough.calculate(gray,1,3);
        const double dur = clock.getTime()- start;
        putText(gray,std::to_string(dur).c_str(),cv::Point(100,100),cv::FONT_HERSHEY_PLAIN,2,cv::Scalar(0,0,255,255));
        //Canny(edges, edges, 0, 30, 3);
        imshow("edges", gray);
        waitKey(0); //break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}


