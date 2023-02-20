#include "Headers/inputpic.h"
#include "ui_inputpic.h"

inputPic::inputPic(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::inputPic)
{
    ui->setupUi(this);

    /*图片处理界面布局*/
    inputButton = new QPushButton("导入图片");
    inputButton->setFixedSize(QSize(150, 50));
    detectButton = new QPushButton("检测面部");
    detectButton->setFixedSize(QSize(150, 50));
    buttonVLayout = new QVBoxLayout;
    buttonVLayout->addWidget(inputButton);
    buttonVLayout->addWidget(detectButton);

    inputPicLayout = new QHBoxLayout;
    inputPicLabel = new QLabel;
    inputPicLabel->setStyleSheet("background-color:rgb(255,255,255);");
    inputPicLayout->addWidget(inputPicLabel);
    inputPicLayout->addLayout(buttonVLayout);
    setLayout(inputPicLayout);

    picUrl = new QString;                 // 创建导入图片路径容器
    face_cascade = new CascadeClassifier;

    /*绑定信号*/
    connect(inputButton, &QPushButton::clicked, this, &inputPic::inputPictures);
    connect(detectButton, &QPushButton::clicked, this, &inputPic::startDetecting);
}

inputPic::~inputPic()
{
    delete ui;
}

/*实现导入图片*/
void inputPic::inputPictures(){
    QString picName = QFileDialog::getOpenFileName(this, "选择图片", QCoreApplication::applicationFilePath(), "*" );
    picUrl = new QString(picName);                      // 存储导入图片信息
    img = new QImage(picName);
    inputPicLabel->setPixmap(QPixmap::fromImage(*img)); // 显示导入的图片
}

void inputPic::startDetecting(){
    /*开始识别*/
    if (picUrl == nullptr || picUrl->isEmpty()) {                   // 判断是否已经导入图片
        QMessageBox::warning(this, "警告", "你没有导入图片！");
    } else {
        QByteArray picUrlData = picUrl->toLocal8Bit();
        Mat img = imread(std::string(picUrlData));                  //1.读取图片
        face_cascade->load("/home/gyd/opencv_build/opencv/data/haarcascades/haarcascade_frontalface_default.xml");    //2.加载haar特征分类器，选择opencv中的分类器
        if(face_cascade->empty())                                   //如果分类器为空，输出错误信息
        {
            qDebug() << "加载特征器失败！" ;
        }
        std::vector<cv::Rect> rects;                                //设置存放识别结果的容器
        face_cascade->detectMultiScale(img, rects, 1.1, 2, 0);      //将图片在特征分类器中进行物体识别，结果放置容器中
        for(auto rect : rects)                                      //循环容器中的元素
        {                                                           //输出物体识别的属性
            rectangle(img, rect, {219,55,214}, 2, 8, 0);            //标注出识别范围
            putText(img,"Faces~",{30,30},102,1.0,{255,0,0});        //在图片上标注
        }
        std::vector<uchar> buf;                                     //转换为Qimage来显示
        cv::imencode(".jpg", img, buf);
        QImage imgQimage = QImage::fromData(buf.data(), static_cast<int>(buf.size()));
        inputPicLabel->clear();
        inputPicLabel->setPixmap(QPixmap::fromImage(imgQimage));    //显示标注后的图片
    }
}
