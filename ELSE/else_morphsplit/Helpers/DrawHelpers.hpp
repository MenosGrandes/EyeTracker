#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>
class DrawHelper
{
    private:
        DrawHelper() {};
    public :
        DrawHelper(DrawHelper const&) = delete;
        void operator=(DrawHelper const&) = delete;
        static DrawHelper& instance()
        {
            static DrawHelper helper;
            return helper;
        }
        void drawBoundingBoxFromRotatedRect(const cv::RotatedRect& rect, cv::Mat& image)
        {
            cv::Point2f vertices[4];
            rect.points(vertices);

            for (int i = 0; i < 4; i++)
            {
                cv::line(image, vertices[i], vertices[(i + 1) % 4], cv::Scalar(0, 255, 0), 2);
            }

            cv::Rect brect = rect.boundingRect();
            cv::rectangle(image, brect, cv::Scalar(255, 0, 0), 2);
        }
};
