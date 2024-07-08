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

namespace WayangHorizontalControl{
    void wayang1(int distance);
    void wayang2(int distance);
    void wayang3(int distance);
    void wayang4(int distance);
    void wayang5(int distance);
    void wayang6(int distance);
    void wayang7(int distance);
    void wayang8(int distance);
    void wayang9(int distance);
    void wayang10(int distance);
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