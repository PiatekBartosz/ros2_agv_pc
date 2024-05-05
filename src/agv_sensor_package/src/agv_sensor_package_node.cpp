#include "rclcpp/rclcpp.hpp"
#include "oak_d_publisher.hpp"

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto node = rclcpp::Node::make_shared("oak_d_publisher");

    // run Node
    OakDPublisher oakdPublisherNode(node);
    oakdPublisherNode.spin();

    rclcpp::shutdown();
    return 0;
}