#include "cameras.h"
#include "ui_cameras.h"

Cameras::Cameras(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Cameras)
{
    ui->setupUi(this);

    // conversion_matrix.release();
    // subscriber.shutdown();

    // rclcpp::init(0, nullptr);
    // auto node = rclcpp::Node::make_shared("image_listener");
    // image_transport::ImageTransport imageTransport(node);
    // subscriber = imageTransport.subscribe("/color/preview/image", 1, &imageCallback);
    // rclcpp::spin(node);
}

Cameras::~Cameras()
{
    // subscriber.shutdown();
    delete ui;
}

void Cameras::on_pushButton_settings_clicked()
{
    emit SettingsClicked();
}


void Cameras::on_pushButton_control_clicked()
{
    emit ControlClicked();
}

void Cameras::on_pushButton_capture_clicked()
{
    emit CaptureClicked();
}

void Cameras::on_pushButton_home_clicked()
{
    emit HomeClicked();
}

// void Cameras::captureRun(QLabel *label, QPushButton *btn)
// {
//     cv::VideoCapture cap(0);
//     cv::Mat frame;

//     if (!cap.isOpened()) {
//         std::runtime_error("Cam not available");
//     }


//     while(true) {
//         cap >> frame;
//         cv::resize(frame, frame, cv::Size(640, 480));

//         cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);

//         QPixmap pix = QPixmap::fromImage(QImage((unsigned char*) frame.data, frame.cols, frame.rows, QImage::Format_RGB888));
//         label_cam1->setPixmap(pix);
//     }

// }