#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (conectSerial()) qDebug() << "Conectado";
    else qDebug() << "Erro en la conexión serial";
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::conectSerial(){
    serial.setPortName(portName);

    if (serial.open(QIODevice::ReadWrite)){
        serial.setBaudRate(QSerialPort::Baud9600);
        return true;
    }
    return false;

}


void MainWindow::sendData(){

    char data = 'a';
    serial.write(&data);

    readData();

}


void MainWindow::readData(){
    QThread::msleep(200);
    if (serial.waitForReadyRead(200)){
        QByteArray data = serial.readAll();
        qDebug() << data;
    }
}


void MainWindow::on_btnUp_clicked(bool checked)
{
    // qDebug()<< checked;
}


void MainWindow::on_btnDown_pressed()
{
    qDebug() << "Pressed";
    sendData();
}


void MainWindow::on_btnUp_toggled(bool checked)
{
    qDebug() << checked;
}

