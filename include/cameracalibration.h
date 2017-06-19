#pragma once

#include <Eigen/Eigen>

class CameraCalibration {
public:
    const Eigen::Matrix3f& instrinsic() const noexcept { return m_intrinsic;}
    const Eigen::Vector4f& distortion() const noexcept { return m_distortion;}

    Eigen::Matrix<float, 3, 4> transformation() const;

private:
    Eigen::Matrix3f m_intrinsic;
    Eigen::Matrix3f m_distortion;
};
