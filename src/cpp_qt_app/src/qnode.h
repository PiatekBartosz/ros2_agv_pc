#ifndef QNODE_H
#define QNODE_H

#include <QThread>
#include <rclcpp/rclcpp.hpp>


class QNode: public QThread {
    Q_OBJECT

public:
    QNode();
    virtual ~QNode();
    bool init();
    void run();

signals:
    void msgSubscribed();

private:
    rclcpp::Node::SharedPtr rosNode;

};

#endif //QNODE_H