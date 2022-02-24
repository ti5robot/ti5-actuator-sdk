#include "serial.h"

#include <QDebug>
Serial::Serial()
{

}

bool Serial::open(char *portname, uint32_t baudRate,uint8_t byteSize)
{
    char str[10]={0};
    WCHAR wszClassName[10]={0};
    sprintf(str,"\\\\.\\%s",portname);
//    sprintf(str,"%s",portname);
    MultiByteToWideChar(CP_ACP, 0, str, strlen(str) , wszClassName, sizeof(wszClassName) / sizeof(wszClassName[0]));
    this->hCom = CreateFile(wszClassName,//COM1口
        GENERIC_READ | GENERIC_WRITE, //允许读和写
        0, //独占方式
        NULL,
        OPEN_EXISTING, //打开而不是创建
        0, //同步方式
        NULL);
    if (this->hCom == INVALID_HANDLE_VALUE)
    {
//        qDebug()<<"open serial failed!\n";
        return false;
    }
    else
    {
//        qDebug()<<"open serial succeed!\n";
    }
    SetupComm(this->hCom, 4096, 4096); //输入缓冲区和输出缓冲区的大小都是1024
    COMMTIMEOUTS TimeOuts;
    //设定读超时
    TimeOuts.ReadIntervalTimeout = MAXDWORD;
    TimeOuts.ReadTotalTimeoutMultiplier = 0;
    TimeOuts.ReadTotalTimeoutConstant = 1;
    //设定写超时
    TimeOuts.WriteTotalTimeoutMultiplier = 0;
    TimeOuts.WriteTotalTimeoutConstant = 1;
    SetCommTimeouts(this->hCom, &TimeOuts); //设置超时
    DCB dcb;
    GetCommState(this->hCom, &dcb);
    dcb.BaudRate = baudRate; //波特率
    dcb.ByteSize = byteSize; //每个字节有8位
    dcb.Parity = NOPARITY; //无奇偶校验位
    dcb.StopBits = ONESTOPBIT; //1个停止位
    SetCommState(this->hCom, &dcb);
    return true;
}

bool Serial::read(char *readBuf, const uint32_t byteToRead, unsigned long *readSize)
{
    return ReadFile(this->hCom, readBuf, byteToRead, readSize, NULL);
}

bool Serial::write(char *writeBuf, const uint32_t byteToWrite, unsigned long *writeSize)
{

    return WriteFile(this->hCom, writeBuf, byteToWrite, writeSize, NULL);
}
