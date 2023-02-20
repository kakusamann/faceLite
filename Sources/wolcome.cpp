#include "Headers/wolcome.h"
#include "ui_wolcome.h"

wolcome::wolcome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wolcome)
{
    ui->setupUi(this);

    wolcomeTextLabel = new QLabel("欢迎使用faceLite!!");        // 定义欢迎界面字体
    wolcomeTextLabel->setFont(QFont("宋体", 20));
    welcomeVLayout = new QVBoxLayout;                          // 定义界面布局
    welcomeVLayout->addWidget(wolcomeTextLabel);
    this->setLayout(welcomeVLayout);
}

wolcome::~wolcome()
{
    delete ui;
}
