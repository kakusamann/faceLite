#include "Headers/help.h"
#include "ui_help.h"

help::help(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::help)
{
    ui->setupUi(this);

    /*帮助界面布局生成*/
    helperQVBoxLayout = new QVBoxLayout;  // 生成布局
    helperTitleLabel = new QLabel;
    helperTitleLabel->setText("欢迎来到帮助界面！");   // 生成标题
    QFont fTitle("黑体", 25, 25, true);
    helperTitleLabel->setFont(fTitle);
    helperContentLabel = new QLabel;      // 生成内容
    helperContentLabel->setText("* 图片识别：导入图片，识别->导入图片面部检测+标注；<br>* 视频面部检测：视频识别->面部检测；<br>* 视频面部识别：视频识别->面部识别(首先准备照片进行模型训练，然后进行面部识别)");
    QFont fContent("宋体", 15, 15, false);
    helperContentLabel->setFont(fContent);
    helperQVBoxLayout->addWidget(helperTitleLabel);     // 绑定布局
    helperQVBoxLayout->addWidget(helperContentLabel);

    setLayout(helperQVBoxLayout);
}

help::~help()
{
    delete ui;
}
