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

int matchFeatures(const Mat a, const Mat b, Mat res)
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
    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", res);

    return 0;
}

int main(int argc, char **argv)
{
    Mat image;
    Mat image1;
    Mat res;
    char file[100];
    for(auto i = 2; i<10; i++)
    {
        sprintf( file, "../capstone/resources/seefood/train/hot_dog/image%d.jpg", i);
        image = imread ( file, IMREAD_GRAYSCALE);
        sprintf( file, "../capstone/resources/seefood/train/not_hot_dog/image%d.jpg", i);
        image1 = imread ( file, IMREAD_GRAYSCALE);
        if ( !image.data || !image1.data )
        {
            continue;
        }
         //imshow("Display Image", image);
        //showDescriptors(image1);
        if ( matchFeatures(image , image1, res ) != -1 )
        {
            //namedWindow("Display Image", WINDOW_AUTOSIZE);
            //imshow("Display Image", res);
        }
        waitKey(0);
    }

	return 0;
}
#endif
