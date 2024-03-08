#ifndef SETTINGS_H
#define SETTINGS_H

#include <QMainWindow>

namespace Ui {
class Settings;
}

class Settings : public QMainWindow
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

private:
    Ui::Settings *ui;

signals:
    void HomeClicked();
    void ControlClicked();
    void CamerasClicked();

private slots:
    void on_pushButton_home_clicked();
    void on_pushButton_control_clicked();
    void on_pushButton_cameras_clicked();
};

#endif // SETTINGS_H
