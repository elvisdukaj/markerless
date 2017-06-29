#pragma once

#include "abstractopencvrunnablefilter.h"
#include "cameracalibration.h"
#include <opencv2/core.hpp>

class MarkerDetectorFilter : public QAbstractVideoFilter {
    Q_OBJECT

public:
    QVideoFilterRunnable* createFilterRunnable() override;

signals:
    void markerFound(QString id);

private:
    friend class ThresholdFilterRunnable;
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

    bool isValid() const noexcept { return m_isValid; }
    uint64_t id() const noexcept { return m_id; }
    const std::vector<cv::Point2f>& points() const noexcept { return m_points; }
    void precisePoints(const std::vector<cv::Point2f>& points) noexcept;
    void drawContours(cv::Mat& image, cv::Scalar color) const noexcept;

private:
    cv::Mat checkFrame(const cv::Mat& image) const noexcept;
    cv::Mat checkOrientationFrame(const cv::Mat& orientation) const noexcept;
    void encodeData(const cv::Mat& dataImage);

private:
    const cv::Size m_squareSize;
    const int m_minArea;
    bool m_isValid;
    std::vector<cv::Point2f> m_points;
    uint64_t m_id;
};

class MarksDetector {
public:
    MarksDetector();

    void processFame(cv::Mat& grayscale);
    uint64_t encode() const;

    const std::vector<Marker>& markers() const noexcept;

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
    std::vector<Marker> m_markers;

    CameraCalibration m_calibration;
};
