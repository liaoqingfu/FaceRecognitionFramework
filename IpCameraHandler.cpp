#include "ipcamerahandler.h"

LONG nPort = -1;

LONGLONG handlerAddr = 0;

IpCameraHandler::IpCameraHandler(QObject *parent) : QObject(parent)
{
    lRealHandle = 0;
    lUserID = 0;
    bPlaying = false;
    ss = "dadas";
    avaliable = true;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(SetAvaliable()));
    timer->start(100);
}

void IpCameraHandler::SetAvaliable()
{
    avaliable = true;
}

void YV12toYUV(char *outYuv, char *inYv12, int width, int height,int widthStep)
{
    int col,row;
    unsigned int Y,U,V;
    int tmp;
    int idx;

    for (row=0; row<height; row++)
    {
        idx=row * widthStep;

        for (col=0; col<width; col++)
        {
            tmp = (row/2)*(width/2)+(col/2);
            Y=(unsigned int) inYv12[row*width+col];
            U=(unsigned int) inYv12[width*height+width*height/4+tmp];
            V=(unsigned int) inYv12[width*height+tmp];

            outYuv[idx+col*3]   = Y;
            outYuv[idx+col*3+1] = U;
            outYuv[idx+col*3+2] = V;
        }
    }
}

void IpCameraHandler::DisplayInfo(cv::Mat img)
{
    if(avaliable)
    {
        //resize(img, img, Size(1280, 720));
        //cv::imshow("test", img);
        //cvWaitKey(1);
//        std::cout << ss << std::endl;
        emit SendFrameMat(img);
        avaliable = false;
    }
}

void CALLBACK DecCBFun(long nPort, char *pBuf, long nSize, FRAME_INFO * pFrameInfo, long pUser,long nReserved2)
{
    long lFrameType = pFrameInfo->nType;
    // std::cout << "Called2" << endl;
    if(lFrameType == T_YV12)
    {
        // std::cout << "after " << pUser << std::endl;
        //        cout << "Called1" << endl;
        //        cout << pFrameInfo->nWidth << "-" << pFrameInfo->nHeight << endl;
        IplImage* pImgYCrCb = cvCreateImage(cvSize(pFrameInfo->nWidth,pFrameInfo->nHeight), 8, 3);
        YV12toYUV(pImgYCrCb->imageData, pBuf, pFrameInfo->nWidth,pFrameInfo->nHeight,pImgYCrCb->widthStep);
        IplImage* pImg = cvCreateImage(cvSize(pFrameInfo->nWidth,pFrameInfo->nHeight), 8, 3);
        cvCvtColor(pImgYCrCb, pImg, CV_YCrCb2RGB);
        cvReleaseImage(&pImgYCrCb);
        cv::Mat img = cv::cvarrToMat(pImg, 1);
        cvReleaseImage(&pImgYCrCb);
        cvReleaseImage(&pImg);
//        resize(img, img, cv::Size(1280, 720));
//        img = img(cv::Rect(img.cols*0.15, 0, img.cols*0.7, img.rows));

//        imshow("test", img);
//        cvWaitKey(1);
        //        cout << "Called3" << endl;
        IpCameraHandler &handler = (*(IpCameraHandler *)handlerAddr);
        handler.DisplayInfo(img);
    }
}

void CALLBACK fRealDataCallBack(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, void *pUser)
{
    DWORD dRet = 0;
    BOOL inData = FALSE;

    handlerAddr = (LONGLONG)pUser;
    // std::cout << "Called" << endl;
    long nUser = (long)pUser;

//    std::cout << "before " << nUser << std::endl;
    // std::cout << dwDataType << std::endl;
    switch (dwDataType)
    {
    case NET_DVR_SYSHEAD:
        if (!PlayM4_GetPort(&nPort))
        {
            break;
        }

        if (!PlayM4_OpenStream(nPort,pBuffer,dwBufSize,1024*1024))
        {
            dRet=PlayM4_GetLastError(nPort);
            break;
        }

        //
        if (!PlayM4_SetDecCallBackExMend(nPort, DecCBFun, NULL, NULL, nUser))
        {
            dRet=PlayM4_GetLastError(nPort);
            break;
        }

        //
        if (!PlayM4_Play(nPort, NULL))
        {
            dRet=PlayM4_GetLastError(nPort);
            break;
        }

        break;

    case NET_DVR_STREAMDATA:
        inData=PlayM4_InputData(nPort,pBuffer,dwBufSize);
        while (!inData)
        {
            Sleep(10);
            inData=PlayM4_InputData(nPort,pBuffer,dwBufSize);
        }
        break;
    default:
        inData=PlayM4_InputData(nPort,pBuffer,dwBufSize);
        while (!inData)
        {
            Sleep(10);
            inData=PlayM4_InputData(nPort,pBuffer,dwBufSize);
        }
        break;
    }
}

void IpCameraHandler::StartRealPlay(QString user_name, QString passwd, QString ip)
{
    ss = "daferqwqq";
    NET_DVR_Init();
    NET_DVR_SetConnectTime(2000, 1);
    NET_DVR_SetReconnect(10000, true);

    qDebug("Try to Login Camera");
    cout << "Try to Login Camera" << endl;
    StopRealPlayAndLogout();
    NET_DVR_USER_LOGIN_INFO struLoginInfo = {0};
    NET_DVR_DEVICEINFO_V40 struDeviceInfo = {0};
    struLoginInfo.bUseAsynLogin = false;
    memcpy(struLoginInfo.sDeviceAddress, ip.toStdString().c_str(), NET_DVR_DEV_ADDRESS_MAX_LEN);
    memcpy(struLoginInfo.sUserName, user_name.toStdString().c_str(), NAME_LEN);
    memcpy(struLoginInfo.sPassword, passwd.toStdString().c_str(), PASSWD_LEN);
    struLoginInfo.wPort = 8000;
    lUserID = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfo);

    if(lUserID < 0)
    {
        cout << "[IpCameraHandler::StartRealPlay]# Login error: " << NET_DVR_GetLastError() << endl;
    }
    else
    {
        cout << "[IpCameraHandler::StartRealPlay]# Login succeed" << endl;

        NET_DVR_PREVIEWINFO struPlayInfo = {0};
        struPlayInfo.lChannel = 1;
        struPlayInfo.dwStreamType = 0;
        struPlayInfo.dwLinkMode = 0;

        lRealHandle = NET_DVR_RealPlay_V40(lUserID, &struPlayInfo, fRealDataCallBack, this);

        if(lRealHandle < 0)
        {
            cout << "[IpCameraHandler::StartRealPlay]# NET_DVR_RealPlay_V40 error: " << NET_DVR_GetLastError() << endl;
            NET_DVR_Logout(lUserID);
            NET_DVR_Cleanup();
        }
        else
        {
            cout << "[IpCameraHandler::StartRealPlay]# NET_DVR_RealPlay_V40 start realplay." << endl;
            bPlaying = true;
        }
    }
}

void IpCameraHandler::StopRealPlayAndLogout()
{
    if(bPlaying)
    {
        cout << "[IpCameraHandler::StopRealPlayAndLogout]# IP Camera Logout..." << endl;

        if(!NET_DVR_StopRealPlay(lRealHandle))
        {
            cout << "[IpCameraHandler::StopRealPlayAndLogout]# Stop Real Play error, error code " << NET_DVR_GetLastError() << endl;
        }
        if(nPort > -1)
        {
            if (!PlayM4_Stop(nPort))
            {
                cout << "[IpCameraHandler::StopRealPlayAndLogout]# Stop PlayM4_Stop error, error code " << PlayM4_GetLastError(nPort) << endl;
            }
            if (!PlayM4_CloseStream(nPort))
            {
                cout << "[IpCameraHandler::StopRealPlayAndLogout]# Stop PlayM4_CloseStream error, error code " << PlayM4_GetLastError(nPort) << endl;
            }
            PlayM4_FreePort(nPort);
            nPort=-1;
        }

        NET_DVR_Logout(lUserID);
        NET_DVR_Cleanup();

        lRealHandle = 0;
        lUserID = 0;
        bPlaying = false;
    }
}

IpCameraHandler::~IpCameraHandler()
{

}

