#ifndef PUBFUN_H
#define PUBFUN_H

#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>

#include <QObject>
#include <QtGui/qimage.h>
#include <QDateTime>

class PubFun :
    public QObject
{
public:
    PubFun();
    ~PubFun();

    static QImage MatToQImage(const cv::Mat&);
    static void YUV2RGB(IplImage *ptrImage, uchar *ptrBuffer);
    static QString GetDate();
    static QString GetTime();
    static string GetString(string str);
    static string GetRootDir();

private:
    // 变换法则
    static int genFun(int size, int key, int i)
    {
        return size + key + i - size / key;
    }

    // 获得文件大小
    static int getFileSize(string file_name)
    {
        FILE *fp = fopen(file_name.c_str(), "rb");
        fseek( fp, 0, SEEK_END );
        int size =  ftell(fp);
        fclose(fp);

        return size;
    }

public:
    static int get_key()
    {
        return 12312;
    }
    // 文件加密
    static void encrypt(string ori_file_name, string encrypted_file_name, int key)
    {
        FILE *fp1 = fopen(ori_file_name.c_str(), "rb");
        FILE *fp2 = fopen(encrypted_file_name.c_str(), "wb");

        int i, s, t, size = getFileSize(ori_file_name);

        for(i = 0; i < size; i++)
        {
            s = getc(fp1);
            t = genFun(size, key, i) ^ s;  // 加密
            putc(t, fp2);
        }

        fclose(fp1);
        fclose(fp2);
    }
    // 文件解密
    static void decrypt(string encrypted_file_name, string decrypted_file_name, int key)
    {
        FILE *fp1 = fopen(encrypted_file_name.c_str(), "rb");
        FILE *fp2 = fopen(decrypted_file_name.c_str(), "wb");

        int i, s, t, size = getFileSize(encrypted_file_name);
        for(i = 0; i < size; i++)
        {
            s = getc(fp1);
            t = genFun(size, key, i) ^ s; // 解密
            putc(t, fp2);
        }

        fclose(fp1);
        fclose(fp2);
    }
};

#endif // PUBFUN_H
