#pragma once

#include <opencv2/core.hpp>
#include <vector>
#include <array>

struct Pattern {
    cv::Mat image;
    cv::Mat grayscale;
    cv::Mat imageKeyPoints;
    std::vector<cv::KeyPoint> keypoints;
    std::array<cv::Point2f, 4> points;
    cv::Mat descriptor;
};
