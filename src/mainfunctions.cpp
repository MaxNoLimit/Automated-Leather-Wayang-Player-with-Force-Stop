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

RamaWijaya wayangRamaWijaya;
Sita wayangSita;
Rahwana wayangRahwana;

int lcd_2040_address;
WayangDisplay::WayangDisplayLCD WayangDisplayLCD_in_main(0x27);
unsigned long last_run = 0;
int loop_state = 0;

int pageRoute = StateManagement::PAGE_ROUTE::MENU_PAGE;
int subPageRouteEpisode = StateManagement::SUB_EPISODE_PAGE_ROUTE::EPISODE123;
int subPageRouteCalibrate = StateManagement::SUB_CALIBRATE_PAGE_ROUTE::CALIBRATE_1;
int subPageRouteSensorStatus = 0;
int settingsPageRoute = StateManagement::SETTINGS_PAGE_ROUTE::OPTION_SETTINGS;

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

    Wire.begin();
    Wire.setClock(400000);
    Wire.setTimeout(500);
    Wire.setWireTimeout(5000, true);
    SoundSystem::justInitTheSoundSystem();

    // beginAllinOneSensor();
    // setAllMOSFETtoLOW();
    // Serial.print(getDistanceSensor1_v2());
    // Serial.print(" mm\n");
    // setAllMOSFETtoHIGH();
    beginSensor1();
    // setAllMOSFETtoHIGH();
    beginSensor2();
    // setAllMOSFETtoHIGH();
    beginSensor3();
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
}

/*
Function untuk setup LCD 20x4
*/
void WayangDisplay::lcd2004setup()
{
    // Scanning address I2C yang terhubung
    lcd_2040_address = I2C_Scanner::scan_n_assign();

    // Reconstruct dengan address yang sudah di-scan
    WayangDisplayLCD_in_main = WayangDisplay::WayangDisplayLCD(lcd_2040_address); // re-construct
    WayangDisplayLCD_in_main.introDisplay();
    delay(2000);
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

        switch (subPageRouteEpisode)
        {
        case StateManagement::SUB_EPISODE_PAGE_ROUTE::EPISODE123:
            WayangDisplayLCD_in_main.EpisodeDisplay();
            break;

        case StateManagement::SUB_EPISODE_PAGE_ROUTE::EPISODE1234:
            WayangDisplayLCD_in_main.EpisodeDisplay2();
            break;

        case StateManagement::SUB_EPISODE_PAGE_ROUTE::EPISODE2345:
            WayangDisplayLCD_in_main.EpisodeDisplay3();
            break;
        }

        break;

    case StateManagement::PAGE_ROUTE::CALIBRATE_PAGE:
        switch (subPageRouteCalibrate)
        {
        case StateManagement::SUB_CALIBRATE_PAGE_ROUTE::CALIBRATE_1:
            WayangDisplayLCD_in_main.CalibrateDisplay();
            break;
        case StateManagement::SUB_CALIBRATE_PAGE_ROUTE::CALIBRATE_2:
            WayangDisplayLCD_in_main.CalibrateDisplay2();
            break;
        }
        break;

    case StateManagement::PAGE_ROUTE::SENSOR_STATUS_PAGE:
        switch (subPageRouteSensorStatus)
        {
        case StateManagement::SENSOR_STATUS_PAGE_ROUTE::SENSOR_123:
            WayangDisplayLCD_in_main.SensorStatusDisplay();
            break;

        case StateManagement::SENSOR_STATUS_PAGE_ROUTE::SENSOR_1234:
            WayangDisplayLCD_in_main.SensorStatusDisplay2();
            break;

        case StateManagement::SENSOR_STATUS_PAGE_ROUTE::SENSOR_2345:
            WayangDisplayLCD_in_main.SensorStatusDisplay3();
            break;

        case StateManagement::SENSOR_STATUS_PAGE_ROUTE::SENSOR_3456:
            WayangDisplayLCD_in_main.SensorStatusDisplay4();
            break;

        case StateManagement::SENSOR_STATUS_PAGE_ROUTE::SENSOR_4567:
            WayangDisplayLCD_in_main.SensorStatusDisplay5();
            break;

        case StateManagement::SENSOR_STATUS_PAGE_ROUTE::SENSOR_5678:
            WayangDisplayLCD_in_main.SensorStatusDisplay6();
            break;

        case StateManagement::SENSOR_STATUS_PAGE_ROUTE::SENSOR_6789:
            WayangDisplayLCD_in_main.SensorStatusDisplay7();
            break;

        case StateManagement::SENSOR_STATUS_PAGE_ROUTE::SENSOR_78910:
            WayangDisplayLCD_in_main.SensorStatusDisplay8();
            break;
        }
        break;

    case StateManagement::PAGE_ROUTE::SETTINGS_PAGE:
        switch (settingsPageRoute)
        {
        case StateManagement::SETTINGS_PAGE_ROUTE::OPTION_SETTINGS:
            WayangDisplayLCD_in_main.SettingsDisplay();
            break;

        case StateManagement::SETTINGS_PAGE_ROUTE::VOLUME_SETTINGS:
            // do nothing
            break;
        }

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
        setAllMOSFETtoLOW();
        // beginAllSensors();
        // wayangRahwana.defaultStandPosition();
        // wayangRahwana.walk_to_a_certain_distance(100); // 10 cm
        // wayangRahwana.walk_to_a_certain_distance(200); // 20 cm
        // wayangRahwana.walk_to_a_certain_distance(300); // 30 cm
        // wayangRahwana.defaultStandPosition();

        // Episodes::testing_sita_horizontal_movement();
        // Episodes::testing_rahwana_horizontal_movement();
        // Episodes::testing_rama_wijaya_horizontal_movement();

        /* Kalibrasi sebenarnya */
        // Wire.begin();
        // Wire.setClock(200000);
        // Wire.setTimeout(500);
        // Wire.setWireTimeout(5000, true);
        // setAllMOSFETtoHIGH();
        // delay(100);
        // if (!getSensorStatus(1))
        // {
        // beginSensor1();
        // }
        // Serial.println("\nMoving wayang 1!");
        // WayangHorizontalControl::wayang1(100);
        // Serial.println("wayang 1 distance: ");
        // Serial.print(getDistanceSensor1());
        // Serial.println(" mm \n");
        // setAllMOSFETtoHIGH();

        // setAllMOSFETtoLOW();
        // setAllMOSFETtoHIGH();

        // delay(100);
        // if (!getSensorStatus(2))
        // {
        // beginSensor2();
        // }
        // Serial.println("\nMoving wayang 2!");
        // WayangHorizontalControl::wayang2(100);
        // Serial.println("wayang 2 distance: ");
        // int d0 = getDistanceSensor2();
        // Serial.print(d0);
        // Serial.println(" mm \n");
        // setAllMOSFETtoHIGH();

        // wayangRahwana.walk_to_scene(280); // 10 cm

        // beginSensor2();

        // Serial.println("wayang 2 distance: ");
        // int d1 = getDistanceSensor2();
        // Serial.print(d1);
        // Serial.println(" mm \n");

        // Serial.print(d1 - d0);

        // wayangRahwana.leave_from_scene(280); // maybe 10 cm

        // beginSensor2();

        // Serial.println("wayang 2 distance: ");
        // int d2 = getDistanceSensor2();
        // Serial.print(d2);
        // Serial.println(" mm \n");

        // Serial.print(d2 - d1);

        // setAllMOSFETtoLOW();

        // delay(100);
        // if (!getSensorStatus(3))
        // {
        // beginSensor3();
        // }
        // Serial.println("\nMoving wayang 3!");
        // WayangHorizontalControl::wayang3(100);
        // Serial.println("wayang 3 distance: ");
        // Serial.print(getDistanceSensor3());
        // Serial.println(" mm \n");
        // setAllMOSFETtoHIGH();

        Serial.println("\nSensor 1\n");
        wayangSita.walk_to_a_certain_distance_before_calibrating_value(60);
        Serial.println("\nSensor 2\n");
        wayangRahwana.walk_to_a_certain_distance_before_calibrating_value(60);
        Serial.println("\nSensor 3\n");
        wayangRamaWijaya.walk_to_a_certain_distance_before_calibrating_value(60);

        Serial.println("\nSensor 1\n");
        wayangSita.walk_to_a_certain_distance_before_calibrating_value(100);
        Serial.println("\nSensor 2\n");
        wayangRahwana.walk_to_a_certain_distance_before_calibrating_value(100);
        Serial.println("\nSensor 3\n");
        wayangRamaWijaya.walk_to_a_certain_distance_before_calibrating_value(100);

        // Serial.println("\nSensor 1\n");
        // wayangSita.walk_to_a_certain_distance(50);
        // // Serial.println("\nSensor 2\n");
        // // wayangRahwana.walk_to_a_certain_distance(50);
        // Serial.println("\nSensor 3\n");
        // wayangRamaWijaya.walk_to_a_certain_distance(50);

        SoundSystem::playDialogFromACertainFolder(SoundSystem::INDICATOR_SOUND, SoundSystem::INDICATOR_SOUND_NUMBER::INDICATOR_VSLOT_CALIBRATION);
        delay(3500);

        setAllMOSFETtoHIGH();

        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::MP3_REINIT:
        setAllMOSFETtoLOW();
        WayangDisplayLCD_in_main.disableLCD();
        SoundSystem::initSound();
        setAllMOSFETtoHIGH();
        WayangDisplayLCD_in_main.enableLCD();
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::WAYANG_HAND_CALIBRATION:

        // testing Sita
        setAllMOSFETtoLOW();
        // WayangDisplayLCD_in_main.disableLCD();
        // wayangSita.hand_movement_test_1();
        wayangSita.defaultHandPosition();

        // testing Rahwana

        wayangRahwana.defaultHandPosition();
        // delay(1000);
        // wayangRahwana.pointToFront();
        // delay(1000);
        // wayangRahwana.pointToSelf();
        // delay(1000);
        // wayangRahwana.defaultHandPosition();
        // delay(1000);
        // testing Rama Wijaya
        // wayangRamaWijaya.hand_movement_test_1();
        wayangRamaWijaya.defaultHandPosition();
        // delay(1000);
        // // wayangRamaWijaya.right_moveHandBackAbit();
        // // delay(2000);
        // // wayangRamaWijaya.right_handOnHip();
        // // delay(2000);
        // // wayangRamaWijaya.left_pointToFront();
        // // delay(2000);
        // wayangRamaWijaya.left_pointToSelf();
        // delay(2000);
        // wayangRamaWijaya.defaultHandPosition();
        setAllMOSFETtoHIGH();
        SoundSystem::playDialogFromACertainFolder(SoundSystem::INDICATOR_SOUND, SoundSystem::INDICATOR_SOUND_NUMBER::INDICATOR_WAYANG_HAND_CALIBRATION);
        delay(3500);
        // WayangDisplayLCD_in_main.enableLCD();

        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::SENSOR_CHECK:
        pageRoute = StateManagement::PAGE_ROUTE::SENSOR_STATUS_PAGE;
        subPageRouteSensorStatus = StateManagement::SENSOR_STATUS_PAGE_ROUTE::SENSOR_123;
        WayangDisplayLCD_in_main.set_selection_point(1);
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::PLAY_EPISODE_1:
        WayangDisplayLCD_in_main.disableLCD();
        Episodes::July29_Episode();
        WayangDisplayLCD_in_main.enableLCD();
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
                subPageRouteEpisode = StateManagement::SUB_EPISODE_PAGE_ROUTE::EPISODE123;
                WayangDisplayLCD_in_main.set_selection_point(1);
                break;

            case 2:
                pageRoute = StateManagement::PAGE_ROUTE::CALIBRATE_PAGE;
                WayangDisplayLCD_in_main.set_selection_point(1);
                break;

            case 3:
                pageRoute = StateManagement::PAGE_ROUTE::SETTINGS_PAGE;
                WayangDisplayLCD_in_main.set_selection_point(1);
                break;
            }
            break;

        case StateManagement::PAGE_ROUTE::EPISODE_PAGE:
            switch (WayangDisplayLCD_in_main.get_selection_point())
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
                // do nothing
                break;

            case 3:
                // Play Episode 3
                // do nothing
                break;
            }
            break;

        case StateManagement::PAGE_ROUTE::SENSOR_STATUS_PAGE:
            switch (subPageRouteSensorStatus)
            {
            case StateManagement::SENSOR_STATUS_PAGE_ROUTE::SENSOR_123:
                switch (WayangDisplayLCD_in_main.get_selection_point())
                {
                case 0:
                    pageRoute = StateManagement::PAGE_ROUTE::CALIBRATE_PAGE;
                    subPageRouteCalibrate = StateManagement::SUB_CALIBRATE_PAGE_ROUTE::CALIBRATE_1;
                    WayangDisplayLCD_in_main.set_selection_point(0);
                    break;
                case 1:
                    // Calibrate Sensor 1
                    // beginSensor1();
                    break;

                case 2:
                    // Calibrate Sensor 2
                    // beginSensor2();
                    break;

                case 3:
                    // Calibrate Sensor 3
                    // beginSensor3();
                    break;
                }
                break;

            case StateManagement::SENSOR_STATUS_PAGE_ROUTE::SENSOR_1234:
                switch (WayangDisplayLCD_in_main.get_selection_point())
                {
                case 0:
                    // Calibrate Sensor 1
                    // beginSensor1();
                    break;

                case 1:
                    // Calibrate Sensor 2
                    // beginSensor2();
                    break;

                case 2:
                    // Calibrate Sensor 3
                    // beginSensor3();
                    break;

                case 3:
                    // Calibrate Sensor 4
                    // beginSensor4();
                    break;
                }
                break;

            case StateManagement::SENSOR_STATUS_PAGE_ROUTE::SENSOR_2345:
                switch (WayangDisplayLCD_in_main.get_selection_point())
                {
                case 0:
                    // Calibrate Sensor 2
                    // beginSensor2();
                    break;

                case 1:
                    // Calibrate Sensor 3
                    // beginSensor3();
                    break;

                case 2:
                    // Calibrate Sensor 4
                    // beginSensor4();
                    break;

                case 3:
                    // Calibrate Sensor 5
                    // beginSensor5();
                    break;
                }
                break;

            case StateManagement::SENSOR_STATUS_PAGE_ROUTE::SENSOR_3456:
                switch (WayangDisplayLCD_in_main.get_selection_point())
                {
                case 0:
                    // Calibrate Sensor 3
                    // beginSensor3();
                    break;

                case 1:
                    // Calibrate Sensor 4
                    // beginSensor4();
                    break;

                case 2:
                    // Calibrate Sensor 5
                    // beginSensor5();
                    break;

                case 3:
                    // Calibrate Sensor 6
                    // beginSensor6();
                    break;
                }
                break;

            case StateManagement::SENSOR_STATUS_PAGE_ROUTE::SENSOR_4567:
                switch (WayangDisplayLCD_in_main.get_selection_point())
                {
                case 0:
                    // Calibrate Sensor 4
                    // beginSensor4();
                    break;

                case 1:
                    // Calibrate Sensor 5
                    // beginSensor5();
                    break;

                case 2:
                    // Calibrate Sensor 6
                    // beginSensor6();
                    break;

                case 3:
                    // Calibrate Sensor 7
                    // beginSensor7();
                    break;
                }
                break;

            case StateManagement::SENSOR_STATUS_PAGE_ROUTE::SENSOR_5678:
                switch (WayangDisplayLCD_in_main.get_selection_point())
                {
                case 0:
                    // Calibrate Sensor 5
                    // beginSensor5();
                    break;

                case 1:
                    // Calibrate Sensor 6
                    // beginSensor6();
                    break;

                case 2:
                    // Calibrate Sensor 7
                    // beginSensor7();
                    break;

                case 3:
                    // Calibrate Sensor 8
                    // beginSensor8();
                    break;
                }
                break;

            case StateManagement::SENSOR_STATUS_PAGE_ROUTE::SENSOR_6789:
                switch (WayangDisplayLCD_in_main.get_selection_point())
                {
                case 0:
                    // Calibrate Sensor 6
                    // beginSensor6();
                    break;

                case 1:
                    // Calibrate Sensor 7
                    // beginSensor7();
                    break;

                case 2:
                    // Calibrate Sensor 8
                    // beginSensor8();
                    break;

                case 3:
                    // Calibrate Sensor 9
                    // beginSensor9();
                    break;
                }
                break;

            case StateManagement::SENSOR_STATUS_PAGE_ROUTE::SENSOR_78910:
                switch (WayangDisplayLCD_in_main.get_selection_point())
                {
                case 0:
                    // Calibrate Sensor 7
                    // beginSensor7();
                    break;

                case 1:
                    // Calibrate Sensor 8
                    // beginSensor8();
                    break;

                case 2:
                    // Calibrate Sensor 9
                    // beginSensor9();
                    break;

                case 3:
                    // Calibrate Sensor 10
                    // beginSensor10();
                    break;
                }
                break;
            }

        case StateManagement::PAGE_ROUTE::CALIBRATE_PAGE:
            switch (subPageRouteCalibrate)
            {
            case StateManagement::SUB_CALIBRATE_PAGE_ROUTE::CALIBRATE_1:
                switch (WayangDisplayLCD_in_main.get_selection_point())
                {
                case 0:
                    pageRoute = StateManagement::PAGE_ROUTE::MENU_PAGE;
                    WayangDisplayLCD_in_main.set_selection_point(1);
                    break;

                case 1:
                    // Calibrate V-Slot Linear
                    // Episodes::manual_begin();
                    loop_state = StateManagement::FSA_STATE::CALIBRATING_ALL_NEMA;
                    // Episodes::testing_rama_wijaya_horizontal_movement();
                    break;

                case 2:
                    // Calibrate Mp3 Player
                    loop_state = StateManagement::FSA_STATE::MP3_REINIT;
                    break;

                case 3:
                    // Calibrate Wayang's Hand
                    loop_state = StateManagement::FSA_STATE::WAYANG_HAND_CALIBRATION;
                    // do nothing
                    break;
                }
                break;

            case StateManagement::SUB_CALIBRATE_PAGE_ROUTE::CALIBRATE_2:
                switch (WayangDisplayLCD_in_main.get_selection_point())
                {
                case 0:
                    // Calibrate V-Slot Linear
                    // Episodes::manual_begin();
                    loop_state = StateManagement::FSA_STATE::CALIBRATING_ALL_NEMA;
                    // Episodes::testing_rama_wijaya_horizontal_movement();
                    break;

                case 1:
                    // Calibrate Mp3 Player
                    loop_state = StateManagement::FSA_STATE::MP3_REINIT;
                    break;

                case 2:
                    // Calibrate Wayang's Hand
                    loop_state = StateManagement::FSA_STATE::WAYANG_HAND_CALIBRATION;
                    // do nothing
                    break;

                case 3:
                    // Calibrate Sensor
                    loop_state = StateManagement::FSA_STATE::SENSOR_CHECK;
                    // do nothing
                    break;
                }
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
                if (WayangDisplayLCD_in_main.get_selection_point() > 1)
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

    case StateManagement::PAGE_ROUTE::EPISODE_PAGE:
        if (millis() - last_run > 5)
        {
            if (digitalRead(OUTPUT_B) == HIGH)
            {
                if (WayangDisplayLCD_in_main.get_selection_point() < 3)
                {
                    Serial.print(WayangDisplayLCD_in_main.get_selection_point());
                    WayangDisplayLCD_in_main.increment_selection_point();
                    // WayangDisplayLCD_in_main.refreshLCD();
                    // WayangDisplayLCD_in_main.MenuDisplay();
                }
                else
                {
                    if (subPageRouteEpisode < StateManagement::SUB_EPISODE_PAGE_ROUTE::EPISODE2345)
                    {
                        subPageRouteEpisode++;
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
                    if (subPageRouteEpisode > StateManagement::SUB_EPISODE_PAGE_ROUTE::EPISODE123)
                    {
                        subPageRouteEpisode--;
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
                    Serial.print(WayangDisplayLCD_in_main.get_selection_point());
                    WayangDisplayLCD_in_main.increment_selection_point();
                    // WayangDisplayLCD_in_main.refreshLCD();
                    // WayangDisplayLCD_in_main.MenuDisplay();
                }
                else
                {
                    if (subPageRouteCalibrate < StateManagement::SUB_CALIBRATE_PAGE_ROUTE::CALIBRATE_2)
                    {
                        subPageRouteCalibrate++;
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
                    if (subPageRouteCalibrate > StateManagement::SUB_CALIBRATE_PAGE_ROUTE::CALIBRATE_1)
                    {
                        subPageRouteCalibrate--;
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
                if (WayangDisplayLCD_in_main.get_selection_point() < 8)
                {
                    Serial.print(WayangDisplayLCD_in_main.get_selection_point());
                    WayangDisplayLCD_in_main.increment_selection_point();
                    // WayangDisplayLCD_in_main.refreshLCD();
                    // WayangDisplayLCD_in_main.MenuDisplay();
                }
                else
                {
                    if (subPageRouteSensorStatus < StateManagement::SENSOR_STATUS_PAGE_ROUTE::SENSOR_78910)
                    {
                        subPageRouteSensorStatus++;
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
                    if (subPageRouteSensorStatus > StateManagement::SENSOR_STATUS_PAGE_ROUTE::SENSOR_123)
                    {
                        subPageRouteSensorStatus--;
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
    moveWhatServo(1, 180, 2000);
    moveWhatServo(2, 90, 2000);
    moveWhatServo(3, 0, 2000);
    moveWhatServo(4, 90, 2000);
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
    switch (servoNum)
    {
    case 1:
        return this->currentDeg[0];
        break;

    case 2:
        return this->currentDeg[1];
        break;

    case 3:
        return this->currentDeg[2];
        break;

    case 4:
        return this->currentDeg[3];
        break;
    }
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
                    delayMicroseconds(getWavePeriod() - degreeToDelay(curdeg - mismatchremainder));
                }
            }

            for (int i = 0; i < largemismatch; i++)
            {
                for (int j = 0; j < waveAmount / largemismatch; j++)
                {
                    digitalWrite(selectedPin, HIGH);
                    delayMicroseconds(degreeToDelay(curdeg - i * divVar));
                    digitalWrite(selectedPin, LOW);
                    delayMicroseconds(getWavePeriod() - degreeToDelay(curdeg - i * divVar));
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
                    delayMicroseconds(getWavePeriod() - degreeToDelay(curdeg + mismatchremainder));
                }
            }

            for (int i = 0; i < largemismatch; i++)
            {
                for (int j = 0; j < waveAmount / largemismatch; j++)
                {
                    digitalWrite(selectedPin, HIGH);
                    delayMicroseconds(degreeToDelay(curdeg + i * divVar));
                    digitalWrite(selectedPin, LOW);
                    delayMicroseconds(getWavePeriod() - degreeToDelay(curdeg + i * divVar));
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