#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    // ui->setupUi(this);
    // // connect the button to the slot
    // connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
}

// MainWindow::~MainWindow() {
//     delete ui;
// }

// void MainWindow::updateTopicInfo(QString &text) {
//     ui->label_4->clear();
//     ui->label_4->setText(text);
// }
