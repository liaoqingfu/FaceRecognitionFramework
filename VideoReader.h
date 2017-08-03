#ifndef VIDEOREADER_H
#define VIDEOREADER_H

#include <iostream>
using namespace std;

#include <QObject>
#include <QTimer>
#include <QSize>
#include <QImage>

#include "PubFun.h"

#include <opencv2/opencv.hpp>

class VideoReader : public QObject
{
    Q_OBJECT
public:
    explicit VideoReader(QObject *parent = 0);
    ~VideoReader();

    bool SetVideo(QString fileName);

private:
    cv::VideoCapture capture;
    QTimer *timer;
    double fps;
    QImage *qImg;
    QString videoName;
    int numFrames;
    int currentFrame;

public slots:
    void PlayVideo();
    void PauseVideo();
    void StopVideo();

    // internal
    void NextFrame();

signals:
    void SendFrameMat(cv::Mat frm);
    void SendFrame(QImage *qImg);
    void SendPlayErrorSig(QString info);
    void WriteLogSig(QString logInfo);
};

#endif // VIDEOREADER_H
