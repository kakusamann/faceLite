#ifndef VIDEOFACEDETECT2_H
#define VIDEOFACEDETECT2_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLayout>
#include <vector>
#include <QTimer>
#include <QFileDialog>
#include <QMessageBox>


/*opencv 头文件*/
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/imgproc/types_c.h"

using namespace cv;
using namespace std;

namespace Ui {
class videoFaceDetect2;
}

class videoFaceDetect2 : public QWidget
{
    Q_OBJECT

public:
    explicit videoFaceDetect2(QWidget *parent = nullptr);
    ~videoFaceDetect2();

    QImage Mat2QImage(Mat cvImg);           // 图片类型转换

private:
    Ui::videoFaceDetect2 *ui;

    /*界面布局参数*/
    QWidget         *faceDetectRealtimeWidget;  // 检测主窗口
    QPushButton     *startVideoButton;          // 开启视频--按钮
    QPushButton     *takePhotoButton;           // 拍摄--按钮
    QPushButton     *savePhotoButton;           // 保存截图--按钮
    QHBoxLayout     *tsPhotoHLayout;            // 拍摄/保存水平布局
    QPushButton     *closeVideoButton;          // 关闭视频--按钮
    QLabel          *videoAreaLabel;            // 拍摄视频区域--标签
    QLabel          *screenShotAreaLabel;       // 显示截图区域--标签
    QVBoxLayout     *buttonVLayout;             // 按钮垂直布局
    QHBoxLayout     *faceDetectMainLayout;      // 整体水平布局

    /*视频面部检测部分参数*/
    QTimer          *timer;
    QImage          imag;
    QImage          imagSave;
    Mat             cap,cap_gray,cap_tmp;   // 定义一个Mat变量，用于存储每一帧的图像
    VideoCapture    capture;                // 声明视频读入类

    CascadeClassifier eye_Classifier;  //载入分类器
    CascadeClassifier face_cascade;    //载入分类器
    //vector 是个类模板 需要提供明确的模板实参 vector<Rect>则是个确定的类 模板的实例化
    vector<Rect> eyeRect;
    vector<Rect> faceRect;
    vector<Rect> faces;

private slots:
    /*视频面部检测槽函数*/
    void openCamara();      // 打开摄像头
    void readFarme();       // 读取当前帧信息
    void saveScreenShot();  // 保存当前帧
    void closeCamara();     // 关闭摄像头。
    void takingPictures();  // 拍照

};

#endif // VIDEOFACEDETECT_H
