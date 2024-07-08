#include "mainheader.hpp"
#include "distanceSensorVL53L0X.hpp"

Adafruit_VL53L0X distanceSensor[10] = {
    Adafruit_VL53L0X(),
    Adafruit_VL53L0X(),
    Adafruit_VL53L0X(),
    Adafruit_VL53L0X(),
    Adafruit_VL53L0X(),
    Adafruit_VL53L0X(),
    Adafruit_VL53L0X(),
    Adafruit_VL53L0X(),
    Adafruit_VL53L0X(),
    Adafruit_VL53L0X()};

VL53L0X_RangingMeasurementData_t distanceData[10];

void beginAllSensors(){
    beginSensor1();
    beginSensor2();
    beginSensor3();
    beginSensor4();
    beginSensor5();
    beginSensor6();
    beginSensor7();
    beginSensor8();
    beginSensor9();
    beginSensor10();
}

void beginSensor1()
{
    digitalWrite(WAYANG_HAND_1, HIGH);
    delay(100);
    if (!distanceSensor[0].begin(SENSOR_ADDRESS_1))
    {
        Serial.println("Failed to boot VL53L0X Sensor 1");
        digitalWrite(WAYANG_HAND_1, LOW);
    }
    else
    {
        Serial.println("VL53L0X Sensor 1 booted");
        digitalWrite(WAYANG_HAND_1, LOW);
    }
}

void beginSensor2()
{
    digitalWrite(WAYANG_HAND_2, HIGH);
    delay(100);
    if (!distanceSensor[1].begin(SENSOR_ADDRESS_2))
    {
        Serial.println("Failed to boot VL53L0X Sensor 2");
        digitalWrite(WAYANG_HAND_2, LOW);
    }
    else
    {
        Serial.println("VL53L0X Sensor 2 booted");
        digitalWrite(WAYANG_HAND_2, LOW);
    }
}

void beginSensor3()
{
    digitalWrite(WAYANG_HAND_3, HIGH);
    delay(100);
    if (!distanceSensor[2].begin(SENSOR_ADDRESS_3))
    {
        Serial.println("Failed to boot VL53L0X Sensor 3");
        digitalWrite(WAYANG_HAND_3, LOW);
    }
    else
    {
        Serial.println("VL53L0X Sensor 3 booted");
        digitalWrite(WAYANG_HAND_3, LOW);
    }
}

void beginSensor4()
{
    digitalWrite(WAYANG_HAND_4, HIGH);
    delay(100);
    if (!distanceSensor[3].begin(SENSOR_ADDRESS_4))
    {
        Serial.println("Failed to boot VL53L0X Sensor 4");
        digitalWrite(WAYANG_HAND_4, LOW);
    }
    else
    {
        Serial.println("VL53L0X Sensor 4 booted");
        digitalWrite(WAYANG_HAND_4, LOW);
    }
}

void beginSensor5()
{
    digitalWrite(WAYANG_HAND_5, HIGH);
    delay(100);
    if (!distanceSensor[4].begin(SENSOR_ADDRESS_5))
    {
        Serial.println("Failed to boot VL53L0X Sensor 5");
        digitalWrite(WAYANG_HAND_5, LOW);
    }
    else
    {
        Serial.println("VL53L0X Sensor 5 booted");
        digitalWrite(WAYANG_HAND_5, LOW);
    }
}

void beginSensor6()
{
    digitalWrite(WAYANG_HAND_6, HIGH);
    delay(100);
    if (!distanceSensor[5].begin(SENSOR_ADDRESS_6))
    {
        Serial.println("Failed to boot VL53L0X Sensor 6");
        digitalWrite(WAYANG_HAND_6, LOW);
    }
    else
    {
        Serial.println("VL53L0X Sensor 6 booted");
        digitalWrite(WAYANG_HAND_6, LOW);
    }
}

void beginSensor7()
{
    digitalWrite(WAYANG_HAND_7, HIGH);
    delay(100);
    if (!distanceSensor[6].begin(SENSOR_ADDRESS_7))
    {
        Serial.println("Failed to boot VL53L0X Sensor 7");
        digitalWrite(WAYANG_HAND_7, LOW);
    }
    else
    {
        Serial.println("VL53L0X Sensor 7 booted");
        digitalWrite(WAYANG_HAND_7, LOW);
    }
}

void beginSensor8()
{
    digitalWrite(WAYANG_HAND_8, HIGH);
    delay(100);
    if (!distanceSensor[7].begin(SENSOR_ADDRESS_8))
    {
        Serial.println("Failed to boot VL53L0X Sensor 8");
        digitalWrite(WAYANG_HAND_8, LOW);
    }
    else
    {
        Serial.println("VL53L0X Sensor 8 booted");
        digitalWrite(WAYANG_HAND_8, LOW);
    }
}

void beginSensor9()
{
    digitalWrite(WAYANG_HAND_9, HIGH);
    delay(100);
    if (!distanceSensor[8].begin(SENSOR_ADDRESS_9))
    {
        Serial.println("Failed to boot VL53L0X Sensor 9");
        digitalWrite(WAYANG_HAND_9, LOW);
    }
    else
    {
        Serial.println("VL53L0X Sensor 9 booted");
        digitalWrite(WAYANG_HAND_9, LOW);
    }
}

void beginSensor10()
{
    digitalWrite(WAYANG_HAND_10, HIGH);
    delay(100);
    if (!distanceSensor[9].begin(SENSOR_ADDRESS_10))
    {
        Serial.println("Failed to boot VL53L0X Sensor 10");
        digitalWrite(WAYANG_HAND_10, LOW);
    }
    else
    {
        Serial.println("VL53L0X Sensor 10 booted");
        digitalWrite(WAYANG_HAND_10, LOW);
    }
}

int getDistanceSensor1()
{
    digitalWrite(WAYANG_HAND_1, HIGH);
    delay(100);
    distanceSensor[0].rangingTest(&distanceData[0], false);
    if (distanceData[0].RangeStatus != 4)
    {
        return distanceData[0].RangeMilliMeter;
    }
    else
    {
        Serial.println("Sensor 1 out of range!");
        digitalWrite(WAYANG_HAND_1, LOW);
        return -1;
    }
}

int getDistanceSensor2()
{
    digitalWrite(WAYANG_HAND_2, HIGH);
    delay(100);
    distanceSensor[1].rangingTest(&distanceData[1], false);
    if (distanceData[1].RangeStatus != 4)
    {
        return distanceData[1].RangeMilliMeter;
    }
    else
    {
        Serial.println("Sensor 2 out of range!");
        digitalWrite(WAYANG_HAND_2, LOW);
        return -1;
    }
}

int getDistanceSensor3()
{
    digitalWrite(WAYANG_HAND_3, HIGH);
    delay(100);
    distanceSensor[2].rangingTest(&distanceData[2], false);
    if (distanceData[2].RangeStatus != 4)
    {
        return distanceData[2].RangeMilliMeter;
    }
    else
    {
        Serial.println("Sensor 3 out of range!");
        digitalWrite(WAYANG_HAND_3, LOW);
        return -1;
    }
}

int getDistanceSensor4()
{
    digitalWrite(WAYANG_HAND_4, HIGH);
    delay(100);
    distanceSensor[3].rangingTest(&distanceData[3], false);
    if (distanceData[3].RangeStatus != 4)
    {
        return distanceData[3].RangeMilliMeter;
    }
    else
    {
        Serial.println("Sensor 4 out of range!");
        digitalWrite(WAYANG_HAND_4, LOW);
        return -1;
    }
}

int getDistanceSensor5()
{
    digitalWrite(WAYANG_HAND_5, HIGH);
    delay(100);
    distanceSensor[4].rangingTest(&distanceData[4], false);
    if (distanceData[4].RangeStatus != 4)
    {
        return distanceData[4].RangeMilliMeter;
    }
    else
    {
        Serial.println("Sensor 5 out of range!");
        digitalWrite(WAYANG_HAND_5, LOW);
        return -1;
    }
}

int getDistanceSensor6()
{
    digitalWrite(WAYANG_HAND_6, HIGH);
    delay(100);
    distanceSensor[5].rangingTest(&distanceData[5], false);
    if (distanceData[5].RangeStatus != 4)
    {
        return distanceData[5].RangeMilliMeter;
    }
    else
    {
        Serial.println("Sensor 6 out of range!");
        digitalWrite(WAYANG_HAND_6, LOW);
        return -1;
    }
}

int getDistanceSensor7()
{
    digitalWrite(WAYANG_HAND_7, HIGH);
    delay(100);
    distanceSensor[6].rangingTest(&distanceData[6], false);
    if (distanceData[6].RangeStatus != 4)
    {
        return distanceData[6].RangeMilliMeter;
    }
    else
    {
        Serial.println("Sensor 7 out of range!");
        digitalWrite(WAYANG_HAND_7, LOW);
        return -1;
    }
}

int getDistanceSensor8()
{
    digitalWrite(WAYANG_HAND_8, HIGH);
    delay(100);
    distanceSensor[7].rangingTest(&distanceData[7], false);
    if (distanceData[7].RangeStatus != 4)
    {
        return distanceData[7].RangeMilliMeter;
    }
    else
    {
        Serial.println("Sensor 8 out of range!");
        digitalWrite(WAYANG_HAND_8, LOW);
        return -1;
    }
}

int getDistanceSensor9()
{
    digitalWrite(WAYANG_HAND_9, HIGH);
    delay(100);
    distanceSensor[8].rangingTest(&distanceData[8], false);
    if (distanceData[8].RangeStatus != 4)
    {
        return distanceData[8].RangeMilliMeter;
    }
    else
    {
        Serial.println("Sensor 9 out of range!");
        digitalWrite(WAYANG_HAND_9, LOW);
        return -1;
    }
}

int getDistanceSensor10()
{
    digitalWrite(WAYANG_HAND_10, HIGH);
    delay(100);
    distanceSensor[9].rangingTest(&distanceData[9], false);
    if (distanceData[9].RangeStatus != 4)
    {
        return distanceData[9].RangeMilliMeter;
    }
    else
    {
        Serial.println("Sensor 10 out of range!");
        digitalWrite(WAYANG_HAND_10, LOW);
        return -1;
    }
}

