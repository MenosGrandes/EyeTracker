#include "opencv2/opencv.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "time/timer.cpp"
#include "Hough/Hough.cpp"
#include "Hough/HoughCircle.hpp"
#include "Hough/HoughLine.hpp"
using namespace cv;
Mat src, dst;

int morph_elem = 0;
int morph_size = 0;
int morph_operator = 0;
int const max_operator = 4;
int const max_elem = 2;
int const max_kernel_size = 21;
char* window_name = "Morphology Transformations Demo";

void Morphology_Operations( int, void* )
{
  // Since MORPH_X : 2,3,4,5 and 6
  int operation = morph_operator + 2;

  Mat element = getStructuringElement( morph_elem, Size( 2*morph_size + 1, 2*morph_size+1 ), Point( morph_size, morph_size ) );

  /// Apply the specified morphology operation
  morphologyEx( src, dst, operation, element );
  imshow( window_name, dst );
  }


int done()
{

/// Load an image

 /// Create window
 namedWindow( window_name, CV_WINDOW_AUTOSIZE );

 /// Create Trackbar to select Morphology operation
 createTrackbar("Operator:\n 0: Opening - 1: Closing \n 2: Gradient - 3: Top Hat \n 4: Black Hat", window_name, &morph_operator, max_operator, Morphology_Operations );

 /// Create Trackbar to select kernel type
 createTrackbar( "Element:\n 0: Rect - 1: Cross - 2: Ellipse", window_name,
                 &morph_elem, max_elem,
                 Morphology_Operations );

 /// Create Trackbar to choose kernel size
 createTrackbar( "Kernel size:\n 2n +1", window_name,
                 &morph_size, max_kernel_size,
                 Morphology_Operations );

 /// Default start
 Morphology_Operations( 0, 0 );

 waitKey(0);
 return 0;
}


	
#define DEBUG
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
        Mat frame = imread("3.jpg",cv::IMREAD_COLOR)	;

        cvtColor(frame, src, COLOR_BGR2GRAY);
        Mat hough_accum = frame.clone();//(frame.size,frame.type());

        GaussianBlur(src,src, Size(9,9), 2, 2);

        Mat edges, dx, dy;
        const int kernelSize = 5;
        const double start = clock.getTime();//CLOCK();
        const int treshold = 10;
        std::vector<cv::Point3f> circles (1000);
        
       Canny(src,src,100,200,kernelSize);
done();	
	
	 //hough.calculate(gray,30,40,treshold,circles);
        for(auto circle : circles)
        {
          cv::circle(hough_accum,cv::Point2f(circle.x,circle.y),circle.z,cv::Scalar(255,0,0),1,2,0);

          cv::circle(hough_accum,cv::Point2f(circle.x,circle.y),1,cv::Scalar(0,255,0),1,2,0);
       	}

/*


	HoughCircle h_circle;
        h_circle.execute2(gray,30,50,treshold,circles,kernelSize);
        for(auto circle : circles)
         {
            cv::circle(hough_accum,cv::Point2f(circle.x,circle.y),circle.z,cv::Scalar(255,0,0),1,2,0);
        
          cv::circle(hough_accum,cv::Point2f(circle.x,circle.y),1,cv::Scalar(0,255,0),1,2,0);
	
	
	 }
*/

     //   std::cout<<std::to_string(dur).c_str()<<std::endl;
        imshow("edges", gray);
        imshow("hough_space",hough_accum);

        waitKey(0); //break;
    }
    return 0;
}


