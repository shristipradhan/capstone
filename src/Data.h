#ifndef DATA_H
#define DATA_H

#include <vector>
#include <opencv2/core.hpp>

class Data
{
    public:
        Data();
        ~Data();

    private:
        int image;
        std::vector<cv::KeyPoint> keypoints;
        float _hotdog_prob;
        float _nothotdog_prob;
};
#endif