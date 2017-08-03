#include "PubFun.h"


PubFun::PubFun()
{
}

QString PubFun::GetDate()
{
    return QDateTime::currentDateTime().toString("yyyyMMdd");
}

QString PubFun::GetTime()
{
    return QDateTime::currentDateTime().toString("hhmmss");
}

void PubFun::YUV2RGB(IplImage *ptrImage, uchar *ptrBuffer)
{
    int width = ptrImage->width;
    int height = ptrImage->height;

    uchar *Y0 = ptrBuffer;
    uchar *Y1 = ptrBuffer + 2 * width;
    uchar *U = ptrBuffer + 4 * width * height;
    uchar *V = ptrBuffer + 5 * width * height;
    uchar *pixel = (uchar *)(ptrImage->imageData);

    for (int h = 0; h < height; ++h) {
        for (int w = 0; w < width; ++w) {
            double y = (double)((Y0[0] >> 2) + (Y0[1] >> 2) + (Y1[0] >> 2) + (Y1[1] >> 2));
            double u = (double)U[0] - 128.0;
            double v = (double)V[0] - 128.0;
            double b = y + 2.03211 * u;
            double g = y - 0.39465 * u - 0.58060 * v;
            double r = y + 1.13983 * v;

            pixel[0] = (uchar)((b < 0.0) ? 0.0 : ((b >= 256.0) ? 255.0 : b));
            pixel[1] = (uchar)((g < 0.0) ? 0.0 : ((g >= 256.0) ? 255.0 : g));
            pixel[2] = (uchar)((r < 0.0) ? 0.0 : ((r >= 256.0) ? 255.0 : r));

            Y0 += 2;
            Y1 += 2;
            ++U;
            ++V;
            pixel += 3;
        }
        Y0 += 2 * width;
        Y1 += 2 * width;
    }
}

QImage PubFun::MatToQImage(const cv::Mat& mat)
{
//    Mat rgb;
//    QImage img;
//    if(mat.channels()==3)
//    {
//        cvtColor(mat, rgb, CV_BGR2RGB);
//        img = QImage((const uchar*)(rgb.data),rgb.cols,rgb.rows,rgb.cols*rgb.channels(),QImage::Format_RGB888);
//    }
//    else
//    {
//        img = QImage((const uchar*)(mat.data),mat.cols,mat.rows,mat.cols*mat.channels(),QImage::Format_Indexed8);
//    }
//    return img;
    // 8-bits unsigned, NO. OF CHANNELS=1
    if (mat.type() == CV_8UC1)
    {
        // Set the color table (used to translate colour indexes to qRgb values)
        QVector<QRgb> colorTable;
        for (int i = 0; i<256; i++)
            colorTable.push_back(qRgb(i, i, i));
        // Copy input Mat
        const uchar *qImageBuffer = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
        img.setColorTable(colorTable);
        return img;
    }
    // 8-bits unsigned, NO. OF CHANNELS=3
    if (mat.type() == CV_8UC3)
    {
        // Copy input Mat
        const uchar *qImageBuffer = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return img.rgbSwapped();
    }
    else
    {
        std::cerr << "ERROR: Mat could not be converted to QImage." << std::endl;
        return QImage();
    }
}

string PubFun::GetRootDir()
{
    return "78475d71e72a3c181c077cb779475f1e";
}

string PubFun::GetString(string str)
{
    if(strcmp(str.c_str(), "face_classify.mdl") == 0)
    {
        return "e14acccc425c7ab1a83d7fdf9b6906ea";
    }
    else if(strcmp(str.c_str(), "haarcascade_frontalface_alt2.xml") == 0)
    {
        return "df4ccccca366c1892f060e927bb3839d";
    }
    else if(strcmp(str.c_str(), "SDMModel.mdl") == 0)
    {
        return "97cee37003657a4dd53e03e5571d1bba";
    }
    else if(strcmp(str.c_str(), "thuvision.prototxt") == 0)
    {
        return "8eac3078842e1945abc6227512894390";
    }
    else if(strcmp(str.c_str(), "thuvision0.model") == 0)
    {
        return "9405bdd61a78ea8172b6fcb0ec034d7f";
    }
    else if(strcmp(str.c_str(), "thuvision1.model") == 0)
    {
        return "9335c97fc3a5fae8f27eb598f9a8126d";
    }
    else if(strcmp(str.c_str(), "thuvision2.model") == 0)
    {
        return "c67b3516e21a5f849d505e111766e249";
    }
    else if(strcmp(str.c_str(), "thuvision3.model") == 0)
    {
        return "91733550a7092a0fcd8a2841634e4a05";
    }
    else if(strcmp(str.c_str(), "thuvision4.model") == 0)
    {
        return "d5eae3ec3fbe137eaca19504a472c6b6";
    }
    else if(strcmp(str.c_str(), "thuvision5.model") == 0)
    {
        return "19632a24ace32e75f69f40c959d650cb";
    }
    else if(strcmp(str.c_str(), "thuvision6.model") == 0)
    {
        return "40876f0787c889a802a95a99fd751526";
    }
    else if(strcmp(str.c_str(), "W.dat") == 0)
    {
        return "356ceba3d44c098aa3f129550e6c3593";
    }
    else if(strcmp(str.c_str(), "W0.dat") == 0)
    {
        return "f8029175057571d134d607bd2ac62074";
    }
    else if(strcmp(str.c_str(), "W1.dat") == 0)
    {
        return "9b4ea500413f4e66b32399135edcabd5";
    }
    else if(strcmp(str.c_str(), "W2.dat") == 0)
    {
        return "f260711a85dea6c5c33243b74a8f132d";
    }
    else if(strcmp(str.c_str(), "W3.dat") == 0)
    {
        return "2c2893aebd5139f5270363f74ede8182";
    }
    else if(strcmp(str.c_str(), "W4.dat") == 0)
    {
        return "792ecf9f28e77747ab621da7e1a2877c";
    }
    else if(strcmp(str.c_str(), "W5.dat") == 0)
    {
        return "1281137fac0f9600cd9fe5a4620c14b7";
    }
    else if(strcmp(str.c_str(), "W6.dat") == 0)
    {
        return "8f8e3f7721b41886b05b32fa0ac0485c";
    }
}

PubFun::~PubFun()
{
}
