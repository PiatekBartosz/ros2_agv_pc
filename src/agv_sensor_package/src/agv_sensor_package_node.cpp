#include "rclcpp/rclcpp.hpp"
#include "oak_d_publisher.hpp"
#include "yaml-cpp/yaml.h"

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto node = rclcpp::Node::make_shared("oak_d_publisher");

    // auto stereoParams = YAML::LoadFile("/workspaces/ros_agv_pc/src/agv_sensor_package/config/oak_d_publisher_param.yaml");

    // run Node
    OakDPublisher oakdPublisherNode(node);
    oakdPublisherNode.spin();

    rclcpp::shutdown();
    return 0;
}