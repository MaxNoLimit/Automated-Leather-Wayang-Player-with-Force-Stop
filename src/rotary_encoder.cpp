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

// int WayangDisplayController::readRotaryEncoder()
// {
//     state = digitalRead(OUTPUT_A); // Reads the "current" state of the outputA

//     // If the previous and the current state of the outputA are different, that means a Pulse has occured
//     if (state != lastState)
//     {
//         // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
//         if (digitalRead(OUTPUT_B) != state)
//         {
//             return 0;
//         }
//         else
//         {
//             return 1;
//         }
//         // Serial.print("Position: ");
//         // Serial.println(counter);
//     }

//     // lastState = state; // Updates the previous state of the outputA with the current state
// }
