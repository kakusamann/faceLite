#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*设置面板参数*/
    setWindowTitle("FaceLite System");
    this->mainStackWidget = new QStackedWidget(this);

    /*导入图片界面*/
    connect(ui->inputAction, &QAction::triggered, this, &MainWindow::inputPictures);        // 绑定槽函数

    this->inputWidget = new QWidget;            // 设置导入图片界面布局
    this->inputPicLayout = new QVBoxLayout;
    this->inputPicLabel = new QLabel;
    inputPicLayout->addWidget(inputPicLabel);
    inputWidget->setLayout(inputPicLayout);

    /*图片面部检测标注部分*/
    connect(ui->trainStartAction_2, &QAction::triggered, this, &MainWindow::startTraining);   // 绑定图片人脸检测槽函数

    /*视频实时人脸检测布局*/
    connect(ui->videoFaceDetectAction, &QAction::triggered, this, &MainWindow::videoFaceDetect);    //绑定槽函数
    this->buttonVLayout = new QVBoxLayout;                      // 创建布局
    this->startVideoButton = new QPushButton("开启视频");
    this->takePhotoButton = new QPushButton("拍摄");
    this->savePhotoButton = new QPushButton("保存");
    this->tsPhotoHLayout = new QHBoxLayout;                     // 拍摄/保存水平布局
    tsPhotoHLayout->addWidget(takePhotoButton);
    tsPhotoHLayout->addWidget(savePhotoButton);
    this->closeVideoButton = new QPushButton("关闭视频");
    this->buttonVLayout->addWidget(this->startVideoButton);
    this->buttonVLayout->addLayout(tsPhotoHLayout);
    this->buttonVLayout->addWidget(this->closeVideoButton);
    this->videoAreaLabel = new QLabel("视频区");
    this->screenShotAreaLabel = new QLabel("截图区");
    this->faceDetectMainLayout = new QHBoxLayout;
    this->faceDetectMainLayout->addWidget(this->videoAreaLabel);
    this->faceDetectMainLayout->addWidget(this->screenShotAreaLabel);
    this->faceDetectMainLayout->addLayout(this->buttonVLayout);

    this->faceDetectRealtimeWidget = new QWidget;
    this->faceDetectRealtimeWidget->setLayout(faceDetectMainLayout);

    timer   = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(readFarme()));  // 时间到，读取当前摄像头信息
    connect(this->startVideoButton, SIGNAL(clicked()), this, SLOT(openCamara()));
    connect(this->takePhotoButton, SIGNAL(clicked()), this, SLOT(takingPictures()));
    connect(this->savePhotoButton, SIGNAL(clicked()), this, SLOT(saveScreenShot()));
    connect(this->closeVideoButton, SIGNAL(clicked()), this, SLOT(closeCamara()));

    /*视频实时人脸识别布局*/
    connect(ui->videoFaceReconitionAction_2, &QAction::triggered, this, &MainWindow::videoFaceReconit); // 绑定槽函数
    this->videoAreaRecoLable = new QLabel("Video");
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
    this->faceRecognitRealtimeWidget = new QWidget;
    this->faceRecognitRealtimeWidget->setLayout(faceRecognitMainLayout);

    timerReco = new QTimer(this);
    connect(timerReco, SIGNAL(timeout()), this, SLOT(readFarmeReco()));
    connect(this->trainButton, &QPushButton::clicked, this, &MainWindow::trainFace);        // 绑定布局内槽函数
    connect(this->recogntButton, &QPushButton::clicked, this, &MainWindow::openCamaraReco);
    connect(this->stopButton, &QPushButton::clicked, this, &MainWindow::closeCamaraReco);


    /*帮助界面布局生成*/
    this->helperWidget = new QWidget;
    connect(ui->helperAction, &QAction::triggered, this, &MainWindow::helper);              // 绑定槽函数
    this->helperQVBoxLayout = new QVBoxLayout;  // 生成布局
    this->helperTitleLabel = new QLabel;
    this->helperTitleLabel->setText("欢迎来到帮助界面！");   // 生成标题
    QFont fTitle("黑体", 25, 25, true);
    this->helperTitleLabel->setFont(fTitle);
    this->helperContentLabel = new QLabel;      // 生成内容
    this->helperContentLabel->setText("* 图片识别：导入图片，识别->导入图片识别；<br>* 面部信息录入：设备->开启设备，记忆->开始录入；<br>* 面部信息识别：设备->开启设备，记忆->开始识别");
    QFont fContent("宋体", 15, 15, false);
    this->helperContentLabel->setFont(fContent);
    this->helperQVBoxLayout->addWidget(this->helperTitleLabel);     // 绑定布局
    this->helperQVBoxLayout->addWidget(this->helperContentLabel);
    this->helperWidget->setLayout(this->helperQVBoxLayout);

    /*将每个页面加入主界面布局*/
    this->setCentralWidget(mainStackWidget);
    this->mainStackWidget->addWidget(inputWidget);
    this->mainStackWidget->addWidget(faceDetectRealtimeWidget);
    this->mainStackWidget->addWidget(faceRecognitRealtimeWidget);
    this->mainStackWidget->addWidget(helperWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::inputPictures(){
    /*导入图片，还需判断导入的是否是图片*/
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);    // 自动调整窗口大小
    this->mainStackWidget->setCurrentWidget(inputWidget);       //将窗口布局设置为导入图片布局
    QString picName = QFileDialog::getOpenFileName(this, "选择图片", QCoreApplication::applicationFilePath(), "*" );
    this->picUrl = QString(picName);            //存储导入图片信息
    QImage *img = new QImage(picName);
    this->inputPicLabel->setPixmap(QPixmap::fromImage(*img));
}

void MainWindow::startTraining(){
    /*开始识别*/
    if (this->picUrl == nullptr || this->picUrl.isEmpty()) {               // 判断是否已经导入图片
        QMessageBox::warning(this, "警告", "你没有导入图片！");
    } else {
        QByteArray picUrlData = this->picUrl.toLocal8Bit();
        Mat img = imread(std::string(picUrlData));       //1.读取图片
        face_cascade.load("/home/gyd/opencv_build/opencv/data/haarcascades/haarcascade_frontalface_default.xml");    //2.加载haar特征分类器，选择opencv中的分类器
        if(face_cascade.empty())                      //如果分类器为空，输出错误信息
        {
            qDebug() << "加载特征器失败！" ;
        }
        std::vector<cv::Rect> rects;                     //设置存放识别结果的容器
        face_cascade.detectMultiScale(img, rects, 1.1, 2, 0);    //将图片在特征分类器中进行物体识别，结果放置容器中
        for(auto rect : rects)                      //循环容器中的元素
        {                                           //输出物体识别的属性
            rectangle(img, rect, {219,55,214}, 2, 8, 0);        //标注出识别范围
            putText(img,"Faces~",{30,30},102,1.0,{255,0,0});      //在图片上标注
        }
        std::vector<uchar> buf;                 //转换为Qimage来显示
        cv::imencode(".jpg", img, buf);
        QImage imgQimage = QImage::fromData(buf.data(), static_cast<int>(buf.size()));
        this->inputPicLabel->clear();
        this->inputPicLabel->setPixmap(QPixmap::fromImage(imgQimage));  //显示标注后的图片
    }
}

void MainWindow::videoFaceDetect(){
    /*视频人脸检测*/
    this->mainStackWidget->setCurrentWidget(faceDetectRealtimeWidget);      //将窗口布局设置为人脸检测布局
}

void MainWindow::videoFaceReconit(){
    /*视频人脸识别*/
    this->mainStackWidget->setCurrentWidget(faceRecognitRealtimeWidget);    //将窗口布局设置为人脸识别布局
}

void MainWindow::helper(){
    /*帮助界面*/
    this->mainStackWidget->setCurrentWidget(helperWidget);                  //将窗口布局设置为帮助界面布局
}

/*打开摄像头--面部检测*/
void MainWindow::openCamara()
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
void MainWindow::readFarme()
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
void MainWindow::takingPictures()
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
void MainWindow::saveScreenShot(){
    if (this->imagSave.isNull()){
        QMessageBox::warning(this, "警告", "目前没有数据要保存！");
    } else {
        timer->stop();      // 先关闭摄像头，不然会进程无响应
        QString fileName = QFileDialog::getSaveFileName(this, tr("保存图片到..."), tr("Images(*.png *.xpm *.jpg)"));
        this->imagSave.save(fileName);
    }
}


/*关闭摄像头，释放资源，必须释放--面部检测**/
void MainWindow::closeCamara(){
    timer->stop();         // 停止读取数据
    capture.release();
}



/*面部识别 TAG*/
/*开始训练面部模型--面部识别*/
void MainWindow::trainFace(){
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
    model->save("/home/gyd/桌面/pro/faceLite_2/picss/MyFacePCAModel.xml");
}

/*打开摄像头--面部识别*/
void MainWindow::openCamaraReco(){
    capture.open(0);    //从摄像头读入视频如果设备只有一个摄像头就传入参数0
    qDebug("open");
    if (!capture.isOpened()) //先判断是否打开摄像头
    {
         qDebug("err");
    }
    timerReco->start(50);              // 开始计时，20ms获取一帧
}

/*读取面部信息--面部识别*/
void MainWindow::readFarmeReco(){
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
        modelPCA->read("/home/gyd/桌面/pro/faceLite_2/picss/MyFacePCAModel.xml");   //加载分类器(地址就是训练出来的XML的地址)

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
void MainWindow::closeCamaraReco(){
    timerReco->stop();
    capture.release();
}


// 图片转换（网上抄的）
QImage MainWindow::Mat2QImage(Mat cvImg)
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
//Qt读入彩色图后一般为Format_RGB32格式（4通道），而OpenCV一般用3通道的，因此进行了转换。
Mat MainWindow::QImage2Mat(QImage image)
{
    cv::Mat mat;
    switch (image.format())
    {
    case QImage::Format_RGB32:  //一般Qt读入彩色图后为此格式
        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
        cv::cvtColor(mat,mat,cv::COLOR_BGRA2BGR);   //转3通道
        break;
    case QImage::Format_RGB888:
        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
        cv::cvtColor(mat,mat,cv::COLOR_RGB2BGR);
        break;
    case QImage::Format_Indexed8:
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
        break;
    }
    return mat;
}
