#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ImageReceiver imageReceiver;

    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("qt_subscriber");

    auto callbackGroup = node->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
    // auto subscriber = node->create_subscription<sensor_msgs::msg::Image>(
    //     "/color/preview/image",
    //     std::bind(&ImageReceiver::imageCallback, &imageReceiver, std::placeholders::_1),
    //     rmw_qos_profile_sensor_data, 
    //     callbackGroup
    // );

    MainWindow w;
    w.show();
    return a.exec();
}
