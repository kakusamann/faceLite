# faceLite -- 基于Qt + openCV 的面部识别小程序
## 环境配置
* 系统：Ubuntu 22.04.1 LTS
* QT版本：5.12.0
* OpenCV版本：4.7.0
## 主要功能
* 导入图片，对图片进行***人脸检测***；
  * QFileDialog
  * QLabel
  * cv::CascadeClassifier
* 视频实时面部检测，可以进***人脸识别*** 和***截图保存***；
  * cv::VideoCapture
  * cv::Mat
  * cv::CascadeClassifier
* 视频实时面部识别，可以对面部进行***身份识别*** (但是需要提前训练特征模型XML)。
  * cv::VideoCapture
  * cv::Mat
  * cv::face::FaceRecognizer
  * cv::face::EigenFaceRecognizer
