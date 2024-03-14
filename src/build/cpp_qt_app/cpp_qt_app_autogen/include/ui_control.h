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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Control
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QStackedWidget *stackedWidget;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    QGridLayout *controler;
    QPushButton *pushButton_left;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_rotleft;
    QPushButton *pushButton_forward;
    QPushButton *pushButton_right;
    QPushButton *pushButton_rotright;
    QPushButton *pushButton_backwards;
    QLabel *label_con;
    QHBoxLayout *menu;
    QPushButton *pushButton_home;
    QPushButton *pushButton_cameras;
    QPushButton *pushButton_settings;

    void setupUi(QMainWindow *Control)
    {
        if (Control->objectName().isEmpty())
            Control->setObjectName(QString::fromUtf8("Control"));
        Control->resize(800, 480);
        centralwidget = new QWidget(Control);
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
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        controler = new QGridLayout();
        controler->setObjectName(QString::fromUtf8("controler"));
        pushButton_left = new QPushButton(page_2);
        pushButton_left->setObjectName(QString::fromUtf8("pushButton_left"));

        controler->addWidget(pushButton_left, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        controler->addItem(horizontalSpacer_2, 1, 4, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        controler->addItem(horizontalSpacer, 1, 0, 1, 1);

        pushButton_rotleft = new QPushButton(page_2);
        pushButton_rotleft->setObjectName(QString::fromUtf8("pushButton_rotleft"));

        controler->addWidget(pushButton_rotleft, 0, 1, 1, 1);

        pushButton_forward = new QPushButton(page_2);
        pushButton_forward->setObjectName(QString::fromUtf8("pushButton_forward"));

        controler->addWidget(pushButton_forward, 0, 2, 1, 1);

        pushButton_right = new QPushButton(page_2);
        pushButton_right->setObjectName(QString::fromUtf8("pushButton_right"));

        controler->addWidget(pushButton_right, 1, 3, 1, 1);

        pushButton_rotright = new QPushButton(page_2);
        pushButton_rotright->setObjectName(QString::fromUtf8("pushButton_rotright"));

        controler->addWidget(pushButton_rotright, 0, 3, 1, 1);

        pushButton_backwards = new QPushButton(page_2);
        pushButton_backwards->setObjectName(QString::fromUtf8("pushButton_backwards"));

        controler->addWidget(pushButton_backwards, 2, 2, 1, 1);

        label_con = new QLabel(page_2);
        label_con->setObjectName(QString::fromUtf8("label_con"));
        label_con->setStyleSheet(QString::fromUtf8("font: 10pt \"Sans Serif\";\n"
"qproperty-alignment: AlignCenter;"));

        controler->addWidget(label_con, 1, 2, 1, 1);


        gridLayout->addLayout(controler, 0, 0, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        menu = new QHBoxLayout();
        menu->setObjectName(QString::fromUtf8("menu"));
        pushButton_home = new QPushButton(page_2);
        pushButton_home->setObjectName(QString::fromUtf8("pushButton_home"));

        menu->addWidget(pushButton_home, 0, Qt::AlignBottom);

        pushButton_cameras = new QPushButton(page_2);
        pushButton_cameras->setObjectName(QString::fromUtf8("pushButton_cameras"));

        menu->addWidget(pushButton_cameras, 0, Qt::AlignBottom);

        pushButton_settings = new QPushButton(page_2);
        pushButton_settings->setObjectName(QString::fromUtf8("pushButton_settings"));

        menu->addWidget(pushButton_settings, 0, Qt::AlignBottom);


        verticalLayout_2->addLayout(menu);

        stackedWidget->addWidget(page_2);

        verticalLayout->addWidget(stackedWidget);

        Control->setCentralWidget(centralwidget);

        retranslateUi(Control);

        QMetaObject::connectSlotsByName(Control);
    } // setupUi

    void retranslateUi(QMainWindow *Control)
    {
        Control->setWindowTitle(QCoreApplication::translate("Control", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("Control", "Control", nullptr));
        pushButton_left->setText(QCoreApplication::translate("Control", "left", nullptr));
        pushButton_rotleft->setText(QCoreApplication::translate("Control", "rot left", nullptr));
        pushButton_forward->setText(QCoreApplication::translate("Control", "forward", nullptr));
        pushButton_right->setText(QCoreApplication::translate("Control", "right", nullptr));
        pushButton_rotright->setText(QCoreApplication::translate("Control", "rot right", nullptr));
        pushButton_backwards->setText(QCoreApplication::translate("Control", "backwards", nullptr));
        label_con->setText(QCoreApplication::translate("Control", "Controler", nullptr));
        pushButton_home->setText(QCoreApplication::translate("Control", "Home", nullptr));
        pushButton_cameras->setText(QCoreApplication::translate("Control", "Cameras", nullptr));
        pushButton_settings->setText(QCoreApplication::translate("Control", "Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Control: public Ui_Control {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROL_H
