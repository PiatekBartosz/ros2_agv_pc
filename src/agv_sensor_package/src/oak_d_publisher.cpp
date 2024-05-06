// #include <cstdio>
// #include <functional>
// #include <iostream>
// #include <tuple>

// #include "camera_info_manager/camera_info_manager.hpp"
// #include "depthai_ros_msgs/msg/spatial_detection_array.hpp"
// #include "rclcpp/node.hpp"
// #include "sensor_msgs/msg/image.hpp"
// #include "sensor_msgs/msg/imu.hpp"

// // Includes common necessary includes for development using depthai library
// #include "depthai/device/DataQueue.hpp"
// #include "depthai/device/Device.hpp"

// #include "depthai/pipeline/Pipeline.hpp"
// #include "depthai/pipeline/node/ColorCamera.hpp"
// #include "depthai/pipeline/node/IMU.hpp"
// #include "depthai/pipeline/node/MonoCamera.hpp"
// #include "depthai/pipeline/node/SpatialDetectionNetwork.hpp"
// #include "depthai/pipeline/node/StereoDepth.hpp"
// #include "depthai/pipeline/node/XLinkIn.hpp"
// #include "depthai/pipeline/node/XLinkOut.hpp"

// #include "depthai_bridge/BridgePublisher.hpp"
// #include "depthai_bridge/DisparityConverter.hpp"
// #include "depthai_bridge/ImageConverter.hpp"
// #include "depthai_bridge/ImuConverter.hpp"
// #include "depthai_bridge/SpatialDetectionConverter.hpp"
// #include "depthai_bridge/depthaiUtility.hpp"

// std::tuple<dai::Pipeline, int, int> createPipeline() {
//     dai::Pipeline pipeline;
//     int width = 300;
//     int height = 300;
//     int monoFPS = 30;

//     // create nodes
//     auto cam = pipeline.create<dai::node::ColorCamera>();
//     auto imu = pipeline.create<dai::node::IMU>();
//     auto leftCam = pipeline.create<dai::node::MonoCamera>();
//     auto rightCam = pipeline.create<dai::node::MonoCamera>();

//     // crete output nodes
//     auto xoutPreview = pipeline.create<dai::node::XLinkOut>();
//     auto xoutImu = pipeline.create<dai::node::XLinkOut>();
//     auto xoutMonoLeft = pipeline.create<dai::node::XLinkOut>();
//     auto xoutMonoRight = pipeline.create<dai::node::XLinkOut>();

//     // name outputs
//     xoutPreview->setStreamName("preview");
//     xoutImu->setStreamName("imu");
//     xoutMonoLeft->setStreamName("left");
//     xoutMonoRight->setStreamName("right");

//     // node properties
//     cam->setPreviewSize(width, height);
//     cam->setBoardSocket(dai::CameraBoardSocket::CAM_A);
//     cam->setResolution(dai::ColorCameraProperties::SensorResolution::THE_1080_P);
//     cam->setInterleaved(false);
//     cam->setColorOrder(dai::ColorCameraProperties::ColorOrder::RGB);

//     imu->enableIMUSensor(dai::IMUSensor::ACCELEROMETER_RAW, 500);
//     imu->enableIMUSensor(dai::IMUSensor::GYROSCOPE_RAW, 400);
//     imu->setMaxBatchReports(10);

//     dai::node::MonoCamera::Properties::SensorResolution monoResolution = dai::node::MonoCamera::Properties::SensorResolution::THE_400_P;
//     leftCam->setResolution(monoResolution);
//     leftCam->setBoardSocket(dai::CameraBoardSocket::CAM_B);
//     leftCam->setFps(monoFPS);
//     rightCam->setResolution(monoResolution);
//     rightCam->setBoardSocket(dai::CameraBoardSocket::CAM_C);
//     rightCam->setFps(monoFPS);

//     // linking
//     cam->preview.link(xoutPreview->input);
//     imu->out.link(xoutImu->input);
//     leftCam->out.link(xoutMonoLeft->input);
//     rightCam->out.link(xoutMonoRight->input);

//     return std::make_tuple(pipeline, width, height);
// }

// int main(int argc, char** argv) {
//     rclcpp::init(argc, argv);
//     auto node = rclcpp::Node::make_shared("oak_d_node");

//     // TODO: move parameters into launch file / cfg file
//     int previewWidth = 300;
//     int previewHeight = 300;
//     int monoWidth = 640;
//     int monoHeight = 400;

//     dai::ros::ImuSyncMethod imuMode = static_cast<dai::ros::ImuSyncMethod>(1);

//     // TODO: what is this covariance
//     double linearAccelCovariance = 0;
//     double angularVelCovariance = 0.02;

//     dai::Pipeline pipeline;
//     int width, height;

//     std::tie(pipeline, width, height) = createPipeline();
//     dai::Device device(pipeline);

//     auto previewQueue = device.getOutputQueue("preview", 30, false);
//     auto imuQueue = device.getOutputQueue("imu", 30, false);
//     auto leftQueue = device.getOutputQueue("left", 30, false);
//     auto rightQueue = device.getOutputQueue("right", 30, false);

//     // sending basic configuration
//     auto calibrationHandler = device.readCalibration();

//     // preview ros2 conversion
//     dai::rosBridge::ImageConverter rgbConverter("oak_camera_optical_frame", true);
//     auto previewCameraInfo = rgbConverter.calibrationToCameraInfo(calibrationHandler, dai::CameraBoardSocket::CAM_A, previewWidth, previewHeight);

//     // imu ros2 conversion
//     dai::rosBridge::ImuConverter imuConverter("oak_imu_frame", imuMode, linearAccelCovariance, angularVelCovariance);

//     // left ros2 conversion
//     dai::rosBridge::ImageConverter leftConverter("oak_camera_optical_frame_left", true);
//     auto leftCameraInfo = leftConverter.calibrationToCameraInfo(calibrationHandler, dai::CameraBoardSocket::CAM_B, monoWidth, monoHeight);

//     // right ros2 conversion
//     dai::rosBridge::ImageConverter rightConverter("oak_camera_optical_frame_right", true);
//     auto rightCameraInfo = rightConverter.calibrationToCameraInfo(calibrationHandler, dai::CameraBoardSocket::CAM_C, monoWidth, monoHeight);

//     dai::rosBridge::BridgePublisher<sensor_msgs::msg::Image, dai::ImgFrame> rgbPreviewPublish(
//         previewQueue,
//         node,
//         std::string("color/preview/image"),
//         std::bind(&dai::rosBridge::ImageConverter::toRosMsg,
//             &rgbConverter,
//             std::placeholders::_1,
//             std::placeholders::_2),
//         30,
//         previewCameraInfo,
//         "color/preview");
//     rgbPreviewPublish.addPublisherCallback();

//     dai::rosBridge::BridgePublisher<sensor_msgs::msg::Imu, dai::IMUData> imuPublish(
//         imuQueue,
//         node,
//         std::string("imu"),
//         std::bind(&dai::rosBridge::ImuConverter::toRosMsg, &imuConverter, std::placeholders::_1, std::placeholders::_2),
//         30,
//         "",
//         "visual_slam/imu");
//     imuPublish.addPublisherCallback();

//     dai::rosBridge::BridgePublisher<sensor_msgs::msg::Image, dai::ImgFrame> leftPublish(
//         leftQueue,
//         node,
//         std::string("/stereo_camera/left"),
//         std::bind(&dai::rosBridge::ImageConverter::toRosMsg,
//             &leftConverter,
//             std::placeholders::_1,
//             std::placeholders::_2),
//         30,
//         leftCameraInfo,
//         "stereo_camera/left");
//     leftPublish.addPublisherCallback();

//     dai::rosBridge::BridgePublisher<sensor_msgs::msg::Image, dai::ImgFrame> rightPublish(
//         rightQueue,
//         node,
//         std::string("stereo_camera/right"),
//         std::bind(&dai::rosBridge::ImageConverter::toRosMsg,
//             &rightConverter,
//             std::placeholders::_1,
//             std::placeholders::_2),
//         30,
//         rightCameraInfo,
//         "stereo_camera/right");
//     rightPublish.addPublisherCallback();

//     rclcpp::spin(node);
//     rclcpp::shutdown();
//     return 0;
// }

#include <string>

#include "oak_d_publisher.hpp"
#include "yaml-cpp/yaml.h"

static constexpr auto timeout = std::chrono::milliseconds(1000);
static const std::string imuTopic = "/visual_slam/imu";
static const std::string leftCamTopic = "/stereo_camera/left/image";
static const std::string leftCamInfoTopic = "/stereo_camera/left/camera_info";
static const std::string rightCamTopic = "/stereo_camera/right/image";
static const std::string rightCamInfoTopic = "/stereo_camera/right/camera_info";

OakDPublisher::OakDPublisher(std::shared_ptr<rclcpp::Node> node) : node(node)
{
    // if (calibration)
    // {
    //     calibrationPtr = std::make_unique<StereoCalibration>(*calibration);

    //     // TODO: for now skip OAK-Calibration
    //     // pipeline.setCalibrationData(calibrationHandler);
    // }

    initOak();
}

OakDPublisher::~OakDPublisher()
{
    isThreadRunning = false;
    if (imagePublisherThread.joinable())
    {
        imagePublisherThread.join();
    }

    if (imuPublisherThread.joinable())
    {
        imuPublisherThread.join();
    }
}

void OakDPublisher::spin()
{
    rclcpp::spin(node);
}

void OakDPublisher::initOak()
{
    int width = 300;
    int height = 300;
    int monoFPS = 30;

    // create nodes
    // auto cam = pipeline.create<dai::node::ColorCamera>();
    auto imu = pipeline.create<dai::node::IMU>();
    auto leftCam = pipeline.create<dai::node::MonoCamera>();
    auto rightCam = pipeline.create<dai::node::MonoCamera>();

    // crete output nodes
    // auto xoutPreview = pipeline.create<dai::node::XLinkOut>();
    auto xoutImu = pipeline.create<dai::node::XLinkOut>();
    auto xoutMonoLeft = pipeline.create<dai::node::XLinkOut>();
    auto xoutMonoRight = pipeline.create<dai::node::XLinkOut>();

    // name outputs
    // xoutPreview->setStreamName("preview");
    xoutImu->setStreamName("imu");
    xoutMonoLeft->setStreamName("left");
    xoutMonoRight->setStreamName("right");

    // node properties
    // cam->setPreviewSize(width, height);
    // cam->setBoardSocket(dai::CameraBoardSocket::CAM_A);
    // cam->setResolution(dai::ColorCameraProperties::SensorResolution::THE_1080_P);
    // cam->setInterleaved(false);
    // cam->setColorOrder(dai::ColorCameraProperties::ColorOrder::RGB);

    imu->enableIMUSensor(dai::IMUSensor::ACCELEROMETER_RAW, 500);
    imu->enableIMUSensor(dai::IMUSensor::GYROSCOPE_RAW, 400);
    imu->setMaxBatchReports(10);

    dai::node::MonoCamera::Properties::SensorResolution monoResolution = dai::node::MonoCamera::Properties::SensorResolution::THE_720_P;
    leftCam->setResolution(monoResolution);
    leftCam->setBoardSocket(dai::CameraBoardSocket::CAM_B);
    leftCam->setFps(monoFPS);
    rightCam->setResolution(monoResolution);
    rightCam->setBoardSocket(dai::CameraBoardSocket::CAM_C);
    rightCam->setFps(monoFPS);

    // linking
    // cam->preview.link(xoutPreview->input);
    imu->out.link(xoutImu->input);
    leftCam->out.link(xoutMonoLeft->input);
    rightCam->out.link(xoutMonoRight->input);

    startTime = std::chrono::steady_clock::now();

    // declare oak device and queue
    device = std::make_unique<dai::Device>(pipeline);
    // previewQueue = device->getOutputQueue("preview", 30, false);
    queueImu = device->getOutputQueue("imu", 30, false);
    // settings left right queue size to 1 for synchronization purposes
    queueLeft = device->getOutputQueue("left", 1, false);
    queueRight = device->getOutputQueue("right", 1, false);

    // create publishers
    leftImagePublisher = node->create_publisher<sensor_msgs::msg::Image>(leftCamTopic, 1);
    leftCameraInfoPublisher = node->create_publisher<sensor_msgs::msg::CameraInfo>(leftCamInfoTopic, 1);
    rightImagePublisher = node->create_publisher<sensor_msgs::msg::Image>(rightCamTopic, 1);
    rightCameraInfoPublisher = node->create_publisher<sensor_msgs::msg::CameraInfo>(rightCamInfoTopic, 1);

    isThreadRunning = true;
    imagePublisherThread = std::thread(&OakDPublisher::imagePublisherThreadFn, this);
    imuPublisherThread = std::thread(&OakDPublisher::imuPublisherThreadFn, this);
}

// TODO change this method to have only one exit point
std::pair<std::shared_ptr<dai::ImgFrame>, std::shared_ptr<dai::ImgFrame>> OakDPublisher::getImagePair()
{
    // check if two frames are present
    auto counter = 0l;
    while (!queueLeft->has<dai::ImgFrame>() || !queueRight->has<dai::ImgFrame>())
    {
        if (counter > std::chrono::duration_cast<std::chrono::microseconds>(timeout).count())
        {
            // TODO throw error and return empty frame ptrs, check return val?
            // RCLCPP_ERROR_STREAM_THROTTLE(node->get_logger(), *node->get_lock(), 1000, "Timeout while waiting for two frames to appear");
            return {};
        }
    }

    auto leftSequenceNum = queueLeft->front<dai::ImgFrame>()->getSequenceNum();
    auto rightSequenceNum = queueRight->front<dai::ImgFrame>()->getSequenceNum();
    if (leftSequenceNum != rightSequenceNum)
    {

        // RCLCPP_ERROR_STREAM_THROTTLE(node->get_logger(), *node->get_lock(), 1000, "Frames not synced");
        // try to sync the frames
        if (leftSequenceNum > rightSequenceNum)
        {
            queueRight->get();
        }
        else
        {
            queueLeft->get();
        }

        return {};
    }

    bool hasTimeout = false;
    auto leftImg = queueLeft->get<dai::ImgFrame>(timeout, hasTimeout);

    if (hasTimeout)
    {
        // RCLCPP_ERROR_STREAM_THROTTLE(node->get_logger(), *node->get_lock(), 1000, "Timeout while getting frame");
        return {};
    }

    auto rightImg = queueRight->get<dai::ImgFrame>(timeout, hasTimeout);

    if (hasTimeout)
    {
        // RCLCPP_ERROR_STREAM_THROTTLE(node->get_logger(), *node->get_lock(), 1000, "Timeout while getting frame");
        return {};
    }

    return std::make_pair(leftImg, rightImg);
}

auto OakDPublisher::getTimestamp(std::chrono::time_point<std::chrono::steady_clock, std::chrono::steady_clock::duration> timestampDataIn)
{
    auto rosNowTime = rclcpp::Clock().now();
    auto steadyTime = std::chrono::steady_clock::now();

    // calculate the difference between the now and ts data in std::chrono format
    auto timeDiff = steadyTime - timestampDataIn;

    // return the difference between ROS now time and difference between std::chrono now and timestamp
    return rosNowTime - timeDiff;
}

void OakDPublisher::imagePublisherThreadFn()
{
    while (isThreadRunning.load())
    {
        auto imgPair = getImagePair();

        std_msgs::msg::Header header;

        // assign the timestamp of the left frame to the msg header
        header.stamp = getTimestamp(imgPair.first->getTimestamp());

        auto firstImg = imgPair.first->getCvFrame();
        auto secondImg = imgPair.second->getCvFrame();

        cv_bridge::CvImage leftBridge(header, "mono8", firstImg);
        cv_bridge::CvImage rightBridge(header, "mono8", secondImg);

        // add default configuration header and update timestamp
        // auto stereoCamInfo = stereo_calibration_convert<std::array<sensor_msgs::msg::CameraInfo, 2>>();
        auto stereoCamInfo = HardcodedCameraInfo::convert();

        stereoCamInfo[0].header = header;
        stereoCamInfo[1].header = header;

        leftImagePublisher->publish(*leftBridge.toImageMsg());
        leftCameraInfoPublisher->publish(stereoCamInfo[0]);
        rightImagePublisher->publish(*rightBridge.toImageMsg());
        rightCameraInfoPublisher->publish(stereoCamInfo[1]);
    }
}

void OakDPublisher::imuPublisherThreadFn()
{
    double linearAccelerationCovariance = 0.0;
    double angularVelocityCovariance = 0.02;

    dai::ros::ImuSyncMethod imuMode = static_cast<dai::ros::ImuSyncMethod>(1);

    imuConverter =
        std::make_unique<dai::rosBridge::ImuConverter>("imu_converter", imuMode, linearAccelerationCovariance, angularVelocityCovariance);

    imuPublisher = std::make_unique<dai::rosBridge::BridgePublisher<sensor_msgs::msg::Imu, dai::IMUData>>(
        queueImu, node, std::string(imuTopic),
        std::bind(&dai::rosBridge::ImuConverter::toRosMsg, imuConverter.get(), std::placeholders::_1,
                  std::placeholders::_2),
        30, "", "imu");

    imuPublisher->addPublisherCallback();
}

// OakCalibration::OakCalibration(const YAML::Node &calibration)
// {
//     K_cam0 = cv::Matx33d(stereo_calibration["K0"]["data"].as<std::vector<double>>().data());
//     K_cam1 = cv::Matx33d(stereo_calibration["K1"]["data"].as<std::vector<double>>().data());
//     D_cam0 = stereo_calibration["D0"]["data"].as<std::vector<double>>();
//     D_cam1 = stereo_calibration["D1"]["data"].as<std::vector<double>>();
//     R_cam0_cam1 = cv::Matx33d(stereo_calibration["R"]["data"].as<std::vector<double>>().data());
//     T_cam0_cam1 = cv::Vec3d(stereo_calibration["T"]["data"].as<std::vector<double>>().data());
//     image_size = cv::Size(stereo_calibration["image_size"].as<std::vector<int>>()[0],
//                           stereo_calibration["image_size"].as<std::vector<int>>()[1]);

//     const cv::Matx33d T_cross_mat(0.0, -T_cam0_cam1[2], T_cam0_cam1[1], T_cam0_cam1[2], 0.0, -T_cam0_cam1[0],
//                                   -T_cam0_cam1[1], T_cam0_cam1[0], 0.0);

//     E = T_cross_mat * R_cam0_cam1;
//     F = K_cam0.inv().t() * E * K_cam1.inv();
//     cv::stereoRectify(K_cam0, D_cam0, K_cam1, D_cam1, cv::Size(1280, 720), R_cam0_cam1, T_cam0_cam1, R0, R1, P0, P1, Q,
//                       cv::CALIB_ZERO_DISPARITY, -1.0, cv::Size(), &valid_roi_left, &valid_roi_right);
// }

// static std::pair<sensor_msgs::ImageInfo, sensor_msgs::ImageInfo> CalibrationConverter::convert(const YAML::Node &calibration)
// {
// }
