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

        void CalibrateDisplay();

        void VSlotDataFarmDisplay();

        void SensorStatusDisplay();

        void WayangHandCalibrationDisplay();

        void pleaseWaitDisplay();

        void playingWhatEpisodeDisplay(int nEpisode);
        void whilePlayingDisplay();

        // Wayang Hand Calibration options
        // Sita
        void SitaHandCalibration();

        // Rahwana
        void RahwanaHandCalibration();

        // Rama Wijaya
        void RamaWijayaHandCalibration();

        // Hanoman
        void HanomanHandCalibration();

        // Laksmana
        void LaksmanaHandCalibration();

        // Sugriwa
        void SugriwaHandCalibration();

        // Subali
        void SubaliHandCalibration();

        // Wibhisana
        void WibhisanaHandCalibration();

        // Anggada
        void AnggadaHandCalibration();

        // Anila
        void AnilaHandCalibration();

        void enableLCD();
        void disableLCD();

        void SettingsDisplay();

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