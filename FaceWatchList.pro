#-------------------------------------------------
#
# Project created by QtCreator 2015-01-20T18:40:24
#
#-------------------------------------------------

QT       += core gui
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FaceWatchList
TEMPLATE = app

SOURCES += main.cpp\
    Top.cpp \
    Left.cpp \
    VideoReader.cpp \
    CameraPicker.cpp \
    MyCamera.cpp \
    FaceRecognition.cpp \
    PubFun.cpp \
    LogWriter.cpp \
    LoadingDialog.cpp \
    FaceImageProcess.cpp \
    RecogResult.cpp \
    FaceRecogResultlist.cpp \
    FaceRecogResult.cpp \
    IpCameraHandler.cpp \
    IpCamera.cpp \
    ../RecogniseCore.cpp

HEADERS  += \
    Top.h \
    Left.h \
    VideoReader.h \
    PubHeader.h \
    CameraPicker.h \
    MyCamera.h \
    FaceRecognition.h \
    PubFun.h \
    LogWriter.h \
    LoadingDialog.h \
    FaceImageProcess.h \
    RecogResult.h \
    FaceRecogResultlist.h \
    FaceRecogResult.h \
    IpCameraHandler.h \
    IpCamera.h \
    ../RecogniseCore.h

FORMS    += \
    Top.ui \
    Left.ui \
    CameraPicker.ui \
    LoadingDialog.ui \
    FaceRecognition.ui \
    PeopleRegister.ui \
    RecogResult.ui \
    FaceRecogResultlist.ui \
    FacerecogResult.ui

INCLUDEPATH += include \
    include/opencv3.1.0/include

LIBS += -L$$PWD/lib/ \
    -lVisionFaceDetect \
    -lVisionFaceAlignment \
    -lVisionExtractFeature \
    -lVisionFaceFeatureSimple \
    -lVisionFaceTracker \
    -lopencv_world310 \
    -lHCNetSDK \
    -lHCCore \
    -lPlayCtrl

RC_FILE = myapp.rc

RESOURCES += \
    resource.qrc
