#ifndef FACERECOGRESULT_H
#define FACERECOGRESULT_H

#include <iostream>
using namespace std;

#include <QWidget>
#include <opencv2/opencv.hpp>

#include "PubFun.h"

namespace Ui {
class FaceRecogResult;
}

class FaceRecogResult : public QWidget
{
    Q_OBJECT

public:
    explicit FaceRecogResult(QWidget *parent = 0);
    ~FaceRecogResult();
    FaceRecogResult(QWidget *parent, QString image_path, QString name, float score);
    void SetResult(cv::Mat rog_img, QString image_path, QString name, float score, bool gender);
    cv::Mat GetCurrImg(){
        return this->curr_img;
    }

    QString GetName(){
        return this->name;
    }

private:
    Ui::FaceRecogResult *ui;
    cv::Mat curr_img;
    QString name;
};

#endif // FACERECOGRESULT_H
