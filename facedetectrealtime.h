#ifndef FACEDETECTREALTIME_H
#define FACEDETECTREALTIME_H

#include <QWidget>
#include <QMainWindow>
#include <QDebug>
#include <QTimer>
#include <QImage>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/types_c.h"
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

namespace Ui {
class faceDetectRealtime;
}

class faceDetectRealtime : public QWidget
{
    Q_OBJECT

public:
    explicit faceDetectRealtime(QWidget *parent = nullptr);
    ~faceDetectRealtime();

    QImage  Mat2QImage(Mat cvImg);

private slots:
    void openCamara();      // 打开摄像头
    void readFarme();       // 读取当前帧信息
    void closeCamara();     // 关闭摄像头。
    void takingPictures();  // 拍照


private:
    Ui::faceDetectRealtime *ui;
    QTimer          *timer;
    QImage          imag;
    Mat             cap,cap_gray,cap_tmp;   // 定义一个Mat变量，用于存储每一帧的图像
    VideoCapture    capture;                // 声明视频读入类

    QPushButton *startVideoButton;           // 窗口布局
    QPushButton *takePhotoButton;
    QPushButton *closeVideoButton;
    QLabel *videoAreaLabel;
    QLabel *screenShotAreaLabel;
    QVBoxLayout *buttonVLayout;
    QHBoxLayout *faceDetectMainLayout;
};

#endif // FACEDETECTREALTIME_H
