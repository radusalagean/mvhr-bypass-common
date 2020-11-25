#ifndef TEMPERATURES_H
#define TEMPERATURES_H

typedef struct
{
    float extEv;
    float extAd;
    float intAd;
    float intEv;
} __attribute__((packed)) Temperatures;

#endif