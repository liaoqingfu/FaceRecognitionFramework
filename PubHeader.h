#ifndef PUBHEADER
#define PUBHEADER

//#define DEBUG
#define TESTVIDEO

#include <QObject>

#define VIDEO_TYPE  0
#define IMG_TYPE  1
#define CAMERA_TYPE 2
struct CameraInfo
{
    QString name;
    uint ID;
    QString IP;
    QString userName;
    QString passWd;
};

#endif // PUBHEADER

