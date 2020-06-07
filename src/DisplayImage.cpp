#include <iostream>
#include "opencv2/core.hpp"
#ifdef HAVE_OPENCV_XFEATURES2D
#include "opencv2/highgui.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
using namespace cv;
using namespace cv::xfeatures2d;
using std::cout;
using std::endl;

int matchFeatures(const Mat a, const Mat b, Mat res, String matchType)
{
    if ( !a.data || !b.data)
    {
        return -1;
    }
    Ptr<cv::xfeatures2d::SIFT> detector = cv::xfeatures2d::SIFT::create(50,5,0.04, 5, 2.0);
    std::vector<KeyPoint> keypoints_1, keypoints_2;

    detector->detect(a, keypoints_1);
    detector->detect(b, keypoints_2);

    Ptr<cv::xfeatures2d::SiftDescriptorExtractor> extractor = cv::xfeatures2d::SiftDescriptorExtractor::create();

    Mat descriptors_1, descriptors_2;

    extractor->compute(a, keypoints_1, descriptors_1);
    extractor->compute(b, keypoints_2, descriptors_2);

    static const cv::Ptr<cv::flann::IndexParams> index_params = new cv::flann::KDTreeIndexParams(16);
    static const cv::Ptr<cv::flann::SearchParams> search_params = new cv::flann::SearchParams(32, 1.0, false);
    //static const cv::Ptr<cv::flann::IndexParams> index_params = new cv::flann::KDTreeIndexParams(4);
    //static const cv::Ptr<cv::flann::SearchParams> search_params = new cv::flann::SearchParams(32, 1.0, true);
    cv::FlannBasedMatcher matcher(index_params, search_params);
    //cv::FlannBasedMatcher matcher = cv::FlannBasedMatcher(cv::makePtr<cv::flann::LshIndexParams>(12, 20, 2));
    //cv::FlannBasedMatcher matcher;

    //cv::FlannBasedMatcher matcher(NORM_L2);
    std::vector< std::vector < cv::DMatch > > raw_matches;
    matcher.knnMatch(descriptors_1, descriptors_2, raw_matches, 1);

    drawMatches(a, keypoints_1, b, keypoints_2, raw_matches, res);
    namedWindow(matchType, WINDOW_AUTOSIZE);
    imshow(matchType, res);
    //cout<<"Match Percentage" << raw_matches.

    return 0;
}

int main(int argc, char **argv)
{
    Mat image;
    Mat image_next;
    Mat image1;
    Mat image2;
    Mat res;
    char file[100];
    for(auto i = 2; i<100; i++)
    {
        sprintf( file, "../capstone/resources/train/images(%d)", i);
        image = imread ( file, IMREAD_ANYCOLOR);
        sprintf( file, "../capstone/resources/train/images(%d)", i+1);
        image_next = imread ( file, IMREAD_ANYCOLOR);
        sprintf( file, "../capstone/resources/test/hot_dog/images(%d)", i);
        image1 = imread ( file, IMREAD_ANYCOLOR);
        sprintf( file, "../capstone/resources/test/not_hot_dog/images(%d)", i);
        image2 = imread ( file, IMREAD_ANYCOLOR);
        if ( !image.data || !image1.data || !image2.data)
        {
            continue;
        }
        matchFeatures(image , image_next, res , "Next Hot Dog" ) ;
        matchFeatures(image , image1, res , "Hot Dog" ) ;
        matchFeatures(image , image2, res , "Not Hot Dog") ;
        waitKey(0);
    }

	return 0;
}
#endif
