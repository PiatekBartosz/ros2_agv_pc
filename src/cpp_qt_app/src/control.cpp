#include "control.h"
#include "ui_control.h"

Control::Control(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Control)
{
    ui->setupUi(this);
}

Control::~Control()
{
    delete ui;
}

void Control::on_pushButton_settings_clicked()
{
    emit SettingsClicked();
}


void Control::on_pushButton_home_clicked()
{
    emit HomeClicked();
}


void Control::on_pushButton_cameras_clicked()
{
    emit CamerasClicked();
}

