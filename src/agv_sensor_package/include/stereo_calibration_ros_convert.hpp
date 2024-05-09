#pragma once

#include "sensor_msgs/distortion_models.hpp"
#include "sensor_msgs/msg/camera_info.hpp"

class HardcodedCameraInfo
{
public:
    /**
     * @brief Convert a StereoCalibration object to a std::array<sensor_msgs::msg::CameraInfo, 2>. The output array is
     * filled with the left, then right camera info.
     *
     * @param calibration The StereoCalibration object to convert.
     * @return std::array<sensor_msgs::msg::CameraInfo, 2>
     */
    static std::array<sensor_msgs::msg::CameraInfo, 2> convert()
    {

        // TODO: hard code for now change it
        std::array<double, 9> k0Hard = {7.9729111496640428e+02,
                                        0.0,
                                        6.6105097896843006e+02,
                                        0.0,
                                        7.9654404477327751e+02,
                                        3.7505947915574194e+02,
                                        0.0,
                                        0.0,
                                        1.0};

        std::vector<double> d0Hard{-1.0213830211147780e+01, 6.8510709385541674e+01,
                                   -8.2820829027617520e-05, 2.4734139353600515e-04,
                                   -8.1909334884705942e+01, -1.0267068372311039e+01,
                                   6.8621408267212558e+01, -8.1832381504479997e+01};

        std::array<double, 9> r0Hard = {9.9165206438534792e-01, 3.4419505290368513e-03,
                                        -1.2889661041638634e-01, -3.5239828954628555e-03,
                                        9.9999370737409299e-01, -4.0835862824141294e-04,
                                        1.2889439376803979e-01, 8.5917912709563551e-04,
                                        9.9165795366466802e-01};

        std::array<double, 12> p0Hard = {7.9919907777638241e+02, 0., 8.2560940551757812e+02, 0., 0.,
                                         7.9919907777638241e+02, 3.6137877273559570e+02, 0., 0., 0., 1.,
                                         0.};

        std::array<double, 9> k1Hard = {8.0263250602985181e+02, 0., 6.4012734502958028e+02, 0.,
                                        8.0185411077948720e+02, 3.7665317612930204e+02, 0., 0., 1.};

        std::vector<double> d1Hard{-1.1227843794555394e+01, 8.7248827063968122e+01,
                                   -1.1776659414862432e-03, 2.3356882826313150e-04,
                                   -8.2874383277203208e+01, -1.1272778963618663e+01,
                                   8.7126226296288991e+01, -8.2245597439955574e+01};

        std::array<double, 9> r1Hard = {9.9256674035125469e-01, 5.1640067272647177e-03,
                                        -1.2159193634039220e-01, -5.0866392612288602e-03,
                                        9.9998661485941187e-01, 9.4668000948516112e-04,
                                        1.2159519747716745e-01, -3.2114877393251686e-04,
                                        9.9257972214525592e-01};

        std::array<double, 12> p1Hard = {7.9919907777638241e+02, 0., 8.2560940551757812e+02,
                                         -6.0244284946139388e+01, 0., 7.9919907777638241e+02,
                                         3.6137877273559570e+02, 0., 0., 0., 1., 0.};

        sensor_msgs::msg::CameraInfo left_cam_info;
        left_cam_info.k = k0Hard;
        left_cam_info.d = d0Hard;
        left_cam_info.r = r0Hard;
        left_cam_info.p = p0Hard;
        left_cam_info.width = 1280;
        left_cam_info.height = 720;
        left_cam_info.distortion_model = sensor_msgs::distortion_models::RATIONAL_POLYNOMIAL;

        sensor_msgs::msg::CameraInfo right_cam_info;
        right_cam_info.k = k1Hard;
        right_cam_info.d = d1Hard;
        right_cam_info.r = r1Hard;
        right_cam_info.p = p1Hard;
        right_cam_info.width = 1280;
        right_cam_info.height = 720;
        right_cam_info.distortion_model = sensor_msgs::distortion_models::RATIONAL_POLYNOMIAL;

        return {left_cam_info, right_cam_info};
    }
};
