#ifndef MAINFUNCTIONS_H
#define MAINFUNCTIONS_H

#include <CheapStepper.h>

void beginingAllGPIOS();
namespace WayangDisplay
{
    void lcd2004setup();
    void lcd2004loop();
    void generalLoop();
};

namespace WayangDisplayController
{
    void spinRotaryEncoder();
    void pressRotaryEncoder();
};

class WayangStepper
{
private:
    int delay_time;
    int rpm;

public:
    void begin(int rpm);
    void leftHandSpin(String dir, int degree);
    void rightHandSpin(String dir, int degree);
    void stopAllStepper();
};

#endif // MAINFUNCTIONS_H