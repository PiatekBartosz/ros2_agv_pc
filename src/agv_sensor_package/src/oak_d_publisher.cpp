#include <string>

#include "oak_d_publisher.hpp"
#include "yaml-cpp/yaml.h"

static constexpr auto timeout = std::chrono::milliseconds(1000);
static const std::string imuTopic = "/visual_slam/imu";
static const std::string leftCamTopic = "/stereo_camera/left/image";
static const std::string leftCamInfoTopic = "/stereo_camera/left/camera_info";
static const std::string rightCamTopic = "/stereo_camera/right/image";
static const std::string rightCamInfoTopic = "/stereo_camera/right/camera_info";
static const std::string previewTopic = "/cam/rgb";

OakDPublisher::OakDPublisher(std::shared_ptr<rclcpp::Node> node) : node(node)
{
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
    cam->setVideoSize(1920, 1080);
    cam->setInterleaved(false);
    cam->setColorOrder(dai::ColorCameraProperties::ColorOrder::RGB);

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
    cam->preview.link(xoutPreview->input);
    imu->out.link(xoutImu->input);
    leftCam->out.link(xoutMonoLeft->input);
    rightCam->out.link(xoutMonoRight->input);

    startTime = std::chrono::steady_clock::now();

    // declare oak device and queue
    device = std::make_unique<dai::Device>(pipeline);

    queuePreview = device->getOutputQueue("preview", 1, false);
    queueImu = device->getOutputQueue("imu", 30, false);

    // settings left right queue size to 1 for synchronization purposes
    queueLeft = device->getOutputQueue("left", 1, false);
    queueRight = device->getOutputQueue("right", 1, false);

    // create publishers
    leftImagePublisher = node->create_publisher<sensor_msgs::msg::Image>(leftCamTopic, 1);
    leftCameraInfoPublisher = node->create_publisher<sensor_msgs::msg::CameraInfo>(leftCamInfoTopic, 1);
    rightImagePublisher = node->create_publisher<sensor_msgs::msg::Image>(rightCamTopic, 1);
    rightCameraInfoPublisher = node->create_publisher<sensor_msgs::msg::CameraInfo>(rightCamInfoTopic, 1);
    previewPublisher = node->create_publisher<sensor_msgs::msg::Image>(previewTopic, 1);

    isThreadRunning = true;
    imagePublisherThread = std::thread(&OakDPublisher::imagePublisherThreadFn, this);
    imuPublisherThread = std::thread(&OakDPublisher::imuPublisherThreadFn, this);
    // previewPublisherThread = std::thread(&OakDPublisher::previewPublisherThreadFn, this);
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
/**
 * @brief
 *
 * @param timestampDataIn
 * @return auto
 */
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

        // Color img publisher
        // TODO: move to septate function
        // doesn't need to be synched
        bool hasTimeout = false;
        auto colorDaiImgFrame = queuePreview->get<dai::ImgFrame>(timeout, hasTimeout);
        auto colorImg = colorDaiImgFrame->getCvFrame();

        cv_bridge::CvImage leftBridge(header, "mono8", firstImg);
        cv_bridge::CvImage rightBridge(header, "mono8", secondImg);
        cv_bridge::CvImage colorBridge(header, "mono8", colorImg);

        // add default configuration header and update timestamp
        auto stereoCamInfo = HardcodedCameraInfo::convert();

        stereoCamInfo[0].header = header;
        stereoCamInfo[1].header = header;

        leftImagePublisher->publish(*leftBridge.toImageMsg());
        leftCameraInfoPublisher->publish(stereoCamInfo[0]);
        rightImagePublisher->publish(*rightBridge.toImageMsg());
        rightCameraInfoPublisher->publish(stereoCamInfo[1]);

        previewPublisher->publish(*colorBridge.toImageMsg());
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
        std::bind(&dai::rosBridge::ImuConverter::toRosMsg,
                  imuConverter.get(),
                  std::placeholders::_1,
                  std::placeholders::_2),
        30, "", "imu");

    imuPublisher->addPublisherCallback();
}

void OakDPublisher::previewPublisherThreadFn()
{
    // // TODO: for now hardcoded
    // int previewWidth = 300;
    // int previewHeight = 300;

    // auto calibrationHandler = device->readCalibration();
    // auto previewInfo = previewConverter->calibrationToCameraInfo(calibrationHandler, dai::CameraBoardSocket::CAM_A, previewWidth, previewHeight);

    // previewPublisher = std::make_unique<dai::rosBridge::BridgePublisher<sensor_msgs::msg::Image, dai::ImgFrame>>(
    //     queuePreview,
    //     node,
    //     std::string("preview123/image123"),
    //     std::bind(&dai::rosBridge::ImageConverter::toRosMsg,
    //               previewConverter.get(),
    //               std::placeholders::_1,
    //               std::placeholders::_2),
    //     30,
    //     "",
    //     "preview123");

    // previewPublisher->addPublisherCallback();
}
