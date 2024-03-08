/********************************************************************************
** Form generated from reading UI file 'cameras.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERAS_H
#define UI_CAMERAS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Cameras
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_cam1;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_settings;
    QPushButton *pushButton_control;
    QPushButton *pushButton_home;
    QPushButton *pushButton_capture;

    void setupUi(QMainWindow *Cameras)
    {
        if (Cameras->objectName().isEmpty())
            Cameras->setObjectName(QString::fromUtf8("Cameras"));
        Cameras->resize(800, 480);
        centralwidget = new QWidget(Cameras);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        verticalLayout_2 = new QVBoxLayout(page);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(page);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("font: 16pt \"Sans Serif\";\n"
"qproperty-alignment: AlignCenter;"));

        verticalLayout_2->addWidget(label);

        widget = new QWidget(page);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_cam1 = new QLabel(widget);
        label_cam1->setObjectName(QString::fromUtf8("label_cam1"));

        horizontalLayout_2->addWidget(label_cam1);


        verticalLayout_2->addWidget(widget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_settings = new QPushButton(page);
        pushButton_settings->setObjectName(QString::fromUtf8("pushButton_settings"));

        horizontalLayout->addWidget(pushButton_settings);

        pushButton_control = new QPushButton(page);
        pushButton_control->setObjectName(QString::fromUtf8("pushButton_control"));

        horizontalLayout->addWidget(pushButton_control);

        pushButton_home = new QPushButton(page);
        pushButton_home->setObjectName(QString::fromUtf8("pushButton_home"));

        horizontalLayout->addWidget(pushButton_home);

        pushButton_capture = new QPushButton(page);
        pushButton_capture->setObjectName(QString::fromUtf8("pushButton_capture"));

        horizontalLayout->addWidget(pushButton_capture);


        verticalLayout_2->addLayout(horizontalLayout);

        stackedWidget->addWidget(page);

        verticalLayout->addWidget(stackedWidget);

        Cameras->setCentralWidget(centralwidget);

        retranslateUi(Cameras);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Cameras);
    } // setupUi

    void retranslateUi(QMainWindow *Cameras)
    {
        Cameras->setWindowTitle(QCoreApplication::translate("Cameras", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("Cameras", "Cameras", nullptr));
#if QT_CONFIG(whatsthis)
        widget->setWhatsThis(QCoreApplication::translate("Cameras", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        label_cam1->setText(QCoreApplication::translate("Cameras", "TextLabel", nullptr));
        pushButton_settings->setText(QCoreApplication::translate("Cameras", "Settings", nullptr));
        pushButton_control->setText(QCoreApplication::translate("Cameras", "Control", nullptr));
        pushButton_home->setText(QCoreApplication::translate("Cameras", "Home", nullptr));
        pushButton_capture->setText(QCoreApplication::translate("Cameras", "Capture", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Cameras: public Ui_Cameras {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERAS_H
