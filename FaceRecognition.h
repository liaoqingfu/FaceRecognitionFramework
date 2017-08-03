#pragma once

#ifndef FACERECOGNITION_H
#define FACERECOGNITION_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QImage>
#include <QMessageBox>
#include <QFileDialog>
#include <QThread>
#include <QTimer>
#include <QApplication>
#include <QDomDocument>
#include <QCloseEvent>
#include "mycamera.h"
#include "pubheader.h"
#include "top.h"
#include "left.h"
#include "videoreader.h"
#include "camerapicker.h"
#include "PubFun.h"
#include "logwriter.h"
#include "loadingdialog.h"
#include "faceimageprocess.h"
#include "recognisecore.h"
#include "ipcamerahandler.h"

using namespace std;

namespace Ui {
class FaceRecognition;
}

class FaceRecognition : public QMainWindow
{
    Q_OBJECT

public:
    explicit FaceRecognition(QWidget *parent = 0);
    ~FaceRecognition();

private:
    Ui::FaceRecognition *ui;
    QGraphicsScene *scene[9];
    QGraphicsScene *faceScene;
    VideoReader *videoReader;
    QSize videoSizeOri;
    QSize videoSize;
    double hwRadio;
    bool videoSizeFlagForStart;
    QString videoName;
    int cameraID;
    QThread *videoReaderThd;
    QVector<CameraInfo> cameras;
    CameraPicker *cameraPicker;
    bool cameraPickerStartFlag;
    MyCamera *myCamera;
    QThread *myCameraThd;
    QString imgName;

    void ReadConFile(QString fileName);
    void SetGv(int i, QString imgName);

    cv::Mat imgMat;

    QDomDocument *dom;
    QString localIPStr;
    QString matlabRoot;

    LogWriter *logWriter;
    QThread *logWriterThd;
    int downSampleRate;

    LoadingDialog *loadingDialog;
    QThread *loadingDialogThd;

    FaceImageProcess *faceImageProcess;
    QThread *faceImageProcessThd;

    RecogniseCore *recogniseCore;
    QThread *recogniseCoreThd;

    float max_score;

    IpCamera *ipCamera;
    IpCameraHandler *ipCameraHandler;

    // IP camera parameters
    QString ipCameraIP;
    QString ipCameraUserName;
    QString ipCameraPasswd;

    int gpu_id;

    QTimer* program_init_timer;

	QString last_open_folder_name;

protected:
    void resizeEvent(QResizeEvent *);
    void closeEvent(QCloseEvent * e);

signals:
    void SendStartCameraSig();
    void SendFrameMat(cv::Mat, uint);
    void SendSingleImgMat(cv::Mat);
    void WriteLogSig(QString logInfo);
    void SendServiceAvailable(bool flag);

public slots:
    void SetVideoFrameMat(cv::Mat frm);
    void ErrorMsgSlot(QString info);
    void VideoChooseSlot();
    void CameraStartSlot();
    void GetCameraIDSlot(int ID);
    void ImgChooseSlot();
    void ClearVideoWindowSlot();
    void SetFaceDetectedSlot(cv::Mat frmShow);
    void SetRecogStateSlot(bool state);
    void SetFaceTrueOrFake(bool flag);
    void SetCurrRegFace(cv::Mat frmShow);
    void StartPeopleRegiste();
    void StartRecogSlot();
    void SetResultLog(QString info);
    void StartIPCameraSlot(int id);
    void InitRogCoreSlot();
};
#endif // FACERECOGNITION_H
