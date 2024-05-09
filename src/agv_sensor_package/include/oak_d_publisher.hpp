/*
    TODO: move to 3rd party
    source: https://github.com/msardonini/flyStereo/tree/253a8e85f6e3fb1bcb39791e9a3aaf858e3a2e49
*/

#pragma once

#include <chrono>
#include <utility>
#include <thread>
#include <atomic>
#include <array>

#include "depthai/depthai.hpp"
#include "rclcpp/rclcpp.hpp"
#include "opencv2/core/core.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "sensor_msgs/msg/camera_info.hpp"
#include "sensor_msgs/msg/imu.hpp"
// #include "stereo_calibration_dai_convert.h"
#include "stereo_calibration_ros_convert.hpp"
#include "cv_bridge/cv_bridge.h"
#include "depthai_bridge/BridgePublisher.hpp"
#include "depthai_bridge/ImuConverter.hpp"
#include "depthai_bridge/ImageConverter.hpp"

class OakDPublisher
{
public:
    OakDPublisher(std::shared_ptr<rclcpp::Node> node);
    ~OakDPublisher();
    void spin();

private:
    void initOak();

    void imagePublisherThreadFn();
    void imuPublisherThreadFn();
    void previewPublisherThreadFn();

    std::pair<std::shared_ptr<dai::ImgFrame>, std::shared_ptr<dai::ImgFrame>> getImagePair();

    std::shared_ptr<rclcpp::Node> node;
    std::atomic<bool> isThreadRunning = (false);
    // std::unique_ptr<StereoCalibration> calibrationPtr;
    // dai::CalibrationHandler calibrationHandler;

    // dai pipeline and pipeline nodes
    dai::Pipeline pipeline;
    std::shared_ptr<dai::node::ColorCamera> cam;
    std::shared_ptr<dai::node::IMU> imu;
    std::shared_ptr<dai::node::MonoCamera> leftCam;
    std::shared_ptr<dai::node::MonoCamera> rightCam;
    std::shared_ptr<dai::node::XLinkOut> xoutPreview;
    std::shared_ptr<dai::node::XLinkOut> xoutImu;
    std::shared_ptr<dai::node::XLinkOut> xoutMonoLeft;
    std::shared_ptr<dai::node::XLinkOut> xoutMonoRight;

    // dai device and queues
    std::unique_ptr<dai::Device> device;
    std::shared_ptr<dai::DataOutputQueue> queueLeft;
    std::shared_ptr<dai::DataOutputQueue> queueRight;
    std::shared_ptr<dai::DataOutputQueue> queueImu;
    std::shared_ptr<dai::DataOutputQueue> queuePreview;

    // ros publishers
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr leftImagePublisher;
    rclcpp::Publisher<sensor_msgs::msg::CameraInfo>::SharedPtr leftCameraInfoPublisher;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr rightImagePublisher;
    rclcpp::Publisher<sensor_msgs::msg::CameraInfo>::SharedPtr rightCameraInfoPublisher;
    rclcpp::Publisher<sensor_msgs::msg::CameraInfo>::SharedPtr previewPublisher;

    // dai imu converter and publisher
    std::unique_ptr<dai::rosBridge::ImuConverter> imuConverter;
    std::unique_ptr<dai::rosBridge::BridgePublisher<sensor_msgs::msg::Imu, dai::IMUData>> imuPublisher;

    // std::unique_ptr<dai::rosBridge::ImageConverter> previewConverter;
    // std::unique_ptr<dai::rosBridge::BridgePublisher<sensor_msgs::msg::Image, dai::ImgFrame>> previewPublisher;

    // threads
    std::thread imagePublisherThread;
    std::thread imuPublisherThread;
    // std::thread previewPublisherThread;

    std::chrono::time_point<std::chrono::steady_clock> startTime;

    // TODO change return type
    static auto getTimestamp(std::chrono::time_point<std::chrono::steady_clock, std::chrono::steady_clock::duration> timestampDataIn);
};
