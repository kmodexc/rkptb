#pragma once

#include <stdint.h>
#include "Measurement.h"

class MeasurePin
{
    uint8_t pin;
    uint32_t val;
    bool updated;

public:
    MeasurePin(uint8_t pin);

    void reset();

    uint32_t getVal();
};