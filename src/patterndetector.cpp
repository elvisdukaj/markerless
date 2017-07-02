#include "patterndetector.h"

using namespace cv;
using namespace std;

#include <opencv2/xfeatures2d.hpp>
#include <QDebug>

PatternDetector::PatternDetector()
    : m_detector{xfeatures2d::SurfFeatureDetector::create(400)}
    , m_extractor{xfeatures2d::SurfDescriptorExtractor::create(400)}
    , m_matcher{FlannBasedMatcher::create()}
{
}

void PatternDetector::buildPatternFromImage(const Mat& image)
{
    m_pattern.image = image.clone();
    cvtColor(m_pattern.image, m_pattern.grayscale, COLOR_BGR2GRAY);
    extractFeatures(m_pattern.grayscale, m_pattern.keypoints, m_pattern.descriptor);

    const float w = static_cast<float>(image.cols);
    const float h = static_cast<float>(image.rows);

    m_pattern.points  = {
        Point2f{0.0f, 0.0f},
        Point2f{w   , 0.0f},
        Point2f{w   , h   },
        Point2f{0.0f, h   }
    };

    drawKeypoints(m_pattern.image, m_pattern.keypoints, m_pattern.imageKeyPoints);
}

int PatternDetector::findPattern(const Mat& grayscale, int minNumberMatchesAllowed, bool showMatches)
{
    extractFeatures(grayscale, m_queryKeyPoints, m_queryDescriptor);
    if (m_queryKeyPoints.empty()) return 0;

    getMatches(m_matches);
    if (m_matches.empty()) return 0;

    filterMatches(minNumberMatchesAllowed);
    if (m_matches.empty()) return 0;

    auto foundKeys = m_matches.size();

    Mat img_matches;
    if (showMatches)
    {
        drawMatches(m_pattern.grayscale, m_pattern.keypoints,
                    grayscale, m_queryKeyPoints,
                    m_matches, img_matches,
                    Scalar::all(-1), Scalar::all(-1),
                    vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    }

    //-- Localize the object
    std::vector<Point2f> obj;
    std::vector<Point2f> scene;

    for( int i = 0; i < m_matches.size(); i++ )
    {
        //-- Get the keypoints from the good matches
        obj.push_back( m_pattern.keypoints[m_matches[i].queryIdx ].pt );
        scene.push_back( m_queryKeyPoints[ m_matches[i].trainIdx ].pt );
    }

    Mat H = findHomography(obj, scene, CV_RANSAC);

    auto img_object = m_pattern.grayscale;

    std::vector<Point2f> obj_corners(4);
    obj_corners[0] = Point2f(0.0f);
    obj_corners[1] = Point2f( img_object.cols, 0.0f );
    obj_corners[2] = Point2f( img_object.cols, img_object.rows );
    obj_corners[3] = Point2f( 0.0f, img_object.rows );

    if (!H.data) return 0;

    perspectiveTransform(obj_corners, m_points, H);

    if (showMatches)
    {
        imshow( "Good Matches & Object detection", img_matches );
        cv::waitKey(1);
    }

    return static_cast<int>(foundKeys);
}

void PatternDetector::extractFeatures(
        const Mat& grayImage,
        vector<KeyPoint>& keypoints,
        Mat& descriptor)
{
    m_detector->detect(grayImage, keypoints);
    m_extractor->compute(grayImage, keypoints, descriptor);
}

void PatternDetector::getMatches(std::vector<DMatch>& matches)
{
    matches.clear();
    m_matcher->match(m_pattern.descriptor, m_queryDescriptor, matches);
}

void PatternDetector::filterMatches(int minNumberMatchesAllowed)
{
    double max_dist = 0; double min_dist = 100;

    for( int i = 0; i < m_pattern.descriptor.rows; i++ )
    {
        double dist = m_matches[i].distance;
        if( dist < min_dist ) min_dist = dist;
        if( dist > max_dist ) max_dist = dist;
    }

    std::vector< DMatch > good_matches;

    for( int i = 0; i < m_pattern.descriptor.rows; i++ )
        if( m_matches[i].distance <= 0.1)
            good_matches.push_back(m_matches[i]);

    swap(m_matches, good_matches);

    if (m_matches.size() < minNumberMatchesAllowed)
        m_matches.clear();
}
