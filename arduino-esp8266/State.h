#ifndef STATE_H
#define STATE_H

#include <Arduino.h>

#define STATE_NUM_OF_FIELDS 6

typedef struct
{
    bool hrModeAuto;
    bool hrDisabled;
    uint8_t intEvMin; /* min: 10 | max: 40 */
    uint8_t extAdMin; /* min: 10 | max: extAdMax - 3 */
    uint8_t extAdMax; /* min: extAdMin + 3 | max: 40 */
    float hysteresis; /* min: 0.0 | max: 1.0 */
} __attribute__((packed)) State;

#endif