#include "cameras.h"
#include "ui_cameras.h"

Cameras::Cameras(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Cameras)
{
    ui->setupUi(this);
}

Cameras::~Cameras()
{
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

void Cameras::on_pushButton_home_clicked()
{
    emit HomeClicked();
}

