#include "filters.h"

cv::Mat applySepiaFilter(const cv::Mat& inputImage) {
    cv::Mat resultImage = inputImage.clone();
    for (int y = 0; y < resultImage.rows; ++y) {
        for (int x = 0; x < resultImage.cols; ++x) {
            cv::Vec3b& pixel = resultImage.at<cv::Vec3b>(y, x);
            pixel[0] = cv::saturate_cast<uchar>(0.393 * pixel[2] + 0.769 * pixel[1] + 0.189 * pixel[0]);
            pixel[1] = cv::saturate_cast<uchar>(0.349 * pixel[2] + 0.686 * pixel[1] + 0.168 * pixel[0]);
            pixel[2] = cv::saturate_cast<uchar>(0.272 * pixel[2] + 0.534 * pixel[1] + 0.131 * pixel[0]);
        }
    }
    return resultImage;
}

cv::Mat applyInvertFilter(const cv::Mat& inputImage) {
    cv::Mat resultImage;
    cv::bitwise_not(inputImage, resultImage);
    return resultImage;
}

cv::Mat applyDetailEnhancement(const cv::Mat& inputImage) {
    cv::Mat resultImage;
    cv::bilateralFilter(inputImage, resultImage, 9, 75, 75);
    return resultImage;
}

cv::Mat applyOliveColorFilter(const cv::Mat& inputImage) {
    cv::Mat resultImage = inputImage.clone();
    resultImage += cv::Scalar(20, 60, 0);
    cv::multiply(resultImage, 1.2, resultImage);
    return resultImage;
}
