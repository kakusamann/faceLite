#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QImage>
#include <QPixmap>
#include <QCameraInfo>
#include <QString>
#include <QTimer>
#include <QPushButton>
#include <QCamera>
#include <QCameraImageCapture>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <cstring>
#include <QLabel>
#include <memory>

/*opencv头文件*/
#include <QtWidgets/QMainWindow>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/imgproc/types_c.h"
#include <opencv2/face/facerec.hpp>


using namespace cv;
using namespace face;
using namespace std;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QImage faceCapture(const Mat &mat);          // 捕获面部截图
    QImage Mat2QImage(Mat cvImg);
    Mat QImage2Mat(QImage qimg);

private slots:
    /*主界面槽函数*/
    void inputPictures();                        // 导入图片
    void startTraining();                        // 识别导入图片
    void helper();                               // 操作教程
    void videoFaceDetect();                      // 视频人脸检测
    void videoFaceReconit();                     // 视频人脸识别

    /*视频面部检测槽函数*/
    void openCamara();      // 打开摄像头
    void readFarme();       // 读取当前帧信息
    void saveScreenShot();  // 保存当前帧
    void closeCamara();     // 关闭摄像头。
    void takingPictures();  // 拍照

    /*视频面部识别槽函数*/
    void trainFace();       // 对已有照片进行训练
    void openCamaraReco();  // 打开摄像头--识别
    void readFarmeReco();   // 读取当前帧信息--身份识别
    void closeCamaraReco(); // 关闭摄像头--识别

private:
    Ui::MainWindow *ui;
    int deviceVideoChoice = 0;

    /*设置主窗口面板*/
    QStackedWidget *mainStackWidget;
    QWidget *inputWidget;
    QWidget *deviceWidget;
    QWidget *helperWidget;

    /*导入图片界面参数*/
    QString picUrl;
    QLabel *inputPicLabel;
    QVBoxLayout *inputPicLayout;

    /*视频面部检测部分*/
    QWidget *faceDetectRealtimeWidget;      // 检测主窗口
    QPushButton *startVideoButton;          // 开启视频--按钮
    QPushButton *takePhotoButton;           // 拍摄--按钮
    QPushButton *savePhotoButton;           // 保存截图--按钮
    QHBoxLayout *tsPhotoHLayout;            // 拍摄/保存水平布局
    QPushButton *closeVideoButton;          // 关闭视频--按钮
    QLabel *videoAreaLabel;                 // 拍摄视频区域--标签
    QLabel *screenShotAreaLabel;            // 显示截图区域--标签
    QVBoxLayout *buttonVLayout;             // 按钮垂直布局
    QHBoxLayout *faceDetectMainLayout;      // 整体水平布局

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

    /*视频面部识别部分*/
    QWidget *faceRecognitRealtimeWidget;    // 识别主窗口
    QLabel *videoAreaRecoLable;             // 左侧视频窗口
    QPushButton *trainButton;               // 右侧训练模型按钮
    QPushButton *recogntButton;             // 右侧人脸识别按钮
    QPushButton *stopButton;                // 右侧停止按钮
    QVBoxLayout *buttonVRecoLayout;         // 右侧按钮垂直布局
    QHBoxLayout *faceRecognitMainLayout;    // 识别总体水平布局

    QTimer          *timerReco;
//    VideoCapture    captureReco;




    /*帮助界面参数代码*/
    bool helperOpened = false;
    QLabel *helperTitleLabel;
    QLabel *helperContentLabel;
    QVBoxLayout *helperQVBoxLayout;
};

#endif // MAINWINDOW_H
