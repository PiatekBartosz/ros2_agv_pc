/********************************************************************************
** Form generated from reading UI file 'settings.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Settings
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page_2;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_home;
    QPushButton *pushButton_control;
    QPushButton *pushButton_cameras;
    QLabel *label;

    void setupUi(QMainWindow *Settings)
    {
        if (Settings->objectName().isEmpty())
            Settings->setObjectName(QString::fromUtf8("Settings"));
        Settings->resize(800, 480);
        centralwidget = new QWidget(Settings);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(10, -20, 781, 491));
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        horizontalLayoutWidget = new QWidget(page_2);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 440, 781, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_home = new QPushButton(horizontalLayoutWidget);
        pushButton_home->setObjectName(QString::fromUtf8("pushButton_home"));

        horizontalLayout->addWidget(pushButton_home);

        pushButton_control = new QPushButton(horizontalLayoutWidget);
        pushButton_control->setObjectName(QString::fromUtf8("pushButton_control"));

        horizontalLayout->addWidget(pushButton_control);

        pushButton_cameras = new QPushButton(horizontalLayoutWidget);
        pushButton_cameras->setObjectName(QString::fromUtf8("pushButton_cameras"));

        horizontalLayout->addWidget(pushButton_cameras);

        label = new QLabel(page_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(300, 150, 67, 21));
        stackedWidget->addWidget(page_2);
        Settings->setCentralWidget(centralwidget);

        retranslateUi(Settings);

        QMetaObject::connectSlotsByName(Settings);
    } // setupUi

    void retranslateUi(QMainWindow *Settings)
    {
        Settings->setWindowTitle(QCoreApplication::translate("Settings", "MainWindow", nullptr));
        pushButton_home->setText(QCoreApplication::translate("Settings", "Home", nullptr));
        pushButton_control->setText(QCoreApplication::translate("Settings", "Control", nullptr));
        pushButton_cameras->setText(QCoreApplication::translate("Settings", "Cameras", nullptr));
        label->setText(QCoreApplication::translate("Settings", "Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Settings: public Ui_Settings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_H
