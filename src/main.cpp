#include "mainheader.hpp"
#include "mainfunctions.hpp"
#include "wayang_lcd_2004.hpp"
#include "distanceSensorVL53L0X.hpp"


void setup()
{
  Serial.begin(9600);
  Serial.println(F("Wayang Debug Serial Monitor!"));
  beginingAllGPIOS();
  WayangDisplay::lcd2004setup();
  beginAllSensors();
  // beginSensor1();
  // beginSensor2();
  // beginSensor3();
}

void loop()
{
  WayangDisplay::generalLoop();
}