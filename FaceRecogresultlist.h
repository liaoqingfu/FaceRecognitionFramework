#ifndef FACERECOGRESULTLIST_H
#define FACERECOGRESULTLIST_H

#include <QWidget>
#include "facerecogresult.h"
#include <QScrollArea>
#include <QScrollBar>

namespace Ui {
class FaceRecogResultList;
}

class FaceRecogResultList : public QWidget
{
    Q_OBJECT

public:
    explicit FaceRecogResultList(QWidget *parent = 0);
    ~FaceRecogResultList();

private:
    Ui::FaceRecogResultList *ui;
    int num2show;
    QVector<FaceRecogResult*> faceRecogResultVector;
    QString resultImagePaths[50];
    vector<cv::Mat> resultRogImage;

    QString resultNames[50];
    float resultScores[50];
    bool resultGender[50];

public slots:
    void SetResult(cv::Mat rog_img, QString image_path, QString name, float score, bool gender);
};

#endif // FACERECOGRESULTLIST_H
