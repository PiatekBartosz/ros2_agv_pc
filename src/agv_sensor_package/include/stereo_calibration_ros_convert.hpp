/*
    TODO: move to 3rd party
    source: https://github.com/msardonini/flyStereo/tree/253a8e85f6e3fb1bcb39791e9a3aaf858e3a2e49
*/

#pragma once

#include "stereo_calibration.h"
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
        // auto get_distortion_model = [](std::size_t num_coeffs)
        // {
        //     if (num_coeffs == 5)
        //     {
        //         return sensor_msgs::distortion_models::PLUMB_BOB;
        //     }
        //     else if (num_coeffs == 8)
        //     {
        //         return sensor_msgs::distortion_models::RATIONAL_POLYNOMIAL;
        //     }
        //     else
        //     {
        //         throw std::runtime_error("Unsupported number of distortion coefficients");
        //     }
        // };

        // TODO: hard code for now change it
        std::array<double, 9> k0Hard = {387.6078796386719,
                                        0.0,
                                        321.7539978027344,
                                        0.0,
                                        387.78021240234375,
                                        195.091552734375,
                                        0.0,
                                        0.0,
                                        1.0};

        std::vector<double> d0Hard{13.927103996276855,
                                   -17.65325355529785,
                                   -0.0012899963185191154,
                                   -0.00023264925403054804,
                                   7.315122604370117,
                                   13.56337833404541,
                                   -16.417219161987305,
                                   6.393351078033447};

        std::array<double, 9> r0Hard = {0.9999092817306519,
                                        -0.0009979094611480832,
                                        -0.013434091582894325,
                                        0.0010041322093456984,
                                        0.9999994039535522,
                                        0.00045646235230378807,
                                        0.013433627784252167,
                                        -0.00046991053386591375,
                                        0.9999096393585205};

        std::array<double, 12> p0Hard = {394.9974670410156,
                                         0.0,
                                         311.137451171875,
                                         -29.79098888168126,
                                         0.0,
                                         395.2129211425781,
                                         218.3057861328125,
                                         0.0,
                                         0.0,
                                         0.0,
                                         1.0,
                                         0.0};

        std::array<double, 9> k1Hard = {394.9974670410156,
                                        0.0,
                                        311.137451171875,
                                        0.0,
                                        395.2129211425781,
                                        218.3057861328125,
                                        0.0,
                                        0.0,
                                        1.0};

        std::vector<double> d1Hard{17.606203079223633,
                                   -25.553176879882812,
                                   -0.0008225829224102199,
                                   -0.0008230231469497085,
                                   11.105332374572754,
                                   17.11235809326172,
                                   -24.001296997070312,
                                   9.950390815734863};

        std::array<double, 9> r1Hard = {0.9998387694358826,
                                        0.0013629017630591989,
                                        0.017905261367559433,
                                        -0.001354607637040317,
                                        0.9999989867210388,
                                        -0.0004753438988700509,
                                        -0.017905890941619873,
                                        0.0004510126600507647,
                                        0.9998396039009094};

        std::array<double, 12> p1Hard = {394.9974670410156,
                                         0.0,
                                         311.137451171875,
                                         0.0,
                                         0.0,
                                         395.2129211425781,
                                         218.3057861328125,
                                         0.0,
                                         0.0,
                                         0.0,
                                         1.0,
                                         0.0};

        sensor_msgs::msg::CameraInfo left_cam_info;
        left_cam_info.k = k0Hard;
        left_cam_info.d = d0Hard;
        left_cam_info.r = r0Hard;
        left_cam_info.p = p0Hard;
        left_cam_info.width = 1280;
        left_cam_info.height = 720;
        // roi should be zeroed? by default
        // left_cam_info.roi = rect_to_roi(calibration.valid_roi_left);
        left_cam_info.distortion_model = sensor_msgs::distortion_models::RATIONAL_POLYNOMIAL;

        sensor_msgs::msg::CameraInfo right_cam_info;
        right_cam_info.k = k1Hard;
        right_cam_info.d = d1Hard;
        right_cam_info.r = r1Hard;
        right_cam_info.p = p1Hard;
        right_cam_info.width = 1280;
        right_cam_info.height = 720;
        // roi should be zeroed? by default
        // right_cam_info.roi = rect_to_roi(calibration.valid_roi_right);
        right_cam_info.distortion_model = sensor_msgs::distortion_models::RATIONAL_POLYNOMIAL;

        return {left_cam_info, right_cam_info};
    }

// private:
//     /**
//      * @brief Helper function to convert a cv::Matx-like array to an std::array<double, N>
//      *
//      * @tparam InputT The cv::Matx-like array type
//      * @tparam ArrSize The size of the output array
//      * @param input The cv::Matx array
//      * @return std::array<double, ArrSize>
//      */
//     template <typename InputT, std::size_t ArrSize = InputT::rows * InputT::cols>
//     static std::array<double, ArrSize> convert_to_array(const InputT &input)
//     {
//         std::array<double, ArrSize> output;
//         for (auto i = 0; i < input.rows; i++)
//         {
//             for (auto j = 0; j < input.cols; j++)
//             {
//                 output[i * input.cols + j] = input(i, j);
//             }
//         }
//         return output;
//     }

//     /**
//      * @brief Helper function to convert a cv::Rect to a sensor_msgs::msg::RegionOfInterest
//      *
//      * @param rect The cv::Rect to convert
//      * @return sensor_msgs::msg::RegionOfInterest
//      */
//     static sensor_msgs::msg::RegionOfInterest rect_to_roi(const cv::Rect &rect)
//     {
//         sensor_msgs::msg::RegionOfInterest roi;
//         roi.x_offset = rect.x;
//         roi.y_offset = rect.y;
//         roi.width = rect.width;
//         roi.height = rect.height;
//         return roi;
//     }
};
