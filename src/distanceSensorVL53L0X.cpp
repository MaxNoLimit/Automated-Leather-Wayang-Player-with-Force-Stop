#include "mainheader.hpp"
#include "distanceSensorVL53L0X.hpp"
#include "mainfunctions.hpp"

// VL53L0X distanceSensor[10];

bool sensorsStatus[10] = {false, false, false, false, false, false, false, false, false, false};

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
//         sensorsStatus[0] = false;
//         digitalWrite(XSHUT_1, LOW);
//     }
//     else
//     {
//         Serial.println("VL53L0X Sensor 1 booted");
//         sensorsStatus[0] = true;
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
//         sensorsStatus[1] = false;
//         digitalWrite(XSHUT_2, LOW);
//         // beginSensor2();
//     }
//     else
//     {
//         Serial.println("VL53L0X Sensor 2 booted");
//         sensorsStatus[1] = true;
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
//         sensorsStatus[2] = false;
//         digitalWrite(XSHUT_3, LOW);
//         // beginSensor3();
//     }
//     else
//     {
//         Serial.println("VL53L0X Sensor 3 booted");
//         sensorsStatus[2] = true;
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
//         sensorsStatus[3] = false;
//         digitalWrite(XSHUT_4, LOW);
//         // beginSensor3();
//     }
//     else
//     {
//         Serial.println("VL53L0X Sensor 4 booted");
//         sensorsStatus[3] = true;
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
//         sensorsStatus[4] = false;
//         digitalWrite(XSHUT_5, LOW);
//         // beginSensor3();
//     }
//     else
//     {
//         Serial.println("VL53L0X Sensor 5 booted");
//         sensorsStatus[4] = true;

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
//         sensorsStatus[5] = false;
//         digitalWrite(XSHUT_6, LOW);
//         // beginSensor3();
//     }
//     else
//     {
//         Serial.println("VL53L0X Sensor 6 booted");
//         sensorsStatus[5] = true;

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
//         sensorsStatus[6] = false;
//         digitalWrite(XSHUT_7, LOW);
//         // beginSensor3();
//     }
//     else
//     {
//         Serial.println("VL53L0X Sensor 7 booted");
//         sensorsStatus[6] = true;

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

bool getSensorStatus(int num)
{
    return sensorsStatus[num - 1];
}

int getDistanceSensor1()
{
    bool _isLoop = true;
    bool _isRun = true;
    int _receivedValue;
    while (_isLoop)
    {
        Serial3.flush();
        if (_isRun)
        {
            _isRun = false;
            Serial.println(F("Sending 0x31 to UART3"));
            Serial3.write(REQUEST_DATA_SENSOR_1);
            // delay(100);
        }
        else
        {
            _isRun = true;
            _isLoop = false;
            _receivedValue = Serial3.readString().toInt();
            Serial.println(_receivedValue);
            Serial3.flush();
        }
    }
    return _receivedValue;
}

int getDistanceSensor2()
{
    bool _isLoop = true;
    bool _isRun = true;
    int _receivedValue;
    while (_isLoop)
    {
        Serial3.flush();
        if (_isRun)
        {
            _isRun = false;
            Serial.println(F("Sending 0x32 to UART3"));
            Serial3.write(REQUEST_DATA_SENSOR_2);
            // delay(100);
        }
        else
        {
            _isRun = true;
            _isLoop = false;
            _receivedValue = Serial3.readString().toInt();
            Serial.println(_receivedValue);
            Serial3.flush();
        }
    }
    return _receivedValue;
}

int getDistanceSensor3()
{
    bool _isLoop = true;
    bool _isRun = true;
    int _receivedValue;
    while (_isLoop)
    {
        Serial3.flush();
        if (_isRun)
        {
            _isRun = false;
            Serial.println(F("Sending 0x33 to UART3"));
            Serial3.write(REQUEST_DATA_SENSOR_3);
            // delay(100);
        }
        else
        {
            _isRun = true;
            _isLoop = false;
            _receivedValue = Serial3.readString().toInt();
            Serial.println(_receivedValue);
            Serial3.flush();
        }
    }
    return _receivedValue;
}

int getDistanceSensor4()
{
    bool _isLoop = true;
    bool _isRun = true;
    int _receivedValue;
    while (_isLoop)
    {
        Serial3.flush();
        if (_isRun)
        {
            _isRun = false;
            Serial.println(F("Sending 0x34 to UART3"));
            Serial3.write(REQUEST_DATA_SENSOR_4);
            // delay(100);
        }
        else
        {
            _isRun = true;
            _isLoop = false;
            _receivedValue = Serial3.readString().toInt();
            Serial.println(_receivedValue);
            Serial3.flush();
        }
    }
    return _receivedValue;
}

int getDistanceSensor5()
{
    bool _isLoop = true;
    bool _isRun = true;
    int _receivedValue;
    while (_isLoop)
    {
        Serial3.flush();
        if (_isRun)
        {
            _isRun = false;
            Serial.println(F("Sending 0x35 to UART3"));
            Serial3.write(REQUEST_DATA_SENSOR_5);
            // delay(100);
        }
        else
        {
            _isRun = true;
            _isLoop = false;
            _receivedValue = Serial3.readString().toInt();
            Serial.println(_receivedValue);
            Serial3.flush();
        }
    }
    return _receivedValue;
}

int getDistanceSensor6()
{
    bool _isLoop = true;
    bool _isRun = true;
    int _receivedValue;
    while (_isLoop)
    {
        Serial3.flush();
        if (_isRun)
        {
            _isRun = false;
            Serial.println(F("Sending 0x36 to UART3"));
            Serial3.write(REQUEST_DATA_SENSOR_6);
            delay(100);
        }
        else
        {
            _isRun = true;
            _isLoop = false;
            _receivedValue = Serial3.readString().toInt();
            Serial.println(_receivedValue);
            Serial3.flush();
        }
    }
    return _receivedValue;
}

int getDistanceSensor7()
{
    bool _isLoop = true;
    bool _isRun = true;
    int _receivedValue;
    while (_isLoop)
    {
        Serial3.flush();
        if (_isRun)
        {
            _isRun = false;
            Serial.println(F("Sending 0x37 to UART3"));
            Serial3.write(REQUEST_DATA_SENSOR_7);
            delay(10);
        }
        else
        {
            _isRun = true;
            _isLoop = false;
            _receivedValue = Serial3.readString().toInt();
            Serial.println(_receivedValue);
        }
    }
    return _receivedValue;
}

int getDistanceSensor8()
{
    bool _isLoop = true;
    bool _isRun = true;
    int _receivedValue;
    while (_isLoop)
    {
        Serial3.flush();
        if (_isRun)
        {
            _isRun = false;
            Serial.println(F("Sending 0x38 to UART3"));
            Serial3.write(REQUEST_DATA_SENSOR_8);
            delay(10);
        }
        else
        {
            _isRun = true;
            _isLoop = false;
            _receivedValue = Serial3.readString().toInt();
            Serial.println(_receivedValue);
        }
    }
    return _receivedValue;
}

int getDistanceSensor9()
{
    bool _isLoop = true;
    bool _isRun = true;
    int _receivedValue;
    while (_isLoop)
    {
        Serial3.flush();
        if (_isRun)
        {
            _isRun = false;
            Serial.println(F("Sending 0x39 to UART3"));
            Serial3.write(REQUEST_DATA_SENSOR_9);
            delay(10);
        }
        else
        {
            _isRun = true;
            _isLoop = false;
            _receivedValue = Serial3.readString().toInt();
            Serial.println(_receivedValue);
        }
    }
    return _receivedValue;
}

int getDistanceSensor10()
{
    bool _isLoop = true;
    bool _isRun = true;
    int _receivedValue;
    while (_isLoop)
    {
        Serial3.flush();
        if (_isRun)
        {
            _isRun = false;
            Serial.println(F("Sending 0x40 to UART3"));
            Serial3.write(REQUEST_DATA_SENSOR_10);
            delay(10);
        }
        else
        {
            _isRun = true;
            _isLoop = false;
            _receivedValue = Serial3.readString().toInt();
            Serial.println(_receivedValue);
        }
    }
    return _receivedValue;
}
