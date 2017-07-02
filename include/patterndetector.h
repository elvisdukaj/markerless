#pragma once

#include "pattern.h"
#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>

class PatternDetector {
public:
    PatternDetector();

    void buildPatternFromImage(const cv::Mat& image);
    int findPattern(const cv::Mat& grayscale, int minNumberMatchesAllowed, bool showMatches);
    const std::vector<cv::Point2f> points() const noexcept { return m_points; }

private:
    void extractFeatures(const cv::Mat& grayImage,
                         std::vector<cv::KeyPoint>& keypoints,
                         cv::Mat& descriptor);

    void getMatches(std::vector<cv::DMatch>& matches );
    void filterMatches(int minNumberMatchesAllowed);

private:
    cv::Ptr<cv::FeatureDetector> m_detector;
    cv::Ptr<cv::DescriptorExtractor> m_extractor;
    cv::Ptr<cv::DescriptorMatcher> m_matcher;

    Pattern m_pattern;
    std::vector<cv::Point2f> m_points;

    std::vector<cv::KeyPoint> m_queryKeyPoints;
    cv::Mat m_queryDescriptor;
    std::vector<cv::DMatch> m_matches;

    cv::Mat m_roughHomography;
};

