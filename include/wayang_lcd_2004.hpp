#ifndef WAYANG_LCD_2004_H
#define WAYANG_LCD_2004_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

namespace WayangDisplay
{
    class WayangDisplayLCD
    {
    private:
        int lcd_Address;
        int selection_point = 1;
        LiquidCrystal_I2C lcdWayang;
        int sensorValueData[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

    public:
        WayangDisplayLCD();
        WayangDisplayLCD(int address);
        virtual ~WayangDisplayLCD();

        void introDisplay();
        void refreshLCD();
        void MenuDisplay();

        void EpisodeDisplay();
        void EpisodeDisplay2();
        void EpisodeDisplay3();

        void CalibrateDisplay();
        void CalibrateDisplay2();

        void SensorStatusDisplay();
        void SensorStatusDisplay2();
        void SensorStatusDisplay3();
        void SensorStatusDisplay4();
        void SensorStatusDisplay5();
        void SensorStatusDisplay6();
        void SensorStatusDisplay7();
        void SensorStatusDisplay8();

        void enableLCD();
        void disableLCD();

        void SettingsDisplay();
        void SettingsVolumeDisplay();

        int get_lcd_Address();
        void set_lcd_Address(int address);

        int get_selection_point();
        void set_selection_point(int point);
        void increment_selection_point();
        void decrement_selection_point();

        void setSensorValueData();
    };

}

#endif // WAYANG_LCD_2004_H