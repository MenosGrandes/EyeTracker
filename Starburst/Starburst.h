#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include "../Helpers/const.hpp"
class Starburst
{
public:
    Starburst(cv::Point2f);
    Starburst();
    void sendRay(const int raysCount) const;
    void calculate( cv::Mat&,const int,const int) const;

private:
    cv::Point2f center;
    std::vector<cv::Point2f> contourPoints;


};
