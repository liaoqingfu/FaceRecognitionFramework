#ifndef MYCAMERA_H
#define MYCAMERA_H

#include <iostream>
using namespace std;

#include <QObject>
#include <QTimer>
#include <QImage>

#include <opencv2/opencv.hpp>

#include "pubheader.h"

class MyCamera : public QObject
{
    Q_OBJECT
public:
    explicit MyCamera(QObject *parent = 0);
    ~MyCamera();

private:
    int cameraID;
    QTimer *timer;
    int interval;
    IplImage *frame;
    QImage *qImg;
    cv::VideoCapture videoCapture;
    bool cameraStarted;

public:
    void SetInterval(int i_interval);
    void StartCamera(int ID);

signals:
    void SendFrameMat(cv::Mat frm);
    void SendPlayErrorSig(QString info);
    void WriteLogSig(QString logInfo);

public slots:
    void StartCameraTimer();
    void NextFrame();
    void CloseCameraSlot();
};

#endif // MYCAMERA_H
