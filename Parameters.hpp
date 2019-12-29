#pragma once
#include "Eigen/Core"
//#include "opencv2/core.hpp"
#include <vector>

namespace roaddb {
namespace trjest {
namespace core {

/**
 * @brief IMU Parameters
 */
struct ImuParameters {
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    ImuParameters() : sigmaBg(0), sigmaBa(0), sigmaG(0), sigmaA(0), f(0) {}

    double sigmaBg;  // Gyroscope bias noise density
    double sigmaBa;  // Accelerometer bias noise density
    double sigmaG;   // Gyroscope gaussian noise density
    double sigmaA;   // Accelerometer gaussian noise density
    unsigned int f;  // Sampling rate, Hz
};

/**
 * @brief GPS Parameters
 */
struct GpsParameters {
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    GpsParameters() : sigmaC(0), f(0) {
        sigmaP.setZero();
        sigmaV.setZero();
    }

    Eigen::Vector3d sigmaP;  // Position gaussian noise density, in [East, North, Up] direction
    Eigen::Vector3d sigmaV;  // Velocity guassian noise density, in [East, North, Up] direction
    double sigmaC;           // Course guassian noise density, in North direction
    unsigned int f;          // Sampling rate, Hz
};

/**
 * @brief Camera Parameters
 */
struct CameraParameters {
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    CameraParameters() {
        f.setZero();
        c.setZero();
        k.setZero();
        p.setZero();
        Tcb.setZero();
    };

    /**
     * @brief Get camera matrix K = [fx, 0, cx; 0, fy, cy; 0, 0, 1]
     * @return Camera matrix
     */
    inline Eigen::Matrix3d K() const {
        Eigen::Matrix3d K;
        K << f[0], 0, c[0], 0, f[1], c[1], 0, 0, 1;
        return K;
    }

    inline bool hasDistCoeffs() const { return k[0] || k[1] || p[0] || p[1]; }

    /**
     * @brief Get distortion coefficients
     * @return
     */
    // error
    // inline std::vector<double> distCoeffs() const { return std::vector<double>{k[0], k[1], p[0], p[1]}; }

    Eigen::Vector2d f;    // focal length, fx, fy
    Eigen::Vector2d c;    // optical center, or principal point, cx, cy
    Eigen::Vector2d k;    // radical distortion parameters, k1, k2
    Eigen::Vector2d p;    // tangential distortion parameters, p1, p2
    Eigen::Matrix4d Tcb;  // extrinsic matrix Tcb, from body to camera
};
/**
 * @brief Config Parameter for Data Preprocess
 */
struct PreprocessConfig {
    PreprocessConfig()
        : enableRepeatedDataCheck(false),
          enableTimeRegionCheck(false),
          enableEnoughLostDataCheck(true),
          enableAccumulatedGpsDataProcess(false) {}

    bool enableRepeatedDataCheck;  // Enable to check have repeated data
    // Enable time region check, to ensure the first/last timestamp of IMU and GPS don't have much difference
    bool enableTimeRegionCheck;
    bool enableEnoughLostDataCheck;        // Enable to check have enough lost data
    bool enableAccumulatedGpsDataProcess;  // Enable to process accumulated GPS data
};
}  // namespace core
}  // namespace trjest
}  // namespace roaddb
