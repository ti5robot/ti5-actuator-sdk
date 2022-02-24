#ifndef SERIAL_H
#define SERIAL_H
#include <stdint.h>
#include <windows.h>
//#include <iostream>
#include <string>

using namespace std;
class Serial
{
public:
    Serial();
    bool open(char *portname, uint32_t baudRate=2000000, uint8_t byteSize=8);
    bool read(char *readBuf, const uint32_t byteToRead, unsigned long *readSize);
    bool write(char *writeBuf, const uint32_t byteToWrite, unsigned long *writeSize);
//    inline bool write(uint8_t *writeBuf, const uint32_t byteToWrite, unsigned long *writeSize);

    HANDLE hCom;


};

#endif // SERIAL_H

