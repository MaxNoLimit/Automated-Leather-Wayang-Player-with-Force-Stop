#include "mainheader.hpp"
#include "mainfunctions.hpp"
#include "wayang_lcd_2004.hpp"
#include "distanceSensorVL53L0X.hpp"

// TaskHandle_t MainTaskHandler;

// void mainLoop(void *pvParameters);

void setup()
{
  Serial.begin(9600);
  Serial.println(F("\n\nWayang Debug Serial Monitor!"));
  beginingAllGPIOS();

  Serial3.begin(9600);
  // Serial.print(F("Distance 1: "));
  // Serial.println(getDistanceSensor1());

  // Serial.print(F("Distance 2: "));
  // Serial.println(getDistanceSensor2());

  // Serial.print(F("Distance 3: "));
  // Serial.println(getDistanceSensor3());

  // Serial.print(F("Distance 4: "));
  // Serial.println(getDistanceSensor4());

  // Serial.print(F("Distance 5: "));
  // Serial.println(getDistanceSensor5());

  // Serial.print(F("Distance 6: "));
  // Serial.println(getDistanceSensor6());

  // Serial.print(F("Distance 7: "));
  // Serial.println(getDistanceSensor7());

  // Serial.print(F("Distance 8: "));
  // Serial.println(getDistanceSensor8());

  // Serial.print(F("Distance 9: "));
  // Serial.println(getDistanceSensor9());

  // Serial.print(F("Distance 10: "));
  // Serial.println(getDistanceSensor10());

  WayangDisplay::lcd2004setup();
  // beginAllSensors();
  // beginSensor1();
  // beginSensor2();
  // beginSensor3();
  // Serial.println(F("Setup done!"));
}

void loop()
{
  // Serial.println(F("Looping..."));
  WayangDisplay::generalLoop();
}
