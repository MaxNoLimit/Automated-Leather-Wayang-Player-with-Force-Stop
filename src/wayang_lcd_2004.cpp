#include "wayang_lcd_2004.hpp"
#include "sound_system.hpp"

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

void WayangDisplay::WayangDisplayLCD::refreshLCD()
{
    lcdWayang.clear();
}

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

int WayangDisplay::WayangDisplayLCD::get_lcd_Address()
{
    return this->lcd_Address;
}

void WayangDisplay::WayangDisplayLCD::set_lcd_Address(int address)
{
    this->lcd_Address = address;
}

int WayangDisplay::WayangDisplayLCD::get_selection_point()
{
    return this->selection_point;
}

void WayangDisplay::WayangDisplayLCD::set_selection_point(int point)
{
    this->selection_point = point;
}

void WayangDisplay::WayangDisplayLCD::increment_selection_point()
{
    this->selection_point++;
}

void WayangDisplay::WayangDisplayLCD::decrement_selection_point()
{
    this->selection_point--;
}
