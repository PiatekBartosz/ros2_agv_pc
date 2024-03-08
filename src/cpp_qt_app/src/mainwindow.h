#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settings.h"
#include "control.h"
#include "cameras.h"
#include "QLabel"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_close_clicked();

    void on_pushButton_settings_clicked();

    void on_pushButton_control_clicked();

    void on_pushButton_cameras_clicked();

    void moveHome();

    void moveSettings();

    void moveControl();

    void moveCameras();

private:
    Ui::MainWindow *ui;
    Settings Set;
    Control Ctrl;
    Cameras Cam;
};
#endif // MAINWINDOW_H
