#include "patterndetectorfilter.h"
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <QDebug>
#include <bitset>
#include <stdexcept>
#include <string>
#include <algorithm>

using namespace std;

QVideoFilterRunnable* PatternDetectorFilter::createFilterRunnable()
{
    return new PatternDetectorFilterRunnable(this);
}

PatternDetectorFilterRunnable::PatternDetectorFilterRunnable(PatternDetectorFilter* filter)
    : m_filter{filter}
{
    m_patternImage = cv::imread("pattern.bmp", CV_LOAD_IMAGE_COLOR);
    m_detecter.buildPatternFromImage(m_patternImage);
}

QVideoFrame PatternDetectorFilterRunnable::run(QVideoFrame* frame, const QVideoSurfaceFormat&, QVideoFilterRunnable::RunFlags)
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
        cv::Mat frameMat, grayscale;
        videoFrameInGrayScaleAndColor(frame, grayscale, frameMat);
        auto keypoints = m_detecter.findPattern(
                    grayscale,
                    m_filter->minNumberMatchesAllowed(),
                    m_filter->showMatches()
                    );

        if (keypoints)
        {
            const auto& points = m_detecter.points();
            cv::line( frameMat, points[0], points[1], cv::Scalar( 0, 255, 0), 4 );
            cv::line( frameMat, points[1], points[2], cv::Scalar( 0, 255, 0), 4 );
            cv::line( frameMat, points[2], points[3], cv::Scalar( 0, 255, 0), 4 );
            cv::line( frameMat, points[3], points[0], cv::Scalar( 0, 255, 0), 4 );

            emit m_filter->patternFound(keypoints);
        }
    }
    catch(const std::exception& exc)
    {
        qDebug() << exc.what();
    }

    frame->unmap();

    return *frame;
}

void PatternDetectorFilterRunnable::loadImagePattern(QString filename)
{
    m_patternImage = cv::imread(filename.toStdString(), CV_LOAD_IMAGE_GRAYSCALE);
    cv::imshow("pattern image", m_patternImage);
}
