#include "patterndetector.h"

using namespace cv;
using namespace std;

#include <opencv2/xfeatures2d.hpp>
#include <QDebug>

// Draw matches between two images
inline cv::Mat getMatchesImage(cv::Mat query, cv::Mat pattern, const std::vector<cv::KeyPoint>& queryKp, const std::vector<cv::KeyPoint>& trainKp, std::vector<cv::DMatch> matches, int maxMatchesDrawn)
{
    cv::Mat outImg;

    if (matches.size() > maxMatchesDrawn)
    {
        matches.resize(maxMatchesDrawn);
    }

    cv::drawMatches
            (
                query,
                queryKp,
                pattern,
                trainKp,
                matches,
                outImg,
                cv::Scalar(0,200,0,255),
                cv::Scalar::all(-1),
                std::vector<char>(),
                cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS
                );

    return outImg;
}

PatternDetector::PatternDetector()
    : m_detector{ORB::create(1000)}
    , m_extractor{xfeatures2d::FREAK::create(false, false)}
    , m_matcher{BFMatcher::create(NORM_HAMMING, true)}
{
}

Pattern PatternDetector::buildPatternFromImage(const Mat& image)
{
    Pattern pattern;

    pattern.image = image.clone();
    cvtColor(pattern.image, pattern.grayscale, COLOR_BGR2GRAY);
    extractFeatures(pattern.grayscale, pattern.keypoints, pattern.descriptor);

    const float w = static_cast<float>(image.cols);
    const float h = static_cast<float>(image.rows);

    pattern.points  = {
        Point2f{0.0f, 0.0f},
        Point2f{w   , 0.0f},
        Point2f{w   , h   },
        Point2f{0.0f, h   }
    };

    drawKeypoints(pattern.image, pattern.keypoints, pattern.imageKeyPoints);
//    cv::imshow("image", pattern.image);
//    cv::imshow("grayscale", pattern.grayscale);
//    cv::imshow("KeyPoint", pattern.imageKeyPoints);
//    cv::waitKey(1);
    return pattern;
}

void PatternDetector::train(const Pattern& pattern)
{
    m_pattern = pattern;
    m_matches.clear();
    vector<Mat> descriptors(1);
    descriptors[0] = pattern.descriptor.clone();
    m_matcher->add(descriptors);
    m_matcher->train();
}

int PatternDetector::findPattern(const Mat& grayscale, int minNumberMatchesAllowed, bool showMatches)
{
    extractFeatures(grayscale, m_queryKeyPoints, m_queryDescriptor);
    m_matches = getMatches(m_queryDescriptor);

    if (m_matches.empty())
        return false;

    auto foundKeys = refineMatchesWithHomography(
                m_queryKeyPoints,
                m_pattern.keypoints,
                3.0f,
                m_matches,
                m_roughHomography,
                minNumberMatchesAllowed
                );

    if (foundKeys && showMatches)
    {
        Mat image = getMatchesImage(
                    grayscale, m_pattern.image,
                    m_queryKeyPoints,
                    m_pattern.keypoints,
                    m_matches,
                    100);

        imshow("matches", image);
        waitKey(1);
    }

    return foundKeys;
}

bool PatternDetector::extractFeatures(
        const Mat& grayImage,
        vector<KeyPoint>& keypoints,
        Mat& descriptor)
{
    m_detector->detectAndCompute(grayImage, Mat(), keypoints, descriptor);
    return true;

    m_detector->detect(grayImage, keypoints);

    if (keypoints.empty())
        return false;

    m_extractor->compute(grayImage, keypoints, descriptor);

    if (keypoints.empty())
        return false;

    return true;
}

vector<DMatch> PatternDetector::getMatches(const Mat& queryDescriptors)
{
    vector<DMatch> matches;
    m_matcher->match(queryDescriptors, matches);
    return matches;
}

int PatternDetector::refineMatchesWithHomography(
        const std::vector<KeyPoint>& queryKeyPoints,
        const std::vector<KeyPoint>& trainKeyPoints,
        float reprojectionThreshold,
        std::vector<DMatch>& matches,
        Mat& homography,
        int minNumberMatchesAllowed)
{
    qDebug() << "FIRST found " << matches.size() << "keypoints";
    if (matches.size() < minNumberMatchesAllowed)
        return 0;

    vector<Point2f> srcPoints; srcPoints.reserve(matches.size());
    vector<Point2f> dstPoints; dstPoints.reserve(matches.size());

    for(const auto& match : matches)
    {
        srcPoints.push_back(trainKeyPoints[match.trainIdx].pt);
        dstPoints.push_back(queryKeyPoints[match.queryIdx].pt);
    }

    vector<unsigned char> inliersMask(srcPoints.size());

    homography = cv::findHomography(
                srcPoints, dstPoints, CV_FM_RANSAC,
                reprojectionThreshold, inliersMask
                );

    vector<DMatch> inliers;
    inliers.reserve(matches.size());

    for(int i = 0; i < inliersMask.size(); ++i)
        if(inliersMask[i])
            inliers.push_back(matches[i]);

    swap(matches, inliers);

    qDebug() << "AFTER found " << matches.size() << "keypoints";

    return matches.size() > minNumberMatchesAllowed ? matches.size() : 0;
}
