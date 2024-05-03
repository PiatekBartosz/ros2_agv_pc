#include <cstdio>
#include <functional>
#include <iostream>
#include <tuple>

#include "camera_info_manager/camera_info_manager.hpp"
#include "depthai_ros_msgs/msg/spatial_detection_array.hpp"
#include "rclcpp/node.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "sensor_msgs/msg/imu.hpp"

// Includes common necessary includes for development using depthai library
#include "depthai/device/DataQueue.hpp"
#include "depthai/device/Device.hpp"

#include "depthai/pipeline/Pipeline.hpp"
#include "depthai/pipeline/node/ColorCamera.hpp"
#include "depthai/pipeline/node/IMU.hpp"
#include "depthai/pipeline/node/MonoCamera.hpp"
#include "depthai/pipeline/node/SpatialDetectionNetwork.hpp"
#include "depthai/pipeline/node/StereoDepth.hpp"
#include "depthai/pipeline/node/XLinkIn.hpp"
#include "depthai/pipeline/node/XLinkOut.hpp"

#include "depthai_bridge/BridgePublisher.hpp"
#include "depthai_bridge/DisparityConverter.hpp"
#include "depthai_bridge/ImageConverter.hpp"
#include "depthai_bridge/ImuConverter.hpp"
#include "depthai_bridge/SpatialDetectionConverter.hpp"
#include "depthai_bridge/depthaiUtility.hpp"

std::tuple<dai::Pipeline, int, int> createPipeline() {
    dai::Pipeline pipeline;
    int width = 300;
    int height = 300;
    int monoFPS = 30;

    // create nodes
    auto cam = pipeline.create<dai::node::ColorCamera>();
    auto imu = pipeline.create<dai::node::IMU>();
    auto leftCam = pipeline.create<dai::node::MonoCamera>();
    auto rightCam = pipeline.create<dai::node::MonoCamera>();

    // crete output nodes
    auto xoutPreview = pipeline.create<dai::node::XLinkOut>();
    auto xoutImu = pipeline.create<dai::node::XLinkOut>();
    auto xoutMonoLeft = pipeline.create<dai::node::XLinkOut>();
    auto xoutMonoRight = pipeline.create<dai::node::XLinkOut>();

    // name outputs
    xoutPreview->setStreamName("preview");
    xoutImu->setStreamName("imu");
    xoutMonoLeft->setStreamName("left");   
    xoutMonoRight->setStreamName("right");

    // node properties
    cam->setPreviewSize(width, height);
    cam->setBoardSocket(dai::CameraBoardSocket::CAM_A);
    cam->setResolution(dai::ColorCameraProperties::SensorResolution::THE_1080_P);
    cam->setInterleaved(false);
    cam->setColorOrder(dai::ColorCameraProperties::ColorOrder::RGB);

    imu->enableIMUSensor(dai::IMUSensor::ACCELEROMETER_RAW, 500);
    imu->enableIMUSensor(dai::IMUSensor::GYROSCOPE_RAW, 400);
    imu->setMaxBatchReports(10);

    dai::node::MonoCamera::Properties::SensorResolution monoResolution = dai::node::MonoCamera::Properties::SensorResolution::THE_400_P;
    leftCam->setResolution(monoResolution);
    leftCam->setBoardSocket(dai::CameraBoardSocket::CAM_B);
    leftCam->setFps(monoFPS);
    rightCam->setResolution(monoResolution);
    rightCam->setBoardSocket(dai::CameraBoardSocket::CAM_C);
    rightCam->setFps(monoFPS);

    // linking 
    cam->preview.link(xoutPreview->input);
    imu->out.link(xoutImu->input);
    leftCam->out.link(xoutMonoLeft->input);
    rightCam->out.link(xoutMonoRight->input);

    return std::make_tuple(pipeline, width, height);
}

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("oak_d_node");

    // TODO: move parameters into launch file / cfg file
    int previewWidth = 300;
    int previewHeight = 300;
    int monoWidth = 640;
    int monoHeight = 400;

    dai::ros::ImuSyncMethod imuMode = static_cast<dai::ros::ImuSyncMethod>(1);

    // TODO: what is this covariance
    double linearAccelCovariance = 0;
    double angularVelCovariance = 0.02;

    dai::Pipeline pipeline;
    int width, height;

    std::tie(pipeline, width, height) = createPipeline(); 
    dai::Device device(pipeline);

    auto previewQueue = device.getOutputQueue("preview", 30, false);
    auto imuQueue = device.getOutputQueue("imu", 30, false);
    auto leftQueue = device.getOutputQueue("left", 30, false);
    auto rightQueue = device.getOutputQueue("right", 30, false);

    // sending basic configuration
    auto calibrationHandler = device.readCalibration();

    // preview ros2 conversion
    dai::rosBridge::ImageConverter rgbConverter("oak_camera_optical_frame", true);
    auto previewCameraInfo = rgbConverter.calibrationToCameraInfo(calibrationHandler, dai::CameraBoardSocket::CAM_A, previewWidth, previewHeight);

    // imu ros2 conversion
    dai::rosBridge::ImuConverter imuConverter("oak_imu_frame", imuMode, linearAccelCovariance, angularVelCovariance);

    // left ros2 conversion
    dai::rosBridge::ImageConverter leftConverter("oak_camera_optical_frame_left", true);
    auto leftCameraInfo = leftConverter.calibrationToCameraInfo(calibrationHandler, dai::CameraBoardSocket::CAM_B, monoWidth, monoHeight);

    // right ros2 conversion
    dai::rosBridge::ImageConverter rightConverter("oak_camera_optical_frame_right", true);
    auto rightCameraInfo = rightConverter.calibrationToCameraInfo(calibrationHandler, dai::CameraBoardSocket::CAM_C, monoWidth, monoHeight);

    dai::rosBridge::BridgePublisher<sensor_msgs::msg::Image, dai::ImgFrame> rgbPreviewPublish(
        previewQueue,
        node,
        std::string("color/preview/image"),
        std::bind(&dai::rosBridge::ImageConverter::toRosMsg,
            &rgbConverter,
            std::placeholders::_1,
            std::placeholders::_2),
        30,
        previewCameraInfo,
        "color/preview");
    rgbPreviewPublish.addPublisherCallback();

    dai::rosBridge::BridgePublisher<sensor_msgs::msg::Imu, dai::IMUData> imuPublish(
        imuQueue,
        node,
        std::string("imu"),
        std::bind(&dai::rosBridge::ImuConverter::toRosMsg, &imuConverter, std::placeholders::_1, std::placeholders::_2),
        30,
        "",
        "imu");
    imuPublish.addPublisherCallback();

    dai::rosBridge::BridgePublisher<sensor_msgs::msg::Image, dai::ImgFrame> leftPublish(
        leftQueue,
        node,
        std::string("mono/left/image"),
        std::bind(&dai::rosBridge::ImageConverter::toRosMsg,
            &leftConverter,
            std::placeholders::_1,
            std::placeholders::_2),
        30,
        leftCameraInfo,
        "left/preview");
    leftPublish.addPublisherCallback();

    dai::rosBridge::BridgePublisher<sensor_msgs::msg::Image, dai::ImgFrame> rightPublish(
        rightQueue,
        node,
        std::string("mono/right/image"),
        std::bind(&dai::rosBridge::ImageConverter::toRosMsg,
            &rightConverter,
            std::placeholders::_1,
            std::placeholders::_2),
        30,
        rightCameraInfo,
        "right/preview");
    rightPublish.addPublisherCallback();

    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
