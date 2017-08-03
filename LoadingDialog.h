#ifndef LOADINGDIALOG_H
#define LOADINGDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPainter>
#include <QMovie>

namespace Ui {
class LoadingDialog;
}

class LoadingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoadingDialog(QWidget *parent = 0);
    ~LoadingDialog();

    void SetInfo(QString info);

private:
    Ui::LoadingDialog *ui;
    QMovie *movie;
    QLabel *label;
};

#endif // LOADINGDIALOG_H
