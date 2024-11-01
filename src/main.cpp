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
      1024 * 2,              /* Stack size of task */
      NULL,                  /* parameter of the task */
      1,                     /* priority of the task */
      &mainLoopTaskHandler); /* Task handle to keep track of created task */

}

void loop()
{
  // Serial.println(F("Looping..."));
  // WayangDisplay::generalLoop();
}
