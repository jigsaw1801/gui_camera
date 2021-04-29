#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QtCore>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    cap.open(0);

    if(!cap.isOpened()){
        ui->plain->appendPlainText("not find camera");
    }
    else {
        ui->plain->appendPlainText("camera is opening");
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));
        timer->start(20);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    disconnect(timer, SIGNAL(timeout()), this, SLOT(update()));
    disconnect(timer, SIGNAL(timeout()), this, SLOT(updategray()));
    disconnect(timer, SIGNAL(timeout()), this, SLOT(updatesobel()));
        cap.release();
        ui->plain->appendPlainText("camera is closing");
}
void MainWindow::update()
{
    cap >> frame;

    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);

    qt_image = QImage((const unsigned char*) (frame.data), frame.cols, frame.rows, QImage::Format_RGB888);

    ui->label->setPixmap(QPixmap::fromImage(qt_image));

    ui->label->resize(ui->label->pixmap()->size());
}
void MainWindow::updategray()
{
    cap >> frame;

    cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);

    qt_image = QImage((const unsigned char*) (frame.data), frame.cols, frame.rows, QImage::Format_Indexed8);

    ui->label->setPixmap(QPixmap::fromImage(qt_image));

    ui->label->resize(ui->label->pixmap()->size());
}

void MainWindow::updatesobel()
{
    cap >> frame;


    cv::Sobel(frame, frame,0, 1, 1);


    qt_image = QImage((const unsigned char*) (frame.data), frame.cols, frame.rows, QImage::Format_RGB888);

    ui->label->setPixmap(QPixmap::fromImage(qt_image));

    ui->label->resize(ui->label->pixmap()->size());
}

void MainWindow::on_pushButton_3_clicked()
{
        connect(timer, SIGNAL(timeout()), this, SLOT(updategray()));
        timer->start(20);
}

void MainWindow::on_pushButton_4_clicked()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(updatesobel()));
    timer->start(20);
}
