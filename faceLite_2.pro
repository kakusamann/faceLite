#-------------------------------------------------
#
# Project created by QtCreator 2023-02-19T14:19:30
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = faceLite_2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        Sources/main.cpp \
        Sources/mainwindow.cpp \
        Sources/wolcome.cpp \
        Sources/inputpic.cpp \
        Sources/videofacedetect2.cpp \
        Sources/help.cpp \
        Sources/videofacerecognit2.cpp

HEADERS += \
        Headers/mainwindow.h \
        Headers/wolcome.h \
        Headers/inputpic.h \
        Headers/videofacedetect2.h \
        Headers/help.h \
        Headers/videofacerecognit2.h

FORMS += \
        Forms/mainwindow.ui \
        Forms/wolcome.ui \
        Forms/inputpic.ui \
        Forms/videofacedetect2.ui \
        Forms/help.ui \
        Forms/videofacerecognit2.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#包含文件opencv
INCLUDEPATH += /usr/local/include/opencv4/

#opencv的动态链接库文件
LIBS += /usr/local/lib/libopencv_*
