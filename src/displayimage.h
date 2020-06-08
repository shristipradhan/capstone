#ifndef DISPLAYIMAGE_H
#define DISPLAYIMAGE_H


#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
using namespace cv;
using namespace cv::xfeatures2d;

class DisplayImage{
    public:
        void readImage(int imageID);
        int matchFeatures(const Mat a, const Mat b, Mat res, String matchType);
    private:
        std::mutex _mtx;
};

#endif // DISPLAYIMAGE_H
