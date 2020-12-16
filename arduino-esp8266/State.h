#ifndef STATE_H
#define STATE_H

#include <Arduino.h>

#define STATE_NUM_OF_FIELDS 6

#define STATE_TEMPERATURES_RANGE_LOW 10
#define STATE_TEMPERATURES_RANGE_HIGH 40
#define STATE_HYST_RANGE_LOW 0.f
#define STATE_HYST_RANGE_HIGH 1.f
#define STATE_RANGE_MIN_VALUES 3

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