#include <sstream>

#include "rclcpp/rclcpp.hpp"
#include "cv_bridge/cv_bridge.h"
#include "image_transport/image_transport.hpp"
#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "std_msgs/msg/header.hpp"

int main(int argc, char ** argv) {
    if (argv[1] == NULL) {
        std::cout << "Provide camera number" << std::endl;
    }

    rclcpp::init(argc, argv);
    rclcpp::NodeOptions options;
    rclcpp::Node::SharedPtr node = rclcpp::Node::make_shared("cpp_demo_pub", options);

    image_transport::ImageTransport it(node);
    image_transport::Publisher pub = it.advertise("webcam/image", options);

    std::istringstream video_sourceCmd(argv[1]);
    int video_source;

    if(!(video_sourceCmd >> video_source)) {
        std::cout << "Invalid camera number" << std::endl;
        return 1;
    }

    cv::VideoCapture cap(video_source);

    if (!cap.isOpened()) {
        std::cout << "Error opening video stream" << std::endl;
        return 1;
    }

    cv::Mat frame;
    std::msgs:msg::Header header;
    sensor_msgs::msg::Image::SharedPtr msg;

    rclcpp::WallRate loop_rate(5);

    while (rclcpp::ok()) {
        cap >> frame;
        if (!frame.empty()) {
            msg = cv_bridge::CvImage(header, "bgr8", frame).toImageMsg();
    }

    return 0;
}