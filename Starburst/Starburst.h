#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include "../Helpers/const.hpp"


struct IntensityAndPoint
{
    const float intensity;
    const cv::Point2f point;
    IntensityAndPoint(const float _intensity, const cv::Point2f _point): intensity(_intensity), point(_point) {};
};
class Starburst
{
    public:
        Starburst(cv::Point2f);
        Starburst();
        void sendRay(const int raysCount) const;
        void calculate(const cv::Mat&, const int, const int, const int) const;

    private:
        cv::Point2f center;
        std::vector<cv::Point2f> contourPoints;


};
