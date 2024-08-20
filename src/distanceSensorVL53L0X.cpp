#include "mainheader.hpp"
#include "distanceSensorVL53L0X.hpp"
#include "mainfunctions.hpp"

VL53L0X distanceSensor[10];

bool sensorsStatus[10] = {false, false, false, false, false, false, false, false, false, false};

void beginAllSensors()
{
    beginSensor1();
    delay(40);

    beginSensor2();
    delay(40);

    beginSensor3();
    delay(40);

    beginSensor4();
    delay(40);

    beginSensor5();
    delay(40);

    beginSensor6();
    delay(40);

    beginSensor7();
    delay(40);

    beginSensor8();
    delay(40);

    beginSensor9();
    delay(40);

    beginSensor10();
    delay(40);
}

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

void beginSensor1()
{
    Serial.println(F("\nBegining sensor 1"));
    // Wire.begin();
    digitalWrite(XSHUT_1, HIGH);
    delay(100);
    distanceSensor[0].setAddress(SENSOR_ADDRESS_1);
    distanceSensor[0].setTimeout(500);
    if (!distanceSensor[0].init()) // bool true for using 2V8 mode, false for using standard mode
    {
        Serial.println("Failed to boot VL53L0X Sensor 1");
        sensorsStatus[0] = false;
        digitalWrite(XSHUT_1, LOW);
    }
    else
    {
        Serial.println("VL53L0X Sensor 1 booted");
        sensorsStatus[0] = true;
        distanceSensor[0].setSignalRateLimit(0.1);                                 // 0.1 MCPS
        distanceSensor[0].setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);   // laser pulse periods 18 PCLKs
        distanceSensor[0].setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14); // Laser pulse periods 14 PCLKs
        distanceSensor[0].setMeasurementTimingBudget(200000);                      // HIGH ACCURACY timming budget 200 ms, HIGH SPEED 20 ms
        // distanceSensor[0].startContinuous(200);
        Serial.println("Sensor 1 distance: ");
        Serial.print(getDistanceSensor1());
        Serial.println(" mm\n");
        // digitalWrite(XSHUT_1, LOW);
    }
}

void beginSensor2()
{
    Serial.println(F("\nBegining sensor 2"));
    // Wire.begin();
    digitalWrite(XSHUT_2, HIGH);
    delay(100);
    distanceSensor[1].setAddress(SENSOR_ADDRESS_2);
    distanceSensor[1].setTimeout(500);
    if (!distanceSensor[1].init())
    {
        Serial.println("Failed to boot VL53L0X Sensor 2");
        sensorsStatus[1] = false;
        digitalWrite(XSHUT_2, LOW);
        // beginSensor2();
    }
    else
    {
        Serial.println("VL53L0X Sensor 2 booted");
        sensorsStatus[1] = true;
        distanceSensor[1].setSignalRateLimit(0.1);                                 // 0.1 MCPS
        distanceSensor[1].setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);   // laser pulse periods 18 PCLKs
        distanceSensor[1].setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14); // Laser pulse periods 14 PCLKs
        distanceSensor[1].setMeasurementTimingBudget(200000);                      // HIGH ACCURACY timming budget 200 ms, HIGH SPEED 20 ms
        // distanceSensor[1].startContinuous(200);
        Serial.println("Sensor 2 distance: ");
        Serial.print(getDistanceSensor2());
        Serial.println(" mm\n");
        // digitalWrite(XSHUT_2, LOW);
    }
}

void beginSensor3()
{
    Serial.println(F("\nBegining sensor 3"));
    // Wire.begin();
    digitalWrite(XSHUT_3, HIGH);
    delay(100);
    distanceSensor[2].setAddress(SENSOR_ADDRESS_3);
    distanceSensor[2].setTimeout(500);
    if (!distanceSensor[2].init())
    {
        Serial.println("Failed to boot VL53L0X Sensor 3");
        sensorsStatus[2] = false;
        digitalWrite(XSHUT_3, LOW);
        // beginSensor3();
    }
    else
    {
        Serial.println("VL53L0X Sensor 3 booted");
        sensorsStatus[2] = true;
        distanceSensor[2].setSignalRateLimit(0.1);                                 // 0.1 MCPS
        distanceSensor[2].setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);   // laser pulse periods 18 PCLKs
        distanceSensor[2].setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14); // Laser pulse periods 14 PCLKs
        distanceSensor[2].setMeasurementTimingBudget(200000);                      // HIGH ACCURACY timming budget 200 ms, HIGH SPEED 20 ms
        // distanceSensor[2].startContinuous(200);
        Serial.println("Sensor 3 distance: ");
        Serial.print(getDistanceSensor3());
        Serial.println(" mm\n");
        // digitalWrite(XSHUT_3, LOW);
    }
}

void beginSensor4()
{
    Serial.println(F("\nBegining sensor 4"));
    // Wire.begin();
    digitalWrite(XSHUT_4, HIGH);
    delay(100);
    distanceSensor[3].setAddress(SENSOR_ADDRESS_4);
    distanceSensor[3].setTimeout(500);
    if (!distanceSensor[3].init())
    {
        Serial.println("Failed to boot VL53L0X Sensor 3");
        sensorsStatus[3] = false;
        digitalWrite(XSHUT_4, LOW);
        // beginSensor3();
    }
    else
    {
        Serial.println("VL53L0X Sensor 4 booted");
        sensorsStatus[3] = true;
        distanceSensor[3].setSignalRateLimit(0.1);                                 // 0.1 MCPS
        distanceSensor[3].setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);   // laser pulse periods 18 PCLKs
        distanceSensor[3].setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14); // Laser pulse periods 14 PCLKs
        distanceSensor[3].setMeasurementTimingBudget(200000);                      // HIGH ACCURACY timming budget 200 ms, HIGH SPEED 20 ms
        // distanceSensor[2].startContinuous(200);
        Serial.println("Sensor 4 distance: ");
        Serial.print(getDistanceSensor4());
        Serial.println(" mm\n");
        // digitalWrite(XSHUT_3, LOW);
    }
}

void beginSensor5()
{
    Serial.println(F("\nBegining sensor 5"));
    // Wire.begin();
    digitalWrite(XSHUT_5, HIGH);
    delay(100);
    distanceSensor[4].setAddress(SENSOR_ADDRESS_5);
    distanceSensor[4].setTimeout(500);
    if (!distanceSensor[4].init())
    {
        Serial.println("Failed to boot VL53L0X Sensor 3");
        sensorsStatus[4] = false;
        digitalWrite(XSHUT_5, LOW);
        // beginSensor3();
    }
    else
    {
        Serial.println("VL53L0X Sensor 5 booted");
        sensorsStatus[4] = true;
        distanceSensor[4].setSignalRateLimit(0.1);                                 // 0.1 MCPS
        distanceSensor[4].setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);   // laser pulse periods 18 PCLKs
        distanceSensor[4].setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14); // Laser pulse periods 14 PCLKs
        distanceSensor[4].setMeasurementTimingBudget(200000);                      // HIGH ACCURACY timming budget 200 ms, HIGH SPEED 20 ms
        // distanceSensor[2].startContinuous(200);
        Serial.println("Sensor 5 distance: ");
        Serial.print(getDistanceSensor5());
        Serial.println(" mm\n");
        // digitalWrite(XSHUT_3, LOW);
    }
}


// void beginSensor4()
// {
//     Serial.println(F("\nBegining sensor 4"));
//     digitalWrite(WAYANG_HAND_4, LOW);
//     delay(40);
//     distanceSensor[3].setAddress(SENSOR_ADDRESS_4);
//     distanceSensor[3].setTimeout(500);
//     if (!distanceSensor[3].init())
//     {
//         Serial.println("Failed to boot VL53L0X Sensor 4");
//         digitalWrite(WAYANG_HAND_4, HIGH);
//     }
//     else
//     {
//         Serial.println("VL53L0X Sensor 4 booted");
//         sensorsStatus[3] = true;
//         digitalWrite(WAYANG_HAND_4, HIGH);
//     }
// }

// void beginSensor5()
// {
//     Serial.println(F("\nBegining sensor 5"));
//     digitalWrite(WAYANG_HAND_5, LOW);
//     delay(40);
//     distanceSensor[4].setAddress(SENSOR_ADDRESS_5);
//     distanceSensor[4].setTimeout(500);
//     if (!distanceSensor[4].init())
//     {
//         Serial.println("Failed to boot VL53L0X Sensor 5");
//         digitalWrite(WAYANG_HAND_5, HIGH);
//     }
//     else
//     {
//         Serial.println("VL53L0X Sensor 5 booted");
//         sensorsStatus[4] = true;
//         digitalWrite(WAYANG_HAND_5, HIGH);
//     }
// }

// void beginSensor6()
// {
//     Serial.println(F("\nBegining sensor 6"));
//     digitalWrite(WAYANG_HAND_6, LOW);
//     delay(40);
//     distanceSensor[5].setAddress(SENSOR_ADDRESS_6);
//     distanceSensor[5].setTimeout(500);
//     if (!distanceSensor[5].init())
//     {
//         Serial.println("Failed to boot VL53L0X Sensor 6");
//         digitalWrite(WAYANG_HAND_6, HIGH);
//     }
//     else
//     {
//         Serial.println("VL53L0X Sensor 6 booted");
//         sensorsStatus[5] = true;
//         digitalWrite(WAYANG_HAND_6, HIGH);
//     }
// }

// void beginSensor7()
// {
//     Serial.println(F("\nBegining sensor 7"));
//     digitalWrite(WAYANG_HAND_7, LOW);
//     delay(40);
//     distanceSensor[6].setAddress(SENSOR_ADDRESS_7);
//     distanceSensor[6].setTimeout(500);
//     if (!distanceSensor[6].init())
//     {
//         Serial.println("Failed to boot VL53L0X Sensor 7");
//         digitalWrite(WAYANG_HAND_7, HIGH);
//     }
//     else
//     {
//         Serial.println("VL53L0X Sensor 7 booted");
//         sensorsStatus[6] = true;
//         digitalWrite(WAYANG_HAND_7, HIGH);
//     }
// }

// void beginSensor8()
// {
//     Serial.println(F("\nBegining sensor 8"));
//     digitalWrite(WAYANG_HAND_8, LOW);
//     delay(40);
//     distanceSensor[7].setAddress(SENSOR_ADDRESS_8);
//     distanceSensor[7].setTimeout(500);
//     if (!distanceSensor[7].init())
//     {
//         Serial.println("Failed to boot VL53L0X Sensor 8");
//         digitalWrite(WAYANG_HAND_8, HIGH);
//     }
//     else
//     {
//         Serial.println("VL53L0X Sensor 8 booted");
//         sensorsStatus[7] = true;
//         digitalWrite(WAYANG_HAND_8, HIGH);
//     }
// }

// void beginSensor9()
// {
//     Serial.println(F("\nBegining sensor 9"));
//     digitalWrite(WAYANG_HAND_9, LOW);
//     delay(40);
//     distanceSensor[8].setAddress(SENSOR_ADDRESS_9);
//     distanceSensor[8].setTimeout(500);
//     if (!distanceSensor[8].init())
//     {
//         Serial.println("Failed to boot VL53L0X Sensor 9");
//         digitalWrite(WAYANG_HAND_9, HIGH);
//     }
//     else
//     {
//         Serial.println("VL53L0X Sensor 9 booted");
//         sensorsStatus[8] = true;
//         digitalWrite(WAYANG_HAND_9, HIGH);
//     }
// }

// void beginSensor10()
// {
//     Serial.println(F("\nBegining sensor 10"));
//     digitalWrite(WAYANG_HAND_10, LOW);
//     delay(40);
//     distanceSensor[9].setAddress(SENSOR_ADDRESS_10);
//     distanceSensor[9].setTimeout(500);
//     if (!distanceSensor[9].init())
//     {
//         Serial.println("Failed to boot VL53L0X Sensor 10\n");
//         digitalWrite(WAYANG_HAND_10, HIGH);
//     }
//     else
//     {
//         Serial.println("VL53L0X Sensor 10 booted\n");
//         sensorsStatus[9] = true;
//         digitalWrite(WAYANG_HAND_10, HIGH);
//     }
// }

int getDistanceSensor1()
{
    // digitalWrite(XSHUT_1, HIGH);
    delay(200);
    if (!distanceSensor[0].timeoutOccurred())
    {
        int data = distanceSensor[0].readRangeSingleMillimeters();
        // distanceSensor[0].stopContinuous();
        // digitalWrite(XSHUT_1, LOW);
        return data;
    }
    else
    {
        Serial.println("Sensor 1 out of range!");
        // digitalWrite(XSHUT_1, LOW);
        return -1;
    }
}

int getDistanceSensor2()
{
    // digitalWrite(XSHUT_2, HIGH);
    delay(200);
    if (!distanceSensor[1].timeoutOccurred())
    {   
        int data = distanceSensor[1].readRangeSingleMillimeters();
        // distanceSensor[1].stopContinuous();
        // digitalWrite(XSHUT_2, LOW);
        return data;
    }
    else
    {
        Serial.println("Sensor 2 out of range!");
        // digitalWrite(XSHUT_2, LOW);
        return -1;
    }
}

int getDistanceSensor3()
{
    // digitalWrite(XSHUT_3, HIGH);
    delay(200);
    if (!distanceSensor[2].timeoutOccurred())
    {
        int data = distanceSensor[2].readRangeSingleMillimeters();
        // distanceSensor[2].stopContinuous();
        // digitalWrite(XSHUT_3, LOW);
        return data;
    }
    else
    {
        Serial.println("Sensor 3 out of range!");
        // digitalWrite(XSHUT_3, LOW);
        return -1;
    }
}

int getDistanceSensor4()
{
    // digitalWrite(XSHUT_3, HIGH);
    delay(200);
    if (!distanceSensor[3].timeoutOccurred())
    {
        int data = distanceSensor[3].readRangeSingleMillimeters();
        // distanceSensor[2].stopContinuous();
        // digitalWrite(XSHUT_3, LOW);
        return data;
    }
    else
    {
        Serial.println("Sensor 4 out of range!");
        // digitalWrite(XSHUT_3, LOW);
        return -1;
    }
}

int getDistanceSensor5()
{
    // digitalWrite(XSHUT_3, HIGH);
    delay(200);
    if (!distanceSensor[4].timeoutOccurred())
    {
        int data = distanceSensor[4].readRangeSingleMillimeters();
        // distanceSensor[2].stopContinuous();
        // digitalWrite(XSHUT_3, LOW);
        return data;
    }
    else
    {
        Serial.println("Sensor 5 out of range!");
        // digitalWrite(XSHUT_3, LOW);
        return -1;
    }
}


// int getDistanceSensor2()
// {
//     digitalWrite(WAYANG_HAND_2, HIGH);
//     delay(100);
//     distanceSensor[1].setSignalRateLimit(0.1);                                 // 0.1 MCPS
//     distanceSensor[1].setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);   // laser pulse periods 18 PCLKs
//     distanceSensor[1].setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14); // Laser pulse periods 14 PCLKs
//     distanceSensor[1].setMeasurementTimingBudget(200000);                      // HIGH ACCURACY timming budget 200 ms, HIGH SPEED 20 ms

//     // distanceSensor[1].startContinuous(100);
//     int distanceData = distanceSensor[1].readRangeSingleMillimeters();
//     if (!distanceSensor[1].timeoutOccurred())
//     {
//         // distanceSensor[1].stopContinuous();
//         return distanceData;
//     }
//     else
//     {
//         Serial.println("Sensor 2 out of range!");
//         digitalWrite(WAYANG_HAND_2, LOW);
//         // distanceSensor[1].stopContinuous();
//         return -1;
//     }
// }

// int getDistanceSensor3()
// {
//     digitalWrite(WAYANG_HAND_3, LOW);
//     delay(100);
//     distanceSensor[2].startContinuous(33);
//     int distanceData = distanceSensor[2].readRangeContinuousMillimeters();
//     if (!distanceSensor[2].timeoutOccurred())
//     {
//         // distanceSensor[2].stopContinuous();
//         return distanceData;
//     }
//     else
//     {
//         Serial.println("Sensor 3 out of range!");
//         digitalWrite(WAYANG_HAND_3, HIGH);
//         // distanceSensor[2].stopContinuous();
//         return -1;
//     }
// }

// int getDistanceSensor4()
// {
//     digitalWrite(WAYANG_HAND_4, LOW);
//     delay(100);
//     distanceSensor[3].startContinuous(100);
//     int distanceData = distanceSensor[3].readRangeContinuousMillimeters();
//     if (!distanceSensor[3].timeoutOccurred())
//     {
//         return distanceData;
//     }
//     else
//     {
//         Serial.println("Sensor 4 out of range!");
//         digitalWrite(WAYANG_HAND_4, HIGH);
//         return -1;
//     }
// }

// int getDistanceSensor5()
// {
//     digitalWrite(WAYANG_HAND_5, LOW);
//     delay(100);
//     distanceSensor[4].startContinuous(100);
//     int distanceData = distanceSensor[4].readRangeContinuousMillimeters();
//     if (!distanceSensor[4].timeoutOccurred())
//     {
//         return distanceData;
//     }
//     else
//     {
//         Serial.println("Sensor 5 out of range!");
//         digitalWrite(WAYANG_HAND_5, HIGH);
//         return -1;
//     }
// }

// int getDistanceSensor6()
// {
//     digitalWrite(WAYANG_HAND_6, LOW);
//     delay(100);
//     distanceSensor[5].startContinuous(100);
//     int distanceData = distanceSensor[5].readRangeContinuousMillimeters();
//     if (!distanceSensor[5].timeoutOccurred())
//     {
//         return distanceData;
//     }
//     else
//     {
//         Serial.println("Sensor 6 out of range!");
//         digitalWrite(WAYANG_HAND_6, HIGH);
//         return -1;
//     }
// }

// int getDistanceSensor7()
// {
//     digitalWrite(WAYANG_HAND_7, LOW);
//     delay(100);
//     distanceSensor[6].startContinuous(100);
//     int distanceData = distanceSensor[6].readRangeContinuousMillimeters();
//     if (!distanceSensor[6].timeoutOccurred())
//     {
//         return distanceData;
//     }
//     else
//     {
//         Serial.println("Sensor 7 out of range!");
//         digitalWrite(WAYANG_HAND_7, HIGH);
//         return -1;
//     }
// }

// int getDistanceSensor8()
// {
//     digitalWrite(WAYANG_HAND_8, LOW);
//     delay(100);
//     distanceSensor[7].startContinuous(100);
//     int distanceData = distanceSensor[7].readRangeContinuousMillimeters();
//     if (!distanceSensor[7].timeoutOccurred())
//     {
//         return distanceData;
//     }
//     else
//     {
//         Serial.println("Sensor 8 out of range!");
//         digitalWrite(WAYANG_HAND_8, HIGH);
//         return -1;
//     }
// }

// int getDistanceSensor9()
// {
//     digitalWrite(WAYANG_HAND_9, LOW);
//     delay(100);
//     distanceSensor[8].startContinuous(100);
//     int distanceData = distanceSensor[8].readRangeContinuousMillimeters();
//     if (!distanceSensor[8].timeoutOccurred())
//     {
//         return distanceData;
//     }
//     else
//     {
//         Serial.println("Sensor 9 out of range!");
//         digitalWrite(WAYANG_HAND_9, HIGH);
//         return -1;
//     }
// }

// int getDistanceSensor10()
// {
//     digitalWrite(WAYANG_HAND_10, LOW);
//     delay(100);
//     distanceSensor[9].startContinuous(100);
//     int distanceData = distanceSensor[9].readRangeContinuousMillimeters();
//     if (!distanceSensor[9].timeoutOccurred())
//     {
//         return distanceData;
//     }
//     else
//     {
//         Serial.println("Sensor 10 out of range!");
//         digitalWrite(WAYANG_HAND_10, HIGH);
//         return -1;
//     }
// }

bool getSensorStatus(int num)
{
    return sensorsStatus[num - 1];
}

// int getDistanceSensor1_v2()
// {
//     digitalWrite(WAYANG_HAND_1, HIGH);
//     delay(100);
//     distanceSensorAllInOne.setSignalRateLimit(0.1);                                 // 0.1 MCPS
//     distanceSensorAllInOne.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);   // laser pulse periods 18 PCLKs
//     distanceSensorAllInOne.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14); // Laser pulse periods 14 PCLKs
//     distanceSensorAllInOne.setMeasurementTimingBudget(200000);                      // HIGH ACCURACY timming budget 200 ms, HIGH SPEED 20 ms

//     // distanceSensor[0].startContinuous(33);
//     int distanceData = distanceSensor[0].readRangeSingleMillimeters();
//     if (!distanceSensor[0].timeoutOccurred())
//     {
//         // distanceSensor[0].stopContinuous();
//         return distanceData;
//     }
//     else
//     {
//         Serial.println("Sensor 1 out of range!");
//         digitalWrite(WAYANG_HAND_1, LOW);
//         // distanceSensor[0].stopContinuous();
//         return -1;
//     }
// }