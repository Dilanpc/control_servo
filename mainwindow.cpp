#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (connectSerial()) qDebug() << "Conectado";
    else qDebug() << "Error en la conexión serial";

    // Configurar el temporizador para llamar a updateAngle() cada segundo
    angleTimer = new QTimer(this);
    connect(angleTimer, &QTimer::timeout, this, &MainWindow::updateAngle);
    angleTimer->start(50);


    // Configurar el temporizador para llamar a readData() cada segundo
    readDataTimer = new QTimer(this);
    connect(readDataTimer, &QTimer::timeout, this, &MainWindow::readData);
    readDataTimer->start(500);

    // Configurar el temporizador para llamar a sendData() cada segundo
    sendDataTimer = new QTimer(this);
    connect(sendDataTimer, &QTimer::timeout, this, &MainWindow::sendData);
    sendDataTimer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}



// SERIAL CONNECTION

bool MainWindow::connectSerial(){
    serial.setPortName(portName);

    if (serial.open(QIODevice::ReadWrite)){
        serial.setBaudRate(QSerialPort::Baud9600);
        return true;
    }
    return false;
}


void MainWindow::sendData(){
    QString str = '@' + QString("%1").arg(angle, 3, 10, QLatin1Char('0'));
    // se envian 4 bytes
    QByteArray data = str.toUtf8();

    serial.write(data);
}


void MainWindow::readData(){

    if (serial.bytesAvailable() >= 4){
        QByteArray data = serial.readAll();
        qDebug() << "recibido: " << data;
    }
}



// ANGLE

void MainWindow::updateAngle(){
    if (pressingDown || pressingUp){
        sendData();
        if(pressingUp) angle++;
        else angle --;

        if (angle < 0) angle = 0;
        if (angle > 180) angle = 180;

        ui->angleTxt->setText(QString::number(angle));
    }




}





// BUTTONS

void MainWindow::on_btnDown_pressed()
{
    pressingDown = true;
}
void MainWindow::on_btnDown_released()
{
    pressingDown = false;

}
void MainWindow::on_btnUp_pressed()
{
    pressingUp = true;
}
void MainWindow::on_btnUp_released()
{
    pressingUp = false;
}




void MainWindow::on_angleTxt_editingFinished()
{
    angle = ui->angleTxt->text().toInt();
    if (angle < 0) angle = 0;
    if (angle > 180) angle = 180;

    ui->angleTxt->setText(QString::number(angle));

    sendData();
}

