#include "qnode.h"
#include <string>

QNode::QNode() {
    auto subscription_options = rclcpp::SubscriptionOptions();
}

QNode::~QNode(){
    rclcpp::shutdown();
}

bool QNode::init() {
    rclcpp::init(0, nullptr);
    return true;

}

void QNode::run() {
}
