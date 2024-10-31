#include "mainfunctions.hpp"
#include "mainheader.hpp"
#include "wayang_lcd_2004.hpp"
#include "state_management.hpp"
#include "i2c_scan_n_assign.hpp"
#include "rotary_encoder.hpp"
#include "sound_system.hpp"
#include "Episodes.hpp"
#include "a4988_nema.hpp"
#include "distanceSensorVL53L0X.hpp"
#include "characters/rama_wijaya.hpp"
#include "characters/sita.hpp"
#include "characters/rahwana.hpp"
#include "characters/hanoman.hpp"
#include "characters/laksmana.hpp"
#include "characters/sugriwa.hpp"
#include "characters/subali.hpp"
#include "characters/wibhisana.hpp"

RamaWijaya wayangRamaWijaya;
Sita wayangSita;
Rahwana wayangRahwana;
Hanoman wayangHanoman;
Laksmana wayangLaksmana;
Sugriwa wayangSugriwa;
Subali wayangSubali;
Wibhisana wayangWibhisana;

TaskHandle_t serialReaderTaskHandler;

int lcd_2040_address;
WayangDisplay::WayangDisplayLCD WayangDisplayLCD_in_main(0x27);
unsigned long last_run = 0;
int loop_state = 0;

int pageRoute = 0;
int subPageRoute = 0;
int subSubPageRoute = 0;

/*
Function untuk begin semua GPIO
*/
void beginingAllGPIOS()
{
    // Rotary Encoder
    pinMode(OUTPUT_A, INPUT);
    pinMode(OUTPUT_B, INPUT);
    pinMode(BUTTON_ROTARY, INPUT);

    // A4988
    pinMode(NEMA_STEP, OUTPUT);
    pinMode(NEMA_DIR, OUTPUT);

    // Servo SG90
    pinMode(LEFT_SERVO_1, OUTPUT);
    pinMode(LEFT_SERVO_2, OUTPUT);
    pinMode(LEFT_SERVO_3, OUTPUT);
    pinMode(LEFT_SERVO_4, OUTPUT);

    pinMode(RIGHT_SERVO_1, OUTPUT);
    pinMode(RIGHT_SERVO_2, OUTPUT);
    pinMode(RIGHT_SERVO_3, OUTPUT);
    pinMode(RIGHT_SERVO_4, OUTPUT);

    // digitalWrite(LEFT_SERVO_1, LOW);
    // digitalWrite(LEFT_SERVO_2, LOW);
    // digitalWrite(LEFT_SERVO_3, LOW);
    // digitalWrite(LEFT_SERVO_4, LOW);

    // digitalWrite(RIGHT_SERVO_1, LOW);
    // digitalWrite(RIGHT_SERVO_2, LOW);
    // digitalWrite(RIGHT_SERVO_3, LOW);
    // digitalWrite(RIGHT_SERVO_4, LOW);

    // EN 1-10 A4988
    pinMode(EN_NEMA_1, OUTPUT);
    pinMode(EN_NEMA_2, OUTPUT);
    pinMode(EN_NEMA_3, OUTPUT);
    pinMode(EN_NEMA_4, OUTPUT);
    pinMode(EN_NEMA_5, OUTPUT);
    pinMode(EN_NEMA_6, OUTPUT);
    pinMode(EN_NEMA_7, OUTPUT);
    pinMode(EN_NEMA_8, OUTPUT);
    pinMode(EN_NEMA_9, OUTPUT);
    pinMode(EN_NEMA_10, OUTPUT);

    digitalWrite(EN_NEMA_1, HIGH);
    digitalWrite(EN_NEMA_2, HIGH);
    digitalWrite(EN_NEMA_3, HIGH);
    digitalWrite(EN_NEMA_4, HIGH);
    digitalWrite(EN_NEMA_5, HIGH);
    digitalWrite(EN_NEMA_6, HIGH);
    digitalWrite(EN_NEMA_7, HIGH);
    digitalWrite(EN_NEMA_8, HIGH);
    digitalWrite(EN_NEMA_9, HIGH);
    digitalWrite(EN_NEMA_10, HIGH);

    // MOSFET FOR SWITCHING WHICH WAYANG WILL BE MOVED
    pinMode(WAYANG_HAND_1, OUTPUT);
    pinMode(WAYANG_HAND_2, OUTPUT);
    pinMode(WAYANG_HAND_3, OUTPUT);
    pinMode(WAYANG_HAND_4, OUTPUT);
    pinMode(WAYANG_HAND_5, OUTPUT);
    pinMode(WAYANG_HAND_6, OUTPUT);
    pinMode(WAYANG_HAND_7, OUTPUT);
    pinMode(WAYANG_HAND_8, OUTPUT);
    pinMode(WAYANG_HAND_9, OUTPUT);
    pinMode(WAYANG_HAND_10, OUTPUT);

    // VL53L0X XSHUTS
    pinMode(XSHUT_1, OUTPUT);
    pinMode(XSHUT_2, OUTPUT);
    pinMode(XSHUT_3, OUTPUT);
    pinMode(XSHUT_4, OUTPUT);
    pinMode(XSHUT_5, OUTPUT);
    pinMode(XSHUT_6, OUTPUT);
    pinMode(XSHUT_7, OUTPUT);
    pinMode(XSHUT_8, OUTPUT);
    pinMode(XSHUT_9, OUTPUT);
    pinMode(XSHUT_10, OUTPUT);

    Wire.begin();
    Wire.setClock(400000);
    Wire.setTimeout(500);
    Wire.setWireTimeout(5000, true);
    SoundSystem::justInitTheSoundSystem();

    // beginAllinOneSensor();
    // setAllMOSFETtoLOW();
    // Serial.print(getDistanceSensor1_v2());
    // Serial.print(" mm\n");

    beginSensor1();
    beginSensor2();
    beginSensor3();
    beginSensor4();
    beginSensor5();
    beginSensor6();
    beginSensor7();
    beginSensor8();
    beginSensor9();
    beginSensor10();
    // beginAllSensors();
    // setAllMOSFETtoLOW();
    // setAllXSHUTtoHIGH();
    setAllMOSFETtoHIGH();
}

void setAllXSHUTtoHIGH()
{
    digitalWrite(XSHUT_1, HIGH);
    digitalWrite(XSHUT_2, HIGH);
    digitalWrite(XSHUT_3, HIGH);
    digitalWrite(XSHUT_4, HIGH);
    digitalWrite(XSHUT_5, HIGH);
    digitalWrite(XSHUT_6, HIGH);
    // digitalWrite(XSHUT_7, HIGH);
}

/*
Function untuk setup LCD 20x4
*/
void WayangDisplay::lcd2004setupIntro()
{
    // Scanning address I2C yang terhubung
    lcd_2040_address = I2C_Scanner::scan_n_assign();

    // Reconstruct dengan address yang sudah di-scan
    WayangDisplayLCD_in_main = WayangDisplay::WayangDisplayLCD(lcd_2040_address); // re-construct
    WayangDisplayLCD_in_main.introDisplay();
}

void WayangDisplay::lcd2004final()
{
    WayangDisplayLCD_in_main.refreshLCD();
    WayangDisplayLCD_in_main.MenuDisplay();

    // Set pageRoute ke MENU_PAGE yang merupakan default page
    pageRoute = StateManagement::PAGE_ROUTE::MENU_PAGE;

    // Memulai Rotary Encoder
    WayangDisplayController::beginRotaryEncoder(OUTPUT_A, OUTPUT_B, BUTTON_ROTARY);

    // attach interrupt ke Rotary Encoder yang membuat fungsi pressRotaryEncoder dan spinRotaryEncoder berjalan
    attachInterrupt(digitalPinToInterrupt(OUTPUT_A), WayangDisplayController::spinRotaryEncoder, FALLING);
    attachInterrupt(digitalPinToInterrupt(BUTTON_ROTARY), WayangDisplayController::pressRotaryEncoder, RISING);
}

/*
Function yang isinya looping check dari LCD 20x4
*/
void WayangDisplay::lcd2004loop()
{
    WayangDisplayLCD_in_main.refreshLCD();

    switch (pageRoute)
    {
    case StateManagement::PAGE_ROUTE::MENU_PAGE:
        WayangDisplayLCD_in_main.MenuDisplay();
        break;

    case StateManagement::PAGE_ROUTE::EPISODE_PAGE:
        WayangDisplayLCD_in_main.EpisodeDisplay();
        break;

    case StateManagement::PAGE_ROUTE::CALIBRATE_PAGE:
        WayangDisplayLCD_in_main.CalibrateDisplay();
        break;

    case StateManagement::PAGE_ROUTE::SETTINGS_PAGE:
        WayangDisplayLCD_in_main.SettingsDisplay();
        break;

    case StateManagement::PAGE_ROUTE::SENSOR_STATUS_PAGE:
        WayangDisplayLCD_in_main.SensorStatusDisplay();
        break;

    case StateManagement::PAGE_ROUTE::WAYANG_HAND_CALIBRATION_PAGE:
        WayangDisplayLCD_in_main.WayangHandCalibrationDisplay();
        break;
    case StateManagement::PAGE_ROUTE::SITA_HAND_PAGE:
        WayangDisplayLCD_in_main.SitaHandCalibration();
        break;
    }
    delay(500);
}

/*
Function untuk melakukan action dari current state
*/
void WayangDisplay::generalLoop()
{
    switch (loop_state)
    {
    case StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD:
        lcd2004loop();
        delay(0);
        break;

    case StateManagement::FSA_STATE::CALIBRATING_ALL_NEMA:
        CalibratingFunction::vSlotLinear();

        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::MP3_REINIT:
        CalibratingFunction::soundSystem();

        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::WAYANG_HAND_CALIBRATION:
        // Final mode
        // CalibratingFunction::wayangHand();

        // Debug mode
        // CalibratingFunction::commandListHandMovementTest();

        pageRoute = StateManagement::PAGE_ROUTE::WAYANG_HAND_CALIBRATION_PAGE;
        subPageRoute = StateManagement::WAYANG_HAND_CALIBRATION_SUB_PAGE_ROUTE::WAYANG_HAND_CALIBRATION_1;
        WayangDisplayLCD_in_main.set_selection_point(1);
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::SENSOR_CHECK:
        WayangDisplayLCD_in_main.setSensorValueData();
        pageRoute = StateManagement::PAGE_ROUTE::SENSOR_STATUS_PAGE;
        WayangDisplayLCD_in_main.set_selection_point(1);
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::PLAY_EPISODE_1:
        WayangDisplayLCD_in_main.disableLCD();
        // Episodes::July29_Episode();
        // Episodes::randomTesting();
        Episodes::Episode_1();
        // xTaskCreate(Episodes::Episode_1_task, "Episode_1_task", 128, NULL, 2, NULL);
        // vTaskSuspend(NULL);
        WayangDisplayLCD_in_main.enableLCD();
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::PLAY_EPISODE_2:
        WayangDisplayLCD_in_main.disableLCD();
        Episodes::Episode_2();
        // xTaskCreate(Episodes::Episode_2_task, "Episode_2_task", 128, NULL, 2, NULL);
        // vTaskSuspend(NULL);
        WayangDisplayLCD_in_main.enableLCD();
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::PLAY_EPISODE_3:
        WayangDisplayLCD_in_main.disableLCD();
        Serial.println("Episode 3");
        Episodes::Episode_3();
        WayangDisplayLCD_in_main.enableLCD();
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::PLAY_EPISODE_4:
        WayangDisplayLCD_in_main.disableLCD();
        Serial.println("Episode 4");
        Episodes::Episode_4();
        WayangDisplayLCD_in_main.enableLCD();
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::PLAY_EPISODE_5:
        WayangDisplayLCD_in_main.disableLCD();
        Serial.println("Episode 5");
        Episodes::Episode_5();
        WayangDisplayLCD_in_main.enableLCD();
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::SIMPLE_WAYANG_HAND_CALIBRATION:
        CalibratingFunction::wayangHand();
        SoundSystem::playDialogFromACertainFolder(SoundSystem::INDICATOR_SOUND, SoundSystem::INDICATOR_SOUND_NUMBER::INDICATOR_WAYANG_HAND_CALIBRATION);
        delay(3500);
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::SITA_HAND:
        wayangSita.walk_to_a_certain_distance_before_calibrating_value(250);
        pageRoute = StateManagement::PAGE_ROUTE::SITA_HAND_PAGE;
        subSubPageRoute = StateManagement::WAYANG_HAND_CALIBRATION_SUB_PAGE_ROUTE_SITA::SITA_HAND_CALIBRATION_1;
        WayangDisplayLCD_in_main.set_selection_point(1);
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::EXIT_SITA_HAND:
        wayangSita.defaultStandPosition();
        pageRoute = StateManagement::PAGE_ROUTE::WAYANG_HAND_CALIBRATION_PAGE;
        subPageRoute = StateManagement::WAYANG_HAND_CALIBRATION_SUB_PAGE_ROUTE::WAYANG_HAND_CALIBRATION_1;
        WayangDisplayLCD_in_main.set_selection_point(2);
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::SITA_POINT_TO_FRONT:
        wayangSita.pointToFront();
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::SITA_LOW_POINT_TO_FRONT:
        wayangSita.lower_pointToFront();
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::SITA_MIDDLE_FRONT:
        wayangSita.middleFront();
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::SITA_DOWN_FRONT:
        wayangSita.downFront();
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::SITA_POINT_TO_SELF:
        wayangSita.pointToSelf();
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::SITA_DOWN_BACK:
        wayangSita.downBack();
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::SITA_ON_HIP_BACK:
        wayangSita.onHipBack();
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;  

    case StateManagement::FSA_STATE::SITA_POINT_TO_BACK:
        wayangSita.pointToBack();
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::SITA_LOW_POINT_TO_BACK:
        wayangSita.lowPointToBack();
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::SITA_MIDDLE_BACK:
        wayangSita.middleBack();
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;
    
    }
}

/*
Function interrupt untuk press button dari Rotary Encoder
*/
void WayangDisplayController::pressRotaryEncoder()
{
    if (millis() - last_run > 10)
    {
        switch (pageRoute)
        {
        case StateManagement::PAGE_ROUTE::MENU_PAGE:
            switch (WayangDisplayLCD_in_main.get_selection_point())
            {
            case 0:
                pageRoute = StateManagement::PAGE_ROUTE::MENU_PAGE;
                WayangDisplayLCD_in_main.set_selection_point(1);
                break;

            case 1:
                pageRoute = StateManagement::PAGE_ROUTE::EPISODE_PAGE;
                // subPageRoute = StateManagement::SUB_EPISODE_PAGE_ROUTE::EPISODE123;
                WayangDisplayLCD_in_main.set_selection_point(1);
                break;

            case 2:
                pageRoute = StateManagement::PAGE_ROUTE::CALIBRATE_PAGE;
                // subPageRoute = StateManagement::SUB_CALIBRATE_PAGE_ROUTE::CALIBRATE_1;
                WayangDisplayLCD_in_main.set_selection_point(1);
                break;

            case 3:
                pageRoute = StateManagement::PAGE_ROUTE::SETTINGS_PAGE;
                // subPageRoute = 0;
                WayangDisplayLCD_in_main.set_selection_point(1);
                break;
            }
            break;

        case StateManagement::PAGE_ROUTE::EPISODE_PAGE:
            switch (WayangDisplayLCD_in_main.get_selection_point() + subPageRoute)
            {
            case 0:
                pageRoute = StateManagement::PAGE_ROUTE::MENU_PAGE;
                WayangDisplayLCD_in_main.set_selection_point(1);
                break;

            case 1:
                // Play Episode 1
                loop_state = StateManagement::FSA_STATE::PLAY_EPISODE_1;
                // do nothing
                break;

            case 2:
                // Play Episode 2
                loop_state = StateManagement::FSA_STATE::PLAY_EPISODE_2;
                // do nothing
                break;

            case 3:
                // Play Episode 3
                // do nothing
                break;

            case 4:
                // Play Episode 4
                // do nothing
                break;

            case 5:
                // Play Episode 5
                // do nothing
                break;
            }
            break;

        case StateManagement::PAGE_ROUTE::CALIBRATE_PAGE:
            switch (WayangDisplayLCD_in_main.get_selection_point() + subPageRoute)
            {
            case 0:
                pageRoute = StateManagement::PAGE_ROUTE::MENU_PAGE;
                WayangDisplayLCD_in_main.set_selection_point(1);
                break;

            case 1:
                loop_state = StateManagement::FSA_STATE::CALIBRATING_ALL_NEMA;
                break;
            case 2:
                loop_state = StateManagement::FSA_STATE::MP3_REINIT;
                break;
            case 3:
                loop_state = StateManagement::FSA_STATE::WAYANG_HAND_CALIBRATION;
                break;
            case 4:
                loop_state = StateManagement::FSA_STATE::SENSOR_CHECK;
                break;
            }

            break;

        case StateManagement::PAGE_ROUTE::SETTINGS_PAGE:
            switch (WayangDisplayLCD_in_main.get_selection_point())
            {
            case 0:
                pageRoute = StateManagement::PAGE_ROUTE::MENU_PAGE;
                WayangDisplayLCD_in_main.set_selection_point(1);
                break;

            case 1:
                // Volume
                // do nothing
                break;
            }
            break;

        case StateManagement::PAGE_ROUTE::SENSOR_STATUS_PAGE:
            switch (WayangDisplayLCD_in_main.get_selection_point())
            {
            case 0:
                pageRoute = StateManagement::PAGE_ROUTE::CALIBRATE_PAGE;
                subPageRoute = StateManagement::SUB_CALIBRATE_PAGE_ROUTE::CALIBRATE_2;
                WayangDisplayLCD_in_main.set_selection_point(3);
                break;

            default:
                break;
            }

        case StateManagement::PAGE_ROUTE::WAYANG_HAND_CALIBRATION_PAGE:
            switch (WayangDisplayLCD_in_main.get_selection_point())
            {
            case 0:
                pageRoute = StateManagement::PAGE_ROUTE::CALIBRATE_PAGE;
                subPageRoute = StateManagement::SUB_CALIBRATE_PAGE_ROUTE::CALIBRATE_1;
                WayangDisplayLCD_in_main.set_selection_point(3);
                break;

            case 1:
                loop_state = StateManagement::FSA_STATE::SIMPLE_WAYANG_HAND_CALIBRATION;
                break;

            case 2:
                loop_state = StateManagement::FSA_STATE::SITA_HAND;
                break;

            case 3:
                // Rahwana
                break;

            case 4:
                // Rama Wijaya
                break;

            case 5:
                // Hanoman
                break;

            case 6:
                // Laksmana
                break;

            case 7:
                // Sugriwa
                break;

            case 8:
                // Subali
                break;

            case 9:
                // Wibhisana
                break;

            case 10:
                // Anggada
                break;

            case 11:
                // Anila
                break;
            }
        case StateManagement::PAGE_ROUTE::SITA_HAND_PAGE:
            switch (WayangDisplayLCD_in_main.get_selection_point())
            {
            case 0:
                loop_state = StateManagement::FSA_STATE::EXIT_SITA_HAND;
                break;

            case 1:
                // loop_state = StateManagement::FSA_STATE::SITA_POINT_TO_FRONT;
                break;

            case 2:
                // loop_state = StateManagement::FSA_STATE::SITA_LOW_POINT_TO_FRONT;
                break;

            case 3:
                // loop_state = StateManagement::FSA_STATE::SITA_MIDDLE_FRONT;
                break;

            case 4:
                // loop_state = StateManagement::FSA_STATE::SITA_DOWN_FRONT;
                break;

            case 5:
                // loop_state = StateManagement::FSA_STATE::SITA_POINT_TO_SELF;
                break;

            case 6:
                // loop_state = StateManagement::FSA_STATE::SITA_DOWN_BACK;
                break;

            case 7:
                // loop_state = StateManagement::FSA_STATE::SITA_ON_HIP_BACK;
                break;

            case 8:
                // loop_state = StateManagement::FSA_STATE::SITA_POINT_TO_BACK;
                break;

            case 9:
                // loop_state = StateManagement::FSA_STATE::SITA_LOW_POINT_TO_BACK;
                break;

            case 10:
                // loop_state = StateManagement::FSA_STATE::SITA_MIDDLE_BACK;
                break;
            }
        }
    }
    last_run = millis();
}

/*
Function interrupt untuk spin dari Rotary Encoder
*/
void WayangDisplayController::spinRotaryEncoder()
{
    switch (pageRoute)
    {
    case StateManagement::PAGE_ROUTE::MENU_PAGE:
        if (millis() - last_run > 5)
        {
            if (digitalRead(OUTPUT_B) == HIGH)
            {
                if (WayangDisplayLCD_in_main.get_selection_point() < 3)
                {
                    // Serial.print(WayangDisplayLCD_in_main.get_selection_point());
                    WayangDisplayLCD_in_main.increment_selection_point();
                    // WayangDisplayLCD_in_main.refreshLCD();
                    // WayangDisplayLCD_in_main.MenuDisplay();
                }
                else
                {
                    Serial.print("UDAH METOK!");
                }
            }
            else if (digitalRead(OUTPUT_B) == LOW)
            {
                if (WayangDisplayLCD_in_main.get_selection_point() > 1)
                {
                    // Serial.print(WayangDisplayLCD_in_main.get_selection_point());
                    WayangDisplayLCD_in_main.decrement_selection_point();
                    // WayangDisplayLCD_in_main.refreshLCD();
                    // WayangDisplayLCD_in_main.MenuDisplay();
                }
                else
                {
                    Serial.print("UDAH METOK!");
                }
            }
        }
        last_run = millis();
        break;

    case StateManagement::PAGE_ROUTE::EPISODE_PAGE:
        if (millis() - last_run > 5)
        {
            if (digitalRead(OUTPUT_B) == HIGH)
            {
                if (WayangDisplayLCD_in_main.get_selection_point() < 3)
                {
                    // Serial.print(WayangDisplayLCD_in_main.get_selection_point());
                    WayangDisplayLCD_in_main.increment_selection_point();
                    // WayangDisplayLCD_in_main.refreshLCD();
                    // WayangDisplayLCD_in_main.MenuDisplay();
                }
                else
                {
                    if (subPageRoute < StateManagement::SUB_EPISODE_PAGE_ROUTE::EPISODE2345)
                    {
                        subPageRoute++;
                        WayangDisplayLCD_in_main.set_selection_point(2);
                    }
                }
            }
            else if (digitalRead(OUTPUT_B) == LOW)
            {
                if (WayangDisplayLCD_in_main.get_selection_point() > 0)
                {
                    // Serial.print(WayangDisplayLCD_in_main.get_selection_point());
                    WayangDisplayLCD_in_main.decrement_selection_point();
                    // WayangDisplayLCD_in_main.refreshLCD();
                    // WayangDisplayLCD_in_main.MenuDisplay();
                }
                else
                {
                    if (subPageRoute > StateManagement::SUB_EPISODE_PAGE_ROUTE::EPISODE123)
                    {
                        subPageRoute--;
                        WayangDisplayLCD_in_main.set_selection_point(1);
                    }
                }
            }
        }
        last_run = millis();
        break;

    case StateManagement::PAGE_ROUTE::CALIBRATE_PAGE:
        if (millis() - last_run > 5)
        {
            if (digitalRead(OUTPUT_B) == HIGH)
            {
                if (WayangDisplayLCD_in_main.get_selection_point() < 3)
                {
                    // Serial.print(WayangDisplayLCD_in_main.get_selection_point());
                    WayangDisplayLCD_in_main.increment_selection_point();
                    // WayangDisplayLCD_in_main.refreshLCD();
                    // WayangDisplayLCD_in_main.MenuDisplay();
                }
                else
                {
                    if (subPageRoute < StateManagement::SUB_CALIBRATE_PAGE_ROUTE::CALIBRATE_2)
                    {
                        subPageRoute++;
                        WayangDisplayLCD_in_main.set_selection_point(2);
                    }
                }
            }
            else if (digitalRead(OUTPUT_B) == LOW)
            {
                if (WayangDisplayLCD_in_main.get_selection_point() > 0)
                {
                    Serial.print(WayangDisplayLCD_in_main.get_selection_point());
                    WayangDisplayLCD_in_main.decrement_selection_point();
                    // WayangDisplayLCD_in_main.refreshLCD();
                    // WayangDisplayLCD_in_main.MenuDisplay();
                }
                else
                {
                    if (subPageRoute > StateManagement::SUB_CALIBRATE_PAGE_ROUTE::CALIBRATE_1)
                    {
                        subPageRoute--;
                        WayangDisplayLCD_in_main.set_selection_point(1);
                    }
                }
            }
        }
        last_run = millis();
        break;

    case StateManagement::PAGE_ROUTE::SETTINGS_PAGE:
        if (millis() - last_run > 5)
        {
            if (digitalRead(OUTPUT_B) == HIGH)
            {
                if (WayangDisplayLCD_in_main.get_selection_point() < 1)
                {
                    Serial.print(WayangDisplayLCD_in_main.get_selection_point());
                    WayangDisplayLCD_in_main.increment_selection_point();
                    // WayangDisplayLCD_in_main.refreshLCD();
                    // WayangDisplayLCD_in_main.MenuDisplay();
                }
                else
                {
                    Serial.print("UDAH METOK!");
                }
            }
            else if (digitalRead(OUTPUT_B) == LOW)
            {
                if (WayangDisplayLCD_in_main.get_selection_point() > 0)
                {
                    Serial.print(WayangDisplayLCD_in_main.get_selection_point());
                    WayangDisplayLCD_in_main.decrement_selection_point();
                    // WayangDisplayLCD_in_main.refreshLCD();
                    // WayangDisplayLCD_in_main.MenuDisplay();
                }
                else
                {
                    Serial.print("UDAH METOK!");
                }
            }
        }
        last_run = millis();
        break;

    case StateManagement::PAGE_ROUTE::SENSOR_STATUS_PAGE:
        if (millis() - last_run > 5)
        {
            if (digitalRead(OUTPUT_B) == HIGH)
            {
                if (WayangDisplayLCD_in_main.get_selection_point() < 3)
                {
                    // Serial.print(WayangDisplayLCD_in_main.get_selection_point());
                    WayangDisplayLCD_in_main.increment_selection_point();
                    // WayangDisplayLCD_in_main.refreshLCD();
                    // WayangDisplayLCD_in_main.MenuDisplay();
                }
                else
                {
                    if (subSubPageRoute < StateManagement::SENSOR_STATUS_PAGE_ROUTE::SENSOR_78910)
                    {
                        subSubPageRoute++;
                        WayangDisplayLCD_in_main.set_selection_point(2);
                    }
                }
            }
            else if (digitalRead(OUTPUT_B) == LOW)
            {
                if (WayangDisplayLCD_in_main.get_selection_point() > 0)
                {
                    Serial.print(WayangDisplayLCD_in_main.get_selection_point());
                    WayangDisplayLCD_in_main.decrement_selection_point();
                    // WayangDisplayLCD_in_main.refreshLCD();
                    // WayangDisplayLCD_in_main.MenuDisplay();
                }
                else
                {
                    if (subSubPageRoute > StateManagement::SENSOR_STATUS_PAGE_ROUTE::SENSOR_123)
                    {
                        subSubPageRoute--;
                        WayangDisplayLCD_in_main.set_selection_point(1);
                    }
                }
            }
        }
        last_run = millis();
        break;

    case StateManagement::PAGE_ROUTE::WAYANG_HAND_CALIBRATION_PAGE:
        if (millis() - last_run > 5)
        {
            if (digitalRead(OUTPUT_B) == HIGH)
            {
                if (WayangDisplayLCD_in_main.get_selection_point() < 3)
                {
                    // Serial.print(WayangDisplayLCD_in_main.get_selection_point());
                    WayangDisplayLCD_in_main.increment_selection_point();
                    // WayangDisplayLCD_in_main.refreshLCD();
                    // WayangDisplayLCD_in_main.MenuDisplay();
                }
                else
                {
                    if (subSubPageRoute < StateManagement::WAYANG_HAND_CALIBRATION_SUB_PAGE_ROUTE::WAYANG_HAND_CALIBRATION_9)
                    {
                        subSubPageRoute++;
                        WayangDisplayLCD_in_main.set_selection_point(2);
                    }
                }
            }
            else if (digitalRead(OUTPUT_B) == LOW)
            {
                if (WayangDisplayLCD_in_main.get_selection_point() > 0)
                {
                    Serial.print(WayangDisplayLCD_in_main.get_selection_point());
                    WayangDisplayLCD_in_main.decrement_selection_point();
                    // WayangDisplayLCD_in_main.refreshLCD();
                    // WayangDisplayLCD_in_main.MenuDisplay();
                }
                else
                {
                    if (subSubPageRoute > StateManagement::WAYANG_HAND_CALIBRATION_SUB_PAGE_ROUTE::WAYANG_HAND_CALIBRATION_1)
                    {
                        subSubPageRoute--;
                        WayangDisplayLCD_in_main.set_selection_point(1);
                    }
                }
            }
        }
        last_run = millis();
        break;
    case StateManagement::PAGE_ROUTE::SITA_HAND_PAGE:
        if (millis() - last_run > 5)
        {
            if (digitalRead(OUTPUT_B) == HIGH)
            {
                if (WayangDisplayLCD_in_main.get_selection_point() < 3)
                {
                    // Serial.print(WayangDisplayLCD_in_main.get_selection_point());
                    WayangDisplayLCD_in_main.increment_selection_point();
                    // WayangDisplayLCD_in_main.refreshLCD();
                    // WayangDisplayLCD_in_main.MenuDisplay();
                }
                else
                {
                    if (subSubPageRoute < StateManagement::WAYANG_HAND_CALIBRATION_SUB_PAGE_ROUTE_SITA::SITA_HAND_CALIBRATION_8)
                    {
                        subSubPageRoute++;
                        WayangDisplayLCD_in_main.set_selection_point(2);
                    }
                }
            }
            else if (digitalRead(OUTPUT_B) == LOW)
            {
                if (WayangDisplayLCD_in_main.get_selection_point() > 0)
                {
                    Serial.print(WayangDisplayLCD_in_main.get_selection_point());
                    WayangDisplayLCD_in_main.decrement_selection_point();
                    // WayangDisplayLCD_in_main.refreshLCD();
                    // WayangDisplayLCD_in_main.MenuDisplay();
                }
                else
                {
                    if (subSubPageRoute > StateManagement::WAYANG_HAND_CALIBRATION_SUB_PAGE_ROUTE_SITA::SITA_HAND_CALIBRATION_1)
                    {
                        subSubPageRoute--;
                        WayangDisplayLCD_in_main.set_selection_point(1);
                    }
                }
            }
        }
        last_run = millis();
        break;
    }
}

void WayangHorizontalControl::wayang1(int distance)
{
    // digitalWrite(WAYANG_HAND_1, HIGH);
    digitalWrite(EN_NEMA_1, LOW);
    // delay(100);
    if (distance > getDistanceSensor1())
    {
        /* menjauhi sensor, CW */
        if (getDistanceSensor1() != -1)
        {
            bool state = true;
            digitalWrite(NEMA_DIR, LOW);
            while (distance != getDistanceSensor1())
            {
                digitalWrite(NEMA_STEP, state);
                state = !state;
                delayMicroseconds(PERIOD_NEMA); // customed delay for experiment
                if (distance == getDistanceSensor1() || distance < getDistanceSensor1() || getDistanceSensor1() == -1)
                {
                    break;
                }
            }
        }
        else
        {
            Serial.println("\nSensor 1 error read, returned -1");
        }
    }
    else if (distance < getDistanceSensor1())
    {
        /* mendekati sensor, CCW */
        bool state = true;
        digitalWrite(NEMA_DIR, HIGH);
        while (distance != getDistanceSensor1())
        {
            digitalWrite(NEMA_STEP, state);
            state = !state;
            delayMicroseconds(PERIOD_NEMA); // customed delay for experiment
            if (distance == getDistanceSensor1() || distance > getDistanceSensor1() || getDistanceSensor1() == -1)
            {
                break;
            }
        }
    }
    digitalWrite(EN_NEMA_1, HIGH);
}

void WayangHorizontalControl::wayang2(int distance)
{
    digitalWrite(EN_NEMA_2, LOW);
    delay(100);
    if (distance > getDistanceSensor2())
    {
        /* menjauhi sensor, CW */
        if (getDistanceSensor2() != -1)
        {
            bool state = true;
            digitalWrite(NEMA_DIR, LOW);
            while (distance != getDistanceSensor2())
            {
                digitalWrite(NEMA_STEP, state);
                state = !state;
                // delayMicroseconds(PERIOD_NEMA);
                if (distance == getDistanceSensor2() || distance < getDistanceSensor2() || getDistanceSensor2() == -1)
                {
                    break;
                }
            }
        }
        else
        {
            Serial.println("\nSensor 2 error read, returned -1");
        }
    }
    else if (distance < getDistanceSensor2())
    {
        /* mendekati sensor, CCW */
        bool state = true;
        digitalWrite(NEMA_DIR, HIGH);
        while (distance != getDistanceSensor2())
        {
            digitalWrite(NEMA_STEP, state);
            state = !state;
            // delayMicroseconds(PERIOD_NEMA);
            if (distance == getDistanceSensor2() || distance > getDistanceSensor2() || getDistanceSensor2() == -1)
            {
                break;
            }
        }
    }
    digitalWrite(EN_NEMA_2, HIGH);
}

void WayangHorizontalControl::wayang3(int distance)
{
    digitalWrite(EN_NEMA_3, LOW);
    delay(100);
    if (distance > getDistanceSensor3())
    {
        /* menjauhi sensor, CW */
        if (getDistanceSensor3() != -1)
        {
            bool state = true;
            digitalWrite(NEMA_DIR, LOW);
            while (distance != getDistanceSensor3())
            {
                digitalWrite(NEMA_STEP, state);
                state = !state;
                delayMicroseconds(PERIOD_NEMA);
                if (distance == getDistanceSensor3() || distance < getDistanceSensor3() || getDistanceSensor3() == -1)
                {
                    break;
                }
            }
        }
        else
        {
            Serial.println("\nSensor 3 error read, returned -1");
        }
    }
    else if (distance < getDistanceSensor3())
    {
        /* mendekati sensor, CCW */
        bool state = true;
        digitalWrite(NEMA_DIR, HIGH);
        while (distance != getDistanceSensor3())
        {
            digitalWrite(NEMA_STEP, state);
            state = !state;
            delayMicroseconds(PERIOD_NEMA);
            if (distance == getDistanceSensor3() || distance > getDistanceSensor3() || getDistanceSensor3() == -1)
            {
                break;
            }
        }
    }
    digitalWrite(EN_NEMA_3, HIGH);
}

// blm tak ubah dirnya
void WayangHorizontalControl::wayang4(int distance)
{
    digitalWrite(EN_NEMA_4, LOW);
    delay(100);
    if (distance > getDistanceSensor4())
    {
        /* menjauhi sensor, CCW */
        bool state = true;
        digitalWrite(NEMA_DIR, LOW);
        while (distance != getDistanceSensor4())
        {
            digitalWrite(NEMA_STEP, state);
            state = !state;
            delayMicroseconds(PERIOD_NEMA);
            if (distance == getDistanceSensor4() || distance < getDistanceSensor4() || getDistanceSensor4() == -1)
            {
                break;
            }
        }
    }
    else if (distance < getDistanceSensor4())
    {
        /* mendekati sensor, CW */
        bool state = true;
        digitalWrite(NEMA_DIR, HIGH);
        while (distance != getDistanceSensor4())
        {
            digitalWrite(NEMA_STEP, state);
            state = !state;
            delayMicroseconds(PERIOD_NEMA);
            if (distance == getDistanceSensor4() || distance > getDistanceSensor4() || getDistanceSensor4() == -1)
            {
                break;
            }
        }
    }
    digitalWrite(EN_NEMA_4, HIGH);
}

void WayangHorizontalControl::wayang5(int distance)
{
    digitalWrite(EN_NEMA_5, LOW);
    delay(100);
    if (distance > getDistanceSensor5())
    {
        /* menjauhi sensor, CCW */
        bool state = true;
        digitalWrite(NEMA_DIR, LOW);
        while (distance != getDistanceSensor5())
        {
            digitalWrite(NEMA_STEP, state);
            state = !state;
            delayMicroseconds(PERIOD_NEMA);
            if (distance == getDistanceSensor5() || distance < getDistanceSensor5() || getDistanceSensor5() == -1)
            {
                break;
            }
        }
    }
    else if (distance < getDistanceSensor5())
    {
        /* mendekati sensor, CW */
        bool state = true;
        digitalWrite(NEMA_DIR, HIGH);
        while (distance != getDistanceSensor5())
        {
            digitalWrite(NEMA_STEP, state);
            state = !state;
            delayMicroseconds(PERIOD_NEMA);
            if (distance == getDistanceSensor5() || distance > getDistanceSensor5() || getDistanceSensor5() == -1)
            {
                break;
            }
        }
    }
    digitalWrite(EN_NEMA_5, HIGH);
}

void WayangHorizontalControl::wayang6(int distance)
{
    digitalWrite(EN_NEMA_6, LOW);
    delay(100);
    if (distance > getDistanceSensor6())
    {
        /* menjauhi sensor, CCW */
        bool state = true;
        digitalWrite(NEMA_DIR, LOW);
        while (distance != getDistanceSensor6())
        {
            digitalWrite(NEMA_STEP, state);
            state = !state;
            delayMicroseconds(PERIOD_NEMA);
            if (distance == getDistanceSensor6() || distance < getDistanceSensor6() || getDistanceSensor6() == -1)
            {
                break;
            }
        }
    }
    else if (distance < getDistanceSensor6())
    {
        /* mendekati sensor, CW */
        bool state = true;
        digitalWrite(NEMA_DIR, HIGH);
        while (distance != getDistanceSensor6())
        {
            digitalWrite(NEMA_STEP, state);
            state = !state;
            delayMicroseconds(PERIOD_NEMA);
            if (distance == getDistanceSensor6() || distance > getDistanceSensor6() || getDistanceSensor6() == -1)
            {
                break;
            }
        }
    }
    digitalWrite(EN_NEMA_6, HIGH);
}

void WayangHorizontalControl::wayang7(int distance)
{
    digitalWrite(EN_NEMA_7, LOW);
    delay(100);
    if (distance > getDistanceSensor7())
    {
        /* menjauhi sensor, CCW */
        bool state = true;
        digitalWrite(NEMA_DIR, LOW);
        while (distance != getDistanceSensor7())
        {
            digitalWrite(NEMA_STEP, state);
            state = !state;
            delayMicroseconds(PERIOD_NEMA);
            if (distance == getDistanceSensor7() || distance < getDistanceSensor7() || getDistanceSensor7() == -1)
            {
                break;
            }
        }
    }
    else if (distance < getDistanceSensor7())
    {
        /* mendekati sensor, CW */
        bool state = true;
        digitalWrite(NEMA_DIR, HIGH);
        while (distance != getDistanceSensor7())
        {
            digitalWrite(NEMA_STEP, state);
            state = !state;
            delayMicroseconds(PERIOD_NEMA);
            if (distance == getDistanceSensor7() || distance > getDistanceSensor7() || getDistanceSensor7() == -1)
            {
                break;
            }
        }
    }
    digitalWrite(EN_NEMA_7, HIGH);
}

void WayangHorizontalControl::wayang8(int distance)
{
    digitalWrite(EN_NEMA_8, LOW);
    delay(100);
    if (distance > getDistanceSensor8())
    {
        /* menjauhi sensor, CCW */
        bool state = true;
        digitalWrite(NEMA_DIR, LOW);
        while (distance != getDistanceSensor8())
        {
            digitalWrite(NEMA_STEP, state);
            state = !state;
            delayMicroseconds(PERIOD_NEMA);
            if (distance == getDistanceSensor8() || distance < getDistanceSensor8() || getDistanceSensor8() == -1)
            {
                break;
            }
        }
    }
    else if (distance < getDistanceSensor8())
    {
        /* mendekati sensor, CW */
        bool state = true;
        digitalWrite(NEMA_DIR, HIGH);
        while (distance != getDistanceSensor8())
        {
            digitalWrite(NEMA_STEP, state);
            state = !state;
            delayMicroseconds(PERIOD_NEMA);
            if (distance == getDistanceSensor8() || distance > getDistanceSensor8() || getDistanceSensor8() == -1)
            {
                break;
            }
        }
    }
    digitalWrite(EN_NEMA_8, HIGH);
}

void WayangHorizontalControl::wayang9(int distance)
{
    digitalWrite(EN_NEMA_9, LOW);
    delay(100);
    if (distance > getDistanceSensor9())
    {
        /* menjauhi sensor, CCW */
        bool state = true;
        digitalWrite(NEMA_DIR, LOW);
        while (distance != getDistanceSensor9())
        {
            digitalWrite(NEMA_STEP, state);
            state = !state;
            delayMicroseconds(PERIOD_NEMA);
            if (distance == getDistanceSensor9() || distance < getDistanceSensor9() || getDistanceSensor9() == -1)
            {
                break;
            }
        }
    }
    else if (distance < getDistanceSensor9())
    {
        /* mendekati sensor, CW */
        bool state = true;
        digitalWrite(NEMA_DIR, HIGH);
        while (distance != getDistanceSensor9())
        {
            digitalWrite(NEMA_STEP, state);
            state = !state;
            delayMicroseconds(PERIOD_NEMA);
            if (distance == getDistanceSensor9() || distance > getDistanceSensor9() || getDistanceSensor9() == -1)
            {
                break;
            }
        }
    }
    digitalWrite(EN_NEMA_9, HIGH);
}

void WayangHorizontalControl::wayang10(int distance)
{
    digitalWrite(EN_NEMA_10, LOW);
    delay(100);
    if (distance > getDistanceSensor10())
    {
        /* menjauhi sensor, CCW */
        bool state = true;
        digitalWrite(NEMA_DIR, LOW);
        while (distance != getDistanceSensor10())
        {
            digitalWrite(NEMA_STEP, state);
            state = !state;
            delayMicroseconds(PERIOD_NEMA);
            if (distance == getDistanceSensor10() || distance < getDistanceSensor10() || getDistanceSensor10() == -1)
            {
                break;
            }
        }
    }
    else if (distance < getDistanceSensor10())
    {
        /* mendekati sensor, CW */
        bool state = true;
        digitalWrite(NEMA_DIR, HIGH);
        while (distance != getDistanceSensor10())
        {
            digitalWrite(NEMA_STEP, state);
            state = !state;
            delayMicroseconds(PERIOD_NEMA);
            if (distance == getDistanceSensor10() || distance > getDistanceSensor10() || getDistanceSensor10() == -1)
            {
                break;
            }
        }
    }
    digitalWrite(EN_NEMA_10, HIGH);
}

WayangHandServo::WayangHandServo(int leftOrRight)
{
    switch (leftOrRight)
    {
    case whatSideServo::LEFT:
        setServoPin1(LEFT_SERVO_1);
        setServoPin2(LEFT_SERVO_2);
        setServoPin3(LEFT_SERVO_3);
        setServoPin4(LEFT_SERVO_4);
        break;

    case whatSideServo::RIGHT:
        setServoPin1(RIGHT_SERVO_1);
        setServoPin2(RIGHT_SERVO_2);
        setServoPin3(RIGHT_SERVO_3);
        setServoPin4(RIGHT_SERVO_4);
        break;
    }
}

WayangHandServo::~WayangHandServo()
{
    // do nothing
}

void WayangHandServo::setServoPin1(int pin)
{
    this->servoPin1 = pin;
}

void WayangHandServo::setServoPin2(int pin)
{
    this->servoPin2 = pin;
}

void WayangHandServo::setServoPin3(int pin)
{
    this->servoPin3 = pin;
}

void WayangHandServo::setServoPin4(int pin)
{
    this->servoPin4 = pin;
}

int WayangHandServo::getServoPin1()
{
    return this->servoPin1;
}

int WayangHandServo::getServoPin2()
{
    return this->servoPin2;
}

int WayangHandServo::getServoPin3()
{
    return this->servoPin3;
}

int WayangHandServo::getServoPin4()
{
    return this->servoPin4;
}

int WayangHandServo::getAmountOfWaves()
{
    return this->amountOfWaves;
}

int WayangHandServo::getWavePeriod()
{
    return this->wavePeriod;
}

int WayangHandServo::degreeToDelay(int degree)
{
    return map(degree, 0, 180, 500, 2500);
}

void WayangHandServo::defaultPosition()
{
    moveWhatServo(1, 180, 500);
    moveWhatServo(2, 90, 200);
    moveWhatServo(3, 0, 500);
    moveWhatServo(4, 90, 200);
}

void WayangHandServo::resetArray()
{
    for (int i = 0; i < 4; i++)
    {
        setCurrentDegServo(i + 1, 0);
    }
}

int WayangHandServo::getCurrentDegServo(int servoNum)
{
    int result;
    switch (servoNum)
    {
    case 1:
        result = this->currentDeg[0];
        break;

    case 2:
        result = this->currentDeg[1];
        break;

    case 3:
        result = this->currentDeg[2];
        break;

    case 4:
        result = this->currentDeg[3];
        break;
    }
    return result;
}

void WayangHandServo::setCurrentDegServo(int servoNum, int degree)
{
    switch (servoNum)
    {
    case 1:
        this->currentDeg[0] = degree;
        break;

    case 2:
        this->currentDeg[1] = degree;
        break;

    case 3:
        this->currentDeg[2] = degree;
        break;

    case 4:
        this->currentDeg[3] = degree;
        break;
    }
}

void WayangHandServo::moveWhatServo(int servoNum, int degree, int desiredDuration)
{
    int selectedPin;
    switch (servoNum)
    {
    case 1:
        selectedPin = getServoPin1();
        break;

    case 2:
        selectedPin = getServoPin2();
        break;

    case 3:
        selectedPin = getServoPin3();
        break;

    case 4:
        selectedPin = getServoPin4();
        break;
    }

    int curdeg = getCurrentDegServo(servoNum);
    if (curdeg - degree != 0)
    {
        int waveAmount = desiredDuration / 20;
        delay(desiredDuration % 20);
        int degmismatch = abs(curdeg - degree);
        int largemismatch = degmismatch;
        int divVar = 1;

        // subdivide until nondec
        while (waveAmount / largemismatch < 1)
        {
            largemismatch = largemismatch / 2;
            divVar = divVar * 2;
        }

        int mismatchremainder = degmismatch % divVar;
        int remainder = waveAmount % largemismatch;
        Serial.println((String)largemismatch);

        if (curdeg > degree)
        {
            if (mismatchremainder != 0)
            {
                for (int i = 0; i < remainder; i++)
                {
                    digitalWrite(selectedPin, HIGH);
                    delayMicroseconds(degreeToDelay(curdeg - mismatchremainder));
                    digitalWrite(selectedPin, LOW);
                    delayMicroseconds((getWavePeriod() - degreeToDelay(curdeg - mismatchremainder)) / 2); // to deal with 16ms delayMicroseconds bug
                    delayMicroseconds((getWavePeriod() - degreeToDelay(curdeg - mismatchremainder)) / 2);
                }
            }

            for (int i = 0; i < largemismatch; i++)
            {
                for (int j = 0; j < waveAmount / largemismatch; j++)
                {
                    digitalWrite(selectedPin, HIGH);
                    delayMicroseconds(degreeToDelay(curdeg - i * divVar));
                    digitalWrite(selectedPin, LOW);
                    delayMicroseconds((getWavePeriod() - degreeToDelay(curdeg - i * divVar)) / 2);
                    delayMicroseconds((getWavePeriod() - degreeToDelay(curdeg - i * divVar)) / 2);
                }
            }

            if (mismatchremainder == 0 && remainder != 0)
            {
                for (int i = 0; i < remainder; i++)
                {
                    digitalWrite(selectedPin, HIGH);
                    delayMicroseconds(degreeToDelay(degree));
                    digitalWrite(selectedPin, LOW);
                    delayMicroseconds((getWavePeriod() - degreeToDelay(degree)) / 2);
                    delayMicroseconds((getWavePeriod() - degreeToDelay(degree)) / 2);
                }
            }
        }
        else
        {
            if (mismatchremainder != 0)
            {
                for (int i = 0; i < remainder; i++)
                {
                    digitalWrite(selectedPin, HIGH);
                    delayMicroseconds(degreeToDelay(curdeg + mismatchremainder));
                    digitalWrite(selectedPin, LOW);
                    delayMicroseconds((getWavePeriod() - degreeToDelay(curdeg + mismatchremainder)) / 2);
                    delayMicroseconds((getWavePeriod() - degreeToDelay(curdeg + mismatchremainder)) / 2);
                }
            }

            for (int i = 0; i < largemismatch; i++)
            {
                for (int j = 0; j < waveAmount / largemismatch; j++)
                {
                    digitalWrite(selectedPin, HIGH);
                    delayMicroseconds(degreeToDelay(curdeg + i * divVar));
                    digitalWrite(selectedPin, LOW);
                    delayMicroseconds((getWavePeriod() - degreeToDelay(curdeg + i * divVar)) / 2);
                    delayMicroseconds((getWavePeriod() - degreeToDelay(curdeg + i * divVar)) / 2);
                }
            }
            // int hajime, sutopu = 0;

            if (mismatchremainder == 0 && remainder != 0)
            {
                for (int i = 0; i < remainder; i++)
                {
                    // hajime = 0;
                    // sutopu = 0;
                    // hajime = millis();
                    digitalWrite(selectedPin, HIGH);
                    delayMicroseconds(degreeToDelay(degree));
                    digitalWrite(selectedPin, LOW);
                    delayMicroseconds((getWavePeriod() - degreeToDelay(degree)) / 2);
                    delayMicroseconds((getWavePeriod() - degreeToDelay(degree)) / 2);

                    // sutopu = millis();
                    // Serial.println("Duration taken: " + (String)(sutopu - hajime) + "\n");
                }
            }
        }

        setCurrentDegServo(servoNum, degree);

        // switch (servoNumber)
        // {
        // case 1:
        //     for (int i = 0; i < getAmountOfWaves(); i++)
        //     {
        //         digitalWrite(getServoPin1(), HIGH);
        //         delayMicroseconds(degreeToDelay(degree));
        //         digitalWrite(getServoPin1(), LOW);
        //         delayMicroseconds(getWavePeriod() - degreeToDelay(degree));
        //     }
        //     break;

        // case 2:
        //     for (int i = 0; i < getAmountOfWaves(); i++)
        //     {
        //         digitalWrite(getServoPin2(), HIGH);
        //         delayMicroseconds(degreeToDelay(degree));
        //         digitalWrite(getServoPin2(), LOW);
        //         delayMicroseconds(getWavePeriod() - degreeToDelay(degree));
        //     }
        //     break;

        // case 3:
        //     for (int i = 0; i < getAmountOfWaves(); i++)
        //     {
        //         digitalWrite(getServoPin3(), HIGH);
        //         delayMicroseconds(degreeToDelay(degree));
        //         digitalWrite(getServoPin3(), LOW);
        //         delayMicroseconds(getWavePeriod() - degreeToDelay(degree));
        //     }
        //     break;

        // case 4:
        //     for (int i = 0; i < getAmountOfWaves(); i++)
        //     {
        //         digitalWrite(getServoPin4(), HIGH);
        //         delayMicroseconds(degreeToDelay(degree));
        //         digitalWrite(getServoPin4(), LOW);
        //         delayMicroseconds(getWavePeriod() - degreeToDelay(degree));
        //     }
        //     break;
        // }
    }
    else
    {
        // do nothing
        delay(desiredDuration);
    }
}

void setAllMOSFETtoHIGH()
{
    digitalWrite(WAYANG_HAND_1, HIGH);
    digitalWrite(WAYANG_HAND_2, HIGH);
    digitalWrite(WAYANG_HAND_3, HIGH);
    digitalWrite(WAYANG_HAND_4, HIGH);
    digitalWrite(WAYANG_HAND_5, HIGH);
    digitalWrite(WAYANG_HAND_6, HIGH);
    digitalWrite(WAYANG_HAND_7, HIGH);
    digitalWrite(WAYANG_HAND_8, HIGH);
    digitalWrite(WAYANG_HAND_9, HIGH);
    digitalWrite(WAYANG_HAND_10, HIGH);
}

void setAllMOSFETtoLOW()
{
    digitalWrite(WAYANG_HAND_1, LOW);
    digitalWrite(WAYANG_HAND_2, LOW);
    digitalWrite(WAYANG_HAND_3, LOW);
    digitalWrite(WAYANG_HAND_4, LOW);
    digitalWrite(WAYANG_HAND_5, LOW);
    digitalWrite(WAYANG_HAND_6, LOW);
    digitalWrite(WAYANG_HAND_7, LOW);
    digitalWrite(WAYANG_HAND_8, LOW);
    digitalWrite(WAYANG_HAND_9, LOW);
    digitalWrite(WAYANG_HAND_10, LOW);
}

void CalibratingFunction::vSlotLinear()
{
    setAllMOSFETtoLOW();

    Serial.println("\nSensor 1\n");
    wayangSita.walk_to_a_certain_distance_before_calibrating_value(155);
    Serial.println("\nSensor 2\n");
    wayangRahwana.walk_to_a_certain_distance_before_calibrating_value(155);
    Serial.println("\nSensor 3\n");
    wayangRamaWijaya.walk_to_a_certain_distance_before_calibrating_value(155);
    Serial.println("\nSensor 4\n");
    wayangHanoman.walk_to_a_certain_distance_before_calibrating_value(155);
    Serial.println("\nSensor 5\n");
    wayangLaksmana.walk_to_a_certain_distance_before_calibrating_value(155);
    Serial.println("\nSensor 6\n");
    wayangSugriwa.walk_to_a_certain_distance_before_calibrating_value(155);
    Serial.println("\nSensor 7\n");
    wayangSubali.walk_to_a_certain_distance_before_calibrating_value(155);
    Serial.println("\nSensor 8\n");
    wayangWibhisana.walk_to_a_certain_distance_before_calibrating_value(155);

    Serial.println("\nSensor 1\n");
    wayangSita.defaultStandPosition();
    Serial.println("\nSensor 2\n");
    wayangRahwana.defaultStandPosition();
    Serial.println("\nSensor 3\n");
    wayangRamaWijaya.defaultStandPosition();
    Serial.println("\nSensor 4\n");
    wayangHanoman.defaultStandPosition();
    Serial.println("\nSensor 5\n");
    wayangLaksmana.defaultStandPosition();
    Serial.println("\nSensor 6\n");
    wayangSugriwa.defaultStandPosition();
    Serial.println("\nSensor 7\n");
    wayangSubali.defaultStandPosition();
    Serial.println("\nSensor 8\n");
    wayangWibhisana.defaultStandPosition();

    SoundSystem::playDialogFromACertainFolder(SoundSystem::INDICATOR_SOUND, SoundSystem::INDICATOR_SOUND_NUMBER::INDICATOR_VSLOT_CALIBRATION);
    delay(3500);

    // Serial.println("\nstep converting algorithm\n");
    // int firstValue = getDistanceSensor2();
    // Serial.print("first value: " + String(firstValue) + "\n");
    // wayangRahwana.walk_to_scene(500);
    // int secondValue = getDistanceSensor2();
    // Serial.print("second value: " + String(secondValue) + "\n");
    // float distance_per_step = abs(firstValue - secondValue) / float(500);
    // Serial.print("distance per step: " + String(distance_per_step) + "mm/step \n");

    setAllMOSFETtoHIGH();
}

void CalibratingFunction::soundSystem()
{
    setAllMOSFETtoLOW();
    WayangDisplayLCD_in_main.disableLCD();
    SoundSystem::initSound();
    setAllMOSFETtoHIGH();
    WayangDisplayLCD_in_main.enableLCD();
}

void CalibratingFunction::wayangHand()
{
    setAllMOSFETtoLOW();

    wayangSita.walk_to_a_certain_distance_before_calibrating_value(200);
    delay(500);
    wayangSita.defaultHandPosition();
    delay(500);
    wayangSita.defaultStandPosition();

    wayangRahwana.walk_to_a_certain_distance_before_calibrating_value(200);
    delay(500);
    wayangRahwana.defaultHandPosition();
    delay(500);
    wayangRahwana.defaultStandPosition();

    wayangRamaWijaya.walk_to_a_certain_distance_before_calibrating_value(200);
    delay(500);
    wayangRamaWijaya.defaultHandPosition();
    delay(500);
    wayangRamaWijaya.defaultStandPosition();

    wayangHanoman.walk_to_a_certain_distance_before_calibrating_value(200);
    delay(500);
    wayangHanoman.defaultHandPosition();
    delay(500);
    wayangHanoman.defaultStandPosition();

    wayangLaksmana.walk_to_a_certain_distance_before_calibrating_value(200);
    delay(500);
    wayangLaksmana.defaultHandPosition();
    delay(500);
    wayangLaksmana.defaultStandPosition();

    wayangSugriwa.walk_to_a_certain_distance_before_calibrating_value(200);
    delay(500);
    wayangSugriwa.mathentengA();
    delay(500);
    wayangSugriwa.defaultStandPosition();

    wayangSubali.walk_to_a_certain_distance_before_calibrating_value(200);
    delay(500);
    wayangSubali.mathenthengA();
    delay(500);
    wayangSubali.defaultStandPosition();

    wayangWibhisana.walk_to_a_certain_distance_before_calibrating_value(200);
    delay(500);
    wayangWibhisana.defaultHandPosition();
    delay(500);
    wayangWibhisana.defaultStandPosition();

    setAllMOSFETtoHIGH();
}

void CalibratingFunction::commandListHandMovementTest()
{

    setAllMOSFETtoLOW();

    // int startTime, endTime = 0;

    // // Duration test
    // // Point to Front
    // Serial.println("\n");
    // startTime = millis();
    // wayangRahwana.pointToFront();
    // endTime = millis();

    // Serial.println("Point to Front: " + String(endTime - startTime) + "ms");
    // delay(500);

    // // Down Front
    // startTime = 0;
    // endTime = 0;

    // startTime = millis();
    // wayangRahwana.downFront();
    // endTime = millis();

    // Serial.println("Down Front: " + String(endTime - startTime) + "ms");
    // delay(500);

    // // Middle Front
    // startTime = 0;
    // endTime = 0;

    // startTime = millis();
    // wayangRahwana.middleFront();
    // endTime = millis();

    // Serial.println("Middle Front: " + String(endTime - startTime) + "ms");
    // delay(500);

    // wayangRahwana.downFront();

    // startTime = 0;
    // endTime = 0;

    // startTime = millis();
    // delayMicroseconds(10000);
    // delayMicroseconds(10000);
    // endTime = millis();

    // Serial.println("Delay 10ms with us: " + String(endTime - startTime) + "ms");

    // // Sita
    // wayangSita.defaultStandPosition();
    // wayangSita.anjujur();
    // wayangSita.walk_to_a_certain_distance_before_calibrating_value(250);
    // delay(500);
    // wayangSita.pointToFront();
    // delay(500);
    // wayangSita.lower_pointToFront();
    // delay(500);
    // wayangSita.downFront();
    // wayangSita.middleFront();
    // delay(500);
    // wayangSita.downFront();
    // delay(500);
    // wayangSita.pointToBack();
    // delay(500);
    // wayangSita.downBack();
    // delay(500);
    // wayangSita.onHipBack();
    // delay(500);
    // wayangSita.downBack();
    // delay(500);
    // wayangSita.pointToSelf();
    // delay(500);
    // wayangSita.downFront();
    // delay(500);
    // wayangSita.middleFrontBack();
    // delay(500);
    // wayangSita.lowPointToBack();
    // delay(500);
    // wayangSita.downBack();
    // delay(500);
    // wayangSita.middleBack();
    // delay(500);
    // wayangSita.downBack();
    // wayangSita.defaultStandPosition();
    // wayangSita.defaultHandPosition();

    // Rahwana
    // wayangRahwana.defaultStandPosition();
    // wayangRahwana.defaultHandPosition();
    // wayangRahwana.walk_to_a_certain_distance_before_calibrating_value(250);
    // delay(500);
    // wayangRahwana.pointToFront();
    // delay(500);
    // wayangRahwana.lower_pointToFront();
    // delay(500);
    // // wayangRahwana.middleFront();
    // // delay(500);
    // wayangRahwana.downFront();
    // delay(500);
    // // wayangRahwana.pointToSelf();
    // // delay(500);
    // wayangRahwana.defaultStandPosition();
    // wayangRahwana.defaultHandPosition();

    // // Rama Wijaya
    // wayangRamaWijaya.defaultStandPosition();
    // wayangRamaWijaya.anjujur();
    // wayangRamaWijaya.mathentengC();
    // delay(500);
    // wayangRamaWijaya.mathenthengA();
    // delay(500);

    // wayangRamaWijaya.walk_to_a_certain_distance_before_calibrating_value(250);
    // delay(500);
    // wayangRamaWijaya.pointToFront();
    // delay(500);
    // wayangRamaWijaya.lower_pointToFront();
    // delay(500);
    // wayangRamaWijaya.middleFront();
    // delay(500);
    // wayangRamaWijaya.downFront();
    // delay(500);
    // wayangRamaWijaya.pointToBack();
    // delay(500);
    // wayangRamaWijaya.downBack();
    // delay(500);
    // wayangRamaWijaya.onHipBack();
    // delay(500);
    // wayangRamaWijaya.downBack();
    // delay(500);
    // wayangRamaWijaya.pointToSelf();
    // delay(500);
    // wayangRamaWijaya.downFront();
    // wayangRamaWijaya.middleFrontBack();
    // delay(500);
    // wayangRamaWijaya.lowPointToBack();
    // delay(500);
    // wayangRamaWijaya.defaultHandPosition();
    // wayangRamaWijaya.downBack();
    // delay(500);
    // wayangRamaWijaya.middleBack();
    // delay(500);
    // wayangRamaWijaya.defaultStandPosition();
    // wayangRamaWijaya.defaultHandPosition();

    // Hanoman
    // wayangHanoman.defaultStandPosition();
    // wayangHanoman.defaultHandPosition();
    // wayangHanoman.walk_to_a_certain_distance_before_calibrating_value(205);
    // delay(500);
    // wayangHanoman.pointToFront();
    // delay(500);
    // wayangHanoman.lower_pointToFront();
    // delay(500);
    // wayangHanoman.downFront();
    // delay(500);
    // wayangHanoman.middleFront();
    // delay(500);
    // wayangHanoman.downFront();
    // delay(500);
    // wayangHanoman.pointToBack();
    // delay(500);
    // wayangHanoman.downBack();
    // delay(500);
    // wayangHanoman.onHipBack();
    // delay(500);
    // wayangHanoman.pointToSelf();
    // delay(500);
    // wayangHanoman.downFront();
    // wayangHanoman.middleFrontBack();
    // delay(500);
    // wayangHanoman.lowPointToBack();
    // delay(500);
    // wayangHanoman.downBack();
    // delay(500);
    // wayangHanoman.middleBack();
    // delay(500);
    // wayangHanoman.defaultStandPosition();
    // wayangHanoman.defaultHandPosition();

    // // Laksmana
    // wayangLaksmana.defaultStandPosition();
    // wayangLaksmana.defaultHandPosition();
    // wayangLaksmana.walk_to_a_certain_distance_before_calibrating_value(250);
    // delay(500);
    // wayangLaksmana.pointToFront();
    // delay(500);
    // wayangLaksmana.lower_pointToFront();
    // delay(500);
    // wayangLaksmana.downFront(); // to make middle front possible
    // delay(500);
    // wayangLaksmana.middleFront();
    // delay(500);
    // wayangLaksmana.downFront();
    // delay(500);
    // wayangLaksmana.pointToBack();
    // delay(500);
    // // wayangLaksmana.downBack();
    // // delay(500);
    // wayangLaksmana.mathenthengA();
    // // wayangLaksmana.onHipBack();
    // // delay(500);
    // wayangLaksmana.pointToSelf();
    // delay(500);
    // wayangLaksmana.downFront();
    // delay(500);
    // // wayangLaksmana.middleFrontBack();
    // // delay(500);
    // wayangLaksmana.lowPointToBack();
    // delay(500);
    // wayangLaksmana.downBack();
    // delay(500); ///
    // wayangLaksmana.middleBack();
    // delay(500);
    // wayangLaksmana.downBack();
    // delay(500); ///
    // // wayangLaksmana.middleFrontBack();
    // // delay(500);
    // wayangLaksmana.defaultHandPosition();
    // wayangLaksmana.defaultStandPosition();

    // Sugriwa
    //
    wayangSugriwa.defaultStandPosition();
    // wayangSugriwa.mathentengA();
    wayangSugriwa.mathentengC();
    wayangSugriwa.walk_to_a_certain_distance_before_calibrating_value(250);
    wayangSugriwa.mathentengA();
    delay(500);
    wayangSugriwa.pointToFront();
    delay(500);
    wayangSugriwa.lower_pointToFront();
    delay(500);
    wayangSugriwa.downFront();
    delay(500);
    wayangSugriwa.middleFront();
    delay(500);
    wayangSugriwa.downFront();
    delay(500);

    wayangSugriwa.downBack();
    wayangSugriwa.pointToBack();
    delay(500);
    // wayangSugriwa.downBack();
    // delay(500);
    wayangSugriwa.mathentengA();
    // wayangSugriwa.onHipBack();
    // delay(500);
    // wayangSugriwa.downBack();
    // delay(500);

    // wayangSugriwa.mathentengA();
    //
    // wayangSugriwa.downFront();
    wayangSugriwa.pointToSelf();
    delay(500);

    // wayangSugriwa.downFront();
    // wayangSugriwa.middleFrontBack(); // ignore this
    // delay(500);
    // wayangSugriwa.downBack();
    // wayangSugriwa.lowPointToBack();
    // delay(500);
    // wayangSugriwa.downBack();
    // delay(500);
    // wayangSugriwa.middleBack();
    // delay(500);
    // wayangSugriwa.downBack();
    // delay(500);
    // wayangSugriwa.middleFrontBack();
    // delay(500);
    //
    wayangSugriwa.mathentengC();
    wayangSugriwa.defaultStandPosition();
    wayangSugriwa.mathentengA();

    // Subali
    // wayangSubali.defaultStandPosition();
    // wayangSubali.defaultHandPosition();

    // wayangSubali.mathenthengC();
    // wayangSubali.walk_to_a_certain_distance_before_calibrating_value(250);
    // delay(500);
    // wayangSubali.mathenthengA();
    // delay(500);
    // wayangSubali.pointToFront();
    // delay(500);
    // wayangSubali.lower_pointToFront();
    // delay(500);
    // wayangSubali.downFront();
    // delay(500);
    // wayangSubali.middleFront();
    // delay(500);
    // wayangSubali.downFront();
    // delay(500);
    // wayangSubali.downBack();
    // wayangSubali.pointToBack();
    // delay(500);
    // wayangSubali.mathenthengA();
    // delay(500);
    // wayangSubali.downBack();
    // delay(500);
    // wayangSubali.onHipBack();
    // delay(500);
    // wayangSubali.downBack();
    // delay(500);
    // wayangSubali.pointToSelf();
    // delay(500);
    // wayangSubali.downFront();
    // delay(500);
    // wayangSubali.middleFrontBack();
    // delay(500);
    // wayangSubali.downBack();
    // wayangSubali.lowPointToBack();
    // delay(500);
    // wayangSubali.downBack();
    // delay(500);
    // wayangSubali.middleBack();
    // delay(500);
    // wayangSubali.downBack();
    // delay(500);
    // wayangSubali.middleFrontBack();
    // delay(500);
    // wayangSubali.mathenthengC();
    // wayangSubali.defaultStandPosition();
    // wayangSubali.mathenthengA();

    setAllMOSFETtoHIGH();
}

void serialReaderTask(void *pvParameters)
{
    Serial.println(F("\n\nWayang Debug Serial Monitor!"));
    WayangDisplayLCD_in_main.introDisplay();
    beginingAllGPIOS();

    Serial.println(F("\nSetup done!"));
    while (1)
    {
        Serial.flush();
        String serial_data_json = Serial.readString();
        JsonDocument serial_data;

        DeserializationError error = deserializeJson(serial_data, serial_data_json);
        if (error)
        {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
            return;
        }

        String mode = serial_data["mode"];
        String command = serial_data["command"];

        if (mode == "play")
        {
            if (command == "ep1")
            {
                Serial.println("Playing Episode 1");
                Episodes::Episode_1();
            }
            else if (command == "ep2")
            {
                Serial.println("Playing Episode 2");
                Episodes::Episode_2();
            }
            else if (command == "ep3")
            {
                Serial.println("Playing Episode 3");
                Episodes::Episode_3();
            }
            else if (command == "ep4")
            {
                Serial.println("Playing Episode 4");
                Episodes::Episode_4();
            }
            else if (command == "ep5")
            {
                Serial.println("Playing Episode 5");
                Episodes::Episode_5();
            }
        }
        else if (mode == "calibrate")
        {
            if (command == "vslot")
            {
                Serial.println("Calibrating V-Slot");
                CalibratingFunction::vSlotLinear();
            }
            else if (command == "mp3")
            {
                Serial.println("Calibrating Sound System");
                CalibratingFunction::soundSystem();
            }
            else if (command == "wayanghand")
            {
                Serial.println("Calibrating Wayang Hand");
                CalibratingFunction::wayangHand();
            }
            else if (command == "tofsensor")
            {
                Serial.println("Tof sensor data");
                Serial.println("Sensor 1: " + getDistanceSensor1());
                Serial.println("Sensor 2: " + getDistanceSensor2());
                Serial.println("Sensor 3: " + getDistanceSensor3());
                Serial.println("Sensor 4: " + getDistanceSensor4());
                Serial.println("Sensor 5: " + getDistanceSensor5());
                Serial.println("Sensor 6: " + getDistanceSensor6());
                Serial.println("Sensor 7: " + getDistanceSensor7());
                Serial.println("Sensor 8: " + getDistanceSensor8());
                Serial.println("Sensor 9: " + getDistanceSensor9());
                Serial.println("Sensor 10: " + getDistanceSensor10());
            }
        }
    }
}

bool isModeChanged()
{
    bool result = false;
    Serial.flush();
    String serial_data_json = Serial.readString();
    JsonDocument serial_data;

    DeserializationError error = deserializeJson(serial_data, serial_data_json);
    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        result = false;
    }
    else
    {
        String mode = serial_data["mode"];
        String command = serial_data["command"];

        if (mode == "changemode")
        {
            if (command == "onlyserial")
            {
                WayangDisplayLCD_in_main.introDisplay();
                vTaskDelete(mainLoopTaskHandler);
            }
        }
        result = true;
    }
    return result;
}

int getSubPageRoute()
{
    return subPageRoute;
}

int getSubSubPageRoute()
{
    return subSubPageRoute;
}