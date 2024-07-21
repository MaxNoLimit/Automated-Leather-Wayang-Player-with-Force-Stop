#include "mainheader.hpp"
#include "distanceSensorVL53L0X.hpp"

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

void beginSensor1()
{
    Serial.println(F("Begining sensor 1"));
    digitalWrite(WAYANG_HAND_1, HIGH);
    distanceSensor[0].setAddress(SENSOR_ADDRESS_1);
    distanceSensor[0].setTimeout(500);
    if (!distanceSensor[0].init())
    {
        Serial.println("Failed to boot VL53L0X Sensor 1");
        digitalWrite(WAYANG_HAND_1, LOW);
    }
    else
    {
        Serial.println("VL53L0X Sensor 1 booted");
        sensorsStatus[0] = true;
        digitalWrite(WAYANG_HAND_1, LOW);
    }
}

void beginSensor2()
{
    Serial.println(F("Begining sensor 2"));
    digitalWrite(WAYANG_HAND_2, HIGH);
    distanceSensor[1].setAddress(SENSOR_ADDRESS_2);
    distanceSensor[1].setTimeout(500);
    if (!distanceSensor[1].init())
    {
        Serial.println("Failed to boot VL53L0X Sensor 2");
        digitalWrite(WAYANG_HAND_2, LOW);
    }
    else
    {
        Serial.println("VL53L0X Sensor 2 booted");
        sensorsStatus[1] = true;
        digitalWrite(WAYANG_HAND_2, LOW);
    }
}

void beginSensor3()
{
    Serial.println(F("Begining sensor 3"));
    digitalWrite(WAYANG_HAND_3, HIGH);
    distanceSensor[2].setAddress(SENSOR_ADDRESS_3);
    distanceSensor[2].setTimeout(500);
    if (!distanceSensor[2].init())
    {
        Serial.println("Failed to boot VL53L0X Sensor 3");
        digitalWrite(WAYANG_HAND_3, LOW);
    }
    else
    {
        Serial.println("VL53L0X Sensor 3 booted");
        sensorsStatus[2] = true;
        digitalWrite(WAYANG_HAND_3, LOW);
    }
}

void beginSensor4()
{
    Serial.println(F("Begining sensor 4"));
    digitalWrite(WAYANG_HAND_4, HIGH);
    distanceSensor[3].setAddress(SENSOR_ADDRESS_4);
    distanceSensor[3].setTimeout(500);
    if (!distanceSensor[3].init())
    {
        Serial.println("Failed to boot VL53L0X Sensor 4");
        digitalWrite(WAYANG_HAND_4, LOW);
    }
    else
    {
        Serial.println("VL53L0X Sensor 4 booted");
        sensorsStatus[3] = true;
        digitalWrite(WAYANG_HAND_4, LOW);
    }
}

void beginSensor5()
{
    Serial.println(F("Begining sensor 5"));
    digitalWrite(WAYANG_HAND_5, HIGH);
    distanceSensor[4].setAddress(SENSOR_ADDRESS_5);
    distanceSensor[4].setTimeout(500);
    if (!distanceSensor[4].init())
    {
        Serial.println("Failed to boot VL53L0X Sensor 5");
        digitalWrite(WAYANG_HAND_5, LOW);
    }
    else
    {
        Serial.println("VL53L0X Sensor 5 booted");
        sensorsStatus[4] = true;
        digitalWrite(WAYANG_HAND_5, LOW);
    }
}

void beginSensor6()
{
    Serial.println(F("Begining sensor 6"));
    digitalWrite(WAYANG_HAND_6, HIGH);
    distanceSensor[5].setAddress(SENSOR_ADDRESS_6);
    distanceSensor[5].setTimeout(500);
    if (!distanceSensor[5].init())
    {
        Serial.println("Failed to boot VL53L0X Sensor 6");
        digitalWrite(WAYANG_HAND_6, LOW);
    }
    else
    {
        Serial.println("VL53L0X Sensor 6 booted");
        sensorsStatus[5] = true;
        digitalWrite(WAYANG_HAND_6, LOW);
    }
}

void beginSensor7()
{
    Serial.println(F("Begining sensor 7"));
    digitalWrite(WAYANG_HAND_7, HIGH);
    distanceSensor[6].setAddress(SENSOR_ADDRESS_7);
    distanceSensor[6].setTimeout(500);
    if (!distanceSensor[6].init())
    {
        Serial.println("Failed to boot VL53L0X Sensor 7");
        digitalWrite(WAYANG_HAND_7, LOW);
    }
    else
    {
        Serial.println("VL53L0X Sensor 7 booted");
        sensorsStatus[6] = true;
        digitalWrite(WAYANG_HAND_7, LOW);
    }
}

void beginSensor8()
{
    Serial.println(F("Begining sensor 8"));
    digitalWrite(WAYANG_HAND_8, HIGH);
    distanceSensor[7].setAddress(SENSOR_ADDRESS_8);
    distanceSensor[7].setTimeout(500);
    if (!distanceSensor[7].init())
    {
        Serial.println("Failed to boot VL53L0X Sensor 8");
        digitalWrite(WAYANG_HAND_8, LOW);
    }
    else
    {
        Serial.println("VL53L0X Sensor 8 booted");
        sensorsStatus[7] = true;
        digitalWrite(WAYANG_HAND_8, LOW);
    }
}

void beginSensor9()
{
    Serial.println(F("Begining sensor 9"));
    digitalWrite(WAYANG_HAND_9, HIGH);
    distanceSensor[8].setAddress(SENSOR_ADDRESS_9);
    distanceSensor[8].setTimeout(500);
    if (!distanceSensor[8].init())
    {
        Serial.println("Failed to boot VL53L0X Sensor 9");
        digitalWrite(WAYANG_HAND_9, LOW);
    }
    else
    {
        Serial.println("VL53L0X Sensor 9 booted");
        sensorsStatus[8] = true;
        digitalWrite(WAYANG_HAND_9, LOW);
    }
}

void beginSensor10()
{
    Serial.println(F("Begining sensor 10"));
    digitalWrite(WAYANG_HAND_10, HIGH);
    distanceSensor[9].setAddress(SENSOR_ADDRESS_10);
    distanceSensor[9].setTimeout(500);
    if (!distanceSensor[9].init())
    {
        Serial.println("Failed to boot VL53L0X Sensor 10");
        digitalWrite(WAYANG_HAND_10, LOW);
    }
    else
    {
        Serial.println("VL53L0X Sensor 10 booted");
        sensorsStatus[9] = true;
        digitalWrite(WAYANG_HAND_10, LOW);
    }
}

int getDistanceSensor1()
{
    digitalWrite(WAYANG_HAND_1, HIGH);
    delay(100);
    distanceSensor[0].startContinuous(100);
    int distanceData = distanceSensor[0].readRangeContinuousMillimeters();
    if (!distanceSensor[0].timeoutOccurred())
    {
        return distanceData;
    }
    else
    {
        Serial.println("Sensor 1 out of range!");
        digitalWrite(WAYANG_HAND_1, LOW);
        return 2000;
    }
}

int getDistanceSensor2()
{
    digitalWrite(WAYANG_HAND_2, HIGH);
    delay(100);
    distanceSensor[1].startContinuous(100);
    int distanceData = distanceSensor[1].readRangeContinuousMillimeters();
    if (!distanceSensor[1].timeoutOccurred())
    {
        return distanceData;
    }
    else
    {
        Serial.println("Sensor 2 out of range!");
        digitalWrite(WAYANG_HAND_2, LOW);
        return 2000;
    }
}

int getDistanceSensor3()
{
    digitalWrite(WAYANG_HAND_3, HIGH);
    delay(100);
    distanceSensor[2].startContinuous(100);
    int distanceData = distanceSensor[2].readRangeContinuousMillimeters();
    if (!distanceSensor[2].timeoutOccurred())
    {
        return distanceData;
    }
    else
    {
        Serial.println("Sensor 3 out of range!");
        digitalWrite(WAYANG_HAND_3, LOW);
        return 2000;
    }
}

int getDistanceSensor4()
{
    digitalWrite(WAYANG_HAND_4, HIGH);
    delay(100);
    distanceSensor[3].startContinuous(100);
    int distanceData = distanceSensor[3].readRangeContinuousMillimeters();
    if (!distanceSensor[3].timeoutOccurred())
    {
        return distanceData;
    }
    else
    {
        Serial.println("Sensor 4 out of range!");
        digitalWrite(WAYANG_HAND_4, LOW);
        return 2000;
    }
}

int getDistanceSensor5()
{
    digitalWrite(WAYANG_HAND_5, HIGH);
    delay(100);
    distanceSensor[4].startContinuous(100);
    int distanceData = distanceSensor[4].readRangeContinuousMillimeters();
    if (!distanceSensor[4].timeoutOccurred())
    {
        return distanceData;
    }
    else
    {
        Serial.println("Sensor 5 out of range!");
        digitalWrite(WAYANG_HAND_5, LOW);
        return 2000;
    }
}

int getDistanceSensor6()
{
    digitalWrite(WAYANG_HAND_6, HIGH);
    delay(100);
    distanceSensor[5].startContinuous(100);
    int distanceData = distanceSensor[5].readRangeContinuousMillimeters();
    if (!distanceSensor[5].timeoutOccurred())
    {
        return distanceData;
    }
    else
    {
        Serial.println("Sensor 6 out of range!");
        digitalWrite(WAYANG_HAND_6, LOW);
        return 2000;
    }
}

int getDistanceSensor7()
{
    digitalWrite(WAYANG_HAND_7, HIGH);
    delay(100);
    distanceSensor[6].startContinuous(100);
    int distanceData = distanceSensor[6].readRangeContinuousMillimeters();
    if (!distanceSensor[6].timeoutOccurred())
    {
        return distanceData;
    }
    else
    {
        Serial.println("Sensor 7 out of range!");
        digitalWrite(WAYANG_HAND_7, LOW);
        return 2000;
    }
}

int getDistanceSensor8()
{
    digitalWrite(WAYANG_HAND_8, HIGH);
    delay(100);
    distanceSensor[7].startContinuous(100);
    int distanceData = distanceSensor[7].readRangeContinuousMillimeters();
    if (!distanceSensor[7].timeoutOccurred())
    {
        return distanceData;
    }
    else
    {
        Serial.println("Sensor 8 out of range!");
        digitalWrite(WAYANG_HAND_8, LOW);
        return 2000;
    }
}

int getDistanceSensor9()
{
    digitalWrite(WAYANG_HAND_9, HIGH);
    delay(100);
    distanceSensor[8].startContinuous(100);
    int distanceData = distanceSensor[8].readRangeContinuousMillimeters();
    if (!distanceSensor[8].timeoutOccurred())
    {
        return distanceData;
    }
    else
    {
        Serial.println("Sensor 9 out of range!");
        digitalWrite(WAYANG_HAND_9, LOW);
        return 2000;
    }
}

int getDistanceSensor10()
{
    digitalWrite(WAYANG_HAND_10, HIGH);
    delay(100);
    distanceSensor[9].startContinuous(100);
    int distanceData = distanceSensor[9].readRangeContinuousMillimeters();
    if (!distanceSensor[9].timeoutOccurred())
    {
        return distanceData;
    }
    else
    {
        Serial.println("Sensor 10 out of range!");
        digitalWrite(WAYANG_HAND_10, LOW);
        return 2000;
    }
}

bool getSensorStatus(int num)
{
    return sensorsStatus[num - 1];
}
