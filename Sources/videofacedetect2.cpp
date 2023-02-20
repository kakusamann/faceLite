#include "Headers/videofacedetect2.h"
#include "ui_videofacedetect2.h"

videoFaceDetect2::videoFaceDetect2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::videoFaceDetect2)
{
    ui->setupUi(this);

    /*界面布局*/
    buttonVLayout = new QVBoxLayout;                      // 创建布局
    startVideoButton = new QPushButton("开启视频");
    takePhotoButton = new QPushButton("拍摄");
    savePhotoButton = new QPushButton("保存");
    tsPhotoHLayout = new QHBoxLayout;                     // 拍摄/保存水平布局
    tsPhotoHLayout->addWidget(takePhotoButton);
    tsPhotoHLayout->addWidget(savePhotoButton);
    closeVideoButton = new QPushButton("关闭视频");
    buttonVLayout->addWidget(startVideoButton);
    buttonVLayout->addLayout(tsPhotoHLayout);
    buttonVLayout->addWidget(closeVideoButton);
    videoAreaLabel = new QLabel("视频区");
    videoAreaLabel->setStyleSheet("background-color:rgb(0,0,0);");
    screenShotAreaLabel = new QLabel("截图区");
    screenShotAreaLabel->setStyleSheet("background-color:rgb(0,0,0);");
    faceDetectMainLayout = new QHBoxLayout;
    faceDetectMainLayout->addWidget(videoAreaLabel);
    faceDetectMainLayout->addWidget(screenShotAreaLabel);
    faceDetectMainLayout->addLayout(buttonVLayout);
    setLayout(faceDetectMainLayout);

    timer   = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(readFarme()));  // 时间到，读取当前摄像头信息
    connect(startVideoButton, SIGNAL(clicked()), this, SLOT(openCamara()));
    connect(takePhotoButton, SIGNAL(clicked()), this, SLOT(takingPictures()));
    connect(savePhotoButton, SIGNAL(clicked()), this, SLOT(saveScreenShot()));
    connect(closeVideoButton, SIGNAL(clicked()), this, SLOT(closeCamara()));
}

videoFaceDetect2::~videoFaceDetect2()
{
    delete ui;
}


/*打开摄像头--面部检测*/
void videoFaceDetect2::openCamara()
{
    capture.open(0);    //从摄像头读入视频如果设备只有一个摄像头就传入参数0
    qDebug("open");
    if (!capture.isOpened()) //先判断是否打开摄像头
    {
         qDebug("err");
    }
    timer->start(20);              // 开始计时，20ms获取一帧
}

/*读取摄像头信息--面部检测*/
void videoFaceDetect2::readFarme()
{
    capture>>cap; //读取当前帧
    if (!cap.empty()) //判断当前帧是否捕捉成功 **这步很重要
    {
        cvtColor(cap, cap_gray, CV_BGR2GRAY);       //转为灰度图
        equalizeHist(cap_gray, cap_gray);           //直方图均衡化，增加对比度方便处理

        //加载分类训练器，OpenCv官方文档提供的xml文档
        if (!eye_Classifier.load("/home/gyd/opencv_build/opencv/data/haarcascades/haarcascade_eye.xml"))  //需要将xml文档放在自己指定的路径下
        {
            qDebug("Load haarcascade_eye.xml failed!");
            return;
        }
        if (!face_cascade.load("/home/gyd/opencv_build/opencv/data/haarcascades/haarcascade_frontalface_alt.xml"))
        {
            qDebug("Load haarcascade_frontalface_alt failed!");
            return;
        }

        //检测关于眼睛部位位置
        eye_Classifier.detectMultiScale(cap_gray, eyeRect, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));//检测
        for (size_t eyeIdx = 0; eyeIdx < eyeRect.size(); eyeIdx++)
        {
            rectangle(cap, eyeRect[eyeIdx], Scalar(0, 0, 255));   //用红色矩形画出检测到的位置
        }
        //检测关于脸部位置
        face_cascade.detectMultiScale(cap_gray, faceRect, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));//检测
        for (size_t i = 0; i < faceRect.size(); i++)
        {
            rectangle(cap, faceRect[i], Scalar(0, 255, 0));      //用绿色矩形画出检测到的位置
        }
        imag = Mat2QImage(cap);     // 将Mat转换成QImage对象来显示
        imag = imag.scaled(this->videoAreaLabel->width(), this->videoAreaLabel->height(),
                                            Qt::IgnoreAspectRatio, Qt::SmoothTransformation);//设置图片大小和label的长宽一致
        //imshow(name, cap); //若当前帧捕捉成功，显示
        this->videoAreaLabel->setPixmap(QPixmap::fromImage(imag));  // 将图片显示到label上
    }
    else
        qDebug("can not ");
}


/*拍照--面部检测*/
void videoFaceDetect2::takingPictures()
{
    capture>>cap; //读取当前帧
    if (!cap.empty()) //判断当前帧是否捕捉成功 **这步很重要
    {
        imag = Mat2QImage(cap);
        imag = imag.scaled(this->screenShotAreaLabel->width(), this->screenShotAreaLabel->height(),
                                            Qt::IgnoreAspectRatio, Qt::SmoothTransformation);//设置图片大小和label的长宽一致
        //imshow(name, cap); //若当前帧捕捉成功，显示
        this->imagSave = imag;
        this->screenShotAreaLabel->setPixmap(QPixmap::fromImage(imag));  // 将图片显示到label上
    }
    else
        qDebug("can not ");
}

/*保存--面部检测*/
void videoFaceDetect2::saveScreenShot(){
    if (this->imagSave.isNull()){
        QMessageBox::warning(this, "警告", "目前没有数据要保存！");
    } else {
        timer->stop();      // 先关闭摄像头，不然会进程无响应
        QString fileName = QFileDialog::getSaveFileName(this, tr("保存图片到..."), tr("Images(*.png *.xpm *.jpg)"));
        this->imagSave.save(fileName);
    }
}


/*关闭摄像头，释放资源，必须释放--面部检测**/
void videoFaceDetect2::closeCamara(){
    timer->stop();         // 停止读取数据
    capture.release();
}

// 图片转换（网上抄的）
QImage videoFaceDetect2::Mat2QImage(Mat cvImg)
{
    QImage qImg;
    if(cvImg.channels()==3)     //3 channels color image
    {

        cv::cvtColor(cvImg,cvImg,CV_BGR2RGB);
        qImg =QImage((const unsigned char*)(cvImg.data),
                    cvImg.cols, cvImg.rows,
                    cvImg.cols*cvImg.channels(),
                    QImage::Format_RGB888);
    }
    else if(cvImg.channels()==1)                    //grayscale image
    {
        qImg =QImage((const unsigned char*)(cvImg.data),
                    cvImg.cols,cvImg.rows,
                    cvImg.cols*cvImg.channels(),
                    QImage::Format_Indexed8);
    }
    else
    {
        qImg =QImage((const unsigned char*)(cvImg.data),
                    cvImg.cols,cvImg.rows,
                    cvImg.cols*cvImg.channels(),
                    QImage::Format_RGB888);
    }
    return qImg;
}
