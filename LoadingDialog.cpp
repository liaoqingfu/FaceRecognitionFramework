#include "loadingdialog.h"
#include "ui_loadingdialog.h"

LoadingDialog::LoadingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadingDialog)
{
    ui->setupUi(this);
//    label = ui->label;
//    this->setFixedSize(200, 200);
    setWindowOpacity(0.7);
    this->setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

//    this->setContentsMargins(0, 0, 0, 0);
//    label->setContentsMargins(0, 0, 0, 0);

//    movie = new QMovie(":/images/loading.png");
//    label->setMovie(movie);
//    movie->start();
//    this->label->setVisible(false);
}

void LoadingDialog::SetInfo(QString info)
{
    ui->infoLb->setText(info);
}

LoadingDialog::~LoadingDialog()
{
    delete ui;
    delete label;
    delete movie;
}
