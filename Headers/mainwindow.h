#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

#include "Headers/wolcome.h"
#include "Headers/inputpic.h"
#include "Headers/videofacedetect2.h"
#include "Headers/videofacerecognit2.h"
#include "Headers/help.h"

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

private slots:
    /*主界面槽函数*/
    void pictureDetect();                        // 图片人脸标注
    void helper();                               // 操作教程
    void videoFaceDetect();                      // 视频人脸检测
    void videoFaceReconit();                     // 视频人脸识别

private:
    Ui::MainWindow *ui;
    int deviceVideoChoice = 0;

    /*设置主窗口面板*/
    QStackedWidget *mainStackWidget;
    wolcome *welcomeWidget;     // 开始界面
    inputPic *inputWidget;      // 图片标注界面
    videoFaceDetect2 *videoFaceDetectWidget;    // 视频面部检测界面
    videoFaceRecognit2 *faceRecognitWidget;     // 视频面部识别界面
    help *helperWidget;       // 帮助界面

};

#endif // MAINWINDOW_H
