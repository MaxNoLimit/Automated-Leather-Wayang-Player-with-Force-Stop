#include "rotary_encoder.hpp"
#include "mainheader.hpp"
#include "wayang_lcd_2004.hpp"

int counter = 0;
int hold = 0;
int lastState, state;

void WayangDisplayController::beginRotaryEncoder(const int pinA, const int pinB, const int pinSW)
{
    pinMode(pinA, INPUT);
    pinMode(pinB, INPUT);
    pinMode(pinSW, INPUT);
}