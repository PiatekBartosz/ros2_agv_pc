/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QPushButton *pushButton_control;
    QLabel *label_menu;
    QPushButton *pushButton_settings;
    QLabel *label_logo;
    QPushButton *pushButton_close;
    QPushButton *pushButton_cameras;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 480);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        horizontalLayout = new QHBoxLayout(page);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton_control = new QPushButton(page);
        pushButton_control->setObjectName(QString::fromUtf8("pushButton_control"));

        gridLayout->addWidget(pushButton_control, 8, 0, 1, 1);

        label_menu = new QLabel(page);
        label_menu->setObjectName(QString::fromUtf8("label_menu"));
        label_menu->setStyleSheet(QString::fromUtf8("font: 16pt \"Sans Serif\";\n"
"qproperty-alignment: AlignCenter;\n"
""));

        gridLayout->addWidget(label_menu, 0, 0, 1, 4);

        pushButton_settings = new QPushButton(page);
        pushButton_settings->setObjectName(QString::fromUtf8("pushButton_settings"));

        gridLayout->addWidget(pushButton_settings, 8, 1, 1, 1);

        label_logo = new QLabel(page);
        label_logo->setObjectName(QString::fromUtf8("label_logo"));
        label_logo->setStyleSheet(QString::fromUtf8("qproperty-alignment: AlignCenter;\n"
"image: url(:/logo.png);"));

        gridLayout->addWidget(label_logo, 1, 1, 7, 2);

        pushButton_close = new QPushButton(page);
        pushButton_close->setObjectName(QString::fromUtf8("pushButton_close"));

        gridLayout->addWidget(pushButton_close, 8, 3, 1, 1);

        pushButton_cameras = new QPushButton(page);
        pushButton_cameras->setObjectName(QString::fromUtf8("pushButton_cameras"));

        gridLayout->addWidget(pushButton_cameras, 8, 2, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        stackedWidget->addWidget(page);

        verticalLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_control->setText(QCoreApplication::translate("MainWindow", "Control", nullptr));
        label_menu->setText(QCoreApplication::translate("MainWindow", "MENU", nullptr));
        pushButton_settings->setText(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        label_logo->setText(QString());
        pushButton_close->setText(QCoreApplication::translate("MainWindow", "Close Application", nullptr));
        pushButton_cameras->setText(QCoreApplication::translate("MainWindow", "Cameras", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
