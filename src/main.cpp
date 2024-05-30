#include "mainheader.hpp"
#include "mainfunctions.hpp"
#include "wayang_lcd_2004.hpp"


void setup()
{
  Serial.begin(9600);
  beginingAllGPIOS();
  WayangDisplay::lcd2004setup();


}

void loop()
{
  WayangDisplay::generalLoop();
}