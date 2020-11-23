#ifndef SERIAL_WRAPPER_H
#define SERIAL_WRAPPER_H

#include <Arduino.h>

class SerialWrapper
{
private:

public:
    virtual int available() = 0;
    virtual byte peek() = 0;
    virtual byte read() = 0;
    virtual void write(byte b) = 0;

    virtual void print(const char str[]) = 0;
    virtual void print(char c) = 0;
    virtual void print(unsigned char uc, int format = DEC) = 0;
    virtual void print(int i, int format = DEC) = 0;
    virtual void print(unsigned int ui, int format = DEC) = 0;
    virtual void print(long l, int format = DEC) = 0;
    virtual void print(unsigned long ul, int format = DEC) = 0;
    virtual void print(double d, int decimals = 2) = 0;

    virtual void println(const char str[]) = 0;
    virtual void println(char c) = 0;
    virtual void println(unsigned char uc, int format = DEC) = 0;
    virtual void println(int i, int format = DEC) = 0;
    virtual void println(unsigned int ui, int format = DEC) = 0;
    virtual void println(long l, int format = DEC) = 0;
    virtual void println(unsigned long ul, int format = DEC) = 0;
    virtual void println(double d, int decimals = 2) = 0;
};

#endif