#include "facedetectrealtime.h"
#include "ui_facedetectrealtime.h"

faceDetectRealtime::faceDetectRealtime(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::faceDetectRealtime)
{
    ui->setupUi(this);

    timer   = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(readFarme()));  // 时间到，读取当前摄像头信息
    connect(this->startVideoButton, &QPushButton::click, this, &faceDetectRealtime::openCamara);
    connect(this->takePhotoButton, &QPushButton::click, this, &faceDetectRealtime::takingPictures);
    connect(this->closeVideoButton, &QPushButton::click, this, &faceDetectRealtime::closeCamara);


}

faceDetectRealtime::~faceDetectRealtime()
{
    delete ui;
}

//打开摄像头
void faceDetectRealtime::openCamara()
{
    capture.open(0);    //从摄像头读入视频如果设备只有一个摄像头就传入参数0
    qDebug("open");
    if (!capture.isOpened()) //先判断是否打开摄像头
    {
         qDebug("err");
    }
    timer->start(20);              // 开始计时，20ms获取一帧
}

//读取摄像头信息
void faceDetectRealtime::readFarme()
{
    capture>>cap; //读取当前帧
    if (!cap.empty()) //判断当前帧是否捕捉成功 **这步很重要
    {
        imag = Mat2QImage(cap);
        imag = imag.scaled(this->videoAreaLabel->width(), this->videoAreaLabel->height(),
                                            Qt::IgnoreAspectRatio, Qt::SmoothTransformation);//设置图片大小和label的长宽一致
        //imshow(name, cap); //若当前帧捕捉成功，显示
        this->videoAreaLabel->setPixmap(QPixmap::fromImage(imag));  // 将图片显示到label上
    }
    else
        qDebug("can not ");

}


// 拍照
void faceDetectRealtime::takingPictures()
{
    capture>>cap; //读取当前帧
    if (!cap.empty()) //判断当前帧是否捕捉成功 **这步很重要
    {
        imag = Mat2QImage(cap);
        imag = imag.scaled(this->screenShotAreaLabel->width(), this->screenShotAreaLabel->height(),
                                            Qt::IgnoreAspectRatio, Qt::SmoothTransformation);//设置图片大小和label的长宽一致

        //imshow(name, cap); //若当前帧捕捉成功，显示
        this->screenShotAreaLabel->setPixmap(QPixmap::fromImage(imag));  // 将图片显示到label上
    }
    else
        qDebug("can not ");
}


//关闭摄像头，释放资源，必须释放***
void faceDetectRealtime::closeCamara()
{
    timer->stop();         // 停止读取数据。
}


// 图片转换（网上抄的）
QImage faceDetectRealtime::Mat2QImage(Mat cvImg)
{
    QImage qImg;
    if(cvImg.channels()==3)     //3 channels color image
    {

        cv::cvtColor(cvImg,cvImg, CV_BGR2RGB);
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
