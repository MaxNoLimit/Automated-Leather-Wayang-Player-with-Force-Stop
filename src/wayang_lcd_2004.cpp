#include "wayang_lcd_2004.hpp"
#include "sound_system.hpp"
#include "distanceSensorVL53L0X.hpp"
#include "mainfunctions.hpp"

// For Menu Display
const char * menuList[4] = {
    "Menu",
    "Play episode",
    "Calibrate",
    "Settings"};


// For Episode Display
const char * episodeList[5] = {
    "Episode 1",
    "Episode 2",
    "Episode 3",
    "Episode 4",
    "Episode 5"};

// For Calibrate Display
const char * calibratingList[4] = {
    "V-Slot Linear",
    "Mp3 Player",
    "Wayang's Hand",
    "Sensor Data"};

// For Wayang Hand Calibration Display
const char * calibratingWayangCharacterList[11] = {
    "s1mple Calibration",
    "Wayang Sita",
    "Wayang Rahwana",
    "Wayang Rama Wijaya",
    "Wayang Hanuman",
    "Wayang Laksmana",
    "Wayang Sugriwa",
    "Wayang Subali",
    "Wayang Wibhisana",
    "Wayang Anggada",
    "Wayang Anila"};

// For Sensor Data Display
const char * calibratingSensorList[10] = {
    "Sensor 1:    ",
    "Sensor 2:    ",
    "Sensor 3:    ",
    "Sensor 4:    ",
    "Sensor 5:    ",
    "Sensor 6:    ",
    "Sensor 7:    ",
    "Sensor 8:    ",
    "Sensor 9:    ",
    "Sensor 10:   "};

// Hand Movement Option
const char * handMovementList[10] = {
    "Point to Front",
    "Low Point to Front",
    "Middle Front",
    "Down Front",
    "Point To Self",
    "Down Back",
    "On Hip Back",
    "Point to Back",
    "Low Point to Back",
    "Middle Back"};

// V-Slot Data Farming
const char * vSlotFarmOption[4] = {
    "Move 100 mm",
    "Move 200 mm",
    "Move 300 mm",
    "Move 400 mm"};

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
    lcdWayang.clear();
    lcdWayang.setCursor(0, 0);
    lcdWayang.print("Automated Leather");
    lcdWayang.setCursor(0, 1);
    lcdWayang.print("Wayang Player");
    // lcdWayang.setCursor(0, 3);
    // lcdWayang.print("Please wait...");
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
    for (int i = 0; i < 4; i++)
    {
        lcdWayang.setCursor(0, i);
        lcdWayang.print(menuList[i]);
    }
    lcdWayang.setCursor(18, get_selection_point());
    lcdWayang.print("<<");
}

/*
Function untuk display bagian episode 1,2,3
*/
void WayangDisplay::WayangDisplayLCD::EpisodeDisplay()
{
    for (int i = 0; i < 4; i++)
    {
        lcdWayang.setCursor(0, i);
        if (i + getSubPageRoute() == 0)
        {
            lcdWayang.print(menuList[1]);
        }
        else
        {
            lcdWayang.print(episodeList[i - 1 + getSubPageRoute()]);
        }
    }
    lcdWayang.setCursor(18, get_selection_point());
    lcdWayang.print("<<");
}

/*
Function untuk display bagian Calibrate
*/
void WayangDisplay::WayangDisplayLCD::CalibrateDisplay()
{
    for (int i = 0; i < 4; i++)
    {
        lcdWayang.setCursor(0, i);
        if (i + getSubPageRoute() == 0)
        {
            lcdWayang.print(menuList[2]);
        }
        else
        {
            lcdWayang.print(calibratingList[i - 1 + getSubPageRoute()]);
        }
    }
    lcdWayang.setCursor(18, get_selection_point());
    lcdWayang.print("<<");
}

/*
Function untuk display opsi pengambilan data horizontal movement
*/
void WayangDisplay::WayangDisplayLCD::VSlotDataFarmDisplay()
{
    for (int i = 0; i < 4; i++)
    {
        lcdWayang.setCursor(0, i);
        if (i + getSubPageRoute() == 0)
        {
            lcdWayang.print(calibratingList[0]);
        }
        else
        {
            lcdWayang.print(vSlotFarmOption[i - 1 + getSubPageRoute()]);
        }
    }
    lcdWayang.setCursor(18, get_selection_point());
    lcdWayang.print("<<");
}

void WayangDisplay::WayangDisplayLCD::SensorStatusDisplay()
{
    for (int i = 0; i < 4; i++)
    {
        lcdWayang.setCursor(0, i);
        if (i + getSubPageRoute() == 0)
        {
            lcdWayang.print(calibratingList[3]);
        }
        else
        {
            lcdWayang.print(calibratingSensorList[i - 1 + getSubPageRoute()] + String(sensorValueData[i - 1 + getSubPageRoute()]));
        }
    }

    lcdWayang.setCursor(18, get_selection_point());
    lcdWayang.print("<<");
}

void WayangDisplay::WayangDisplayLCD::WayangHandCalibrationDisplay()
{
    for (int i = 0; i < 4; i++)
    {
        lcdWayang.setCursor(0, i);
        if (i + getSubPageRoute() == 0)
        {
            lcdWayang.print(calibratingList[2]);
        }
        else
        {
            lcdWayang.print(calibratingWayangCharacterList[i - 1 + getSubPageRoute()]);
        }
    }
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

/*
Function untuk display please wait
*/
void WayangDisplay::WayangDisplayLCD::pleaseWaitDisplay()
{
    refreshLCD();
    lcdWayang.setCursor(4, 1);
    lcdWayang.print(F("Please wait"));
}

/*
Function untuk display episode yang sedang dimainkan
*/
void WayangDisplay::WayangDisplayLCD::playingWhatEpisodeDisplay(int nEpisode)
{
    refreshLCD();
    lcdWayang.setCursor(5, 1);
    lcdWayang.print(F("Playing: "));
    lcdWayang.setCursor(5, 2);
    lcdWayang.print(episodeList[nEpisode - 1]);
}

void WayangDisplay::WayangDisplayLCD::SitaHandCalibration()
{
    for (int i = 0; i < 4; i++)
    {
        lcdWayang.setCursor(0, i);
        if (i + getSubPageRoute() == 0)
        {
            lcdWayang.print(calibratingWayangCharacterList[1]);
        }
        else
        {
            lcdWayang.print(handMovementList[i - 1 + getSubPageRoute()]);
        }
    }
    lcdWayang.setCursor(18, get_selection_point());
    lcdWayang.print("<<");
}

void WayangDisplay::WayangDisplayLCD::RahwanaHandCalibration()
{
    for (int i = 0; i < 4; i++)
    {
        lcdWayang.setCursor(0, i);
        if (i + getSubPageRoute() == 0)
        {
            lcdWayang.print(calibratingWayangCharacterList[2]);
        }
        else
        {
            lcdWayang.print(handMovementList[i - 1 + getSubPageRoute()]);
        }
    }
    lcdWayang.setCursor(18, get_selection_point());
    lcdWayang.print("<<");
}

void WayangDisplay::WayangDisplayLCD::RamaWijayaHandCalibration()
{
    for (int i = 0; i < 4; i++)
    {
        lcdWayang.setCursor(0, i);
        if (i + getSubPageRoute() == 0)
        {
            lcdWayang.print(calibratingWayangCharacterList[3]);
        }
        else
        {
            lcdWayang.print(handMovementList[i - 1 + getSubPageRoute()]);
        }
    }
    lcdWayang.setCursor(18, get_selection_point());
    lcdWayang.print("<<");
}

void WayangDisplay::WayangDisplayLCD::HanomanHandCalibration()
{
    for (int i = 0; i < 4; i++)
    {
        lcdWayang.setCursor(0, i);
        if (i + getSubPageRoute() == 0)
        {
            lcdWayang.print(calibratingWayangCharacterList[4]);
        }
        else
        {
            lcdWayang.print(handMovementList[i - 1 + getSubPageRoute()]);
        }
    }
    lcdWayang.setCursor(18, get_selection_point());
    lcdWayang.print("<<");
}

void WayangDisplay::WayangDisplayLCD::LaksmanaHandCalibration()
{
    for (int i = 0; i < 4; i++)
    {
        lcdWayang.setCursor(0, i);
        if (i + getSubPageRoute() == 0)
        {
            lcdWayang.print(calibratingWayangCharacterList[5]);
        }
        else
        {
            lcdWayang.print(handMovementList[i - 1 + getSubPageRoute()]);
        }
    }
    lcdWayang.setCursor(18, get_selection_point());
    lcdWayang.print("<<");
}

void WayangDisplay::WayangDisplayLCD::SugriwaHandCalibration()
{
    for (int i = 0; i < 4; i++)
    {
        lcdWayang.setCursor(0, i);
        if (i + getSubPageRoute() == 0)
        {
            lcdWayang.print(calibratingWayangCharacterList[6]);
        }
        else
        {
            lcdWayang.print(handMovementList[i - 1 + getSubPageRoute()]);
        }
    }
    lcdWayang.setCursor(18, get_selection_point());
    lcdWayang.print("<<");
}

void WayangDisplay::WayangDisplayLCD::SubaliHandCalibration()
{
    for (int i = 0; i < 4; i++)
    {
        lcdWayang.setCursor(0, i);
        if (i + getSubPageRoute() == 0)
        {
            lcdWayang.print(calibratingWayangCharacterList[7]);
        }
        else
        {
            lcdWayang.print(handMovementList[i - 1 + getSubPageRoute()]);
        }
    }
    lcdWayang.setCursor(18, get_selection_point());
    lcdWayang.print("<<");
}

void WayangDisplay::WayangDisplayLCD::WibhisanaHandCalibration()
{
    for (int i = 0; i < 4; i++)
    {
        lcdWayang.setCursor(0, i);
        if (i + getSubPageRoute() == 0)
        {
            lcdWayang.print(calibratingWayangCharacterList[8]);
        }
        else
        {
            lcdWayang.print(handMovementList[i - 1 + getSubPageRoute()]);
        }
    }
    lcdWayang.setCursor(18, get_selection_point());
    lcdWayang.print("<<");
}

void WayangDisplay::WayangDisplayLCD::AnggadaHandCalibration()
{
    for (int i = 0; i < 4; i++)
    {
        lcdWayang.setCursor(0, i);
        if (i + getSubPageRoute() == 0)
        {
            lcdWayang.print(calibratingWayangCharacterList[9]);
        }
        else
        {
            lcdWayang.print(handMovementList[i - 1 + getSubPageRoute()]);
        }
    }
    lcdWayang.setCursor(18, get_selection_point());
    lcdWayang.print("<<");
}

void WayangDisplay::WayangDisplayLCD::AnilaHandCalibration()
{
    for (int i = 0; i < 4; i++)
    {
        lcdWayang.setCursor(0, i);
        if (i + getSubPageRoute() == 0)
        {
            lcdWayang.print(calibratingWayangCharacterList[10]);
        }
        else
        {
            lcdWayang.print(handMovementList[i - 1 + getSubPageRoute()]);
        }
    }
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

void WayangDisplay::WayangDisplayLCD::enableLCD()
{
    lcdWayang.on();
}

void WayangDisplay::WayangDisplayLCD::disableLCD()
{
    lcdWayang.off();
}

void WayangDisplay::WayangDisplayLCD::setSensorValueData()
{
    for (int i = 0; i < 10; i++)
    {
        sensorValueData[i] = getDistanceSensorNum(i + 1);
    }
}