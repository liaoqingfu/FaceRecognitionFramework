#include "left.h"
#include "ui_left.h"

Left::Left(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Left)
{
    ui->setupUi(this);
    normalStyle = "QPushButton{border-image: url(:/images/btnbg2.PNG); font: 10pt '微软雅黑'; color: rgb(255, 255, 255);}"
                          "QPushButton:hover{border-image: url(:/images/btnbg2on.PNG); font: 10pt '微软雅黑'; color: rgb(204, 88, 34);}"
                          "QPushButton:pressed{border-image: url(:/images/btnbg2on.PNG); font: 10pt '微软雅黑'; color: rgb(204, 88, 34);}";
    pressedStyle = "QPushButton{border-image: url(:/images/btnbg2on.PNG); font: 10pt '微软雅黑'; color: rgb(204, 88, 34);}";

    ui->cameraStartBtn->setStyleSheet(normalStyle);
    ui->videoStartBtn->setStyleSheet(normalStyle);
    ui->videoPauseBtn->setStyleSheet(normalStyle);
    ui->videoClearBtn->setStyleSheet(normalStyle);
    ui->imgChooseBtn->setStyleSheet(normalStyle);
    ui->videoChooseBtn->setStyleSheet(normalStyle);
    //ui->initBtn->setVisible(false);
}

Left::~Left()
{
    delete ui;
}

void Left::on_cameraStartBtn_clicked()
{
    ui->cameraStartBtn->setStyleSheet(pressedStyle);
    ui->videoStartBtn->setStyleSheet(normalStyle);
    ui->videoPauseBtn->setStyleSheet(normalStyle);
    ui->videoClearBtn->setStyleSheet(normalStyle);
    ui->imgChooseBtn->setStyleSheet(normalStyle);
    ui->videoChooseBtn->setStyleSheet(normalStyle);
    emit VideoClearSig();
    emit CameraStartSig();
    emit StartRecogSig();
}

void Left::on_videoChooseBtn_clicked()
{
    ui->cameraStartBtn->setStyleSheet(normalStyle);
    ui->videoStartBtn->setStyleSheet(normalStyle);
    ui->videoPauseBtn->setStyleSheet(normalStyle);
    ui->videoClearBtn->setStyleSheet(normalStyle);
    ui->imgChooseBtn->setStyleSheet(normalStyle);
    ui->videoChooseBtn->setStyleSheet(pressedStyle);
    emit VideoClearSig();
    emit VideoChooseSig();
}

void Left::on_imgChooseBtn_clicked()
{
    ui->cameraStartBtn->setStyleSheet(normalStyle);
    ui->videoStartBtn->setStyleSheet(normalStyle);
    ui->videoPauseBtn->setStyleSheet(normalStyle);
    ui->videoClearBtn->setStyleSheet(normalStyle);
    ui->imgChooseBtn->setStyleSheet(pressedStyle);
    ui->videoChooseBtn->setStyleSheet(normalStyle);
    emit VideoClearSig();
    emit ImgChooseSig();
}

void Left::on_videoStartBtn_clicked()
{
    ui->cameraStartBtn->setStyleSheet(normalStyle);
    ui->videoStartBtn->setStyleSheet(pressedStyle);
    ui->videoPauseBtn->setStyleSheet(normalStyle);
    ui->videoClearBtn->setStyleSheet(normalStyle);
    ui->imgChooseBtn->setStyleSheet(normalStyle);
    ui->videoChooseBtn->setStyleSheet(normalStyle);
    emit VideoStartSig();
}

void Left::on_videoPauseBtn_clicked()
{
    ui->cameraStartBtn->setStyleSheet(normalStyle);
    ui->videoStartBtn->setStyleSheet(normalStyle);
    ui->videoPauseBtn->setStyleSheet(pressedStyle);
    ui->videoClearBtn->setStyleSheet(normalStyle);
    ui->imgChooseBtn->setStyleSheet(normalStyle);
    ui->videoChooseBtn->setStyleSheet(normalStyle);
    emit VideoPauseSig();
}

void Left::on_videoClearBtn_clicked()
{
    ui->cameraStartBtn->setStyleSheet(normalStyle);
    ui->videoStartBtn->setStyleSheet(normalStyle);
    ui->videoPauseBtn->setStyleSheet(normalStyle);
    ui->videoClearBtn->setStyleSheet(pressedStyle);
    ui->imgChooseBtn->setStyleSheet(normalStyle);
    ui->videoChooseBtn->setStyleSheet(normalStyle);
    emit VideoClearSig();
}

void Left::on_registBtn_clicked()
{
    emit StartRegisterSig();
}

void Left::on_initBtn_clicked()
{
    emit InitRogCoreSig();
}
