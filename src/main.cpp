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
