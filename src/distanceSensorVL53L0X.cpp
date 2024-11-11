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

// void beginAllinOneSensor()
// {
//     Serial.println("\nBegining all in one sensor");
//     setAllMOSFETtoHIGH();
//     delay(50);
//     distanceSensorAllInOne.setTimeout(500);
//     if (!distanceSensorAllInOne.init())
//     {
//         Serial.println("Failed to boot VL53L0X Sensor All in One");
//         // setAllMOSFETtoLOW();
//     }
//     else
//     {
//         Serial.println("VL53L0X Sensor All in One booted");
//         // setAllMOSFETtoLOW();
//     }
// }

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
        digitalWrite(xshut_pis[nSensor - 1], LOW);
    }
    else
    {
        distanceSensor[nSensor - 1].startContinuous(20);
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

// void beginSensor1()
// {
//     Serial.println(F("\nBegining sensor 1"));
//     // Wire.begin();
//     digitalWrite(XSHUT_1, HIGH);
//     delay(100);
//     distanceSensor[0].setAddress(SENSOR_ADDRESS_1);
//     distanceSensor[0].setTimeout(500);
//     if (!distanceSensor[0].init()) // bool true for using 2V8 mode, false for using standard mode
//     {
//         Serial.println("Failed to boot VL53L0X Sensor 1");
//         digitalWrite(XSHUT_1, LOW);
//     }
//     else
//     {
//         Serial.println("VL53L0X Sensor 1 booted");
//         distanceSensor[0].setSignalRateLimit(0.1);                                 // 0.1 MCPS
//         distanceSensor[0].setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);   // laser pulse periods 18 PCLKs
//         distanceSensor[0].setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14); // Laser pulse periods 14 PCLKs
//         distanceSensor[0].setMeasurementTimingBudget(200000);                      // HIGH ACCURACY timming budget 200 ms, HIGH SPEED 20 ms
//         // distanceSensor[0].startContinuous(200);
//         Serial.println("Sensor 1 distance: ");
//         Serial.print(getDistanceSensor1());
//         Serial.println(" mm\n");
//         // digitalWrite(XSHUT_1, LOW);
//     }
// }

// void beginSensor2()
// {
//     Serial.println(F("\nBegining sensor 2"));
//     // Wire.begin();
//     digitalWrite(XSHUT_2, HIGH);
//     delay(100);
//     distanceSensor[1].setAddress(SENSOR_ADDRESS_2);
//     distanceSensor[1].setTimeout(500);
//     if (!distanceSensor[1].init())
//     {
//         Serial.println("Failed to boot VL53L0X Sensor 2");
//         digitalWrite(XSHUT_2, LOW);
//         // beginSensor2();
//     }
//     else
//     {
//         Serial.println("VL53L0X Sensor 2 booted");
//         distanceSensor[1].setSignalRateLimit(0.1);                                 // 0.1 MCPS
//         distanceSensor[1].setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);   // laser pulse periods 18 PCLKs
//         distanceSensor[1].setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14); // Laser pulse periods 14 PCLKs
//         distanceSensor[1].setMeasurementTimingBudget(200000);                      // HIGH ACCURACY timming budget 200 ms, HIGH SPEED 20 ms
//         // distanceSensor[1].startContinuous(200);
//         Serial.println("Sensor 2 distance: ");
//         Serial.print(getDistanceSensor2());
//         Serial.println(" mm\n");
//         // digitalWrite(XSHUT_2, LOW);
//     }
// }

// void beginSensor3()
// {
//     Serial.println(F("\nBegining sensor 3"));
//     // Wire.begin();
//     digitalWrite(XSHUT_3, HIGH);
//     delay(100);
//     distanceSensor[2].setAddress(SENSOR_ADDRESS_3);
//     distanceSensor[2].setTimeout(500);
//     if (!distanceSensor[2].init())
//     {
//         Serial.println("Failed to boot VL53L0X Sensor 3");
//         digitalWrite(XSHUT_3, LOW);
//         // beginSensor3();
//     }
//     else
//     {
//         Serial.println("VL53L0X Sensor 3 booted");
//         distanceSensor[2].setSignalRateLimit(0.1);                                 // 0.1 MCPS
//         distanceSensor[2].setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);   // laser pulse periods 18 PCLKs
//         distanceSensor[2].setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14); // Laser pulse periods 14 PCLKs
//         distanceSensor[2].setMeasurementTimingBudget(200000);                      // HIGH ACCURACY timming budget 200 ms, HIGH SPEED 20 ms
//         // distanceSensor[2].startContinuous(200);
//         Serial.println("Sensor 3 distance: ");
//         Serial.print(getDistanceSensor3());
//         Serial.println(" mm\n");
//         // digitalWrite(XSHUT_3, LOW);
//     }
// }

// void beginSensor4()
// {
//     Serial.println(F("\nBegining sensor 4"));
//     // Wire.begin();
//     digitalWrite(XSHUT_4, HIGH);
//     delay(100);
//     distanceSensor[3].setAddress(SENSOR_ADDRESS_4);
//     distanceSensor[3].setTimeout(500);
//     if (!distanceSensor[3].init())
//     {
//         Serial.println("Failed to boot VL53L0X Sensor 4");
//         digitalWrite(XSHUT_4, LOW);
//         // beginSensor3();
//     }
//     else
//     {
//         Serial.println("VL53L0X Sensor 4 booted");
//         distanceSensor[3].setSignalRateLimit(0.1);                                 // 0.1 MCPS
//         distanceSensor[3].setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);   // laser pulse periods 18 PCLKs
//         distanceSensor[3].setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14); // Laser pulse periods 14 PCLKs
//         distanceSensor[3].setMeasurementTimingBudget(200000);                      // HIGH ACCURACY timming budget 200 ms, HIGH SPEED 20 ms
//         // distanceSensor[2].startContinuous(200);
//         Serial.println("Sensor 4 distance: ");
//         Serial.print(getDistanceSensor4());
//         Serial.println(" mm\n");
//         // digitalWrite(XSHUT_3, LOW);
//     }
// }

// void beginSensor5()
// {
//     Serial.println(F("\nBegining sensor 5"));
//     // Wire.begin();
//     digitalWrite(XSHUT_5, HIGH);
//     delay(100);
//     distanceSensor[4].setAddress(SENSOR_ADDRESS_5);
//     distanceSensor[4].setTimeout(500);
//     if (!distanceSensor[4].init())
//     {
//         Serial.println("Failed to boot VL53L0X Sensor 3");
//         digitalWrite(XSHUT_5, LOW);
//         // beginSensor3();
//     }
//     else
//     {
//         Serial.println("VL53L0X Sensor 5 booted");
//         distanceSensor[4].setSignalRateLimit(0.1);                                 // 0.1 MCPS
//         distanceSensor[4].setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 14);   // laser pulse periods 18 PCLKs
//         distanceSensor[4].setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 10); // Laser pulse periods 14 PCLKs
//         distanceSensor[4].setMeasurementTimingBudget(200000);                      // HIGH ACCURACY timming budget 200 ms, HIGH SPEED 20 ms

//         // distanceSensor[4].startContinuous(200);
//         Serial.println("Sensor 5 distance: ");
//         Serial.print(getDistanceSensor5());
//         Serial.println(" mm\n");
//         // digitalWrite(XSHUT_3, LOW);
//     }
// }

// void beginSensor6()
// {
//     Serial.println(F("\nBegining sensor 6"));
//     // Wire.begin();
//     digitalWrite(XSHUT_6, HIGH);
//     delay(100);
//     distanceSensor[5].setAddress(SENSOR_ADDRESS_6);
//     distanceSensor[5].setTimeout(500);
//     if (!distanceSensor[5].init())
//     {
//         Serial.println("Failed to boot VL53L0X Sensor 6");
//         digitalWrite(XSHUT_6, LOW);
//         // beginSensor3();
//     }
//     else
//     {
//         Serial.println("VL53L0X Sensor 6 booted");
//         distanceSensor[5].setSignalRateLimit(0.1);                                 // 0.1 MCPS
//         distanceSensor[5].setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 14);   // laser pulse periods 18 PCLKs
//         distanceSensor[5].setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 10); // Laser pulse periods 14 PCLKs
//         distanceSensor[5].setMeasurementTimingBudget(200000);                      // HIGH ACCURACY timming budget 200 ms, HIGH SPEED 20 ms

//         // distanceSensor[5].startContinuous(200);
//         Serial.println("Sensor 6 distance: ");
//         Serial.print(getDistanceSensor6());
//         Serial.println(" mm\n");
//         // digitalWrite(XSHUT_3, LOW);
//     }
// }

// void beginSensor7()
// {
//     Serial.println(F("\nBegining sensor 7"));
//     // Wire.begin();
//     digitalWrite(XSHUT_7, HIGH);
//     delay(100);
//     distanceSensor[6].setAddress(SENSOR_ADDRESS_7);
//     distanceSensor[6].setTimeout(500);
//     if (!distanceSensor[6].init())
//     {
//         Serial.println("Failed to boot VL53L0X Sensor 7");
//         digitalWrite(XSHUT_7, LOW);
//         // beginSensor3();
//     }
//     else
//     {
//         Serial.println("VL53L0X Sensor 7 booted");
//         distanceSensor[6].setSignalRateLimit(0.1);                                 // 0.1 MCPS
//         distanceSensor[6].setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 14);   // laser pulse periods 18 PCLKs
//         distanceSensor[6].setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 10); // Laser pulse periods 14 PCLKs
//         distanceSensor[6].setMeasurementTimingBudget(200000);                      // HIGH ACCURACY timming budget 200 ms, HIGH SPEED 20 ms

//         // distanceSensor[6].startContinuous(200);
//         Serial.println("Sensor 7 distance: ");
//         Serial.print(getDistanceSensor7());
//         Serial.println(" mm\n");
//         // digitalWrite(XSHUT_3, LOW);
//     }
// }

// void beginSensor8()
// {
//     Serial.println(F("\nBegining sensor 8"));
//     // Wire.begin();
//     digitalWrite(XSHUT_8, HIGH);
//     delay(100);
//     distanceSensor[7].setAddress(SENSOR_ADDRESS_8);
//     distanceSensor[7].setTimeout(500);
//     if (!distanceSensor[7].init())
//     {
//         Serial.println("Failed to boot VL53L0X Sensor 8");
//         digitalWrite(XSHUT_8, LOW);
//         // beginSensor3();
//     }
//     else
//     {
//         Serial.println("VL53L0X Sensor 8 booted");
//         distanceSensor[7].setSignalRateLimit(0.1);                                 // 0.1 MCPS
//         distanceSensor[7].setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 14);   // laser pulse periods 18 PCLKs
//         distanceSensor[7].setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 10); // Laser pulse periods 14 PCLKs
//         distanceSensor[7].setMeasurementTimingBudget(200000);                      // HIGH ACCURACY timming budget 200 ms, HIGH SPEED 20 ms

//         // distanceSensor[7].startContinuous(200);
//         Serial.println("Sensor 8 distance: ");
//         Serial.print(getDistanceSensor8());
//         Serial.println(" mm\n");
//         // digitalWrite(XSHUT_3, LOW);
//     }
// }

// void beginSensor9()
// {
//     Serial.println(F("\nBegining sensor 9"));
//     // Wire.begin();
//     digitalWrite(XSHUT_9, HIGH);
//     delay(100);
//     distanceSensor[8].setAddress(SENSOR_ADDRESS_9);
//     distanceSensor[8].setTimeout(500);
//     if (!distanceSensor[8].init())
//     {
//         Serial.println("Failed to boot VL53L0X Sensor 9");
//         digitalWrite(XSHUT_9, LOW);
//         // beginSensor3();
//     }
//     else
//     {
//         Serial.println("VL53L0X Sensor 9 booted");
//         distanceSensor[8].setSignalRateLimit(0.1);                                 // 0.1 MCPS
//         distanceSensor[8].setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 14);   // laser pulse periods 18 PCLKs
//         distanceSensor[8].setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 10); // Laser pulse periods 14 PCLKs
//         distanceSensor[8].setMeasurementTimingBudget(200000);                      // HIGH ACCURACY timming budget 200 ms, HIGH SPEED 20 ms

//         // distanceSensor[8].startContinuous(200);
//         Serial.println("Sensor 9 distance: ");
//         Serial.print(getDistanceSensor9());
//         Serial.println(" mm\n");
//         // digitalWrite(XSHUT_3, LOW);
//     }
// }

// void beginSensor10()
// {
//     Serial.println(F("\nBegining sensor 10"));
//     // Wire.begin();
//     digitalWrite(XSHUT_10, HIGH);
//     delay(100);
//     distanceSensor[9].setAddress(SENSOR_ADDRESS_10);
//     distanceSensor[9].setTimeout(500);
//     if (!distanceSensor[9].init())
//     {
//         Serial.println("Failed to boot VL53L0X Sensor 10");
//         digitalWrite(XSHUT_10, LOW);
//         // beginSensor3();
//     }
//     else
//     {
//         Serial.println("VL53L0X Sensor 10 booted");
//         distanceSensor[9].setSignalRateLimit(0.1);                                 // 0.1 MCPS
//         distanceSensor[9].setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 14);   // laser pulse periods 18 PCLKs
//         distanceSensor[9].setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 10); // Laser pulse periods 14 PCLKs
//         distanceSensor[9].setMeasurementTimingBudget(200000);                      // HIGH ACCURACY timming budget 200 ms, HIGH SPEED 20 ms

//         // distanceSensor[9].startContinuous(200);
//         Serial.println("Sensor 10 distance: ");
//         Serial.print(getDistanceSensor10());
//         Serial.println(" mm\n");
//         // digitalWrite(XSHUT_3, LOW);
//     }
// }

// int getDistanceSensor1()
// {
//     // digitalWrite(XSHUT_1, HIGH);
//     delay(200);
//     if (!distanceSensor[0].timeoutOccurred())
//     {
//         int data = distanceSensor[0].readRangeSingleMillimeters();
//         // distanceSensor[0].stopContinuous();
//         // digitalWrite(XSHUT_1, LOW);
//         return data;
//     }
//     else
//     {
//         Serial.println("Sensor 1 out of range!");
//         // digitalWrite(XSHUT_1, LOW);
//         return -1;
//     }
// }

// int getDistanceSensor2()
// {
//     // digitalWrite(XSHUT_2, HIGH);
//     delay(200);
//     if (!distanceSensor[1].timeoutOccurred())
//     {
//         int data = distanceSensor[1].readRangeSingleMillimeters();
//         // distanceSensor[1].stopContinuous();
//         // digitalWrite(XSHUT_2, LOW);
//         return data;
//     }
//     else
//     {
//         Serial.println("Sensor 2 out of range!");
//         // digitalWrite(XSHUT_2, LOW);
//         return -1;
//     }
// }

// int getDistanceSensor3()
// {
//     // digitalWrite(XSHUT_3, HIGH);
//     delay(200);
//     if (!distanceSensor[2].timeoutOccurred())
//     {
//         int data = distanceSensor[2].readRangeSingleMillimeters();
//         // distanceSensor[2].stopContinuous();
//         // digitalWrite(XSHUT_3, LOW);
//         return data;
//     }
//     else
//     {
//         Serial.println("Sensor 3 out of range!");
//         // digitalWrite(XSHUT_3, LOW);
//         return -1;
//     }
// }

// int getDistanceSensor4()
// {
//     // digitalWrite(XSHUT_3, HIGH);
//     delay(200);
//     if (!distanceSensor[3].timeoutOccurred())
//     {
//         int data = distanceSensor[3].readRangeSingleMillimeters();
//         // distanceSensor[2].stopContinuous();
//         // digitalWrite(XSHUT_3, LOW);
//         return data;
//     }
//     else
//     {
//         Serial.println("Sensor 4 out of range!");
//         // digitalWrite(XSHUT_3, LOW);
//         return -1;
//     }
// }

// int getDistanceSensor5()
// {
//     // digitalWrite(XSHUT_3, HIGH);
//     delay(200);
//     if (!distanceSensor[4].timeoutOccurred())
//     {
//         int data = distanceSensor[4].readRangeSingleMillimeters();
//         // int data = distanceSensor[4].readRangeContinuousMillimeters();
//         // distanceSensor[2].stopContinuous();
//         // digitalWrite(XSHUT_3, LOW);
//         return data;
//     }
//     else
//     {
//         Serial.println("Sensor 5 out of range!");
//         // digitalWrite(XSHUT_3, LOW);
//         return -1;
//     }
// }

// int getDistanceSensor6()
// {
//     // digitalWrite(XSHUT_3, HIGH);
//     delay(200);
//     if (!distanceSensor[5].timeoutOccurred())
//     {
//         int data = distanceSensor[5].readRangeSingleMillimeters();
//         // int data = distanceSensor[4].readRangeContinuousMillimeters();
//         // distanceSensor[2].stopContinuous();
//         // digitalWrite(XSHUT_3, LOW);
//         return data;
//     }
//     else
//     {
//         Serial.println("Sensor 6 out of range!");
//         // digitalWrite(XSHUT_3, LOW);
//         return -1;
//     }
// }

// int getDistanceSensor7()
// {
//     // digitalWrite(XSHUT_3, HIGH);
//     delay(200);
//     if (!distanceSensor[6].timeoutOccurred())
//     {
//         int data = distanceSensor[6].readRangeSingleMillimeters();
//         // int data = distanceSensor[4].readRangeContinuousMillimeters();
//         // distanceSensor[2].stopContinuous();
//         // digitalWrite(XSHUT_3, LOW);
//         return data;
//     }
//     else
//     {
//         Serial.println("Sensor 7 out of range!");
//         // digitalWrite(XSHUT_3, LOW);
//         return -1;
//     }
// }

// int getDistanceSensor8()
// {
//     // digitalWrite(XSHUT_3, HIGH);
//     delay(200);
//     if (!distanceSensor[7].timeoutOccurred())
//     {
//         int data = distanceSensor[7].readRangeSingleMillimeters();
//         // int data = distanceSensor[4].readRangeContinuousMillimeters();
//         // distanceSensor[2].stopContinuous();
//         // digitalWrite(XSHUT_3, LOW);
//         return data;
//     }
//     else
//     {
//         Serial.println("Sensor 8 out of range!");
//         // digitalWrite(XSHUT_3, LOW);
//         return -1;
//     }
// }

// int getDistanceSensor9()
// {
//     // digitalWrite(XSHUT_3, HIGH);
//     delay(200);
//     if (!distanceSensor[8].timeoutOccurred())
//     {
//         int data = distanceSensor[8].readRangeSingleMillimeters();
//         // int data = distanceSensor[4].readRangeContinuousMillimeters();
//         // distanceSensor[2].stopContinuous();
//         // digitalWrite(XSHUT_3, LOW);
//         return data;
//     }
//     else
//     {
//         Serial.println("Sensor 9 out of range!");
//         // digitalWrite(XSHUT_3, LOW);
//         return -1;
//     }
// }

// int getDistanceSensor10()
// {
//     // digitalWrite(XSHUT_3, HIGH);
//     delay(200);
//     if (!distanceSensor[9].timeoutOccurred())
//     {
//         int data = distanceSensor[9].readRangeSingleMillimeters();
//         // int data = distanceSensor[4].readRangeContinuousMillimeters();
//         // distanceSensor[2].stopContinuous();
//         // digitalWrite(XSHUT_3, LOW);
//         return data;
//     }
//     else
//     {
//         Serial.println("Sensor 10 out of range!");
//         // digitalWrite(XSHUT_3, LOW);
//         return -1;
//     }
// }

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
