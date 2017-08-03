#include "camerapicker.h"
#include "ui_camerapicker.h"

CameraPicker::CameraPicker(QWidget *parent, QVector<CameraInfo> i_cameras) :
    QDialog(parent),
    ui(new Ui::CameraPicker)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Please Choose A Camera(Double Click)."));
    cameras = i_cameras;
    ui->cameraListWg->setRowCount(cameras.size() + 1);
    for(int i=0; i<cameras.size(); i++)
    {
        ui->cameraListWg->setItem(i, 0, new QTableWidgetItem(cameras.at(i).name));
        ui->cameraListWg->setItem(i, 1, new QTableWidgetItem(QString::number(cameras.at(i).ID)));
        ui->cameraListWg->setItem(i, 2, new QTableWidgetItem(cameras.at(i).IP));
    }

    ui->cameraListWg->setItem(cameras.count(), 0, new QTableWidgetItem("Local Camera 0"));
    ui->cameraListWg->setItem(cameras.count(), 1, new QTableWidgetItem(""));
    ui->cameraListWg->setItem(cameras.count(), 2, new QTableWidgetItem(""));

    this->showNormal();
}

CameraPicker::~CameraPicker()
{
    delete ui;
}

void CameraPicker::on_cameraListWg_doubleClicked(const QModelIndex &index)
{
    int idx = index.row();
    int cameraID = ui->cameraListWg->item(idx, 1)->text().toInt();

    if(idx == (ui->cameraListWg->rowCount()-1))
    {
        // Local camera war choosen
        emit SendCameraIDSig(0);
    }
    else
    {
        // Open Ip Camera
        emit SendStartIPCameraSig(cameraID);
        //emit SendCameraIDSig(cameraID);
    }
#ifdef DEBUG
    cout << "Double Clicked! Camera " << cameraID << " Was Choosen." << endl;
#endif
    this->close();
}
