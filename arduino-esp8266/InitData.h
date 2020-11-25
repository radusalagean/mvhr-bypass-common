#ifndef INIT_DATA_H
#define INIT_DATA_H

#include "State.h"
#include "Temperatures.h"

typedef struct
{
    State state;
    Temperatures temperatures;
} __attribute__((packed)) InitData;

#endif