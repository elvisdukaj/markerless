#include "markerdetectorfilter.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <QDebug>
#include <stdexcept>
using namespace std;

float perimeter(const std::vector<cv::Point2f>& a)
{
  float sum=0, dx, dy;

  for (size_t i=0;i<a.size();i++)
  {
    size_t i2=(i+1) % a.size();

    dx = a[i].x - a[i2].x;
    dy = a[i].y - a[i2].y;

    sum += sqrt(dx*dx + dy*dy);
  }

  return sum;
}

QVideoFilterRunnable* MarkerDetectorFilter::createFilterRunnable()
{
    return new MarkerDetectorFilterRunnable(this);
}

MarkerDetectorFilterRunnable::MarkerDetectorFilterRunnable(MarkerDetectorFilter* filter)
    : m_filter{filter}
{
}

QVideoFrame MarkerDetectorFilterRunnable::run(QVideoFrame* frame, const QVideoSurfaceFormat&, QVideoFilterRunnable::RunFlags)
{
    if (!isFrameValid(frame))
    {
        qDebug() << "Frame is NOT valid";
        return QVideoFrame{};
    }

    if (!frame->map(QAbstractVideoBuffer::ReadWrite))
    {
        qDebug() << "Unable to map the videoframe in memory" << endl;
        return *frame;
    }

    try
    {
        cv::Mat frameMat, grayscale, binarized;
        videoFrameInGrayScaleAndColor(frame, grayscale, frameMat);

        MarksDetector marksDetector{};

        marksDetector.processFame(grayscale);

        cv::flip(grayscale, grayscale, 1);
        cv::threshold(grayscale, binarized, 0, 255.0, cv::THRESH_BINARY | cv::THRESH_OTSU);

        grayscaleToVideoFrame(frame, binarized, frameMat);
    }
    catch(const std::exception& exc)
    {
        qDebug() << exc.what();
    }

    frame->unmap();


    return *frame;
}

MarksDetector::MarksDetector()
{
}

void MarksDetector::processFame(cv::Mat& grayscale)
{
    m_contours.clear();
    m_minCountournSize = grayscale.cols / 5;
    binarize(grayscale);
    findContours();
    findCandidates();
}

void MarksDetector::binarize(cv::Mat &grayscale)
{
    cv::threshold(grayscale, m_binarized, 0, 255.0, cv::THRESH_BINARY | cv::THRESH_OTSU);
}

void MarksDetector::findContours()
{
    cv::findContours(m_binarized, m_contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
    //    filterContours();

    cv::Mat contousImage(m_binarized.size(), CV_8UC3, cv::Scalar{255, 255, 255});
    cv::drawContours(contousImage, m_contours, -1, cv::Scalar{255});
    cv::flip(contousImage, contousImage, 0);
    cv::imshow("Contours", contousImage);
    cv::waitKey(1);
}

std::vector<Marker> MarksDetector::findCandidates()
{
    vector<cv::Point> approxCurve;
    vector<Marker> possibleMarkers;

    // For each contour, analyze if it is a parallelepiped likely to be the marker
    for (size_t i=0; i < m_contours.size(); i++)
    {
        // Approximate to a polygon
        double eps = m_contours[i].size() * 0.05;
        cv::approxPolyDP(m_contours[i], approxCurve, eps, true);

        // We interested only in polygons that contains only four points
        if (approxCurve.size() != 4)
            continue;

        // And they have to be convex
        if (!cv::isContourConvex(approxCurve))
            continue;

        // Ensure that the distance between consecutive points is large enough
        float minDist = std::numeric_limits<float>::max();

        for (int i = 0; i < 4; i++)
        {
            cv::Point side = approxCurve[i] - approxCurve[(i+1)%4];
            float squaredSideLength = side.dot(side);
            minDist = std::min(minDist, squaredSideLength);
        }

        // Check that distance is not very small
        if (minDist < 10000)
            continue;

        qDebug() << "minDist is " << minDist;

        // All tests are passed. Save marker candidate:
        vector<cv::Point2f> markerPoints;
        markerPoints.reserve(4);

        for (int i = 0; i<4; i++)
            markerPoints.push_back( cv::Point2f(approxCurve[i].x,approxCurve[i].y) );

        // Sort the points in anti-clockwise order
        // Trace a line between the first and second point.
        // If the third point is at the right side, then the points are anti-clockwise
        auto v1 = markerPoints[1] - markerPoints[0];
        auto v2 = markerPoints[2] - markerPoints[0];

        double o = (v1.x * v2.y) - (v1.y * v2.x);

        if (o < 0.0)		 // if the third point is in the left side, then sort in anti-clockwise order
            std::swap(markerPoints[1], markerPoints[3]);

        possibleMarkers.emplace_back(m_binarized, markerPoints);
    }

    // calculate the average distance of each corner to the nearest corner of the other marker candidate

    std::vector< std::pair<int,int> > tooNearCandidates;
    for (int i=0;i<possibleMarkers.size();i++)
    {
        const Marker& m1 = possibleMarkers[i];

        //calculate the average distance of each corner to the nearest corner of the other marker candidate
        for (int j=i+1;j<possibleMarkers.size();j++)
        {
            const Marker& m2 = possibleMarkers[j];

            float distSquared = 0;

            for (int c = 0; c < 4; c++)
            {
                auto v = m1.points()[c] - m2.points()[c];
                distSquared += v.dot(v);
            }

            distSquared /= 4;

            if (distSquared < 100)
            {
                tooNearCandidates.push_back(std::pair<int,int>(i,j));
            }
        }
    }

    // Mark for removal the element of the pair with smaller perimeter
    std::vector<bool> removalMask (possibleMarkers.size(), false);

    for (size_t i = 0; i < tooNearCandidates.size(); i++)
    {
        float p1 = perimeter(possibleMarkers[tooNearCandidates[i].first ].points());
        float p2 = perimeter(possibleMarkers[tooNearCandidates[i].second].points());

        size_t removalIndex;
        if (p1 > p2)
            removalIndex = tooNearCandidates[i].second;
        else
            removalIndex = tooNearCandidates[i].first;

        removalMask[removalIndex] = true;
    }

    if (!possibleMarkers.empty())
        qDebug() << "found " << possibleMarkers.size();

    std::vector<Marker> detectedMarkers;
    for (size_t i = 0; i < possibleMarkers.size(); i++)
    {
        if (!removalMask[i])
            detectedMarkers.push_back(possibleMarkers[i]);
    }

    return detectedMarkers;
}

void MarksDetector::filterContours()
{
    qDebug() << "First " << m_contours.size();
    auto toRemove = remove_if(begin(m_contours), end(m_contours),
                              [&](const std::vector<cv::Point>& vec)
    {
        return vec.size() > m_minCountournSize;
    }
    );

    m_contours.erase(toRemove, end(m_contours));
    qDebug() << "After" << m_contours.size();
}

Marker::Marker(const cv::Mat& image, const std::vector<cv::Point2f> &points)
    : m_points{points}
{
    qDebug() << "Possible marker found!!!!" << endl;
}
