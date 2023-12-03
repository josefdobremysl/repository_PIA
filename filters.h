#ifndef FILTERS_H
#define FILTERS_H

#include <opencv2/opencv.hpp>

cv::Mat applySepiaFilter(const cv::Mat& inputImage);
cv::Mat applyInvertFilter(const cv::Mat& inputImage);
cv::Mat applyDetailEnhancement(const cv::Mat& inputImage);
cv::Mat applyOliveColorFilter(const cv::Mat& inputImage);




#endif  // FILTERS_H

