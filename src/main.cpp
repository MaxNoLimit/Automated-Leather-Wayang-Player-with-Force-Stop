#include "mainheader.hpp"
#include "mainfunctions.hpp"
#include "wayang_lcd_2004.hpp"
#include "distanceSensorVL53L0X.hpp"

// TaskHandle_t MainTaskHandler;
TaskHandle_t mainLoopTaskHandler;

// void mainLoop(void *pvParameters);

static void mainLoop(void *pvParameters)
{
  Serial.println(F("\n\nWayang Debug Serial Monitor!"));
  beginingAllGPIOS();

  Serial.println(F("Setup done!"));
  WayangDisplay::lcd2004setup();
  while (1)
  {
    WayangDisplay::generalLoop();
    // vTaskDelay(1000);
  }
}

void setup()
{
  Serial.begin(9600);
  Serial.println(F("Setup..."));
  xTaskCreate(
      mainLoop,              /* Task function. */
      "MainLoop",            /* name of task. */
      1024 * 3,              /* Stack size of task */
      NULL,                  /* parameter of the task */
      1,                     /* priority of the task */
      &mainLoopTaskHandler); /* Task handle to keep track of created task */
  // vTaskStartScheduler();
}

void loop()
{
  // Serial.println(F("Looping..."));
  // WayangDisplay::generalLoop();
}
