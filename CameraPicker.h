#ifndef CAMERAPICKER_H
#define CAMERAPICKER_H

#include <QDialog>
#include <iostream>
#include "pubheader.h"

using namespace std;

namespace Ui {
class CameraPicker;
}

class CameraPicker : public QDialog
{
    Q_OBJECT

public:
    explicit CameraPicker(QWidget *parent, QVector<CameraInfo> i_cameras);
    ~CameraPicker();

private slots:
    void on_cameraListWg_doubleClicked(const QModelIndex &index);

private:
    Ui::CameraPicker *ui;
    QVector<CameraInfo> cameras;

signals:
    void SendCameraIDSig(int ID);
    void SendStartIPCameraSig(int ID);
};

#endif // CAMERAPICKER_H
