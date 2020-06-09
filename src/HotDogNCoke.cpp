#include <iostream>
#include "opencv2/core.hpp"
#ifdef HAVE_OPENCV_XFEATURES2D
#include "opencv2/highgui.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/imgproc.hpp"

#include "../include/template_matcher.hpp"

using namespace cv;
using namespace cv::xfeatures2d;
using std::cout;
using std::endl;

#define COMPUTE_SIZE 300
#define TEMPLATE_SIZE 10

void MouseCallBack(int event, int x, int y, int flags, void* userdata)
{
     if  ( event == EVENT_LBUTTONDOWN )
     {
          cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
     }
     else if  ( event == EVENT_RBUTTONDOWN )
     {
          cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
     }
     else if  ( event == EVENT_MBUTTONDOWN )
     {
          cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
     }
     else if ( event == EVENT_MOUSEMOVE )
     {
          cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;

     }
}

int matchFeatures(const std::vector<cv::Mat> a, const std::vector<cv::Mat> b, cv::Mat test, String matchType)
{
    TemplateMatcher hotdogMatcher;
    Mat a_small, b_small;
    Mat res;
    cv::Ptr<cv::xfeatures2d::SIFT> detector = cv::xfeatures2d::SIFT::create(50,3,0.04, 10, 0.5);
    std::vector<KeyPoint> keypoints_1, keypoints_2;
    Mat descriptors_1, descriptors_2;
    cv::Ptr<cv::xfeatures2d::SiftDescriptorExtractor> extractor = cv::xfeatures2d::SiftDescriptorExtractor::create();
    static const cv::Ptr<cv::flann::IndexParams> index_params = new cv::flann::KDTreeIndexParams(16);
    static const cv::Ptr<cv::flann::SearchParams> search_params = new cv::flann::SearchParams(32, 0.0, false);
    cv::FlannBasedMatcher matcher(index_params, search_params);
    std::vector< std::vector < cv::DMatch > > raw_matches;

    if(a.size() > 0)
    {
      for(const auto& template_it : a)
      {
        if(template_it.data)
        {
            cv::Rect coke_roi = hotdogMatcher.getMatchingROI(test, template_it);
            cv::rectangle(test, coke_roi, CV_RGB(0,255,0),4);
        }
      }
    }
    if (b.size() > 0)
      for(const auto& template_it : b)
      {
          if(!template_it.data)
              continue;

        cv::Rect hotdog_roi = hotdogMatcher.getMatchingROI(test, template_it);
        cv::rectangle(test, hotdog_roi, CV_RGB(0,0,255),4);
      }
    namedWindow(matchType+"Features", WINDOW_AUTOSIZE);
    setMouseCallback(matchType+"Features", MouseCallBack, NULL);
    imshow(matchType+"Features", test);


    return 0;
}

int main(int argc, char **argv)
{
    Mat a, b;
    Mat a_small, b_small;
    std::vector<cv::Mat> template_hotdog;
    std::vector<cv::Mat> template_coke;

    cv::Mat test_hotdog;
    cv::Mat test_coke;
    char file[50];

    for(int i = 0; i<100; i++)
    {
        sprintf( file, "../capstone/resources/train/coke/images(%d)", i);
        a = imread ( file, IMREAD_COLOR);
        if (!a.data) continue;
        cv::resize(a,a_small,Size(TEMPLATE_SIZE,TEMPLATE_SIZE));
        template_coke.push_back(a_small);
        sprintf( file, "../capstone/resources/train/hotdog/images(%d)", i);
        b = imread ( file, IMREAD_COLOR);
        cv::resize(b,b_small,Size(TEMPLATE_SIZE,TEMPLATE_SIZE));
        template_hotdog.push_back(b_small);
    }

    b_small.data ={0};
    a_small.data ={0};
    for(auto i = 0; i<20; i++)
    {
        sprintf( file, "../capstone/resources/train/hotdog/images(%d)", rand()%100);
        a = imread ( file, IMREAD_COLOR);
        if (!a.data) continue;
        cv::resize(a,a_small,Size(COMPUTE_SIZE,COMPUTE_SIZE));
        a_small.copyTo(test_hotdog);

        sprintf( file, "../capstone/resources/train/coke/images(%d)", rand()%100);
        a = imread ( file, IMREAD_COLOR);
        if (!a.data) continue;
        cv::resize(a,a_small,Size(COMPUTE_SIZE,COMPUTE_SIZE));
        a_small.copyTo(test_coke);

        matchFeatures(template_hotdog, template_coke, test_coke, "Green Coke " ) ;
        matchFeatures(template_hotdog, template_coke, test_hotdog, "Blue Hotdog " ) ;

        waitKey(0);
    }

	return 0;
}
#endif
