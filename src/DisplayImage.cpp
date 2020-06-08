#include <iostream>
#include <thread>
#include "displayimage.h"

using std::cout;
using std::endl;



int DisplayImage::matchFeatures(const Mat a, const Mat b, Mat res, String matchType)
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
    static const cv::Ptr<cv::flann::SearchParams> search_params = new cv::flann::SearchParams(32, 0.0, false);
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
    return 0;
}

void DisplayImage::readImage(int imageID)
{
    std::lock_guard<std::mutex> lck(_mtx);

    Mat image;
    Mat image_next;
    Mat image1;
    Mat image2;
    Mat res;
    char file[100];

    std::cout << "imageID = " << imageID << std::endl;
    std::cout << "Hello from thread# " << std::this_thread::get_id() << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    sprintf( file, "../capstone/resources/train/images(%d)", imageID);
    image = imread ( file, IMREAD_ANYCOLOR);
    sprintf( file, "../capstone/resources/train/images(%d)", imageID+1);
    image_next = imread ( file, IMREAD_ANYCOLOR);
    sprintf( file, "../capstone/resources/test/soft_test/hot_dog/images(%d)", imageID);
    image1 = imread ( file, IMREAD_ANYCOLOR);
    sprintf( file, "../capstone/resources/test/soft_test/not_hot_dog/images(%d)", imageID);
    image2 = imread ( file, IMREAD_ANYCOLOR);
    if ( !image.data || !image1.data || !image2.data)
    {
        return;
    }
    matchFeatures(image, image_next, res, "Next Hot Dog");
    matchFeatures(image, image1, res, "Hot Dog");
    matchFeatures(image, image2, res, "Not Hot Dog");
}

int main(int argc, char **argv)
{
    std::cout<<"Hello from main thread# " << std::this_thread::get_id() << std::endl;

    //DisplayImage *dispImg = new DisplayImage();
    std::shared_ptr<DisplayImage> di(new DisplayImage);

    std::vector<std::thread> threads;

    for(auto i = 1; i <= 240; i++)
    {
        threads.emplace_back(std::thread(&DisplayImage::readImage, di, i));
    }

    for (auto& t : threads)
    {
        t.join();
    }

	return 0;
}
