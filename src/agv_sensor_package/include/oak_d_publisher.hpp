#pragma once

#include <chrono>

#include "thread"
#include "depthai/depthai.hpp"
#include "rclcpp/rclcpp.hpp"
#include "opencv2/core/core.hpp"

class OakDPublisher
{
public:
    OakDPublisher(std::shared_ptr<rclcpp::Node> node);
    ~OakDPublisher();
    void spin();
    int getSynchronizedData(cv::Mat_<uint8_t> &leftImg, cv::Mat_<uint8_t> &rightImg,
                            std::vector<dai::IMUPacket> imuData, uint64_t timestamp);

private:
    void initOak();
    std::shared_ptr<rclcpp::Node> node;

    dai::Pipeline pipeline;

    std::shared_ptr<dai::node::ColorCamera> cam;
    std::shared_ptr<dai::node::IMU> imu;
    std::shared_ptr<dai::node::MonoCamera> leftCam;
    std::shared_ptr<dai::node::MonoCamera> rightCam;

    std::shared_ptr<dai::node::XLinkOut> xoutPreview;
    std::shared_ptr<dai::node::XLinkOut> xoutImu;
    std::shared_ptr<dai::node::XLinkOut> xoutMonoLeft;
    std::shared_ptr<dai::node::XLinkOut> xoutMonoRight;

    std::chrono::time_point<std::chrono::steady_clock> startTime;
};