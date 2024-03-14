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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Settings
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QStackedWidget *stackedWidget;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_home;
    QPushButton *pushButton_control;
    QPushButton *pushButton_cameras;

    void setupUi(QMainWindow *Settings)
    {
        if (Settings->objectName().isEmpty())
            Settings->setObjectName(QString::fromUtf8("Settings"));
        Settings->resize(800, 480);
        centralwidget = new QWidget(Settings);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("font: 16pt \"Sans Serif\";\n"
"qproperty-alignment: AlignCenter;"));

        verticalLayout->addWidget(label);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        verticalLayout_2 = new QVBoxLayout(page_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_home = new QPushButton(page_2);
        pushButton_home->setObjectName(QString::fromUtf8("pushButton_home"));

        horizontalLayout->addWidget(pushButton_home);

        pushButton_control = new QPushButton(page_2);
        pushButton_control->setObjectName(QString::fromUtf8("pushButton_control"));

        horizontalLayout->addWidget(pushButton_control);

        pushButton_cameras = new QPushButton(page_2);
        pushButton_cameras->setObjectName(QString::fromUtf8("pushButton_cameras"));

        horizontalLayout->addWidget(pushButton_cameras);


        verticalLayout_2->addLayout(horizontalLayout);

        stackedWidget->addWidget(page_2);

        verticalLayout->addWidget(stackedWidget);

        Settings->setCentralWidget(centralwidget);

        retranslateUi(Settings);

        QMetaObject::connectSlotsByName(Settings);
    } // setupUi

    void retranslateUi(QMainWindow *Settings)
    {
        Settings->setWindowTitle(QCoreApplication::translate("Settings", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("Settings", "Settings", nullptr));
        pushButton_home->setText(QCoreApplication::translate("Settings", "Home", nullptr));
        pushButton_control->setText(QCoreApplication::translate("Settings", "Control", nullptr));
        pushButton_cameras->setText(QCoreApplication::translate("Settings", "Cameras", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Settings: public Ui_Settings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_H
