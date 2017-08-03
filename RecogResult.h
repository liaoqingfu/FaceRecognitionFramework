#ifndef RECOGRESULT_H
#define RECOGRESULT_H

#include <QWidget>
#include <iostream>

namespace Ui {
class RecogResult;
}

class RecogResult : public QWidget
{
    Q_OBJECT

public:
    explicit RecogResult(QWidget *parent = 0);
    ~RecogResult();

private:
    Ui::RecogResult *ui;

public:
    void ClearScreen();

signals:
    void SendLogSig(QString info);

public slots:
    void SetResult(QVector<QString> resultList);
};

#endif // RECOGRESULT_H
