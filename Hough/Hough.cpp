#ifndef HOUGH_HPP
#define HOUGH_HPP
#include <opencv2/core/core.hpp>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
//#include "../precompiled/CompileTimeAngle.hpp"


#include <iostream>
#include <vector>
#include "../Helpers/const.hpp"


template <typename Function>
class Hough
{
private:
    Function * function;
public:
    Hough():function(new Function()) {};

    ~Hough()
    {
        delete function;
    };

    std::vector<cv::Point3f > calculate(cv::Mat &mat,int min,int max,int treshold,std::vector<cv::Point3f> &points) const
    {
        if(!lookup::arrayBuild)
        {
            std::cerr<<"BUILD LOOKUP ARRAY"<<std::endl;
            return std::vector<cv::Point3f>();
        }
        if(max>mat.rows)
        {
            max = std::min(mat.cols ,mat.rows)/2;
        }
        //std::vector<cv::Point3f> points(1000);
        function->execute(mat,min,max,treshold,points);

        return points;

    }

};

#endif
