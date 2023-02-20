#include "inputpic.h"
#include "ui_inputpic.h"

inputPic::inputPic(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::inputPic)
{
    ui->setupUi(this);
}

inputPic::~inputPic()
{
    delete ui;
}
