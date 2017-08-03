#include "logwriter.h"

LogWriter::LogWriter(QObject *parent) : QObject(parent)
{
    // if log directory is not exist, create one
    QDir *dir = new QDir;
    if(!dir->exists("log"))
    {
        dir->mkdir("log");
    }
}

void LogWriter::WriteLogSlot(QString logInfo)
{
    QString dateStr = QDate::currentDate().toString("yyyy_MM_dd");
    QString dateTimeStr = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    file = new QFile("log/" + dateStr + ".log");

    if(file->open(QIODevice::WriteOnly  | QIODevice::Text | QIODevice::Append))
    {
        QTextStream txtOutput(file);
        txtOutput << dateTimeStr + "  " + logInfo << endl;
        file->close();
    }
    else
    {
        cout << "Cannot open logfile." << endl;
    }
}

LogWriter::~LogWriter()
{
}

