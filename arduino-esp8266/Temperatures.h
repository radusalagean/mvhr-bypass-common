#ifndef TEMPERATURES_H
#define TEMPERATURES_H

#define TEMPERATURES_NUM_OF_FIELDS 4

typedef struct
{
    float extEv;
    float extAd;
    float intAd;
    float intEv;
} __attribute__((packed)) Temperatures;

#endif