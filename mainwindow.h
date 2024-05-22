#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QDebug>
#include <QThread>

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

    void sendData();

    void readData();

    bool conectSerial();


private slots:
    void on_btnUp_clicked(bool checked);

    void on_btnDown_pressed();

    void on_btnUp_toggled(bool checked);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
