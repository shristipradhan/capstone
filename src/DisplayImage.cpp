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
    Ptr<cv::xfeatures2d::SIFT> detector = cv::xfeatures2d::SIFT::create(100,5,0.09, 20, 2.0);
    std::vector<KeyPoint> keypoints_1, keypoints_2;

    detector->detect(a, keypoints_1);
    detector->detect(b, keypoints_2);

    Ptr<cv::xfeatures2d::SiftDescriptorExtractor> extractor = cv::xfeatures2d::SiftDescriptorExtractor::create();

    Mat descriptors_1, descriptors_2;

    extractor->compute( a, keypoints_1, descriptors_1);
    extractor->compute(b, keypoints_2, descriptors_2);

    cv::BFMatcher matcher(NORM_L2);
    std::vector< cv::DMatch > matches;
    matcher.match(descriptors_1, descriptors_2, matches);

    drawMatches(a, keypoints_1, b, keypoints_2, matches, res);
    namedWindow(matchType, WINDOW_AUTOSIZE);
    imshow(matchType, res);

    return 0;
}

int main(int argc, char **argv)
{
    Mat image;
    Mat image1;
    Mat image2;
    Mat res;
    char file[100];
    for(auto i = 2; i<100; i++)
    {
        sprintf( file, "../capstone/resources/hot_dog/images(%d)", i);
        image = imread ( file, IMREAD_GRAYSCALE);
        sprintf( file, "../capstone/resources/seefood/train/hot_dog/image%d.jpg", i);
        image1 = imread ( file, IMREAD_GRAYSCALE);
        sprintf( file, "../capstone/resources/seefood/train/not_hot_dog/image%d.jpg", i);
        image2 = imread ( file, IMREAD_GRAYSCALE);
        if ( !image.data || !image1.data || !image2.data)
        {
            continue;
        }
        matchFeatures(image , image1, res , "Hot Dog" ) ;
        matchFeatures(image , image2, res , "Not Hot Dog") ;
        waitKey(0);
    }

	return 0;
}
#endif
