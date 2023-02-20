#ifndef INPUTPIC_H
#define INPUTPIC_H

#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QFileDialog>
#include <QPushButton>
#include <QMessageBox>
#include <QtCore>

// opencv 头文件
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

namespace Ui {
class inputPic;
}

class inputPic : public QWidget
{
    Q_OBJECT

public:
    explicit inputPic(QWidget *parent = nullptr);
    ~inputPic();


private slots:
    void inputPictures();               // 导入图片的方法
    void startDetecting();              // 图片面部检测标注的方法


private:
    Ui::inputPic *ui;


    /*界面参数*/
    QLabel          *inputPicLabel;
    QHBoxLayout     *inputPicLayout;
    QVBoxLayout     *buttonVLayout;
    QPushButton     *inputButton;
    QPushButton     *detectButton;

    QString         *picUrl;            // 传入图片的路径
    QImage          *img;               // 导入的图片
    CascadeClassifier   *face_cascade;  // 定义分类器
};

#endif // INPUTPIC_H
