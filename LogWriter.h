#ifndef LOGWRITER_H
#define LOGWRITER_H

#include <QObject>
#include <QFile>
#include <QDate>
#include <iostream>
#include <QTextStream>
#include <QDateTime>
#include <QDir>
#include "pubheader.h"

using namespace std;

class LogWriter : public QObject
{
    Q_OBJECT
public:
    explicit LogWriter(QObject *parent = 0);
    ~LogWriter();

private:
    QFile *file;

signals:

public slots:
    void WriteLogSlot(QString logInfo);
};

#endif // LOGWRITER_H
