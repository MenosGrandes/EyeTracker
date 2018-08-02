#ifndef HOUGHCIRCLETBB_HPP
#define HOUGHCIRCLETBB_HPP
#include <vector>
#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>
#include <tbb/task_scheduler_init.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "../Helpers/const.hpp"
#include <cmath>

class HoughCircleMultiThreadInvoker
{
    private:
        cv::Mat mat;
        int min, max, kernelSize, treshold;
        cv::Point3f* circles;
        cv::Mat* spaces;
        cv::Mat canny, sobelX, sobelY;



    public:

        ~HoughCircleMultiThreadInvoker() {};

        HoughCircleMultiThreadInvoker(const cv::Mat& _mat, const cv::Mat& _canny, const cv::Mat& _sobelX, const cv::Mat& _sobelY, int _min, int _max, int _kernelSize, int _treshold, cv::Point3f* _circles,
                                      cv::Mat* _spaces): mat(_mat), min(_min), max(_max), kernelSize(_kernelSize), treshold(_treshold), circles(_circles), spaces(_spaces), canny(_canny), sobelX(_sobelX), sobelY(_sobelY)
        {}

        void operator()(const tbb::blocked_range<int>& r) const
        {
            for (int i = r.begin(); i != r.end(); i++)
            {
                for (int x = 0; x < mat.rows; ++x)
                {
                    for (int y = 0; y < mat.cols; ++y)
                    {
                        if (!mat.at<uchar>(x, y))
                        {
                            const float gradientX = sobelX.at<const short>(x, y);
                            const float gradientY = sobelY.at<const short>(x, y);

                            if (gradientX == 0 && gradientY == 0)
                            {
                                continue;
                            }

                            const float magnitude = std::sqrt(gradientX * gradientX + gradientY * gradientY);
                            const int angle = (atan2(gradientY, gradientX) * 180 / CV_PI); // + 0.5f;

                            if (magnitude < 1.0f)
                            {
                                continue;
                            }

                            const int a = x - i * lookup::sinArray[angle];//+ 0.5f;
                            const int b = y - i * lookup::cosArray[angle]; //+ 0.5f;

                            if (a >= 0 && a < spaces[i].rows && b >= 0 && b < spaces[i].cols)
                            {
                                spaces[i].at<uchar>(a, b)++;
                            }

                            //Don't know the direction of the gradient so go another side
                            const int a2 = x - i * lookup::sinArray[angle + 180]; //+ 0.5f;
                            const int b2 = y - i * lookup::cosArray[angle + 180]; //+ 0.5f;

                            if (a2 >= 0 && a2 < spaces[i].rows && b2 >= 0 && b2 < spaces[i].cols)
                            {
                                spaces[i].at<uchar>(a2, b2)++;
                            }
                        }
                    }
                }

                double min_f, max_f;
                cv::Point min_loc, max_loc;
                cv::minMaxLoc(spaces[i], &min_f, &max_f, &min_loc, &max_loc);

                if (max_f >= treshold)
                {
                    circles[static_cast<int>(i)] = cv::Point3f(max_loc.x, max_loc.y, i);
                }
            }
        }
};

class HoughCircleTBB
{
    public:

        HoughCircleTBB() {};
        ~HoughCircleTBB() {};

        void execute(cv::Mat& mat, int min, int max, int treshold, std::vector<cv::Point3f>& circles, int kernelSize) const
        {
            const int count = pow((max - min), 3);
            cv::Point3f* circles2 = new cv::Point3f[count];
            cv::Mat* spaces = new cv::Mat[count];

            for (int i = 0; i < count; i++)
            {
                spaces[i] = cv::Mat::zeros(mat.rows, mat.cols, CV_8U);
            }

            cv::Mat sobelX, sobelY;
            Sobel(mat, sobelX, CV_16S, 1, 0, kernelSize, 1, 0, cv::BORDER_REPLICATE);
            Sobel(mat, sobelY, CV_16S, 0, 1, kernelSize, 1, 0, cv::BORDER_REPLICATE);
            cv::Canny(mat, mat, 100, 200, kernelSize, false);
            tbb::parallel_for(tbb::blocked_range<int>(min, max, 1), HoughCircleMultiThreadInvoker(mat, mat, sobelX, sobelY, min, max, kernelSize, treshold, circles2, spaces));

            for (int i = min; i < max; i++)
            {
                circles.emplace_back(circles2[i]);
            }

            delete []circles2;
            delete [] spaces;
        }
};

#endif
