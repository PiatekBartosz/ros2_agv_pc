#include "image_receiver.h"

ImageReceiver::ImageReceiver(QObject *parent) : QObject(parent) {

}

ImageReceiver::imageCallback(const sensor_msgs::msg::Image::SharedPtr msg) {
    try {
        cv_bridge::CvImageConstPtr cvPtr = cv_bridge::toCvShare(msg, sensor_msgs::image_encodings::RGB8);
        // emit OnReceiveImage(img);

    } catch (cv_bridge::Exception& e) {
        std::cerr << "Cannot convert image" << e.what() << std::endl;
    }
}