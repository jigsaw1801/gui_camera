#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

#include <opencv2/imgproc/imgproc.hpp>
#include <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    cv::VideoCapture cap;
    cv::Mat frame;


    QImage qt_image;

    QTimer* timer;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void update();
    void updategray();
    void updatesobel();

    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

};
#endif // MAINWINDOW_H
