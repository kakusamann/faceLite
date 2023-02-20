#include "Headers/videofacerecognit2.h"
#include "ui_videofacerecognit2.h"

videoFaceRecognit2::videoFaceRecognit2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::videoFaceRecognit2)
{
    ui->setupUi(this);

    /*设置面部识别布局*/
    this->videoAreaRecoLable = new QLabel("Video");
    videoAreaRecoLable->setStyleSheet("background-color:rgb(0,0,0);");
    this->trainButton = new QPushButton("训练模型");
    this->recogntButton = new QPushButton("识别身份");
    this->stopButton = new QPushButton("停止识别");
    this->buttonVRecoLayout = new QVBoxLayout;
    this->buttonVRecoLayout->addWidget(trainButton);
    this->buttonVRecoLayout->addWidget(recogntButton);
    this->buttonVRecoLayout->addWidget(stopButton);
    this->faceRecognitMainLayout = new QHBoxLayout;
    this->faceRecognitMainLayout->addWidget(videoAreaRecoLable);
    this->faceRecognitMainLayout->addLayout(buttonVRecoLayout);
    setLayout(faceRecognitMainLayout);

    timerReco = new QTimer(this);
    connect(timerReco, SIGNAL(timeout()), this, SLOT(readFarmeReco()));
    connect(this->trainButton, &QPushButton::clicked, this, &videoFaceRecognit2::trainFace);        // 绑定布局内槽函数
    connect(this->recogntButton, &QPushButton::clicked, this, &videoFaceRecognit2::openCamaraReco);
    connect(this->stopButton, &QPushButton::clicked, this, &videoFaceRecognit2::closeCamaraReco);
}

videoFaceRecognit2::~videoFaceRecognit2()
{
    delete ui;
}

/*面部识别 TAG*/
/*开始训练面部模型--面部识别*/
void videoFaceRecognit2::trainFace(){
    vector<Mat> images;
    // 加入10张照片进行训练
    images.push_back(imread("/home/gyd/桌面/pro/faceLite_2/picss/1.jpg", IMREAD_GRAYSCALE));
    images.push_back(imread("/home/gyd/桌面/pro/faceLite_2/picss/2.jpg", IMREAD_GRAYSCALE));
    images.push_back(imread("/home/gyd/桌面/pro/faceLite_2/picss/3.jpg", IMREAD_GRAYSCALE));
    images.push_back(imread("/home/gyd/桌面/pro/faceLite_2/picss/4.jpg", IMREAD_GRAYSCALE));
    images.push_back(imread("/home/gyd/桌面/pro/faceLite_2/picss/5.jpg", IMREAD_GRAYSCALE));
    images.push_back(imread("/home/gyd/桌面/pro/faceLite_2/picss/6.jpg", IMREAD_GRAYSCALE));
    images.push_back(imread("/home/gyd/桌面/pro/faceLite_2/picss/7.jpg", IMREAD_GRAYSCALE));
    images.push_back(imread("/home/gyd/桌面/pro/faceLite_2/picss/8.jpg", IMREAD_GRAYSCALE));
    images.push_back(imread("/home/gyd/桌面/pro/faceLite_2/picss/9.jpg", IMREAD_GRAYSCALE));
    images.push_back(imread("/home/gyd/桌面/pro/faceLite_2/picss/10.jpg", IMREAD_GRAYSCALE));
    images.push_back(imread("/home/gyd/桌面/pro/faceLite_2/picss/11.jpg", IMREAD_GRAYSCALE));
    images.push_back(imread("/home/gyd/桌面/pro/faceLite_2/picss/12.jpg", IMREAD_GRAYSCALE));
    images.push_back(imread("/home/gyd/桌面/pro/faceLite_2/picss/13.jpg", IMREAD_GRAYSCALE));
    images.push_back(imread("/home/gyd/桌面/pro/faceLite_2/picss/14.jpg", IMREAD_GRAYSCALE));
    images.push_back(imread("/home/gyd/桌面/pro/faceLite_2/picss/15.jpg", IMREAD_GRAYSCALE));
    images.push_back(imread("/home/gyd/桌面/pro/faceLite_2/picss/16.jpg", IMREAD_GRAYSCALE));
    images.push_back(imread("/home/gyd/桌面/pro/faceLite_2/picss/17.jpg", IMREAD_GRAYSCALE));
    images.push_back(imread("/home/gyd/桌面/pro/faceLite_2/picss/18.jpg", IMREAD_GRAYSCALE));
    images.push_back(imread("/home/gyd/桌面/pro/faceLite_2/picss/19.jpg", IMREAD_GRAYSCALE));
    images.push_back(imread("/home/gyd/桌面/pro/faceLite_2/picss/20.jpg", IMREAD_GRAYSCALE));
    images.push_back(imread("/home/gyd/桌面/pro/faceLite_2/picss/21.jpg", IMREAD_GRAYSCALE));
    images.push_back(imread("/home/gyd/桌面/pro/faceLite_2/picss/22.jpg", IMREAD_GRAYSCALE));
    images.push_back(imread("/home/gyd/桌面/pro/faceLite_2/picss/23.jpg", IMREAD_GRAYSCALE));
    images.push_back(imread("/home/gyd/桌面/pro/faceLite_2/picss/24.jpg", IMREAD_GRAYSCALE));
    images.push_back(imread("/home/gyd/桌面/pro/faceLite_2/picss/25.jpg", IMREAD_GRAYSCALE));
    images.push_back(imread("/home/gyd/桌面/pro/faceLite_2/picss/26.jpg", IMREAD_GRAYSCALE));
    images.push_back(imread("/home/gyd/桌面/pro/faceLite_2/picss/27.jpg", IMREAD_GRAYSCALE));
    images.push_back(imread("/home/gyd/桌面/pro/faceLite_2/picss/28.jpg", IMREAD_GRAYSCALE));
    images.push_back(imread("/home/gyd/桌面/pro/faceLite_2/picss/29.jpg", IMREAD_GRAYSCALE));
    images.push_back(imread("/home/gyd/桌面/pro/faceLite_2/picss/30.jpg", IMREAD_GRAYSCALE));
//    vector<Mat> images_gray(images.size());
//    for (int var = 0; var < images.size(); ++var) {
//        cvtColor(images[var], images_gray[var], CV_BGR2GRAY);
//    }
    vector<int> labels = {1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3};

    Ptr<face::FaceRecognizer> model = EigenFaceRecognizer::create();
    model->train(images, labels);
    model->save("/home/gyd/桌面/picss/MyFacePCAModel.xml");
}

/*打开摄像头--面部识别*/
void videoFaceRecognit2::openCamaraReco(){
    capture.open(0);    //从摄像头读入视频如果设备只有一个摄像头就传入参数0
    qDebug("open");
    if (!capture.isOpened()) //先判断是否打开摄像头
    {
         qDebug("err");
    }
    timerReco->start(50);              // 开始计时，20ms获取一帧
}

/*读取面部信息--面部识别*/
void videoFaceRecognit2::readFarmeReco(){
    capture>>cap; //读取当前帧
    if (!cap.empty()) //判断当前帧是否捕捉成功 **这步很重要
    {
        cvtColor(cap, cap_gray, CV_BGR2GRAY);   //转为灰度图
        equalizeHist(cap_gray, cap_gray);       //直方图均衡化，增加对比度方便处理
        if (!face_cascade.load("/home/gyd/opencv_build/opencv/data/haarcascades/haarcascade_frontalface_alt.xml"))
        {
            qDebug("Load haarcascade_frontalface_alt failed!");
            return;
        }
        if (!eye_Classifier.load("/home/gyd/opencv_build/opencv/data/haarcascades/haarcascade_eye.xml"))  //需要将xml文档放在自己指定的路径下
        {
            qDebug("Load haarcascade_eye.xml failed!");
            return;
        }
        Ptr<face::FaceRecognizer> modelPCA = EigenFaceRecognizer::create();
        modelPCA->read("/home/gyd/桌面/picss/MyFacePCAModel.xml");   //加载分类器(地址就是训练出来的XML的地址)

        //检测关于脸部位置
        face_cascade.detectMultiScale(cap_gray, faceRect, 1.1, 3, 0 | CASCADE_DO_ROUGH_SEARCH, Size(50, 50));//检测
        for (size_t i = 0; i < faceRect.size(); i++)
        {
            rectangle(cap, faceRect[i], Scalar(0, 255, 0));      //用绿色矩形画出检测到的位置
            Mat faceROI = cap_gray(faceRect[i]);

            int predictPCA = -1;
            Mat face_test;
            Point text_lb;
            // 不加前面的cv::的话resize()方法会和MainWindow中的resize()冲突。
            cv::resize(faceROI,face_test,Size(100, 100));
//            imshow("frame", face_test);
            //测试图像应该是灰度图
            predictPCA = modelPCA->predict(face_test);
            qDebug("%d",predictPCA);
            if(predictPCA==1)  // 这个3也就是上面labels.push_back(3);和图片是一一对应的
            {
                string name = "gyd";  // 文本提示
                text_lb = Point(faceRect[i].x, faceRect[i].y);
                putText(cap, name, text_lb, FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255));
            }
            else if (predictPCA==2) {
                string name = "qu chang";  // 文本提示
                text_lb = Point(faceRect[i].x, faceRect[i].y);
                putText(cap, name, text_lb, FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255));
            }
            else if (predictPCA==3) {
                string name = "qu ruihua";  // 文本提示
                text_lb = Point(faceRect[i].x, faceRect[i].y);
                putText(cap, name, text_lb, FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255));
            }
            else {
                text_lb = Point(faceRect[i].x, faceRect[i].y);
                putText(cap, string("未知！"), text_lb, FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255));
            }

//            imshow("frame", faceROI);
            //检测关于眼睛部位位置
            int eye_num=0;
            eye_Classifier.detectMultiScale(faceROI, eyeRect, 1.1, 1, 0 | CASCADE_DO_ROUGH_SEARCH, Size(30, 30));//检测
            for (size_t j = 0; j < eyeRect.size(); j++)
            {
                Rect rect(faceRect[i].x + eyeRect[j].x, faceRect[i].y + eyeRect[j].y, eyeRect[j].width, eyeRect[j].height);
                rectangle(cap, rect, Scalar(255, 0, 0));   //用蓝色矩形画出检测到的位置
                eye_num++;
                if(eye_num==2)
                    break;
            }
        }
        imag = Mat2QImage(cap);     // 将Mat转换成QImage对象来显示
        imag = imag.scaled(this->videoAreaRecoLable->width(), this->videoAreaRecoLable->height(),
                                            Qt::IgnoreAspectRatio, Qt::SmoothTransformation);//设置图片大小和label的长宽一致
        this->videoAreaRecoLable->setPixmap(QPixmap::fromImage(imag));  // 将图片显示到label上
    }
    else
        qDebug("can not ");
}

/*停止识别--面部识别*/
void videoFaceRecognit2::closeCamaraReco(){
    timerReco->stop();
    capture.release();
}


// 图片转换（网上抄的）
QImage videoFaceRecognit2::Mat2QImage(Mat cvImg)
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

