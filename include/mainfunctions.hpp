#ifndef MAINFUNCTIONS_H
#define MAINFUNCTIONS_H

#include <Arduino_FreeRTOS.h>

void beginingAllGPIOS();
void setAllMOSFETtoHIGH();
void setAllMOSFETtoLOW();
namespace WayangDisplay
{
    void lcd2004setupIntro();
    void lcd2004final();
    void lcd2004loop();
    void generalLoop();
};

namespace WayangDisplayController
{
    void spinRotaryEncoder();
    void pressRotaryEncoder();
};

namespace CalibratingFunction{
    void vSlotLinear();
    void soundSystem();
    void wayangHand();
    void commandListHandMovementTest();
};

enum whatSideServo
{
    RIGHT = 0,
    LEFT = 1,
};

class WayangHandServo
{
public:
    WayangHandServo(int leftOrRight);
    virtual ~WayangHandServo();
    void defaultPosition();
    void moveWhatServo(int servoNumber, int degree, int desiredDuration);

    void setServoPin1(int pin);
    void setServoPin2(int pin);
    void setServoPin3(int pin);
    void setServoPin4(int pin);

    int getServoPin1();
    int getServoPin2();
    int getServoPin3();
    int getServoPin4();

    int getAmountOfWaves();
    int getWavePeriod();
    int degreeToDelay(int degree);

    void setCurrentDegServo(int pin, int degree);
    int getCurrentDegServo(int pin);

    void resetArray();

private:
    const int wavePeriod = 20000; // in microseconds
    const int amountOfWaves = 100;
    int servoPin1;
    int servoPin2;
    int servoPin3;
    int servoPin4;
    int currentDeg[4] = {0, 0, 0, 0};
};

extern bool isPlaying;
extern int currentEpisode;
int getSubPageRoute();
void setAllENtoHIGH();
extern TaskHandle_t episodeTaskHandler[5];
extern bool isEpisodeTaskCreated;
void backToEpisodeSelection();

#endif // MAINFUNCTIONS_H