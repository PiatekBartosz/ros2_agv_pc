#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Settings)
{
    ui->setupUi(this);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_pushButton_home_clicked()
{
    emit HomeClicked();
}


void Settings::on_pushButton_control_clicked()
{
    emit ControlClicked();
}


void Settings::on_pushButton_cameras_clicked()
{
    emit CamerasClicked();
}

