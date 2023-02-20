# faceLite -- 基于Qt + openCV 的面部识别小程序
## 环境配置
* 系统：Ubuntu 22.04.1 LTS
* QT版本：5.12.0
* OpenCV版本：4.7.0

  ![开始界面](https://user-images.githubusercontent.com/68045911/220116974-34faca15-0312-4aca-a0af-0f880c27a774.png)
## 主要功能
* 导入图片，对图片进行***人脸检测***；
  * QFileDialog
  * QLabel
  * cv::CascadeClassifier
  
  ![图片标注](https://user-images.githubusercontent.com/68045911/220117313-f3ac29c1-a07c-4448-a6b7-fbbcc5393c6f.png)
* 视频实时面部检测，可以进***人脸识别*** 和***截图保存***；
  * cv::VideoCapture
  * cv::Mat
  * cv::CascadeClassifier
  
  ![image](https://user-images.githubusercontent.com/68045911/220117586-de095b1a-c157-4ba7-97ff-fc88e6824a26.png)
* 视频实时面部识别，可以对面部进行***身份识别*** (但是需要提前训练特征模型XML)。
  * cv::VideoCapture
  * cv::Mat
  * cv::face::FaceRecognizer
  * cv::face::EigenFaceRecognizer
  
  ![image](https://user-images.githubusercontent.com/68045911/220117646-e3a79620-afa0-45c7-b934-aa4e2d04feb8.png)
  ![image](https://user-images.githubusercontent.com/68045911/220118177-bde4e63e-aa16-46b0-9044-6ef3e99ea20a.png)
