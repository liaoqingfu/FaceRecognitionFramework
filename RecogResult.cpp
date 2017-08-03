#include "recogresult.h"
#include "ui_recogresult.h"

RecogResult::RecogResult(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecogResult)
{
    ui->setupUi(this);
}

void RecogResult::ClearScreen()
{
    if(ui->GV1->scene() != NULL)
    {
        ui->GV1->scene()->clear();
    }
    if(ui->GV2->scene() != NULL)
    {
        ui->GV2->scene()->clear();
    }
    if(ui->GV3->scene() != NULL)
    {
        ui->GV3->scene()->clear();
    }
    if(ui->GV4->scene() != NULL)
    {
        ui->GV4->scene()->clear();
    }
    if(ui->GV5->scene() != NULL)
    {
        ui->GV5->scene()->clear();
    }
    if(ui->GV6->scene() != NULL)
    {
        ui->GV6->scene()->clear();
    }
    if(ui->GV7->scene() != NULL)
    {
        ui->GV7->scene()->clear();
    }
    if(ui->GV8->scene() != NULL)
    {
        ui->GV8->scene()->clear();
    }
}

void RecogResult::SetResult(QVector<QString> resultList)
{
    QString info = "";
    for(int i=0; i<resultList.size(); i++)
    {
        if(i < 5)
        {
            QString peopleName = resultList.at(i);
            peopleName = peopleName.remove("./data/");
            peopleName = peopleName.remove("/1.jpg");
            info += QString::number(i) + ":" + peopleName + ", ";
        }
        QImage img(resultList.at(i));
        //std::cout << resultList.at(i).toStdString() << std::endl;
        QGraphicsScene *sceneTmp = new QGraphicsScene;
        sceneTmp->addPixmap(QPixmap::fromImage(img));
        QStringList tmpList = resultList.at(i).split("/");
        QString tmpName = tmpList.at(tmpList.size()-2);
        switch (i+1) {
        case 1:
            if(ui->GV1->scene() != NULL)
            {
                ui->GV1->scene()->clear();
            }
            ui->GV1->setScene(sceneTmp);
            ui->lb1->setText(tmpName);
            break;
        case 2:
            if(ui->GV2->scene() != NULL)
            {
                ui->GV2->scene()->clear();
            }
            ui->GV2->setScene(sceneTmp);
            ui->lb2->setText(tmpName);
            break;
        case 3:
            if(ui->GV3->scene() != NULL)
            {
                ui->GV3->scene()->clear();
            }
            ui->GV3->setScene(sceneTmp);
            ui->lb3->setText(tmpName);
            break;
        case 4:
            if(ui->GV4->scene() != NULL)
            {
                ui->GV4->scene()->clear();
            }
            ui->GV4->setScene(sceneTmp);
            ui->lb4->setText(tmpName);
            break;
        case 5:
            if(ui->GV5->scene() != NULL)
            {
                ui->GV5->scene()->clear();
            }
            ui->GV5->setScene(sceneTmp);
            ui->lb5->setText(tmpName);
            break;
        case 6:
            if(ui->GV6->scene() != NULL)
            {
                ui->GV6->scene()->clear();
            }
            ui->GV6->setScene(sceneTmp);
            ui->lb6->setText(tmpName);
            break;
        case 7:
            if(ui->GV7->scene() != NULL)
            {
                ui->GV7->scene()->clear();
            }
            ui->GV7->setScene(sceneTmp);
            ui->lb7->setText(tmpName);
            break;
        case 8:
            if(ui->GV8->scene() != NULL)
            {
                ui->GV8->scene()->clear();
            }
            ui->GV8->setScene(sceneTmp);
            ui->lb8->setText(tmpName);
            break;
        default:
            break;
        }
    }
    emit SendLogSig(info);
}

RecogResult::~RecogResult()
{
    delete ui;
}
