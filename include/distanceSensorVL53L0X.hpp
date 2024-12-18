#ifndef DISTANCE_SENSOR_VL53L0X_HPP
#define DISTANCE_SENSOR_VL53L0X_HPP

#define SENSOR_ADDRESS_1 0x30
#define SENSOR_ADDRESS_2 0x31
#define SENSOR_ADDRESS_3 0x32
#define SENSOR_ADDRESS_4 0x33
#define SENSOR_ADDRESS_5 0x34
#define SENSOR_ADDRESS_6 0x35
#define SENSOR_ADDRESS_7 0x36
#define SENSOR_ADDRESS_8 0x37
#define SENSOR_ADDRESS_9 0x38
#define SENSOR_ADDRESS_10 0x39

#include <VL53L0X.h>
#include <Wire.h>


void beginSensorNum(int nSensor);
int getDistanceSensorNum(int nSensor);

#endif // DISTANCE_SENSOR_VL53L0X_HPP