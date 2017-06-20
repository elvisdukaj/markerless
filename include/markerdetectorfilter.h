#pragma once

#include "abstractopencvrunnablefilter.h"
#include <opencv2/core.hpp>

class MarkerDetectorFilter : public QAbstractVideoFilter {
    Q_OBJECT

public:
    QVideoFilterRunnable* createFilterRunnable() override;

signals:
    void thresholdChanged();

private:
    friend class ThresholdFilterRunnable;

private:
    int m_threshold = 128;
};

class MarkerDetectorFilterRunnable : public AbstractVideoFilterRunnable {
public:
    MarkerDetectorFilterRunnable(MarkerDetectorFilter* filter);
    QVideoFrame run(QVideoFrame* input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags) override;

private:
    MarkerDetectorFilter* m_filter;
};

class Marker {
public:
    Marker(const cv::Mat& image, const std::vector<cv::Point2f>& points);
    uint64_t id() const;
private:
    uint64_t m_id;
};

class MarksDetector {
public:
    MarksDetector();

    void processFame(cv::Mat& grayscale);
    uint64_t encode() const;

private:
    void binarize(cv::Mat& grayscale);
    void findContours();
    void findCandidates();

private:
    int m_minCountournSize;
    uint64_t m_id;
    cv::Mat m_binarized;
    std::vector<std::vector<cv::Point>> m_contours;
    void filterContours();
};

