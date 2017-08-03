#ifndef IPCAMERAHANDLER_H
#define IPCAMERAHANDLER_H

#include <iostream>
using namespace std;

#include <QObject>
#include <QDebug>
#include <QTimer>

#include <opencv2/opencv.hpp>

#include "windows.h"
#include "incCn/HCNetSDK.h"
#include "incCn/plaympeg4.h"

#include "ipcamera.h"
#include "faceimageprocess.h"


class IpCameraHandler : public QObject
{
    Q_OBJECT
public:
    explicit IpCameraHandler(QObject *parent = 0);
    ~IpCameraHandler();

//    void StartRealPlay(QString user_name, QString passwd, QString ip, IpCamera *ipCamera);
    void StartRealPlay(QString user_name, QString passwd, QString ip);


private:
    LONG lRealHandle;
    LONG lUserID;
    bool bPlaying;
    string ss;
    QTimer *timer;
    bool avaliable;

public:
    void DisplayInfo(cv::Mat img);
    void StopRealPlayAndLogout();

private slots:
    void SetAvaliable();

signals:
    void SendFrameMat(cv::Mat img);
};

#endif // IPCAMERAHANDLER_H
