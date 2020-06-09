#include <opencv2/imgproc/imgproc.hpp>

class TemplateMatcher{
  public:
    double distance(cv::Rect a, cv::Rect b);

    cv::Rect getMatchingROI(cv::Mat input, cv::Mat filter);
};
