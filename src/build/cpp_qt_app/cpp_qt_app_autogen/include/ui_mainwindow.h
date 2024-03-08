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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_settings;
    QPushButton *pushButton_control;
    QPushButton *pushButton_cameras;
    QPushButton *pushButton_close;
    QLabel *label;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 480);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(9, 9, 781, 461));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        horizontalLayoutWidget = new QWidget(page);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 420, 781, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_settings = new QPushButton(horizontalLayoutWidget);
        pushButton_settings->setObjectName(QString::fromUtf8("pushButton_settings"));

        horizontalLayout->addWidget(pushButton_settings);

        pushButton_control = new QPushButton(horizontalLayoutWidget);
        pushButton_control->setObjectName(QString::fromUtf8("pushButton_control"));

        horizontalLayout->addWidget(pushButton_control);

        pushButton_cameras = new QPushButton(horizontalLayoutWidget);
        pushButton_cameras->setObjectName(QString::fromUtf8("pushButton_cameras"));

        horizontalLayout->addWidget(pushButton_cameras);

        pushButton_close = new QPushButton(horizontalLayoutWidget);
        pushButton_close->setObjectName(QString::fromUtf8("pushButton_close"));

        horizontalLayout->addWidget(pushButton_close);

        label = new QLabel(page);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(310, 90, 67, 21));
        stackedWidget->addWidget(page);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_settings->setText(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        pushButton_control->setText(QCoreApplication::translate("MainWindow", "Control", nullptr));
        pushButton_cameras->setText(QCoreApplication::translate("MainWindow", "Cameras", nullptr));
        pushButton_close->setText(QCoreApplication::translate("MainWindow", "Close Application", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "MENU", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
