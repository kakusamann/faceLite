#include "Headers/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*设置面板参数*/
    setWindowTitle("FaceLite System");
    this->mainStackWidget = new QStackedWidget(this);
    this->setCentralWidget(mainStackWidget);

    /*欢迎界面*/
    welcomeWidget = new wolcome;
    mainStackWidget->addWidget(welcomeWidget);
    mainStackWidget->setCurrentWidget(welcomeWidget);

    /*图片处理界面*/
    inputWidget = new inputPic;
    mainStackWidget->addWidget(inputWidget);
    connect(ui->picAction, &QAction::triggered, this, &MainWindow::pictureDetect);          // 绑定处理槽函数

    /*视频实时人脸检测*/
    videoFaceDetectWidget = new videoFaceDetect2;
    mainStackWidget->addWidget(videoFaceDetectWidget);
    connect(ui->videoFaceDetectAction, &QAction::triggered, this, &MainWindow::videoFaceDetect);

    /*视频实时人脸识别*/
    faceRecognitWidget = new videoFaceRecognit2;
    mainStackWidget->addWidget(faceRecognitWidget);
    connect(ui->videoFaceReconitionAction_2, &QAction::triggered, this, &MainWindow::videoFaceReconit);

    /*帮助界面*/
    helperWidget = new help;
    mainStackWidget->addWidget(helperWidget);
    connect(ui->helperAction, &QAction::triggered, this, &MainWindow::helper);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pictureDetect(){
    /*图片人脸标注*/
    mainStackWidget->setCurrentWidget(inputWidget);                   //将窗口布局设置为图片处理布局
}

void MainWindow::videoFaceDetect(){
    /*视频人脸检测*/
    mainStackWidget->setCurrentWidget(videoFaceDetectWidget);         //将窗口布局设置为人脸检测布局
}

void MainWindow::videoFaceReconit(){
    /*视频人脸识别*/
    this->mainStackWidget->setCurrentWidget(faceRecognitWidget);    //将窗口布局设置为人脸识别布局
}

void MainWindow::helper(){
    /*帮助界面*/
    this->mainStackWidget->setCurrentWidget(helperWidget);                  //将窗口布局设置为帮助界面布局
}
