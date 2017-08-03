#include "facerecogresult.h"
#include "ui_facerecogresult.h"

FaceRecogResult::FaceRecogResult(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FaceRecogResult)
{
    ui->setupUi(this);
    ui->name_lb->setText("");
    ui->score_label->setText("");
    QGraphicsScene *scene = new QGraphicsScene;
    ui->ori_face_img_gv->setScene(scene);
    ui->ori_face_img_gv->setAlignment(Qt::AlignHCenter);
    QGraphicsScene *scene1 = new QGraphicsScene;
    ui->face_img_gv->setScene(scene1);
    ui->face_img_gv->setAlignment(Qt::AlignHCenter);
}

void FaceRecogResult::SetResult(cv::Mat rog_img, QString image_path, QString name, float score, bool gender)
{
    this->name = name;
    if(!rog_img.empty())
    {
        if(gender)
        {
            ui->gendel_label->setText("female");
        }
        else
        {
            ui->gendel_label->setText("male");
        }
        curr_img.release();
        curr_img = rog_img.clone();
        rog_img.release();
        //        imshow("1", curr_img);
        double height = curr_img.rows;
        double width = curr_img.cols;

        double r = height / width;
        QSize size = ui->ori_face_img_gv->size();
        if ((double)size.height() / (double)size.width() > r)
        {
            width = size.width();
            height = width * r;
        }
        else
        {
            height = size.height();
            width = height / r;
        }

        if(width <= 0 || height <=0)
        {
            //QMessageBox::critical(this, "ERROR", "Resize error, Please contact the programmer.");
        }
        else
        {
            cv::resize(curr_img, curr_img, cv::Size(width-1, height-1), 0, 0, CV_INTER_LINEAR);
            QImage qimg = PubFun::MatToQImage(curr_img);
            ui->ori_face_img_gv->scene()->clear();
            ui->ori_face_img_gv->scene()->addPixmap(QPixmap::fromImage(qimg));
        }
    }

    cv::Mat img = cv::imread(image_path.toStdString());
    if(!img.empty())
    {
        double height = img.rows;
        double width = img.cols;

        double r = height / width;
        QSize size = ui->face_img_gv->size();
        if ((double)size.height() / (double)size.width() > r)
        {
            width = size.width();
            height = width * r;
        }
        else
        {
            height = size.height();
            width = height / r;
        }

        if(width <= 0 || height <=0)
        {
            //QMessageBox::critical(this, "ERROR", "Resize error, Please contact the programmer.");
        }
        else
        {
            cv::resize(img, img, cv::Size(width-1, height-1), 0, 0, CV_INTER_LINEAR);
            QImage qimg = PubFun::MatToQImage(img);
            ui->face_img_gv->scene()->clear();
            ui->face_img_gv->scene()->addPixmap(QPixmap::fromImage(qimg));
        }

        ui->name_lb->setText(name);
        ui->score_label->setText(QString::number(score, 'f', 2));

        ui->time_lb->setText(QDateTime::currentDateTime().toString("hh:mm:ss"));
        img.release();
    }
}

FaceRecogResult::~FaceRecogResult()
{
    delete ui;
}
