#ifndef IPCAMERA_H
#define IPCAMERA_H

#include <iostream>
using namespace std;

#include <QObject>

#include <opencv2/opencv.hpp>

extern cv::Mat ip_mat;

class IpCamera : public QObject
{
    Q_OBJECT
public:
    explicit IpCamera(QObject *parent = 0);
    ~IpCamera();

public:
    void DispInfo(cv::Mat img)
    {
        //        ip_mat.release();
        //        ip_mat = img.clone();
        //        imwrite("ll.jpg", img);
        //        if(!img.empty())
        //        {
        //            emit SendFrameMat(img);
        //        }
        //        cout << "Good" << endl;
//        imshow("IPCamera", img);
        //ipCameraHandler.SendFrameMat(img);
        emit SendFrameMat(img);
//        cvWaitKey(1);
    }

    void SetInfo()
    {
        info = "testfads";
    }
    string info;
signals:
    void SendFrameMat(cv::Mat img);
public slots:
};

#endif // IPCAMERA_H
