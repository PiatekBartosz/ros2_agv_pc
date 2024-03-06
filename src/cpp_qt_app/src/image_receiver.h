#ifndef IMAGE_RECEIVER_H
#define IMAGE_RECEIVER_H

#include <QObject>
#include <QImage>

#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>


class ImageReceiver : public QObject
{
    Q_OBJECT
public:
    explicit ImageReceiver(QObject *parent = nullptr);

public:
    void imageCallback(const sensor_msgs::msg::Image::SharedPtr msg);

signals:
    void OnReceiveImage(QImage image);
};

#endif // IMAGE_RECEIVER_H