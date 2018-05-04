#ifndef CONST_HPP
#define CONST_HPP
#include <opencv2/core/core.hpp>
#define PI_180 CV_PI / 180

#define DEBUG
namespace lookup
{
bool arrayBuild = false;
float sinArray[360];// = new float[360];
float cosArray[360];// = new float[360]
void buildArray()
{
        for (int i =0 ; i <360; ++i)
        {
            sinArray[i] = sin(i*PI_180);
            cosArray[i] = cos(i*PI_180);
        }
    arrayBuild = true;
}
}
namespace debug
{
void showImage(const char*name,const cv::Mat &mat)
{
#ifdef DEBUG
    imshow(name,mat);
#endif //DEBUG
}
}
#endif
