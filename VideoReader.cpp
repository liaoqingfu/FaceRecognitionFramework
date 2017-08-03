#include "videoreader.h"

VideoReader::VideoReader(QObject *parent) : QObject(parent)
{
    timer = new QTimer(this);
}

bool VideoReader::SetVideo(QString fileName)
{
    videoName = fileName;
    string fileNameStd = fileName.toStdString();
    const char *fileNameChar = fileNameStd.c_str();
    capture.open(fileNameChar);
    if(capture.isOpened())
    {
        cout << "Open Video SUCCEED!" << endl;
        numFrames = capture.get(CV_CAP_PROP_FRAME_COUNT);
        currentFrame = 1;
        fps = capture.get(CV_CAP_PROP_FPS);
        cout << "FPS: " + QString::number(fps).toStdString() << endl;
        cv::Mat frame;
        capture >> frame;
        if(!frame.empty())
        {
            cout << "Send First Frame to MainWindow." << endl;
            emit SendFrame(&PubFun::MatToQImage(frame));
        }

        int vfps = 1000 / fps + 1;
        //vfps = vfps<100 ? 100:vfps;
#ifdef DEBUG
        cout << "Video Timer Interval: " + QString::number(vfps).toStdString() << endl;
#endif
        timer->setInterval(vfps);
//        timer->setInterval(1000);
        connect(timer, SIGNAL(timeout()), this, SLOT(NextFrame()));
        return true;
    }
    else
    {
        cout << "Open Video FAILED." << endl;
    }

    return false;
}

void VideoReader::NextFrame()
{
    if(capture.isOpened())
    {
        if(currentFrame < numFrames + 1)
        {
            cv::Mat frame;
            capture >> frame;
            emit SendFrameMat(frame);
        }
        else
        {
            timer->stop();
        }
    }
}

void VideoReader::PlayVideo()
{
    if(videoName.trimmed() == "")
    {
        emit SendPlayErrorSig("Please Choose a Valid Video First!");
    }
    else
    {
        timer->start();
    }
}

void VideoReader::PauseVideo()
{
    if(videoName.trimmed() == "")
    {
        emit SendPlayErrorSig(tr("Please Choose a Valid Video First!"));
    }
    else
    {
        timer->stop();
    }
}

void VideoReader::StopVideo()
{
    timer->stop();
}

VideoReader::~VideoReader()
{

}

