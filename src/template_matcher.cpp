#include "../include/template_matcher.hpp"

double TemplateMatcher::distance(cv::Rect a, cv::Rect b)
{
  double dist = std::sqrt(std::pow( a.x - b.x, 2) +
         std::pow (a.y - b.y , 2));
  return dist;
}

cv::Rect TemplateMatcher::getMatchingRectangle(cv::Mat input, cv::Mat filter)
{
  cv::Mat result;

  /// Options for match_method
  /// 0: SQDIFF
  /// 1: SQDIFF NORMED
  /// 2: TM CCORR
  /// 3: TM CCORR NORMED
  /// 4: TM COEFF
  /// 5: TM COEFF NORMED";
  int match_method = 5; //rand()%6;

  /// Create the result matrix
  int result_cols = input.cols;// - filter.cols + 1;
  int result_rows = input.rows;// - filter.rows + 1;
  result.create( result_rows, result_cols, CV_32FC1 );

  /// Do the Matching and Normalize
  cv::matchTemplate( input, filter, result, match_method );
  cv::normalize( result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat() );

  /// Localizing the best match with minMaxLoc
  double minVal; double maxVal; cv::Point minLoc; cv::Point maxLoc;
  cv::Point matchLoc;

  cv::minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat() );

  /// For SQDIFF and SQDIFF_NORMED,
  /// the best matches are lower values.
  /// For all the other methods, the higher the better
  if( match_method  == cv::TM_SQDIFF || match_method == cv::TM_SQDIFF_NORMED )
    { matchLoc = minLoc; }
  else
    { matchLoc = maxLoc; }

  cv::Rect return_rect = cv::Rect(matchLoc.x , matchLoc.y , filter.cols , filter.rows );

  return return_rect;
}
