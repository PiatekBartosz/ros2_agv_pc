#ifndef CONTROL_H
#define CONTROL_H

#include <QMainWindow>

namespace Ui {
class Control;
}

class Control : public QMainWindow
{
    Q_OBJECT

public:
    explicit Control(QWidget *parent = nullptr);
    ~Control();

private slots:
    void on_pushButton_settings_clicked();

    void on_pushButton_home_clicked();

    void on_pushButton_cameras_clicked();

signals:
    void SettingsClicked();
    void HomeClicked();
    void CamerasClicked();

private:
    Ui::Control *ui;
};

#endif // CONTROL_H
