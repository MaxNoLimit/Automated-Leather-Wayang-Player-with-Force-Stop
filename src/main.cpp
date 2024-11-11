#include "mainheader.hpp"
#include "mainfunctions.hpp"
#include "wayang_lcd_2004.hpp"
#include "distanceSensorVL53L0X.hpp"

// TaskHandle_t MainTaskHandler;
TaskHandle_t mainLoopTaskHandler;

static void mainLoop(void *pvParameters)
{
  Serial.println(F("\n\nWayang Debug Serial Monitor!"));
  WayangDisplay::lcd2004setupIntro();
  beginingAllGPIOS();
  WayangDisplay::lcd2004final();

  while (1)
  {
    WayangDisplay::generalLoop();
  }
}

void setup()
{
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial.println(F("Setup..."));
  xTaskCreate(
      mainLoop,              /* Task function. */
      "MainLoop",            /* name of task. */
      512,              /* Stack size of task */
      NULL,                  /* parameter of the task */
      2,                     /* priority of the task */
      &mainLoopTaskHandler); /* Task handle to keep track of created task */

}

void loop()
{
  // not using this anymore, no more simple superloop

  // Serial.println(F("Looping..."));
  // WayangDisplay::generalLoop();
}
