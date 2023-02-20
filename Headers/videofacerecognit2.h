#ifndef VIDEOFACERECOGNIT2_H
#define VIDEOFACERECOGNIT2_H

#include <QWidget>
#include <vector>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QTimer>

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/imgproc/types_c.h"

using namespace std;
using namespace cv;
using namespace face;

namespace Ui {
class videoFaceRecognit2;
}

class videoFaceRecognit2 : public QWidget
{
    Q_OBJECT

public:
    explicit videoFaceRecognit2(QWidget *parent = nullptr);
    ~videoFaceRecognit2();

    QImage faceCapture(const Mat &mat);          // 捕获面部截图
    QImage Mat2QImage(Mat cvImg);
    Mat QImage2Mat(QImage qimg);


private:
    Ui::videoFaceRecognit2 *ui;

    //vector 是个类模板 需要提供明确的模板实参 vector<Rect>则是个确定的类 模板的实例化
    vector<Rect>        eyeRect;
    vector<Rect>        faceRect;
    vector<Rect>        faces;

    /*视频面部识别部分*/
    QImage          imag;
    QImage          imagSave;
    Mat             cap,cap_gray,cap_tmp;   // 定义一个Mat变量，用于存储每一帧的图像
    VideoCapture    capture;                // 声明视频读入类

    CascadeClassifier eye_Classifier;  //载入分类器
    CascadeClassifier face_cascade;    //载入分类器

    QWidget             *faceRecognitRealtimeWidget;    // 识别主窗口
    QLabel              *videoAreaRecoLable;             // 左侧视频窗口
    QPushButton         *trainButton;               // 右侧训练模型按钮
    QPushButton         *recogntButton;             // 右侧人脸识别按钮
    QPushButton         *stopButton;                // 右侧停止按钮
    QVBoxLayout         *buttonVRecoLayout;         // 右侧按钮垂直布局
    QHBoxLayout         *faceRecognitMainLayout;    // 识别总体水平布局

    QTimer              *timerReco;
//    VideoCapture    captureReco;

private slots:
    /*视频面部识别槽函数*/
    void trainFace();       // 对已有照片进行训练
    void openCamaraReco();  // 打开摄像头--识别
    void readFarmeReco();   // 读取当前帧信息--身份识别
    void closeCamaraReco(); // 关闭摄像头--识别
};


#endif // VIDEOFACERECOGNIT2_H
