#ifndef CAMERAS_H
#define CAMERAS_H

#include <QMainWindow>
#include <QLabel>
#include <QFileDialog>
#include <thread>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.hpp>
#include <image_transport/subscriber.hpp>

#include <sensor_msgs/msg/image.hpp>


namespace Ui {
class Cameras;
}

class Cameras : public QMainWindow {
    Q_OBJECT

public:
    explicit Cameras(QWidget *parent = nullptr);
    ~Cameras();

private slots:

    void on_pushButton_settings_clicked();

    void on_pushButton_control_clicked();

    void on_pushButton_home_clicked();

    // static void captureRun(QLabel *label, QPushButton *btn);

    void on_pushButton_capture_clicked();


signals:
    void HomeClicked();
    void ControlClicked();
    void SettingsClicked();
    void CaptureClicked();

private:
    Ui::Cameras *ui;
};

#endif // CAMERAS_H
