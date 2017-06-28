#pragma once

#include <Eigen/Eigen>
#include <opencv2/opencv.hpp>

class CameraCalibration {
public:
    CameraCalibration();

    cv::Mat instrinsic() const noexcept { return m_intrinsic; }
    cv::Mat distortion() const noexcept { return m_distortion; }

    Eigen::Matrix<float, 3, 4> transformation() const;

private:
    cv::Mat m_intrinsic;
    cv::Mat m_distortion;
};
