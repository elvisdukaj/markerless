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
    m_patternImage = cv::imread("image.bmp", CV_LOAD_IMAGE_COLOR);
    auto pattern = m_detecter.buildPatternFromImage(m_patternImage);
    m_detecter.train(pattern);
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
        m_detecter.findPattern(grayscale);
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
