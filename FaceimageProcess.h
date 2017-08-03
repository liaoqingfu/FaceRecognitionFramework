// 传入一帧视频，完成检测、定点和旋转
#ifndef FACEIMAGEPROCESS_H
#define FACEIMAGEPROCESS_H

#include <QObject>
#include <QTimer>
#include <QDir>

#include "PubFun.h"

#include "VisionFaceDetect.h"
#include "VisionFaceAlignment.h"
#include "VisionFaceTracker.h"

class FaceImageProcess : public QObject
{
    Q_OBJECT
public:
    explicit FaceImageProcess(QObject *parent = 0);
    ~FaceImageProcess();

    bool Init();
    bool registerFlag;

private:
    vision::VisionFaceDetect *faceDetect;
    vision::VisionFaceAlignment *faceAlignment;
    vision::VisionFaceTracker *faceTracker;

    vector<cv::Point2f> keyPoints;
    bool recogniseCoreAvaliable;
    int trueOrfalse[10];
    int currIdx;
    bool useBestFace;

    QString historyDir;
    QTimer *timer;

    vector<cv::Point3d> model_points;
    vector<float> GetHeadPos(const cv::Mat& img, const std::vector<cv::Point3d>& model_points, const std::vector<cv::Point2f>& face_points);

signals:
    void SendFrameShow(cv::Mat frmShow);
    void SendFrameForMainWindow(cv::Mat frmShow);
    void WriteLogSig(QString info);
    void SendFrameToRecognise(cv::Mat img);
    void SendFaceTrueOrFake(bool flag);
    void SendCurrRegFace(cv::Mat img);
    void SendFaceImageProcessAvaliable();

public slots:
    void DataProcessing(cv::Mat img);
    void SingleImageProcessing(cv::Mat img);
    void SetRecogniseCoreAvaliable();
};

#endif // FACEIMAGEPROCESS_H
