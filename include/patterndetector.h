#pragma once

#include "pattern.h"
#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>

class PatternDetector {
public:
    PatternDetector();

    Pattern buildPatternFromImage(const cv::Mat& image);
    void train(const Pattern& pattern);
    int findPattern(const cv::Mat& grayscale, int minNumberMatchesAllowed, bool showMatches);

private:
    bool extractFeatures(const cv::Mat& grayImage,
                         std::vector<cv::KeyPoint>& keypoints,
                         cv::Mat& descriptor);

    std::vector<cv::DMatch> getMatches(const cv::Mat& queryDescriptors);

    int refineMatchesWithHomography(
            const std::vector<cv::KeyPoint>& queryKeyPoints,
            const std::vector<cv::KeyPoint>& trainKeyPoints,
            float reprojectionThreshold,
            std::vector<cv::DMatch>& matches,
            cv::Mat& homography,
            int minNumberMatchesAllowed
            );

private:
    cv::Ptr<cv::FeatureDetector> m_detector;
    cv::Ptr<cv::DescriptorExtractor> m_extractor;
    cv::Ptr<cv::DescriptorMatcher> m_matcher;

    Pattern m_pattern;

    std::vector<cv::KeyPoint> m_queryKeyPoints;
    cv::Mat m_queryDescriptor;
    std::vector<cv::DMatch> m_matches;

    cv::Mat m_roughHomography;
};

