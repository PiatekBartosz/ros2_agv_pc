#ifndef CAMERAS_H
#define CAMERAS_H

#include <QMainWindow>

namespace Ui {
class Cameras;
}

class Cameras : public QMainWindow
{
    Q_OBJECT

public:
    explicit Cameras(QWidget *parent = nullptr);
    ~Cameras();

private slots:

    void on_pushButton_settings_clicked();

    void on_pushButton_control_clicked();

    void on_pushButton_home_clicked();

signals:
    void HomeClicked();
    void ControlClicked();
    void SettingsClicked();

private:
    Ui::Cameras *ui;
};

#endif // CAMERAS_H
