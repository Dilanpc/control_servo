#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QDebug>
#include <QThread>
#include <QTimer>

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

protected:
    QSerialPort serial;
    const QString portName = "COM3";

    int angle = 90;
    void updateAngle();
    QTimer* angleTimer;

    bool pressingDown = false;
    bool pressingUp = false;

    QTimer* readDataTimer;
    QTimer* sendDataTimer;

    void sendData();

    void readData();

    bool connectSerial();



private slots:

    void on_btnDown_pressed();


    void on_btnDown_released();

    void on_btnUp_pressed();

    void on_btnUp_released();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
