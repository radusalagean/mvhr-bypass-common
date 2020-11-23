#ifndef SERIAL_WRAPPER_H
#define SERIAL_WRAPPER_H

#include <Arduino.h>

class SerialWrapper
{
private:

public:
    virtual int available() = 0;
    virtual void print(const char str[]) = 0;
    virtual void println(const char str[]) = 0;
    virtual byte read() = 0;
    virtual void write(byte b) = 0;
};

#endif