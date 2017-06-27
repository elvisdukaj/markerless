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
    uint64_t id() const noexcept { return m_id; }
    void precisePoints(const std::vector<cv::Point2f>& points) noexcept;
    void drawContours(cv::Mat& image, cv::Scalar color) const noexcept;

private:
    cv::Mat checkFrame(const cv::Mat& image) const noexcept;
    cv::Mat checkOrientationFrame(const cv::Mat& orientation) const noexcept;
    void encodeData(const cv::Mat& dataImage);

private:
    cv::Mat m_image;
    const cv::Size m_squareSize;
    const int m_minArea;
    std::vector<cv::Point2f> m_points;
    uint64_t m_id;
};

class MarkerNotFound : public std::exception {
public:
    const char* what() const noexcept { return "Marker not found"; };
};

class MarksDetector {
public:
    MarksDetector();

    void processFame(cv::Mat& grayscale);
    uint64_t encode() const;

private:
    void binarize(const cv::Mat &grayscale);
    void findContours();
    void findCandidates();
    void recognizeCandidates();

    void filterContours();

private:
    int m_minCountournSize;
    uint64_t m_id;
    cv::Mat m_grayscale;
    cv::Mat m_binarized;
    std::vector<std::vector<cv::Point>> m_contours;
    std::vector<std::vector<cv::Point2f>> m_possibleContours;

    const cv::Size m_markerSize;
    std::vector<cv::Point3f> m_markerCorners3d;
    std::vector<cv::Point2f> m_markerCorners2d;
};
