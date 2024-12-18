#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H

#include <Arduino.h>

namespace WayangDisplayController{
    void beginRotaryEncoder(const int pinA, const int pinB, const int pinSW);
}

#endif // ROTARY_ENCODER_H