#include "facerecogresultlist.h"
#include "ui_facerecogresultlist.h"

FaceRecogResultList::FaceRecogResultList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FaceRecogResultList)
{
    ui->setupUi(this);
    faceRecogResultVector.resize(0);
    num2show = 10;

    for(int i=0; i<num2show; i++)
    {
        FaceRecogResult* recogResult = new FaceRecogResult(this);
        ui->horizontalLayout->addWidget(recogResult);
        faceRecogResultVector.append(recogResult);

        resultImagePaths[i] = "";
        resultNames[i] = "";
        resultScores[i] = -1;
    }
}

void FaceRecogResultList::SetResult(cv::Mat rog_img, QString image_path, QString name, float score, bool gender)
{
//    if(name != faceRecogResultVector.at(0)->GetName())
    {
        cv::Mat img = rog_img.clone();

        //    imshow("2", rog_img);
        for(int i=(num2show-1); i>0; i--)
        {
            resultImagePaths[i] = resultImagePaths[i-1];
            resultNames[i] = resultNames[i-1];
            resultScores[i] = resultScores[i-1];
            resultGender[i] = resultGender[i-1];
        }

        resultImagePaths[0] = image_path;
        resultNames[0] = name;
        resultScores[0] = score;
        resultGender[0] = gender;

        if(name != faceRecogResultVector.at(0)->GetName())
        {
            for(int i=(num2show-1); i>=0; i--)
            {
                if(i==0)
                {
                    faceRecogResultVector.at(i)->SetResult(img, resultImagePaths[i], resultNames[i], resultScores[i], resultGender[i]);
                }
                else
                {
                    faceRecogResultVector.at(i)->SetResult(faceRecogResultVector.at(i-1)->GetCurrImg(), resultImagePaths[i], resultNames[i], resultScores[i], resultGender[i]);
                }
            }
        }
        else
        {
            int i = 0;
            faceRecogResultVector.at(i)->SetResult(img, resultImagePaths[i], resultNames[i], resultScores[i], resultGender[i]);
        }
        img.release();
    }
    rog_img.release();
    //    FaceRecogResult* recogResult = new FaceRecogResult(this, image_path, name, score);
    //    ui->horizontalLayout->addWidget(recogResult);
}

FaceRecogResultList::~FaceRecogResultList()
{
    delete ui;
}
