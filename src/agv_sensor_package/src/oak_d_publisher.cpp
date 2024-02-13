#include <cstdio>
#include <functional>
#include <iostream>
#include <tuple>

#include "camera_info_manager/camera_info_manager.hpp"
#include "depthai_ros_msgs/msg/spatial_detection_array.hpp"
#include "rclcpp/node.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "stereo_msgs/msg/disparity_image.hpp"

// Inludes common necessary includes for development using depthai library
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

    // create nodes
    auto cam = pipeline.create<dai::node::ColorCamera>();
    auto xoutPreview = pipeline.create<dai::node::XLinkOut>();

    // name inputs and outputs
    xoutPreview->setStreamName("preview");

    // node properties
    cam->setPreviewSize(width, height);
    cam->setBoardSocket(dai::CameraBoardSocket::CAM_A);
    cam->setResolution(dai::ColorCameraProperties::SensorResolution::THE_1080_P);
    cam->setInterleaved(false);
    cam->setColorOrder(dai::ColorCameraProperties::ColorOrder::RGB);

    // linking 
    cam->preview.link(xoutPreview->input);


    return std::make_tuple(pipeline, width, height);
}

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("stereo_inertial_node");

    bool isDeviceFound = false;

    // TODO: move parameters into launch file / cfg file
    int previewWidth = 300;
    int previewHeight = 300;

    dai::Pipeline pipeline;
    int width, height;

    std::tie(pipeline, width, height) = createPipeline(); 

    // TODO: change single pointer to a vector for multiple OAK-D's
    std::shared_ptr<dai::Device> device;
    std::vector<dai::DeviceInfo> availableDevices = dai::Device::getAllAvailableDevices();

    std::cout << "Listening for devices" << std::endl;

    // bind device based on MxID
    for (auto deviceInfo: availableDevices) {
        std::cout << "Device Mx ID:" << deviceInfo.getMxId() << std::endl;

        // TODO: change for specific deviceID  
        if (deviceInfo.state == X_LINK_UNBOOTED || deviceInfo.state == X_LINK_BOOTLOADER) {
            isDeviceFound = true;
            device = std::make_shared<dai::Device>(pipeline, deviceInfo);
        } else {
            throw std::runtime_error("DepthAI already booted");
        }
    }

    if (!isDeviceFound) {
        throw std::runtime_error("Device not found");
    }
    auto calibrationHandler = device->readCalibration();

    dai::rosBridge::ImageConverter rgbConverter("oak_camera_optical_frame", true);

    auto previewQueue = device->getOutputQueue("xoutPreview", 30, false);
    auto previewCameraInfo = rgbConverter.calibrationToCameraInfo(calibrationHandler, dai::CameraBoardSocket::CAM_A, previewWidth, previewHeight);

    dai::rosBridge::BridgePublisher<sensor_msgs::msg::Image, dai::ImgFrame> previewPublish(
        previewQueue,
        node,
        std::string("color/preview/image"),
        std::bind(&dai::rosBridge::ImageConverter::toRosMsg, &rgbConverter, std::placeholders::_1, std::placeholders::_2),
        30,
        previewCameraInfo,
        "color/preview");

    previewPublish.addPublisherCallback();

    rclcpp::spin(node);
    return 0;
}