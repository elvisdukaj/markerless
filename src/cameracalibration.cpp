#include "cameracalibration.h"

CameraCalibration::CameraCalibration()
{
    float dist[] = {0, 0, 0, 0};

    float intr[3][3] = {
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f}
    };

    cv::Mat distMat(1, 4, CV_32F, dist);
    cv::Mat intrMat(1, 4, CV_32F, intr);

    distMat.copyTo(m_distortion);
    intrMat.copyTo(m_intrinsic);
}
