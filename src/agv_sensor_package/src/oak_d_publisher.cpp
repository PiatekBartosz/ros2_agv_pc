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

std::tuple<dai::Pipeline, int, int> createPipeline(int previewWidth,
                                                    int previewHeight) {
    dai::Pipeline pipeline;

    // TODO: resolution options from cfg
    auto camRgbResolution= dai::ColorCameraProperties::SensorResolution::THE_1080_P;
    int width = 1920;
    int height = 1080;


    // create nodes
    auto camRgb = pipeline.create<dai::node::ColorCamera>();
    auto xoutRgb = pipeline.create<dai::node::XLinkOut>();

    // name inputs and outputs
    xoutRgb->setStreamName("rgb");

    // node properties
    // cam->setPreviewSize(width, height);
    camRgb->setBoardSocket(dai::CameraBoardSocket::CAM_A);
    camRgb->setResolution(camRgbResolution);
    camRgb->setInterleaved(false);
    camRgb->setColorOrder(dai::ColorCameraProperties::ColorOrder::RGB);
    camRgb->setPreviewSize(previewWidth, previewHeight);

    // linking 
    camRgb->preview.link(xoutRgb->input);

    return std::make_tuple(pipeline, width, height);
}

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("stereo_inertial_node");

    // bool isDeviceFound = false;

    // TODO: move parameters into launch file / cfg file
    int previewWidth = 300;
    int previewHeight = 300;

    dai::Pipeline pipeline;
    int width, height;

    std::tie(pipeline, width, height) = createPipeline(previewWidth, previewHeight); 

    dai::Device device(pipeline);

    auto previewQueue = device.getOutputQueue("preview", 30, false);

    auto calibrationHandler = device.readCalibration();

    std::unique_ptr<dai::rosBridge::BridgePublisher<sensor_msgs::msg::Image, dai::ImgFrame>> rgbPreviewPublish;

    dai::rosBridge::ImageConverter rgbConverter("oak_rgb_camera_optical_frame", true);

    auto previewCameraInfo = rgbConverter.calibrationToCameraInfo(calibrationHandler, 
                                        dai::CameraBoardSocket::CAM_A, previewWidth, previewHeight);

    rgbPreviewPublish = std::make_unique<dai::rosBridge::BridgePublisher<sensor_msgs::msg::Image, dai::ImgFrame>(
        previewQueue,
        node,
        std::string("color/preview/image"),
        std::bind(&dai::rosBridge::ImageConverter::toRosMsg,
                &rgbConverter,
                std::placeholders::_1,
                std::placeholders::_2,
                30,
                previewCameraInfo,
                "color/preview");

    )

    rgbPreviewPublish->addPublisherCallback();

    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}