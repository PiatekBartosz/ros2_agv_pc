#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->insertWidget(1, &Set);
    ui->stackedWidget->insertWidget(2, &Ctrl);
    ui->stackedWidget->insertWidget(3, &Cam);

    connect(&Set, SIGNAL(HomeClicked()), this, SLOT(moveHome()));
    connect(&Set, SIGNAL(ControlClicked()), this, SLOT(moveControl()));
    connect(&Set, SIGNAL(CamerasClicked()), this, SLOT(moveCameras()));

    connect(&Ctrl, SIGNAL(SettingsClicked()), this, SLOT(moveSettings()));
    connect(&Ctrl, SIGNAL(HomeClicked()), this, SLOT(moveHome()));
    connect(&Ctrl, SIGNAL(CamerasClicked()), this, SLOT(moveCameras()));

    connect(&Cam, SIGNAL(SettingsClicked()), this, SLOT(moveSettings()));
    connect(&Cam, SIGNAL(ControlClicked()), this, SLOT(moveControl()));
    connect(&Cam, SIGNAL(HomeClicked()), this, SLOT(moveHome()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_close_clicked()
{
    this->close();
}


void MainWindow::on_pushButton_settings_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_control_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_pushButton_cameras_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::moveHome()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::moveSettings()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::moveControl()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::moveCameras()
{
    ui->stackedWidget->setCurrentIndex(3);
}

