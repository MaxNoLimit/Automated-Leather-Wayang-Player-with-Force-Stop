#include "wayang_lcd_2004.hpp"
#include "sound_system.hpp"
#include "distanceSensorVL53L0X.hpp"

WayangDisplay::WayangDisplayLCD::WayangDisplayLCD()
    : lcdWayang(get_lcd_Address(), 20, 4)
{
}

WayangDisplay::WayangDisplayLCD::WayangDisplayLCD(int address)
    : lcdWayang(address, 20, 4)
{
}

WayangDisplay::WayangDisplayLCD::~WayangDisplayLCD()
{
}

/*
Function untuk display intro display
*/
void WayangDisplay::WayangDisplayLCD::introDisplay()
{
    // LiquidCrystal_I2C lcdWayang(this->lcd_Address, 20, 4);
    lcdWayang.init();
    lcdWayang.backlight();
    lcdWayang.setCursor(0, 0);
    lcdWayang.print("Automated Leather");
    lcdWayang.setCursor(0, 1);
    lcdWayang.print("Wayang Player");
}

/*
Function untuk refresh display LCD
*/
void WayangDisplay::WayangDisplayLCD::refreshLCD()
{
    lcdWayang.clear();
}

/*
Function untuk display bagian menu
*/
void WayangDisplay::WayangDisplayLCD::MenuDisplay()
{
    // LiquidCrystal_I2C lcdWayang(this->lcd_Address, 20, 4);
    // lcdWayang.init();
    // lcdWayang.backlight();
    lcdWayang.setCursor(0, 0);
    lcdWayang.print("Menu");
    lcdWayang.setCursor(0, 1);
    lcdWayang.print("Play episode");
    lcdWayang.setCursor(0, 2);
    lcdWayang.print("Calibrate");
    lcdWayang.setCursor(0, 3);
    lcdWayang.print("Settings");
    lcdWayang.setCursor(18, get_selection_point());
    lcdWayang.print("<<");
}

/*
Function untuk display bagian episode 1,2,3
*/
void WayangDisplay::WayangDisplayLCD::EpisodeDisplay()
{
    lcdWayang.setCursor(0, 0);
    lcdWayang.print("Play Episode");
    lcdWayang.setCursor(0, 1);
    lcdWayang.print("Episode 1");
    lcdWayang.setCursor(0, 2);
    lcdWayang.print("Episode 2");
    lcdWayang.setCursor(0, 3);
    lcdWayang.print("Episode 3");
    lcdWayang.setCursor(18, get_selection_point());
    lcdWayang.print("<<");
}

/*
Function untuk display bagian episode 1,2,3,4
*/
void WayangDisplay::WayangDisplayLCD::EpisodeDisplay2()
{
    lcdWayang.setCursor(0, 0);
    lcdWayang.print("Episode 1");
    lcdWayang.setCursor(0, 1);
    lcdWayang.print("Episode 2");
    lcdWayang.setCursor(0, 2);
    lcdWayang.print("Episode 3");
    lcdWayang.setCursor(0, 3);
    lcdWayang.print("Episode 4");
    lcdWayang.setCursor(18, get_selection_point());
    lcdWayang.print("<<");
}

/*
Function untuk display bagian episode 2,3,4,5
*/
void WayangDisplay::WayangDisplayLCD::EpisodeDisplay3()
{
    lcdWayang.setCursor(0, 0);
    lcdWayang.print("Episode 2");
    lcdWayang.setCursor(0, 1);
    lcdWayang.print("Episode 3");
    lcdWayang.setCursor(0, 2);
    lcdWayang.print("Episode 4");
    lcdWayang.setCursor(0, 3);
    lcdWayang.print("Episode 5");
    lcdWayang.setCursor(18, get_selection_point());
    lcdWayang.print("<<");
}

/*
Function untuk display bagian Calibrate
*/
void WayangDisplay::WayangDisplayLCD::CalibrateDisplay()
{
    lcdWayang.setCursor(0, 0);
    lcdWayang.print("Calibrate");
    lcdWayang.setCursor(0, 1);
    lcdWayang.print("V-Slot Linear");
    lcdWayang.setCursor(0, 2);
    lcdWayang.print("Mp3 Player");
    lcdWayang.setCursor(0, 3);
    lcdWayang.print("Wayang's Hand");
    lcdWayang.setCursor(18, get_selection_point());
    lcdWayang.print("<<");
}

void WayangDisplay::WayangDisplayLCD::CalibrateDisplay2(){
    lcdWayang.setCursor(0, 0);
    lcdWayang.print("V-Slot Linear");
    lcdWayang.setCursor(0, 1);
    lcdWayang.print("Mp3 Player");
    lcdWayang.setCursor(0, 2);
    lcdWayang.print("Wayang's Hand");
    lcdWayang.setCursor(0, 3);
    lcdWayang.print("Sensor status");
    lcdWayang.setCursor(18, get_selection_point());
    lcdWayang.print("<<");
}

void WayangDisplay::WayangDisplayLCD::SensorStatusDisplay()
{
    lcdWayang.setCursor(0, 0);
    lcdWayang.print("Sensor Status");
    lcdWayang.setCursor(0, 1);
    lcdWayang.print("Sensor 1 " + String(getDistanceSensor1()));
    lcdWayang.setCursor(0, 2);
    lcdWayang.print("Sensor 2 " + String(getDistanceSensor2()));
    lcdWayang.setCursor(0, 3);
    lcdWayang.print("Sensor 3 " + String(getDistanceSensor3()));
    lcdWayang.setCursor(18, get_selection_point());
    lcdWayang.print("<<");
}

void WayangDisplay::WayangDisplayLCD::SensorStatusDisplay2()
{
    lcdWayang.setCursor(0, 0);
    lcdWayang.print("Sensor 1 " + String(getDistanceSensor1()));
    lcdWayang.setCursor(0, 1);
    lcdWayang.print("Sensor 2 " + String(getDistanceSensor2()));
    lcdWayang.setCursor(0, 2);
    lcdWayang.print("Sensor 3 " + String(getDistanceSensor3()));
    lcdWayang.setCursor(0, 3);
    lcdWayang.print("Sensor 4 " + String(getDistanceSensor4()));
    lcdWayang.setCursor(18, get_selection_point());
    lcdWayang.print("<<");
}

void WayangDisplay::WayangDisplayLCD::SensorStatusDisplay3()
{
    lcdWayang.setCursor(0, 0);
    lcdWayang.print("Sensor 2 " + String(getDistanceSensor2()));
    lcdWayang.setCursor(0, 1);
    lcdWayang.print("Sensor 3 " + String(getDistanceSensor3()));
    lcdWayang.setCursor(0, 2);
    lcdWayang.print("Sensor 4 " + String(getDistanceSensor4()));
    lcdWayang.setCursor(0, 3);
    lcdWayang.print("Sensor 5 " + String(getDistanceSensor5()));
    lcdWayang.setCursor(18, get_selection_point());
    lcdWayang.print("<<");
}

void WayangDisplay::WayangDisplayLCD::SensorStatusDisplay4()
{
    lcdWayang.setCursor(0, 0);
    lcdWayang.print("Sensor 3 " + String(getDistanceSensor3()));
    lcdWayang.setCursor(0, 1);
    lcdWayang.print("Sensor 4 " + String(getDistanceSensor4()));
    lcdWayang.setCursor(0, 2);
    lcdWayang.print("Sensor 5 " + String(getDistanceSensor5()));
    lcdWayang.setCursor(0, 3);
    lcdWayang.print("Sensor 6 " + String(getDistanceSensor6()));
    lcdWayang.setCursor(18, get_selection_point());
    lcdWayang.print("<<");
}

void WayangDisplay::WayangDisplayLCD::SensorStatusDisplay5()
{
    lcdWayang.setCursor(0, 0);
    lcdWayang.print("Sensor 4 " + String(getDistanceSensor4()));
    lcdWayang.setCursor(0, 1);
    lcdWayang.print("Sensor 5 " + String(getDistanceSensor5()));
    lcdWayang.setCursor(0, 2);
    lcdWayang.print("Sensor 6 " + String(getDistanceSensor6()));
    lcdWayang.setCursor(0, 3);
    lcdWayang.print("Sensor 7 " + String(getDistanceSensor7()));
    lcdWayang.setCursor(18, get_selection_point());
    lcdWayang.print("<<");
}

void WayangDisplay::WayangDisplayLCD::SensorStatusDisplay6()
{
    lcdWayang.setCursor(0, 0);
    lcdWayang.print("Sensor 5 " + String(getDistanceSensor5()));
    lcdWayang.setCursor(0, 1);
    lcdWayang.print("Sensor 6 " + String(getDistanceSensor6()));
    lcdWayang.setCursor(0, 2);
    lcdWayang.print("Sensor 7 " + String(getDistanceSensor7()));
    lcdWayang.setCursor(0, 3);
    lcdWayang.print("Sensor 8 " + String(getDistanceSensor8()));
    lcdWayang.setCursor(18, get_selection_point());
    lcdWayang.print("<<");
}

void WayangDisplay::WayangDisplayLCD::SensorStatusDisplay7()
{
    lcdWayang.setCursor(0, 0);
    lcdWayang.print("Sensor 6 " + String(getDistanceSensor6()));
    lcdWayang.setCursor(0, 1);
    lcdWayang.print("Sensor 7 " + String(getDistanceSensor7()));
    lcdWayang.setCursor(0, 2);
    lcdWayang.print("Sensor 8 " + String(getDistanceSensor8()));
    lcdWayang.setCursor(0, 3);
    lcdWayang.print("Sensor 9 " + String(getDistanceSensor9()));
    lcdWayang.setCursor(18, get_selection_point());
    lcdWayang.print("<<");
}

void WayangDisplay::WayangDisplayLCD::SensorStatusDisplay8()
{
    lcdWayang.setCursor(0, 0);
    lcdWayang.print("Sensor 7 " + String(getDistanceSensor7()));
    lcdWayang.setCursor(0, 1);
    lcdWayang.print("Sensor 8 " + String(getDistanceSensor8()));
    lcdWayang.setCursor(0, 2);
    lcdWayang.print("Sensor 9 " + String(getDistanceSensor9()));
    lcdWayang.setCursor(0, 3);
    lcdWayang.print("Sensor 10 " + String(getDistanceSensor10()));
    lcdWayang.setCursor(18, get_selection_point());
    lcdWayang.print("<<");
}



/*
Function untuk display bagian Settings
*/
void WayangDisplay::WayangDisplayLCD::SettingsDisplay()
{
    lcdWayang.setCursor(0, 0);
    lcdWayang.print("Settings");
    lcdWayang.setCursor(0, 1);
    lcdWayang.print("Volume:");
    lcdWayang.setCursor(8, 1);
    lcdWayang.print("30");
    lcdWayang.setCursor(18, get_selection_point());
    lcdWayang.print("<<");
}

// Function untuk mendapat address LCD 20x4
int WayangDisplay::WayangDisplayLCD::get_lcd_Address()
{
    return this->lcd_Address;
}

// Function untuk set address LCD 20x4 pada class
void WayangDisplay::WayangDisplayLCD::set_lcd_Address(int address)
{
    this->lcd_Address = address;
}

// Function untuk mendapat value selection point pada cursor display
int WayangDisplay::WayangDisplayLCD::get_selection_point()
{
    return this->selection_point;
}


// Function untuk set value selection point pada cursor display
void WayangDisplay::WayangDisplayLCD::set_selection_point(int point)
{
    this->selection_point = point;
}

// Function untuk menambah value selection point pada cursor display yang membuat cursor bergerak ke bawah
void WayangDisplay::WayangDisplayLCD::increment_selection_point()
{
    this->selection_point++;
}

// Function untuk mengurangi value selection point pada cursor display yang membuat cursor bergerak ke atas
void WayangDisplay::WayangDisplayLCD::decrement_selection_point()
{
    this->selection_point--;
}

void WayangDisplay::WayangDisplayLCD::enableLCD(){
    lcdWayang.on();
}

void WayangDisplay::WayangDisplayLCD::disableLCD(){
    lcdWayang.off();
}