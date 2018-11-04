#include <opencv2/core/core.hpp>
#include <iostream>
#include "Helpers/DrawHelpers.hpp"
#include "algo.h"
int main()
{
    cv::Mat image = cv::imread("image/1.png", CV_LOAD_IMAGE_GRAYSCALE);

    if (!image.data)
    {
        std::cout << "Could not open image!" << std::endl;
    }
 
    DrawHelper::instance().drawBoundingBoxFromRotatedRect(ELSE::run(image),image);
    imshow("rectangles", image);
    cv::waitKey(0);
    return 0;
}
