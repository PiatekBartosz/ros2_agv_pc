/********************************************************************************
** Form generated from reading UI file 'control.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROL_H
#define UI_CONTROL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Control
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page_2;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_settings;
    QPushButton *pushButton_home;
    QPushButton *pushButton_cameras;
    QLabel *label;

    void setupUi(QMainWindow *Control)
    {
        if (Control->objectName().isEmpty())
            Control->setObjectName(QString::fromUtf8("Control"));
        Control->resize(800, 480);
        centralwidget = new QWidget(Control);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(9, 9, 781, 461));
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        horizontalLayoutWidget = new QWidget(page_2);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 410, 781, 51));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_settings = new QPushButton(horizontalLayoutWidget);
        pushButton_settings->setObjectName(QString::fromUtf8("pushButton_settings"));

        horizontalLayout->addWidget(pushButton_settings);

        pushButton_home = new QPushButton(horizontalLayoutWidget);
        pushButton_home->setObjectName(QString::fromUtf8("pushButton_home"));

        horizontalLayout->addWidget(pushButton_home);

        pushButton_cameras = new QPushButton(horizontalLayoutWidget);
        pushButton_cameras->setObjectName(QString::fromUtf8("pushButton_cameras"));

        horizontalLayout->addWidget(pushButton_cameras);

        label = new QLabel(page_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(310, 170, 67, 21));
        stackedWidget->addWidget(page_2);
        Control->setCentralWidget(centralwidget);

        retranslateUi(Control);

        QMetaObject::connectSlotsByName(Control);
    } // setupUi

    void retranslateUi(QMainWindow *Control)
    {
        Control->setWindowTitle(QCoreApplication::translate("Control", "MainWindow", nullptr));
        pushButton_settings->setText(QCoreApplication::translate("Control", "Settings", nullptr));
        pushButton_home->setText(QCoreApplication::translate("Control", "Home", nullptr));
        pushButton_cameras->setText(QCoreApplication::translate("Control", "Cameras", nullptr));
        label->setText(QCoreApplication::translate("Control", "Control", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Control: public Ui_Control {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROL_H
