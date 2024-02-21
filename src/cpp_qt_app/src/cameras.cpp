#include "cameras.h"
#include "ui_cameras.h"

Cameras::Cameras(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Cameras)
{
    ui->setupUi(this);

    conversion_matrix.release();
    subscriber.shutdown();

    image_transport::ImageTransport it(getNodeHandle());

    ui_.image_frame->setImage(QImage());

    try {
        subscriber = it.subscribe()
    }


    // std::cout << "here" << std::endl;
    // std::thread capRunTh(captureRun, ui->label_cam1, ui->pushButton_capture);
    // capRunTh.detach();
}

Cameras::~Cameras()
{
    subscriber.shutdown();
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

void Cameras::captureRun(QLabel *label, QPushButton *btn)
{
    cv::VideoCapture cap(0);
    cv::Mat frame;

    if (!cap.isOpened()) {
        std::runtime_error("Cam not available");
    }


    while(true) {
        cap >> frame;
        cv::resize(frame, frame, cv::Size(640, 480));

        cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);

        QPixmap pix = QPixmap::fromImage(QImage((unsigned char*) frame.data, frame.cols, frame.rows, QImage::Format_RGB888));
        label->setPixmap(pix);
    }

}

void Cameras::imageCallback(const sensor_msgs::msg::Image::ConstSharedPtr & msg)
{
    try {
        cv_bridge::CvImageConstPtr cvPtr = cv_bridge::toCvShare(msg, sensor_msgs::image_encodings::RGB8);
        conversion_matrix = cvPtr->image;
    } catch (cv_bridge::Exception& e) {
        // TODO: Properly display error in Qt / ROS2
        std::cerr << "Cannot convert image:" << e.what() << std::endl;
    }

    QImage image(conversion_matrix.data, conversion_matrix.cols, conversion_matrix.rows, conversion_matrix.step[0], QImage::Format_RGB888);


}