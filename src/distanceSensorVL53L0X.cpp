#include "mainheader.hpp"
#include "distanceSensorVL53L0X.hpp"
#include "mainfunctions.hpp"

VL53L0X distanceSensor[10];
const int xshut_pis[10] = {
    XSHUT_1,
    XSHUT_2,
    XSHUT_3,
    XSHUT_4,
    XSHUT_5,
    XSHUT_6,
    XSHUT_7,
    XSHUT_8,
    XSHUT_9,
    XSHUT_10};

void beginSensorNum(int nSensor)
{
    Serial.print(F("\nBegining sensor "));
    Serial.println(nSensor);
    digitalWrite(xshut_pis[nSensor - 1], HIGH);
    delay(100);
    distanceSensor[nSensor - 1].setAddress(0x29 + nSensor);
    distanceSensor[nSensor - 1].setTimeout(500);

    if (!distanceSensor[nSensor - 1].init())
    {
        Serial.print(F("Failed to boot VL53L0X Sensor "));
        Serial.println(nSensor);
        // digitalWrite(xshut_pis[nSensor - 1], LOW);
    }
    else
    {
        distanceSensor[nSensor - 1].startContinuous(200);
        // distanceSensor[nSensor - 1].setSignalRateLimit(0.1);                                 // 0.1 MCPS
        // distanceSensor[nSensor - 1].setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);   // laser pulse periods 18 PCLKs
        // distanceSensor[nSensor - 1].setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14); // Laser pulse periods 14 PCLKs
        // distanceSensor[nSensor - 1].setMeasurementTimingBudget(200000);                      // HIGH ACCURACY timming budget 200 ms, HIGH SPEED 20 ms
        Serial.print(F("VL53L0X Sensor "));
        Serial.print(nSensor);
        Serial.println(F(" booted"));
        Serial.print(getDistanceSensorNum(nSensor));
        Serial.println(F(" mm\n"));
    }
}

int getDistanceSensorNum(int nSensor)
{
    if (!distanceSensor[nSensor - 1].timeoutOccurred())
    {
        int data = distanceSensor[nSensor - 1].readRangeContinuousMillimeters();
        return data;
    }
    else
    {
        Serial.print(F("Sensor "));
        Serial.print(nSensor);
        Serial.println(F(" out of range!"));
        return -1;
    }
}
