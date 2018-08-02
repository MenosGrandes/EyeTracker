#ifndef CONST_HPP
#define CONST_HPP
#include <opencv2/core/core.hpp>
#define PI_180 CV_PI / 180


namespace lookup
{
    bool arrayBuild = false;
    float sinArray[360];// = new float[360];
    float cosArray[360];// = new float[360]
    void buildArray()
    {
        for (int i = 0 ; i < 360; ++i)
        {
            sinArray[i] = sin(i * PI_180);
            cosArray[i] = cos(i * PI_180);
        }

        arrayBuild = true;
    }
}
namespace debug
{
    void showImage(const char* name, const cv::Mat& mat)
    {
#ifdef DEBUG
        imshow(name, mat);
#endif //DEBUG
    }
    void drawMarker(cv::Mat& mat, const cv::Point2f center, const cv::Scalar& color)
    {
#ifdef DEBUG
        cv::drawMarker(mat, center, color, cv::MarkerTypes::MARKER_CROSS, 10, 1, 8);
#endif
    }
    void drawLine(cv::Mat& mat, const cv::Point2f start, const cv::Point2f end, const cv::Scalar& color)
    {
#ifdef DEBUG
        cv::line(mat, start, end, color, 1, cv::LINE_8, 0);
#endif
    }
}
#endif
