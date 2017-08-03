#ifndef LEFT_H
#define LEFT_H

#include <QWidget>
#include "pubheader.h"
#include <iostream>

namespace Ui {
class Left;
}

class Left : public QWidget
{
    Q_OBJECT

public:
    explicit Left(QWidget *parent = 0);
    ~Left();

private slots:
    void on_cameraStartBtn_clicked();
    void on_videoChooseBtn_clicked();
    void on_imgChooseBtn_clicked();
    void on_videoStartBtn_clicked();
    void on_videoPauseBtn_clicked();
    void on_videoClearBtn_clicked();
    void on_registBtn_clicked();

    void on_initBtn_clicked();

private:
    Ui::Left *ui;
    QString normalStyle;
    QString pressedStyle;

signals:
    void CameraStartSig();
    void VideoChooseSig();
    void ImgChooseSig();
    void VideoStartSig();
    void VideoPauseSig();
    void VideoClearSig();
    void StartRegisterSig();
    void StartRecogSig();

    void InitRogCoreSig();
};

#endif // LEFT_H
