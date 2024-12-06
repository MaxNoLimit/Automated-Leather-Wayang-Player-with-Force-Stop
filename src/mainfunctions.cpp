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
#include "characters/anggada.hpp"
#include "characters/anila.hpp"

RamaWijaya wayangRamaWijaya;
Sita wayangSita;
Rahwana wayangRahwana;
Hanoman wayangHanoman;
Laksmana wayangLaksmana;
Sugriwa wayangSugriwa;
Subali wayangSubali;
Wibhisana wayangWibhisana;
Anggada wayangAnggada;
Anila wayangAnila;

int lcd_2040_address;
WayangDisplay::WayangDisplayLCD WayangDisplayLCD_in_main(0x27);
unsigned long last_run = 0;
unsigned int loop_state = 0;
bool isEpisodeTaskCreated = false;
bool isPlaying = true;
int currentEpisode = 0;

unsigned int pageRoute = 0;
unsigned int subPageRoute = 0;
const unsigned int displayLoopDelay PROGMEM = 500;

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

    setAllENtoHIGH();

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
    Wire.setClock(200000);
    Wire.setTimeout(500);
    Wire.setWireTimeout(5000, true);
    SoundSystem::justInitTheSoundSystem();

    for (int i = 0; i < 10; i++)
    {
        beginSensorNum(i + 1);
    }
    Serial.println(F("\nAll GPIOs are set"));
    Serial.print(F("Current available stack: "));
    Serial.println(uxTaskGetStackHighWaterMark(NULL));
    setAllMOSFETtoLOW();
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

    case StateManagement::PAGE_ROUTE::VSLOT_DATA_PAGE:
        WayangDisplayLCD_in_main.VSlotDataFarmDisplay();
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

    case StateManagement::PAGE_ROUTE::RAHWANA_HAND_PAGE:
        WayangDisplayLCD_in_main.RahwanaHandCalibration();
        break;

    case StateManagement::PAGE_ROUTE::RAMA_WIJAYA_HAND_PAGE:
        WayangDisplayLCD_in_main.RamaWijayaHandCalibration();
        break;

    case StateManagement::PAGE_ROUTE::HANOMAN_HAND_PAGE:
        WayangDisplayLCD_in_main.HanomanHandCalibration();
        break;

    case StateManagement::PAGE_ROUTE::LAKSMANA_HAND_PAGE:
        WayangDisplayLCD_in_main.LaksmanaHandCalibration();
        break;

    case StateManagement::PAGE_ROUTE::SUGRIWA_HAND_PAGE:
        WayangDisplayLCD_in_main.SugriwaHandCalibration();
        break;

    case StateManagement::PAGE_ROUTE::SUBALI_HAND_PAGE:
        WayangDisplayLCD_in_main.SubaliHandCalibration();
        break;

    case StateManagement::PAGE_ROUTE::WIBHISANA_HAND_PAGE:
        WayangDisplayLCD_in_main.WibhisanaHandCalibration();
        break;

    case StateManagement::PAGE_ROUTE::ANGGADA_HAND_PAGE:
        WayangDisplayLCD_in_main.AnggadaHandCalibration();
        break;

    case StateManagement::PAGE_ROUTE::ANILA_HAND_PAGE:
        WayangDisplayLCD_in_main.AnilaHandCalibration();
        break;

    case StateManagement::PAGE_ROUTE::WHILE_PLAYING_PAGE:
        WayangDisplayLCD_in_main.whilePlayingDisplay();
        break;
    }
    delay(displayLoopDelay);
}

/*
Function untuk melakukan action dari current state
*/
void WayangDisplay::generalLoop()
{
    switch (loop_state)
    {
    case StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD:
        setAllENtoHIGH();
        lcd2004loop();
        delay(0);
        break;

    case StateManagement::FSA_STATE::CALIBRATING_ALL_NEMA:
        // setAllMOSFETtoHIGH();
        CalibratingFunction::vSlotLinear();
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::EXIT_VSLOT_FARM:
        // setAllMOSFETtoHIGH();
        WayangDisplayLCD_in_main.pleaseWaitDisplay();
        wayangRahwana.defaultStandPosition();
        pageRoute = StateManagement::PAGE_ROUTE::CALIBRATE_PAGE;
        WayangDisplayLCD_in_main.set_selection_point(1);
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::VSLOT_100_MM:
        // setAllMOSFETtoHIGH();
        WayangDisplayLCD_in_main.pleaseWaitDisplay();
        wayangRahwana.defaultStandPosition();
        wayangRahwana.walk_to_a_certain_distance_before_calibrating_value(100); // move 100 mm
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::VSLOT_200_MM:
        // setAllMOSFETtoHIGH();
        WayangDisplayLCD_in_main.pleaseWaitDisplay();
        wayangRahwana.defaultStandPosition();
        wayangRahwana.walk_to_a_certain_distance_before_calibrating_value(200); // move 200 mm
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::VSLOT_300_MM:
        // setAllMOSFETtoHIGH();
        WayangDisplayLCD_in_main.pleaseWaitDisplay();
        wayangRahwana.defaultStandPosition();
        wayangRahwana.walk_to_a_certain_distance_before_calibrating_value(300); // move 300 mm
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::VSLOT_400_MM:
        // setAllMOSFETtoHIGH();
        WayangDisplayLCD_in_main.pleaseWaitDisplay();
        wayangRahwana.defaultStandPosition();
        wayangRahwana.walk_to_a_certain_distance_before_calibrating_value(400); // move 400 mm
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::MP3_REINIT:
        CalibratingFunction::soundSystem();
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::WAYANG_HAND_CALIBRATION:
        pageRoute = StateManagement::PAGE_ROUTE::WAYANG_HAND_CALIBRATION_PAGE;
        subPageRoute = StateManagement::WAYANG_HAND_CALIBRATION_SUB_PAGE_ROUTE::WAYANG_HAND_CALIBRATION_1;
        WayangDisplayLCD_in_main.set_selection_point(1);
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::SENSOR_CHECK:
        // setAllMOSFETtoHIGH();
        WayangDisplayLCD_in_main.pleaseWaitDisplay();
        WayangDisplayLCD_in_main.setSensorValueData();
        pageRoute = StateManagement::PAGE_ROUTE::SENSOR_STATUS_PAGE;
        subPageRoute = StateManagement::SENSOR_STATUS_SUB_PAGE_ROUTE::SENSOR_123;
        WayangDisplayLCD_in_main.set_selection_point(1);
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::PAUSE_CONTINUE_PLAYING:
        if (isPlaying)
        {
            Serial.println(F("Pause"));
            SoundSystem::pause();
            isPlaying = false;
            Serial.print(F("Current episode stack left: "));
            Serial.println(uxTaskGetStackHighWaterMark(episodeTaskHandler[currentEpisode - 1]));
            vTaskSuspend(episodeTaskHandler[currentEpisode - 1]);
        }
        else
        {
            Serial.println(F("Continue"));
            SoundSystem::continuePlaying();
            isPlaying = true;
            Serial.print(F("Current episode stack left: "));
            Serial.println(uxTaskGetStackHighWaterMark(episodeTaskHandler[currentEpisode - 1]));
            vTaskResume(episodeTaskHandler[currentEpisode - 1]);
        }
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::STOP_PLAYING:
        SoundSystem::pause();
        Serial.println(F("Stop"));
        Serial.print(F("Current episode stack: "));
        Serial.println(uxTaskGetStackHighWaterMark(episodeTaskHandler[currentEpisode - 1]));
        // vTaskSuspend(episodeTaskHandler[currentEpisode - 1]);
        vTaskDelete(episodeTaskHandler[currentEpisode - 1]);
        isEpisodeTaskCreated = false;
        pageRoute = StateManagement::PAGE_ROUTE::EPISODE_PAGE;
        WayangDisplayLCD_in_main.set_selection_point(1);
        // vTaskDelay(1000 / portTICK_PERIOD_MS);
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::PLAY_EPISODE_1:
        pageRoute = StateManagement::PAGE_ROUTE::WHILE_PLAYING_PAGE;
        WayangDisplayLCD_in_main.playingWhatEpisodeDisplay(1);
        WayangDisplayLCD_in_main.set_selection_point(1);
        WayangDisplayLCD_in_main.disableLCD();
        // Episodes::Episode_1();
        currentEpisode = 1;
        xTaskCreate(
            Episodes::Episode_1_task,
            "Episode_1_task",
            1024,
            NULL,
            1,
            &episodeTaskHandler[0]);
        // vTaskSuspend(mainLoopTaskHandler);
        // attachInterrupt(digitalPinToInterrupt(BUTTON_ROTARY), WayangDisplayController::pressRotaryEncoder, RISING);
        // Serial.println(F("Back to main loop"));
        // vTaskDelay(100 / portTICK_PERIOD_MS);
        WayangDisplayLCD_in_main.enableLCD();
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::PLAY_EPISODE_2:
        pageRoute = StateManagement::PAGE_ROUTE::WHILE_PLAYING_PAGE;
        WayangDisplayLCD_in_main.playingWhatEpisodeDisplay(2);
        WayangDisplayLCD_in_main.set_selection_point(1);
        WayangDisplayLCD_in_main.disableLCD();
        // Episodes::Episode_2();
        currentEpisode = 2;
        Serial.print(F("Main Loop current stack left: "));
        Serial.println(uxTaskGetStackHighWaterMark(NULL));
        xTaskCreate(
            Episodes::Episode_2_task,
            "Episode_2_task",
            1024,
            NULL,
            1,
            &episodeTaskHandler[1]);
        // vTaskSuspend(mainLoopTaskHandler);
        // attachInterrupt(digitalPinToInterrupt(BUTTON_ROTARY), WayangDisplayController::pressRotaryEncoder, RISING);
        // Serial.println(F("Back to main loop"));
        // vTaskDelay(100 / portTICK_PERIOD_MS);
        WayangDisplayLCD_in_main.enableLCD();
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::PLAY_EPISODE_3:
        pageRoute = StateManagement::PAGE_ROUTE::WHILE_PLAYING_PAGE;
        WayangDisplayLCD_in_main.playingWhatEpisodeDisplay(3);
        WayangDisplayLCD_in_main.set_selection_point(1);
        WayangDisplayLCD_in_main.disableLCD();
        // Episodes::Episode_3();
        currentEpisode = 3;
        xTaskCreate(
            Episodes::Episode_3_task,
            "Episode_3_task",
            512,
            NULL,
            1,
            &episodeTaskHandler[2]);
        // vTaskSuspend(mainLoopTaskHandler);
        // attachInterrupt(digitalPinToInterrupt(BUTTON_ROTARY), WayangDisplayController::pressRotaryEncoder, RISING);
        // Serial.println(F("Back to main loop"));
        // vTaskDelay(100 / portTICK_PERIOD_MS);
        WayangDisplayLCD_in_main.enableLCD();
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::PLAY_EPISODE_4:
        pageRoute = StateManagement::PAGE_ROUTE::WHILE_PLAYING_PAGE;
        WayangDisplayLCD_in_main.playingWhatEpisodeDisplay(4);
        WayangDisplayLCD_in_main.set_selection_point(1);
        WayangDisplayLCD_in_main.disableLCD();
        // Episodes::Episode_4();
        currentEpisode = 4;
        xTaskCreate(
            Episodes::Episode_4_task,
            "Episode_4_task",
            512,
            NULL,
            1,
            &episodeTaskHandler[3]);
        // vTaskSuspend(mainLoopTaskHandler);
        // attachInterrupt(digitalPinToInterrupt(BUTTON_ROTARY), WayangDisplayController::pressRotaryEncoder, RISING);
        // Serial.println(F("Back to main loop"));
        // vTaskDelay(100 / portTICK_PERIOD_MS);
        WayangDisplayLCD_in_main.enableLCD();
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::PLAY_EPISODE_5:
        pageRoute = StateManagement::PAGE_ROUTE::WHILE_PLAYING_PAGE;
        WayangDisplayLCD_in_main.playingWhatEpisodeDisplay(5);
        WayangDisplayLCD_in_main.set_selection_point(1);
        WayangDisplayLCD_in_main.disableLCD();
        // Episodes::Episode_5();
        currentEpisode = 5;
        xTaskCreate(
            Episodes::Episode_5_task,
            "Episode_5_task",
            512,
            NULL,
            1,
            &episodeTaskHandler[4]);
        // vTaskSuspend(mainLoopTaskHandler);
        // attachInterrupt(digitalPinToInterrupt(BUTTON_ROTARY), WayangDisplayController::pressRotaryEncoder, RISING);
        // Serial.println(F("Back to main loop"));
        // vTaskDelay(100 / portTICK_PERIOD_MS);
        WayangDisplayLCD_in_main.enableLCD();
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

    case StateManagement::FSA_STATE::SIMPLE_WAYANG_HAND_CALIBRATION:
        WayangDisplayLCD_in_main.pleaseWaitDisplay();
        // setAllMOSFETtoHIGH();
        CalibratingFunction::wayangHand();
        SoundSystem::playDialogFromACertainFolder(SoundSystem::INDICATOR_SOUND, SoundSystem::INDICATOR_SOUND_NUMBER::INDICATOR_WAYANG_HAND_CALIBRATION);
        delay(3500);
        loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
        delay(1);
        break;

        if (pageRoute == StateManagement::PAGE_ROUTE::WAYANG_HAND_CALIBRATION_PAGE)
        {
        // SITA GENERAL LOOP
        case StateManagement::FSA_STATE::SITA_HAND:
            WayangDisplayLCD_in_main.pleaseWaitDisplay();
            wayangSita.walk_to_a_certain_distance_before_calibrating_value(250);
            pageRoute = StateManagement::PAGE_ROUTE::SITA_HAND_PAGE;
            subPageRoute = StateManagement::SITA_SUB_PAGE_ROUTE::SITA_HAND_CALIBRATION_1;
            WayangDisplayLCD_in_main.set_selection_point(1);
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        // RAHWANA GENERAL LOOP
        case StateManagement::FSA_STATE::RAHWANA_HAND:
            WayangDisplayLCD_in_main.pleaseWaitDisplay();
            wayangRahwana.walk_to_a_certain_distance_before_calibrating_value(250);
            pageRoute = StateManagement::PAGE_ROUTE::RAHWANA_HAND_PAGE;
            subPageRoute = StateManagement::RAHWANA_SUB_PAGE_ROUTE::RAHWANA_HAND_CALIBRATION_1;
            WayangDisplayLCD_in_main.set_selection_point(1);
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        // RAMA WIJAYA GENERAL LOOP
        case StateManagement::FSA_STATE::RAMA_WIJAYA_HAND:
            WayangDisplayLCD_in_main.pleaseWaitDisplay();
            wayangRamaWijaya.walk_to_a_certain_distance_before_calibrating_value(250);
            pageRoute = StateManagement::PAGE_ROUTE::RAMA_WIJAYA_HAND_PAGE;
            subPageRoute = StateManagement::RAMA_WIJAYA_SUB_PAGE_ROUTE::RAMA_WIJAYA_HAND_CALIBRATION_1;
            WayangDisplayLCD_in_main.set_selection_point(1);
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        // HANOMAN GENERAL LOOP
        case StateManagement::FSA_STATE::HANOMAN_HAND:
            WayangDisplayLCD_in_main.pleaseWaitDisplay();
            wayangHanoman.walk_to_a_certain_distance_before_calibrating_value(250);
            pageRoute = StateManagement::PAGE_ROUTE::HANOMAN_HAND_PAGE;
            subPageRoute = StateManagement::HANOMAN_SUB_PAGE_ROUTE::HANOMAN_HAND_CALIBRATION_1;
            WayangDisplayLCD_in_main.set_selection_point(1);
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        // LAKSMANA GENERAL LOOP
        case StateManagement::FSA_STATE::LAKSMANA_HAND:
            WayangDisplayLCD_in_main.pleaseWaitDisplay();
            wayangLaksmana.walk_to_a_certain_distance_before_calibrating_value(250);
            pageRoute = StateManagement::PAGE_ROUTE::LAKSMANA_HAND_PAGE;
            subPageRoute = StateManagement::LAKSMANA_SUB_PAGE_ROUTE::LAKSMANA_HAND_CALIBRATION_1;
            WayangDisplayLCD_in_main.set_selection_point(1);
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        // SUGRIWA GENERAL LOOP
        case StateManagement::FSA_STATE::SUGRIWA_HAND:
            WayangDisplayLCD_in_main.pleaseWaitDisplay();
            wayangSugriwa.walk_to_a_certain_distance_before_calibrating_value(250);
            pageRoute = StateManagement::PAGE_ROUTE::SUGRIWA_HAND_PAGE;
            subPageRoute = StateManagement::SUGRIWA_SUB_PAGE_ROUTE::SUGRIWA_HAND_CALIBRATION_1;
            WayangDisplayLCD_in_main.set_selection_point(1);
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        // SUBALI GENERAL LOOP
        case StateManagement::FSA_STATE::SUBALI_HAND:
            WayangDisplayLCD_in_main.pleaseWaitDisplay();
            wayangSubali.walk_to_a_certain_distance_before_calibrating_value(250);
            pageRoute = StateManagement::PAGE_ROUTE::SUBALI_HAND_PAGE;
            subPageRoute = StateManagement::SUBALI_SUB_PAGE_ROUTE::SUBALI_HAND_CALIBRATION_1;
            WayangDisplayLCD_in_main.set_selection_point(1);
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        // WIBHISANA GENERAL LOOP
        case StateManagement::FSA_STATE::WIBHISANA_HAND:
            WayangDisplayLCD_in_main.pleaseWaitDisplay();
            wayangWibhisana.walk_to_a_certain_distance_before_calibrating_value(250);
            pageRoute = StateManagement::PAGE_ROUTE::WIBHISANA_HAND_PAGE;
            subPageRoute = StateManagement::WIBHISANA_SUB_PAGE_ROUTE::WIBHISANA_HAND_CALIBRATION_1;
            WayangDisplayLCD_in_main.set_selection_point(1);
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        // ANGGADA GENERAL LOOP
        case StateManagement::FSA_STATE::ANGGADA_HAND:
            WayangDisplayLCD_in_main.pleaseWaitDisplay();
            wayangAnggada.walk_to_a_certain_distance_before_calibrating_value(250);
            pageRoute = StateManagement::PAGE_ROUTE::ANGGADA_HAND_PAGE;
            subPageRoute = StateManagement::ANGGADA_SUB_PAGE_ROUTE::ANGGADA_HAND_CALIBRATION_1;
            WayangDisplayLCD_in_main.set_selection_point(1);
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        // ANILA GENERAL LOOP
        case StateManagement::FSA_STATE::ANILA_HAND:
            WayangDisplayLCD_in_main.pleaseWaitDisplay();
            wayangAnila.walk_to_a_certain_distance_before_calibrating_value(250);
            pageRoute = StateManagement::PAGE_ROUTE::ANILA_HAND_PAGE;
            subPageRoute = StateManagement::ANILA_SUB_PAGE_ROUTE::ANILA_HAND_CALIBRATION_1;
            WayangDisplayLCD_in_main.set_selection_point(1);
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;
        }
        else if (pageRoute == StateManagement::PAGE_ROUTE::SITA_HAND_PAGE)
        {
        case StateManagement::FSA_STATE::EXIT_SITA_HAND:
            WayangDisplayLCD_in_main.pleaseWaitDisplay();
            setAllMOSFETtoLOW();
            wayangSita.defaultHandPosition();
            wayangSita.defaultStandPosition();
            // setAllMOSFETtoHIGH();
            pageRoute = StateManagement::PAGE_ROUTE::WAYANG_HAND_CALIBRATION_PAGE;
            subPageRoute = StateManagement::WAYANG_HAND_CALIBRATION_SUB_PAGE_ROUTE::WAYANG_HAND_CALIBRATION_1;
            WayangDisplayLCD_in_main.set_selection_point(2);
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::SITA_POINT_TO_FRONT:
            setAllMOSFETtoLOW();
            wayangSita.pointToFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::SITA_LOW_POINT_TO_FRONT:
            setAllMOSFETtoLOW();
            wayangSita.lower_pointToFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::SITA_MIDDLE_FRONT:
            setAllMOSFETtoLOW();
            wayangSita.middleFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::SITA_DOWN_FRONT:
            setAllMOSFETtoLOW();
            wayangSita.downFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::SITA_POINT_TO_SELF:
            setAllMOSFETtoLOW();
            wayangSita.pointToSelf();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::SITA_DOWN_BACK:
            setAllMOSFETtoLOW();
            wayangSita.downBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::SITA_ON_HIP_BACK:
            setAllMOSFETtoLOW();
            wayangSita.onHipBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::SITA_POINT_TO_BACK:
            setAllMOSFETtoLOW();
            wayangSita.pointToBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::SITA_LOW_POINT_TO_BACK:
            setAllMOSFETtoLOW();
            wayangSita.lowPointToBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::SITA_MIDDLE_BACK:
            setAllMOSFETtoLOW();
            wayangSita.middleBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;
        }
        else if (pageRoute == StateManagement::PAGE_ROUTE::RAHWANA_HAND_PAGE)
        {
        case StateManagement::FSA_STATE::EXIT_RAHWANA_HAND:
            WayangDisplayLCD_in_main.pleaseWaitDisplay();
            setAllMOSFETtoLOW();
            wayangRahwana.defaultHandPosition();
            wayangRahwana.defaultStandPosition();
            // setAllMOSFETtoHIGH();
            pageRoute = StateManagement::PAGE_ROUTE::WAYANG_HAND_CALIBRATION_PAGE;
            subPageRoute = StateManagement::WAYANG_HAND_CALIBRATION_SUB_PAGE_ROUTE::WAYANG_HAND_CALIBRATION_1;
            WayangDisplayLCD_in_main.set_selection_point(3);
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::RAHWANA_POINT_TO_FRONT:
            setAllMOSFETtoLOW();
            wayangRahwana.pointToFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::RAHWANA_LOW_POINT_TO_FRONT:
            setAllMOSFETtoLOW();
            wayangRahwana.lower_pointToFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::RAHWANA_MIDDLE_FRONT:
            setAllMOSFETtoLOW();
            wayangRahwana.middleFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::RAHWANA_DOWN_FRONT:
            setAllMOSFETtoLOW();
            wayangRahwana.downFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::RAHWANA_POINT_TO_SELF:
            setAllMOSFETtoLOW();
            wayangRahwana.pointToSelf();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;
        }
        else if (pageRoute == StateManagement::PAGE_ROUTE::RAMA_WIJAYA_HAND_PAGE)
        {
        case StateManagement::FSA_STATE::EXIT_RAMA_WIJAYA_HAND:
            WayangDisplayLCD_in_main.pleaseWaitDisplay();
            setAllMOSFETtoLOW();
            wayangRamaWijaya.defaultHandPosition();
            wayangRamaWijaya.defaultStandPosition();
            // setAllMOSFETtoHIGH();
            pageRoute = StateManagement::PAGE_ROUTE::WAYANG_HAND_CALIBRATION_PAGE;
            subPageRoute = StateManagement::WAYANG_HAND_CALIBRATION_SUB_PAGE_ROUTE::WAYANG_HAND_CALIBRATION_2;
            WayangDisplayLCD_in_main.set_selection_point(3);
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::RAMA_WIJAYA_POINT_TO_FRONT:
            setAllMOSFETtoLOW();
            wayangRamaWijaya.pointToFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::RAMA_WIJAYA_LOW_POINT_TO_FRONT:
            setAllMOSFETtoLOW();
            wayangRamaWijaya.lower_pointToFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::RAMA_WIJAYA_MIDDLE_FRONT:
            setAllMOSFETtoLOW();
            wayangRamaWijaya.middleFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::RAMA_WIJAYA_DOWN_FRONT:
            setAllMOSFETtoLOW();
            wayangRamaWijaya.downFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::RAMA_WIJAYA_POINT_TO_SELF:
            setAllMOSFETtoLOW();
            wayangRamaWijaya.pointToSelf();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::RAMA_WIJAYA_DOWN_BACK:
            setAllMOSFETtoLOW();
            wayangRamaWijaya.downBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::RAMA_WIJAYA_ON_HIP_BACK:
            setAllMOSFETtoLOW();
            wayangRamaWijaya.onHipBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::RAMA_WIJAYA_POINT_TO_BACK:
            setAllMOSFETtoLOW();
            wayangRamaWijaya.pointToBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::RAMA_WIJAYA_LOW_POINT_TO_BACK:
            setAllMOSFETtoLOW();
            wayangRamaWijaya.lowPointToBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::RAMA_WIJAYA_MIDDLE_BACK:
            setAllMOSFETtoLOW();
            wayangRamaWijaya.middleBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;
        }
        else if (pageRoute == StateManagement::PAGE_ROUTE::HANOMAN_HAND_PAGE)
        {
        case StateManagement::FSA_STATE::EXIT_HANOMAN_HAND:
            WayangDisplayLCD_in_main.pleaseWaitDisplay();
            setAllMOSFETtoLOW();
            wayangHanoman.defaultHandPosition();
            wayangHanoman.defaultStandPosition();
            // setAllMOSFETtoHIGH();
            pageRoute = StateManagement::PAGE_ROUTE::WAYANG_HAND_CALIBRATION_PAGE;
            subPageRoute = StateManagement::WAYANG_HAND_CALIBRATION_SUB_PAGE_ROUTE::WAYANG_HAND_CALIBRATION_3;
            WayangDisplayLCD_in_main.set_selection_point(3);
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::HANOMAN_POINT_TO_FRONT:
            setAllMOSFETtoLOW();
            wayangHanoman.pointToFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::HANOMAN_LOW_POINT_TO_FRONT:
            setAllMOSFETtoLOW();
            wayangHanoman.lower_pointToFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::HANOMAN_MIDDLE_FRONT:
            setAllMOSFETtoLOW();
            wayangHanoman.middleFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::HANOMAN_DOWN_FRONT:
            setAllMOSFETtoLOW();
            wayangHanoman.downFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::HANOMAN_POINT_TO_SELF:
            setAllMOSFETtoLOW();
            wayangHanoman.pointToSelf();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::HANOMAN_DOWN_BACK:
            setAllMOSFETtoLOW();
            wayangHanoman.downBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::HANOMAN_ON_HIP_BACK:
            setAllMOSFETtoLOW();
            wayangHanoman.onHipBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::HANOMAN_POINT_TO_BACK:
            setAllMOSFETtoLOW();
            wayangHanoman.pointToBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::HANOMAN_LOW_POINT_TO_BACK:
            setAllMOSFETtoLOW();
            wayangHanoman.lowPointToBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::HANOMAN_MIDDLE_BACK:
            setAllMOSFETtoLOW();
            wayangHanoman.middleBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;
        }
        else if (pageRoute == StateManagement::PAGE_ROUTE::LAKSMANA_HAND_PAGE)
        {
        case StateManagement::FSA_STATE::EXIT_LAKSMANA_HAND:
            WayangDisplayLCD_in_main.pleaseWaitDisplay();
            setAllMOSFETtoLOW();
            wayangLaksmana.defaultHandPosition();
            wayangLaksmana.defaultStandPosition();
            // setAllMOSFETtoHIGH();
            pageRoute = StateManagement::PAGE_ROUTE::WAYANG_HAND_CALIBRATION_PAGE;
            subPageRoute = StateManagement::WAYANG_HAND_CALIBRATION_SUB_PAGE_ROUTE::WAYANG_HAND_CALIBRATION_4;
            WayangDisplayLCD_in_main.set_selection_point(3);
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::LAKSMANA_POINT_TO_FRONT:
            setAllMOSFETtoLOW();
            wayangLaksmana.pointToFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::LAKSMANA_LOW_POINT_TO_FRONT:
            setAllMOSFETtoLOW();
            wayangLaksmana.lower_pointToFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::LAKSMANA_MIDDLE_FRONT:
            setAllMOSFETtoLOW();
            wayangLaksmana.middleFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::LAKSMANA_DOWN_FRONT:
            setAllMOSFETtoLOW();
            wayangLaksmana.downFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::LAKSMANA_POINT_TO_SELF:
            setAllMOSFETtoLOW();
            wayangLaksmana.pointToSelf();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::LAKSMANA_DOWN_BACK:
            setAllMOSFETtoLOW();
            wayangLaksmana.downBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::LAKSMANA_ON_HIP_BACK:
            setAllMOSFETtoLOW();
            wayangLaksmana.onHipBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::LAKSMANA_POINT_TO_BACK:
            setAllMOSFETtoLOW();
            wayangLaksmana.pointToBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::LAKSMANA_LOW_POINT_TO_BACK:
            setAllMOSFETtoLOW();
            wayangLaksmana.lowPointToBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::LAKSMANA_MIDDLE_BACK:
            setAllMOSFETtoLOW();
            wayangLaksmana.middleBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;
        }
        else if (pageRoute == StateManagement::PAGE_ROUTE::SUGRIWA_HAND_PAGE)
        {
        case StateManagement::FSA_STATE::EXIT_SUGRIWA_HAND:
            WayangDisplayLCD_in_main.pleaseWaitDisplay();
            setAllMOSFETtoLOW();
            wayangSugriwa.defaultHandPosition();
            wayangSugriwa.defaultStandPosition();
            // setAllMOSFETtoHIGH();
            pageRoute = StateManagement::PAGE_ROUTE::WAYANG_HAND_CALIBRATION_PAGE;
            subPageRoute = StateManagement::WAYANG_HAND_CALIBRATION_SUB_PAGE_ROUTE::WAYANG_HAND_CALIBRATION_5;
            WayangDisplayLCD_in_main.set_selection_point(3);
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::SUGRIWA_POINT_TO_FRONT:
            setAllMOSFETtoLOW();
            wayangSugriwa.pointToFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::SUGRIWA_LOW_POINT_TO_FRONT:
            setAllMOSFETtoLOW();
            wayangSugriwa.lower_pointToFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::SUGRIWA_MIDDLE_FRONT:
            setAllMOSFETtoLOW();
            wayangSugriwa.middleFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::SUGRIWA_DOWN_FRONT:
            setAllMOSFETtoLOW();
            wayangSugriwa.downFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::SUGRIWA_POINT_TO_SELF:
            setAllMOSFETtoLOW();
            wayangSugriwa.pointToSelf();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::SUGRIWA_DOWN_BACK:
            setAllMOSFETtoLOW();
            wayangSugriwa.downBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::SUGRIWA_ON_HIP_BACK:
            setAllMOSFETtoLOW();
            wayangSugriwa.onHipBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::SUGRIWA_POINT_TO_BACK:
            setAllMOSFETtoLOW();
            wayangSugriwa.pointToBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::SUGRIWA_LOW_POINT_TO_BACK:
            setAllMOSFETtoLOW();
            wayangSugriwa.lowPointToBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::SUGRIWA_MIDDLE_BACK:
            setAllMOSFETtoLOW();
            wayangSugriwa.middleBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;
        }
        else if (pageRoute == StateManagement::PAGE_ROUTE::SUBALI_HAND_PAGE)
        {
        case StateManagement::FSA_STATE::EXIT_SUBALI_HAND:
            WayangDisplayLCD_in_main.pleaseWaitDisplay();
            setAllMOSFETtoLOW();
            wayangSubali.defaultHandPosition();
            wayangSubali.defaultStandPosition();
            // setAllMOSFETtoHIGH();
            pageRoute = StateManagement::PAGE_ROUTE::WAYANG_HAND_CALIBRATION_PAGE;
            subPageRoute = StateManagement::WAYANG_HAND_CALIBRATION_SUB_PAGE_ROUTE::WAYANG_HAND_CALIBRATION_6;
            WayangDisplayLCD_in_main.set_selection_point(3);
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::SUBALI_POINT_TO_FRONT:
            setAllMOSFETtoLOW();
            wayangSubali.pointToFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::SUBALI_LOW_POINT_TO_FRONT:
            setAllMOSFETtoLOW();
            wayangSubali.lower_pointToFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::SUBALI_MIDDLE_FRONT:
            setAllMOSFETtoLOW();
            wayangSubali.middleFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::SUBALI_DOWN_FRONT:
            setAllMOSFETtoLOW();
            wayangSubali.downFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::SUBALI_POINT_TO_SELF:
            setAllMOSFETtoLOW();
            wayangSubali.pointToSelf();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::SUBALI_DOWN_BACK:
            setAllMOSFETtoLOW();
            wayangSubali.downBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::SUBALI_ON_HIP_BACK:
            setAllMOSFETtoLOW();
            wayangSubali.onHipBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::SUBALI_POINT_TO_BACK:
            setAllMOSFETtoLOW();
            wayangSubali.pointToBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::SUBALI_LOW_POINT_TO_BACK:
            setAllMOSFETtoLOW();
            wayangSubali.lowPointToBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::SUBALI_MIDDLE_BACK:
            setAllMOSFETtoLOW();
            wayangSubali.middleBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;
        }
        else if (pageRoute == StateManagement::PAGE_ROUTE::WIBHISANA_HAND_PAGE)
        {
        case StateManagement::FSA_STATE::EXIT_WIBHISANA_HAND:
            WayangDisplayLCD_in_main.pleaseWaitDisplay();
            setAllMOSFETtoLOW();
            wayangWibhisana.defaultHandPosition();
            wayangWibhisana.defaultStandPosition();
            // setAllMOSFETtoHIGH();
            pageRoute = StateManagement::PAGE_ROUTE::WAYANG_HAND_CALIBRATION_PAGE;
            subPageRoute = StateManagement::WAYANG_HAND_CALIBRATION_SUB_PAGE_ROUTE::WAYANG_HAND_CALIBRATION_7;
            WayangDisplayLCD_in_main.set_selection_point(3);
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::WIBHISANA_POINT_TO_FRONT:
            setAllMOSFETtoLOW();
            wayangWibhisana.pointToFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::WIBHISANA_LOW_POINT_TO_FRONT:
            setAllMOSFETtoLOW();
            wayangWibhisana.lower_pointToFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::WIBHISANA_MIDDLE_FRONT:
            setAllMOSFETtoLOW();
            wayangWibhisana.middleFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::WIBHISANA_DOWN_FRONT:
            setAllMOSFETtoLOW();
            wayangWibhisana.downFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::WIBHISANA_POINT_TO_SELF:
            setAllMOSFETtoLOW();
            wayangWibhisana.pointToSelf();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::WIBHISANA_DOWN_BACK:
            setAllMOSFETtoLOW();
            wayangWibhisana.downBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::WIBHISANA_ON_HIP_BACK:
            setAllMOSFETtoLOW();
            wayangWibhisana.onHipBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::WIBHISANA_POINT_TO_BACK:
            setAllMOSFETtoLOW();
            wayangWibhisana.pointToBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::WIBHISANA_LOW_POINT_TO_BACK:
            setAllMOSFETtoLOW();
            wayangWibhisana.lowPointToBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::WIBHISANA_MIDDLE_BACK:
            setAllMOSFETtoLOW();
            wayangWibhisana.middleBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;
        }
        else if (pageRoute == StateManagement::PAGE_ROUTE::ANGGADA_HAND_PAGE)
        {
        case StateManagement::FSA_STATE::EXIT_ANGGADA_HAND:
            WayangDisplayLCD_in_main.pleaseWaitDisplay();
            setAllMOSFETtoLOW();
            wayangAnggada.defaultHandPosition();
            wayangAnggada.defaultStandPosition();
            // setAllMOSFETtoHIGH();
            pageRoute = StateManagement::PAGE_ROUTE::WAYANG_HAND_CALIBRATION_PAGE;
            subPageRoute = StateManagement::WAYANG_HAND_CALIBRATION_SUB_PAGE_ROUTE::WAYANG_HAND_CALIBRATION_8;
            WayangDisplayLCD_in_main.set_selection_point(3);
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::ANGGADA_POINT_TO_FRONT:
            setAllMOSFETtoLOW();
            wayangAnggada.pointToFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::ANGGADA_LOW_POINT_TO_FRONT:
            setAllMOSFETtoLOW();
            wayangAnggada.lower_pointToFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::ANGGADA_MIDDLE_FRONT:
            setAllMOSFETtoLOW();
            wayangAnggada.middleFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::ANGGADA_DOWN_FRONT:
            setAllMOSFETtoLOW();
            wayangAnggada.downFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::ANGGADA_POINT_TO_SELF:
            setAllMOSFETtoLOW();
            wayangAnggada.pointToSelf();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::ANGGADA_DOWN_BACK:
            setAllMOSFETtoLOW();
            wayangAnggada.downBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::ANGGADA_ON_HIP_BACK:
            setAllMOSFETtoLOW();
            wayangAnggada.onHipBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::ANGGADA_POINT_TO_BACK:
            setAllMOSFETtoLOW();
            wayangAnggada.pointToBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::ANGGADA_LOW_POINT_TO_BACK:
            setAllMOSFETtoLOW();
            wayangAnggada.lowPointToBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::ANGGADA_MIDDLE_BACK:
            setAllMOSFETtoLOW();
            wayangAnggada.middleBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;
        }
        else if (pageRoute == StateManagement::PAGE_ROUTE::ANILA_HAND_PAGE)
        {
        case StateManagement::FSA_STATE::EXIT_ANILA_HAND:
            WayangDisplayLCD_in_main.pleaseWaitDisplay();
            setAllMOSFETtoLOW();
            wayangAnila.defaultHandPosition();
            wayangAnila.defaultStandPosition();
            // setAllMOSFETtoHIGH();
            pageRoute = StateManagement::PAGE_ROUTE::WAYANG_HAND_CALIBRATION_PAGE;
            subPageRoute = StateManagement::WAYANG_HAND_CALIBRATION_SUB_PAGE_ROUTE::WAYANG_HAND_CALIBRATION_9;
            WayangDisplayLCD_in_main.set_selection_point(3);
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::ANILA_POINT_TO_FRONT:
            setAllMOSFETtoLOW();
            wayangAnila.pointToFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::ANILA_LOW_POINT_TO_FRONT:
            setAllMOSFETtoLOW();
            wayangAnila.lower_pointToFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::ANILA_MIDDLE_FRONT:
            setAllMOSFETtoLOW();
            wayangAnila.middleFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::ANILA_DOWN_FRONT:
            setAllMOSFETtoLOW();
            wayangAnila.downFront();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::ANILA_POINT_TO_SELF:
            setAllMOSFETtoLOW();
            wayangAnila.pointToSelf();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::ANILA_DOWN_BACK:
            setAllMOSFETtoLOW();
            wayangAnila.downBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::ANILA_ON_HIP_BACK:
            setAllMOSFETtoLOW();
            wayangAnila.onHipBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::ANILA_POINT_TO_BACK:
            setAllMOSFETtoLOW();
            wayangAnila.pointToBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::ANILA_LOW_POINT_TO_BACK:
            setAllMOSFETtoLOW();
            wayangAnila.lowPointToBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;

        case StateManagement::FSA_STATE::ANILA_MIDDLE_BACK:
            setAllMOSFETtoLOW();
            wayangAnila.middleBack();
            // setAllMOSFETtoHIGH();
            loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
            delay(1);
            break;
        }
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
                // subPageRoute = StateManagement::CALIBRATE_SUB_PAGE_ROUTE::CALIBRATE_1;
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
                isPlaying = true;
                isEpisodeTaskCreated = true;
                loop_state = StateManagement::FSA_STATE::PLAY_EPISODE_1;
                // do nothing
                break;

            case 2:
                // Play Episode 2
                isPlaying = true;
                isEpisodeTaskCreated = true;
                loop_state = StateManagement::FSA_STATE::PLAY_EPISODE_2;
                // do nothing
                break;

            case 3:
                // Play Episode 3
                isPlaying = true;
                isEpisodeTaskCreated = true;
                loop_state = StateManagement::FSA_STATE::PLAY_EPISODE_3;
                // do nothing
                break;

            case 4:
                // Play Episode 4
                isPlaying = true;
                isEpisodeTaskCreated = true;
                loop_state = StateManagement::FSA_STATE::PLAY_EPISODE_4;
                // do nothing
                break;

            case 5:
                // Play Episode 5
                isPlaying = true;
                isEpisodeTaskCreated = true;
                loop_state = StateManagement::FSA_STATE::PLAY_EPISODE_5;
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
                // loop_state = StateManagement::FSA_STATE::CALIBRATING_ALL_NEMA;
                pageRoute = StateManagement::PAGE_ROUTE::VSLOT_DATA_PAGE;
                WayangDisplayLCD_in_main.set_selection_point(1);
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

        case StateManagement::PAGE_ROUTE::VSLOT_DATA_PAGE:
            switch (WayangDisplayLCD_in_main.get_selection_point() + subPageRoute)
            {
            case 0:
                loop_state = StateManagement::FSA_STATE::EXIT_VSLOT_FARM;
                break;

            case 1:
                loop_state = StateManagement::FSA_STATE::VSLOT_100_MM;
                break;

            case 2:
                loop_state = StateManagement::FSA_STATE::VSLOT_200_MM;
                break;

            case 3:
                loop_state = StateManagement::FSA_STATE::VSLOT_300_MM;
                break;

            case 4:
                loop_state = StateManagement::FSA_STATE::VSLOT_400_MM;
                break;

            default:
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
            switch (WayangDisplayLCD_in_main.get_selection_point() + subPageRoute)
            {
            case 0:
                pageRoute = StateManagement::PAGE_ROUTE::CALIBRATE_PAGE;
                subPageRoute = StateManagement::CALIBRATE_SUB_PAGE_ROUTE::CALIBRATE_2;
                WayangDisplayLCD_in_main.set_selection_point(3);
                break;

            default:
                break;
            }
            break;

        case StateManagement::PAGE_ROUTE::WAYANG_HAND_CALIBRATION_PAGE:
            switch (WayangDisplayLCD_in_main.get_selection_point() + subPageRoute)
            {
            case 0:
                pageRoute = StateManagement::PAGE_ROUTE::CALIBRATE_PAGE;
                subPageRoute = StateManagement::CALIBRATE_SUB_PAGE_ROUTE::CALIBRATE_1;
                WayangDisplayLCD_in_main.set_selection_point(3);
                break;

            case 1:
                loop_state = StateManagement::FSA_STATE::SIMPLE_WAYANG_HAND_CALIBRATION;
                break;

            case 2:
                loop_state = StateManagement::FSA_STATE::SITA_HAND;
                break;

            case 3:
                loop_state = StateManagement::FSA_STATE::RAHWANA_HAND;
                break;

            case 4:
                loop_state = StateManagement::FSA_STATE::RAMA_WIJAYA_HAND;
                break;

            case 5:
                loop_state = StateManagement::FSA_STATE::HANOMAN_HAND;
                break;

            case 6:
                loop_state = StateManagement::FSA_STATE::LAKSMANA_HAND;
                break;

            case 7:
                loop_state = StateManagement::FSA_STATE::SUGRIWA_HAND;
                break;

            case 8:
                loop_state = StateManagement::FSA_STATE::SUBALI_HAND;
                break;

            case 9:
                loop_state = StateManagement::FSA_STATE::WIBHISANA_HAND;
                break;

            case 10:
                loop_state = StateManagement::FSA_STATE::ANGGADA_HAND;
                break;

            case 11:
                loop_state = StateManagement::FSA_STATE::ANILA_HAND;
                break;
            }
            break;

        case StateManagement::PAGE_ROUTE::SITA_HAND_PAGE:
            switch (WayangDisplayLCD_in_main.get_selection_point() + subPageRoute)
            {
            case 0:
                loop_state = StateManagement::FSA_STATE::EXIT_SITA_HAND;
                break;

            case 1:
                loop_state = StateManagement::FSA_STATE::SITA_POINT_TO_FRONT;
                break;

            case 2:
                loop_state = StateManagement::FSA_STATE::SITA_LOW_POINT_TO_FRONT;
                break;

            case 3:
                loop_state = StateManagement::FSA_STATE::SITA_MIDDLE_FRONT;
                break;

            case 4:
                loop_state = StateManagement::FSA_STATE::SITA_DOWN_FRONT;
                break;

            case 5:
                loop_state = StateManagement::FSA_STATE::SITA_POINT_TO_SELF;
                break;

            case 6:
                loop_state = StateManagement::FSA_STATE::SITA_DOWN_BACK;
                break;

            case 7:
                loop_state = StateManagement::FSA_STATE::SITA_ON_HIP_BACK;
                break;

            case 8:
                loop_state = StateManagement::FSA_STATE::SITA_POINT_TO_BACK;
                break;

            case 9:
                loop_state = StateManagement::FSA_STATE::SITA_LOW_POINT_TO_BACK;
                break;

            case 10:
                loop_state = StateManagement::FSA_STATE::SITA_MIDDLE_BACK;
                break;
            }
            break;

        case StateManagement::PAGE_ROUTE::RAHWANA_HAND_PAGE:
            switch (WayangDisplayLCD_in_main.get_selection_point() + subPageRoute)
            {
            case 0:
                loop_state = StateManagement::FSA_STATE::EXIT_RAHWANA_HAND;
                break;

            case 1:
                loop_state = StateManagement::FSA_STATE::RAHWANA_POINT_TO_FRONT;
                break;

            case 2:
                loop_state = StateManagement::FSA_STATE::RAHWANA_LOW_POINT_TO_FRONT;
                break;

            case 3:
                loop_state = StateManagement::FSA_STATE::RAHWANA_MIDDLE_FRONT;
                break;

            case 4:
                loop_state = StateManagement::FSA_STATE::RAHWANA_DOWN_FRONT;
                break;

            case 5:
                loop_state = StateManagement::FSA_STATE::RAHWANA_POINT_TO_SELF;
                break;
            }
            break;

        case StateManagement::PAGE_ROUTE::RAMA_WIJAYA_HAND_PAGE:
            switch (WayangDisplayLCD_in_main.get_selection_point() + subPageRoute)
            {
            case 0:
                loop_state = StateManagement::FSA_STATE::EXIT_RAMA_WIJAYA_HAND;
                break;

            case 1:
                loop_state = StateManagement::FSA_STATE::RAMA_WIJAYA_POINT_TO_FRONT;
                break;

            case 2:
                loop_state = StateManagement::FSA_STATE::RAMA_WIJAYA_LOW_POINT_TO_FRONT;
                break;

            case 3:
                loop_state = StateManagement::FSA_STATE::RAMA_WIJAYA_MIDDLE_FRONT;
                break;

            case 4:
                loop_state = StateManagement::FSA_STATE::RAMA_WIJAYA_DOWN_FRONT;
                break;

            case 5:
                loop_state = StateManagement::FSA_STATE::RAMA_WIJAYA_POINT_TO_SELF;
                break;

            case 6:
                loop_state = StateManagement::FSA_STATE::RAMA_WIJAYA_DOWN_BACK;
                break;

            case 7:
                loop_state = StateManagement::FSA_STATE::RAMA_WIJAYA_ON_HIP_BACK;
                break;

            case 8:
                loop_state = StateManagement::FSA_STATE::RAMA_WIJAYA_POINT_TO_BACK;
                break;

            case 9:
                loop_state = StateManagement::FSA_STATE::RAMA_WIJAYA_LOW_POINT_TO_BACK;
                break;

            case 10:
                loop_state = StateManagement::FSA_STATE::RAMA_WIJAYA_MIDDLE_BACK;
                break;
            }
            break;

        case StateManagement::PAGE_ROUTE::HANOMAN_HAND_PAGE:
            switch (WayangDisplayLCD_in_main.get_selection_point() + subPageRoute)
            {
            case 0:
                loop_state = StateManagement::FSA_STATE::EXIT_HANOMAN_HAND;
                break;

            case 1:
                loop_state = StateManagement::FSA_STATE::HANOMAN_POINT_TO_FRONT;
                break;

            case 2:
                loop_state = StateManagement::FSA_STATE::HANOMAN_LOW_POINT_TO_FRONT;
                break;

            case 3:
                loop_state = StateManagement::FSA_STATE::HANOMAN_MIDDLE_FRONT;
                break;

            case 4:
                loop_state = StateManagement::FSA_STATE::HANOMAN_DOWN_FRONT;
                break;

            case 5:
                loop_state = StateManagement::FSA_STATE::HANOMAN_POINT_TO_SELF;
                break;

            case 6:
                loop_state = StateManagement::FSA_STATE::HANOMAN_DOWN_BACK;
                break;

            case 7:
                loop_state = StateManagement::FSA_STATE::HANOMAN_ON_HIP_BACK;
                break;

            case 8:
                loop_state = StateManagement::FSA_STATE::HANOMAN_POINT_TO_BACK;
                break;

            case 9:
                loop_state = StateManagement::FSA_STATE::HANOMAN_LOW_POINT_TO_BACK;
                break;

            case 10:
                loop_state = StateManagement::FSA_STATE::HANOMAN_MIDDLE_BACK;
                break;
            }
            break;

        case StateManagement::PAGE_ROUTE::LAKSMANA_HAND_PAGE:
            switch (WayangDisplayLCD_in_main.get_selection_point() + subPageRoute)
            {
            case 0:
                loop_state = StateManagement::FSA_STATE::EXIT_LAKSMANA_HAND;
                break;

            case 1:
                loop_state = StateManagement::FSA_STATE::LAKSMANA_POINT_TO_FRONT;
                break;

            case 2:
                loop_state = StateManagement::FSA_STATE::LAKSMANA_LOW_POINT_TO_FRONT;
                break;

            case 3:
                loop_state = StateManagement::FSA_STATE::LAKSMANA_MIDDLE_FRONT;
                break;

            case 4:
                loop_state = StateManagement::FSA_STATE::LAKSMANA_DOWN_FRONT;
                break;

            case 5:
                loop_state = StateManagement::FSA_STATE::LAKSMANA_POINT_TO_SELF;
                break;

            case 6:
                loop_state = StateManagement::FSA_STATE::LAKSMANA_DOWN_BACK;
                break;

            case 7:
                loop_state = StateManagement::FSA_STATE::LAKSMANA_ON_HIP_BACK;
                break;

            case 8:
                loop_state = StateManagement::FSA_STATE::LAKSMANA_POINT_TO_BACK;
                break;

            case 9:
                loop_state = StateManagement::FSA_STATE::LAKSMANA_LOW_POINT_TO_BACK;
                break;

            case 10:
                loop_state = StateManagement::FSA_STATE::LAKSMANA_MIDDLE_BACK;
                break;
            }
            break;

        case StateManagement::PAGE_ROUTE::SUGRIWA_HAND_PAGE:
            switch (WayangDisplayLCD_in_main.get_selection_point() + subPageRoute)
            {
            case 0:
                loop_state = StateManagement::FSA_STATE::EXIT_SUGRIWA_HAND;
                break;

            case 1:
                loop_state = StateManagement::FSA_STATE::SUGRIWA_POINT_TO_FRONT;
                break;

            case 2:
                loop_state = StateManagement::FSA_STATE::SUGRIWA_LOW_POINT_TO_FRONT;
                break;

            case 3:
                loop_state = StateManagement::FSA_STATE::SUGRIWA_MIDDLE_FRONT;
                break;

            case 4:
                loop_state = StateManagement::FSA_STATE::SUGRIWA_DOWN_FRONT;
                break;

            case 5:
                loop_state = StateManagement::FSA_STATE::SUGRIWA_POINT_TO_SELF;
                break;

            case 6:
                loop_state = StateManagement::FSA_STATE::SUGRIWA_DOWN_BACK;
                break;

            case 7:
                loop_state = StateManagement::FSA_STATE::SUGRIWA_ON_HIP_BACK;
                break;

            case 8:
                loop_state = StateManagement::FSA_STATE::SUGRIWA_POINT_TO_BACK;
                break;

            case 9:
                loop_state = StateManagement::FSA_STATE::SUGRIWA_LOW_POINT_TO_BACK;
                break;

            case 10:
                loop_state = StateManagement::FSA_STATE::SUGRIWA_MIDDLE_BACK;
                break;
            }
            break;

        case StateManagement::PAGE_ROUTE::SUBALI_HAND_PAGE:
            switch (WayangDisplayLCD_in_main.get_selection_point() + subPageRoute)
            {
            case 0:
                loop_state = StateManagement::FSA_STATE::EXIT_SUBALI_HAND;
                break;

            case 1:
                loop_state = StateManagement::FSA_STATE::SUBALI_POINT_TO_FRONT;
                break;

            case 2:
                loop_state = StateManagement::FSA_STATE::SUBALI_LOW_POINT_TO_FRONT;
                break;

            case 3:
                loop_state = StateManagement::FSA_STATE::SUBALI_MIDDLE_FRONT;
                break;

            case 4:
                loop_state = StateManagement::FSA_STATE::SUBALI_DOWN_FRONT;
                break;

            case 5:
                loop_state = StateManagement::FSA_STATE::SUBALI_POINT_TO_SELF;
                break;

            case 6:
                loop_state = StateManagement::FSA_STATE::SUBALI_DOWN_BACK;
                break;

            case 7:
                loop_state = StateManagement::FSA_STATE::SUBALI_ON_HIP_BACK;
                break;

            case 8:
                loop_state = StateManagement::FSA_STATE::SUBALI_POINT_TO_BACK;
                break;

            case 9:
                loop_state = StateManagement::FSA_STATE::SUBALI_LOW_POINT_TO_BACK;
                break;

            case 10:
                loop_state = StateManagement::FSA_STATE::SUBALI_MIDDLE_BACK;
                break;
            }
            break;

        case StateManagement::PAGE_ROUTE::WIBHISANA_HAND_PAGE:
            switch (WayangDisplayLCD_in_main.get_selection_point() + subPageRoute)
            {
            case 0:
                loop_state = StateManagement::FSA_STATE::EXIT_WIBHISANA_HAND;
                break;

            case 1:
                loop_state = StateManagement::FSA_STATE::WIBHISANA_POINT_TO_FRONT;
                break;

            case 2:
                loop_state = StateManagement::FSA_STATE::WIBHISANA_LOW_POINT_TO_FRONT;
                break;

            case 3:
                loop_state = StateManagement::FSA_STATE::WIBHISANA_MIDDLE_FRONT;
                break;

            case 4:
                loop_state = StateManagement::FSA_STATE::WIBHISANA_DOWN_FRONT;
                break;

            case 5:
                loop_state = StateManagement::FSA_STATE::WIBHISANA_POINT_TO_SELF;
                break;

            case 6:
                loop_state = StateManagement::FSA_STATE::WIBHISANA_DOWN_BACK;
                break;

            case 7:
                loop_state = StateManagement::FSA_STATE::WIBHISANA_ON_HIP_BACK;
                break;

            case 8:
                loop_state = StateManagement::FSA_STATE::WIBHISANA_POINT_TO_BACK;
                break;

            case 9:
                loop_state = StateManagement::FSA_STATE::WIBHISANA_LOW_POINT_TO_BACK;
                break;

            case 10:
                loop_state = StateManagement::FSA_STATE::WIBHISANA_MIDDLE_BACK;
                break;
            }
            break;

        case StateManagement::PAGE_ROUTE::ANGGADA_HAND_PAGE:
            switch (WayangDisplayLCD_in_main.get_selection_point() + subPageRoute)
            {
            case 0:
                loop_state = StateManagement::FSA_STATE::EXIT_ANGGADA_HAND;
                break;

            case 1:
                loop_state = StateManagement::FSA_STATE::ANGGADA_POINT_TO_FRONT;
                break;

            case 2:
                loop_state = StateManagement::FSA_STATE::ANGGADA_LOW_POINT_TO_FRONT;
                break;

            case 3:
                loop_state = StateManagement::FSA_STATE::ANGGADA_MIDDLE_FRONT;
                break;

            case 4:
                loop_state = StateManagement::FSA_STATE::ANGGADA_DOWN_FRONT;
                break;

            case 5:
                loop_state = StateManagement::FSA_STATE::ANGGADA_POINT_TO_SELF;
                break;

            case 6:
                loop_state = StateManagement::FSA_STATE::ANGGADA_DOWN_BACK;
                break;

            case 7:
                loop_state = StateManagement::FSA_STATE::ANGGADA_ON_HIP_BACK;
                break;

            case 8:
                loop_state = StateManagement::FSA_STATE::ANGGADA_POINT_TO_BACK;
                break;

            case 9:
                loop_state = StateManagement::FSA_STATE::ANGGADA_LOW_POINT_TO_BACK;
                break;

            case 10:
                loop_state = StateManagement::FSA_STATE::ANGGADA_MIDDLE_BACK;
                break;
            }
            break;

        case StateManagement::PAGE_ROUTE::ANILA_HAND_PAGE:
            switch (WayangDisplayLCD_in_main.get_selection_point() + subPageRoute)
            {
            case 0:
                loop_state = StateManagement::FSA_STATE::EXIT_ANILA_HAND;
                break;

            case 1:
                loop_state = StateManagement::FSA_STATE::ANILA_POINT_TO_FRONT;
                break;

            case 2:
                loop_state = StateManagement::FSA_STATE::ANILA_LOW_POINT_TO_FRONT;
                break;

            case 3:
                loop_state = StateManagement::FSA_STATE::ANILA_MIDDLE_FRONT;
                break;

            case 4:
                loop_state = StateManagement::FSA_STATE::ANILA_DOWN_FRONT;
                break;

            case 5:
                loop_state = StateManagement::FSA_STATE::ANILA_POINT_TO_SELF;
                break;

            case 6:
                loop_state = StateManagement::FSA_STATE::ANILA_DOWN_BACK;
                break;

            case 7:
                loop_state = StateManagement::FSA_STATE::ANILA_ON_HIP_BACK;
                break;

            case 8:
                loop_state = StateManagement::FSA_STATE::ANILA_POINT_TO_BACK;
                break;

            case 9:
                loop_state = StateManagement::FSA_STATE::ANILA_LOW_POINT_TO_BACK;
                break;

            case 10:
                loop_state = StateManagement::FSA_STATE::ANILA_MIDDLE_BACK;
                break;
            }
            break;

        case StateManagement::PAGE_ROUTE::WHILE_PLAYING_PAGE:
            switch (WayangDisplayLCD_in_main.get_selection_point())
            {
            case 0:
                // do nothing
                break;

            case 1:
                loop_state = StateManagement::FSA_STATE::PAUSE_CONTINUE_PLAYING;
                break;

            case 2:
                loop_state = StateManagement::FSA_STATE::STOP_PLAYING;
                break;

            default:
                break;
            }
            break;
        }
        last_run = millis();
    }
}

/*
Function interrupt untuk spin dari Rotary Encoder
*/
void WayangDisplayController::spinRotaryEncoder()
{
    switch (pageRoute)
    {
    case StateManagement::PAGE_ROUTE::MENU_PAGE:
        if (millis() - last_run > displayLoopDelay / 50)
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
        if (millis() - last_run > displayLoopDelay / 50)
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
                    if (subPageRoute < StateManagement::EPISODE_SUB_PAGE_ROUTE::EPISODE2345)
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
                    if (subPageRoute > StateManagement::EPISODE_SUB_PAGE_ROUTE::EPISODE123)
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
        if (millis() - last_run > displayLoopDelay / 50)
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
                    if (subPageRoute < StateManagement::CALIBRATE_SUB_PAGE_ROUTE::CALIBRATE_2)
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
                    if (subPageRoute > StateManagement::CALIBRATE_SUB_PAGE_ROUTE::CALIBRATE_1)
                    {
                        subPageRoute--;
                        WayangDisplayLCD_in_main.set_selection_point(1);
                    }
                }
            }
        }
        last_run = millis();
        break;

    case StateManagement::PAGE_ROUTE::VSLOT_DATA_PAGE:
        if (millis() - last_run > displayLoopDelay / 50)
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
                    if (subPageRoute < StateManagement::VSLOT_DATA_FARM_SUB_PAGE_ROUTE::VSLOT_DISPLAY_2)
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
                    if (subPageRoute > StateManagement::VSLOT_DATA_FARM_SUB_PAGE_ROUTE::VSLOT_DISPLAY_1)
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
        if (millis() - last_run > displayLoopDelay / 50)
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
        if (millis() - last_run > displayLoopDelay / 50)
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
                    if (subPageRoute < StateManagement::SENSOR_STATUS_SUB_PAGE_ROUTE::SENSOR_78910)
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
                    if (subPageRoute > StateManagement::SENSOR_STATUS_SUB_PAGE_ROUTE::SENSOR_123)
                    {
                        subPageRoute--;
                        WayangDisplayLCD_in_main.set_selection_point(1);
                    }
                }
            }
        }
        last_run = millis();
        break;

    case StateManagement::PAGE_ROUTE::WAYANG_HAND_CALIBRATION_PAGE:
        if (millis() - last_run > displayLoopDelay / 50)
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
                    if (subPageRoute < StateManagement::WAYANG_HAND_CALIBRATION_SUB_PAGE_ROUTE::WAYANG_HAND_CALIBRATION_9)
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
                    if (subPageRoute > StateManagement::WAYANG_HAND_CALIBRATION_SUB_PAGE_ROUTE::WAYANG_HAND_CALIBRATION_1)
                    {
                        subPageRoute--;
                        WayangDisplayLCD_in_main.set_selection_point(1);
                    }
                }
            }
        }
        last_run = millis();
        break;
    case StateManagement::PAGE_ROUTE::SITA_HAND_PAGE:
        if (millis() - last_run > displayLoopDelay / 50)
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
                    if (subPageRoute < StateManagement::SITA_SUB_PAGE_ROUTE::SITA_HAND_CALIBRATION_8)
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
                    if (subPageRoute > StateManagement::SITA_SUB_PAGE_ROUTE::SITA_HAND_CALIBRATION_1)
                    {
                        subPageRoute--;
                        WayangDisplayLCD_in_main.set_selection_point(1);
                    }
                }
            }
        }
        last_run = millis();
        break;

    case StateManagement::PAGE_ROUTE::RAHWANA_HAND_PAGE:
        if (millis() - last_run > displayLoopDelay / 50)
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
                    if (subPageRoute < StateManagement::RAHWANA_SUB_PAGE_ROUTE::RAHWANA_HAND_CALIBRATION_3)
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
                    if (subPageRoute > StateManagement::RAHWANA_SUB_PAGE_ROUTE::RAHWANA_HAND_CALIBRATION_1)
                    {
                        subPageRoute--;
                        WayangDisplayLCD_in_main.set_selection_point(1);
                    }
                }
            }
        }
        last_run = millis();
        break;

    case StateManagement::PAGE_ROUTE::RAMA_WIJAYA_HAND_PAGE:
        if (millis() - last_run > displayLoopDelay / 50)
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
                    if (subPageRoute < StateManagement::RAMA_WIJAYA_SUB_PAGE_ROUTE::RAMA_WIJAYA_HAND_CALIBRATION_8)
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
                    if (subPageRoute > StateManagement::RAMA_WIJAYA_SUB_PAGE_ROUTE::RAMA_WIJAYA_HAND_CALIBRATION_1)
                    {
                        subPageRoute--;
                        WayangDisplayLCD_in_main.set_selection_point(1);
                    }
                }
            }
        }
        last_run = millis();
        break;

    case StateManagement::PAGE_ROUTE::HANOMAN_HAND_PAGE:
        if (millis() - last_run > displayLoopDelay / 50)
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
                    if (subPageRoute < StateManagement::HANOMAN_SUB_PAGE_ROUTE::HANOMAN_HAND_CALIBRATION_8)
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
                    if (subPageRoute > StateManagement::HANOMAN_SUB_PAGE_ROUTE::HANOMAN_HAND_CALIBRATION_1)
                    {
                        subPageRoute--;
                        WayangDisplayLCD_in_main.set_selection_point(1);
                    }
                }
            }
        }
        last_run = millis();
        break;

    case StateManagement::PAGE_ROUTE::LAKSMANA_HAND_PAGE:
        if (millis() - last_run > displayLoopDelay / 50)
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
                    if (subPageRoute < StateManagement::LAKSMANA_SUB_PAGE_ROUTE::LAKSMANA_HAND_CALIBRATION_8)
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
                    if (subPageRoute > StateManagement::LAKSMANA_SUB_PAGE_ROUTE::LAKSMANA_HAND_CALIBRATION_1)
                    {
                        subPageRoute--;
                        WayangDisplayLCD_in_main.set_selection_point(1);
                    }
                }
            }
        }
        last_run = millis();
        break;

    case StateManagement::PAGE_ROUTE::SUGRIWA_HAND_PAGE:
        if (millis() - last_run > displayLoopDelay / 50)
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
                    if (subPageRoute < StateManagement::SUGRIWA_SUB_PAGE_ROUTE::SUGRIWA_HAND_CALIBRATION_8)
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
                    if (subPageRoute > StateManagement::SUGRIWA_SUB_PAGE_ROUTE::SUGRIWA_HAND_CALIBRATION_1)
                    {
                        subPageRoute--;
                        WayangDisplayLCD_in_main.set_selection_point(1);
                    }
                }
            }
        }
        last_run = millis();
        break;

    case StateManagement::PAGE_ROUTE::SUBALI_HAND_PAGE:
        if (millis() - last_run > displayLoopDelay / 50)
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
                    if (subPageRoute < StateManagement::SUBALI_SUB_PAGE_ROUTE::SUBALI_HAND_CALIBRATION_8)
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
                    if (subPageRoute > StateManagement::SUBALI_SUB_PAGE_ROUTE::SUBALI_HAND_CALIBRATION_1)
                    {
                        subPageRoute--;
                        WayangDisplayLCD_in_main.set_selection_point(1);
                    }
                }
            }
        }
        last_run = millis();
        break;

    case StateManagement::PAGE_ROUTE::WIBHISANA_HAND_PAGE:
        if (millis() - last_run > displayLoopDelay / 50)
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
                    if (subPageRoute < StateManagement::WIBHISANA_SUB_PAGE_ROUTE::WIBHISANA_HAND_CALIBRATION_8)
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
                    if (subPageRoute > StateManagement::WIBHISANA_SUB_PAGE_ROUTE::WIBHISANA_HAND_CALIBRATION_1)
                    {
                        subPageRoute--;
                        WayangDisplayLCD_in_main.set_selection_point(1);
                    }
                }
            }
        }
        last_run = millis();
        break;

    case StateManagement::PAGE_ROUTE::ANGGADA_HAND_PAGE:
        if (millis() - last_run > displayLoopDelay / 50)
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
                    if (subPageRoute < StateManagement::ANGGADA_SUB_PAGE_ROUTE::ANGGADA_HAND_CALIBRATION_8)
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
                    if (subPageRoute > StateManagement::ANGGADA_SUB_PAGE_ROUTE::ANGGADA_HAND_CALIBRATION_1)
                    {
                        subPageRoute--;
                        WayangDisplayLCD_in_main.set_selection_point(1);
                    }
                }
            }
        }
        last_run = millis();
        break;

    case StateManagement::PAGE_ROUTE::ANILA_HAND_PAGE:
        if (millis() - last_run > displayLoopDelay / 50)
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
                    if (subPageRoute < StateManagement::ANILA_SUB_PAGE_ROUTE::ANILA_HAND_CALIBRATION_8)
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
                    if (subPageRoute > StateManagement::ANILA_SUB_PAGE_ROUTE::ANILA_HAND_CALIBRATION_1)
                    {
                        subPageRoute--;
                        WayangDisplayLCD_in_main.set_selection_point(1);
                    }
                }
            }
        }
        last_run = millis();
        break;

    case StateManagement::PAGE_ROUTE::WHILE_PLAYING_PAGE:
        if (millis() - last_run > displayLoopDelay / 50)
        {
            if (digitalRead(OUTPUT_B) == HIGH)
            {
                if (WayangDisplayLCD_in_main.get_selection_point() < 2)
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
    }
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

void WayangHandServo::moveWhatServoV2(int servoNum, int degree, int desireDuration)
{
    int selectedPin;
    int startTime, endTime = 0;
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

        if (curdeg > degree)
        {
            if (mismatchremainder != 0)
            {
                for (int i = 0; i < remainder; i++)
                {
                    endTime = micros();
                    while (endTime - 0 > degreeToDelay(curdeg - mismatchremainder))
                    {
                        digitalWrite(selectedPin, HIGH);
                    }
                    endTime = 0;

                    for (int i = 0; i < 2; i++)
                    {
                        endTime = micros();
                        while (endTime - 0 > getWavePeriod() - degreeToDelay((curdeg - mismatchremainder) / 2))
                        {
                            digitalWrite(selectedPin, LOW);
                        }
                        endTime = 0;
                    }
                }
            }

            for (int i = 0; i < largemismatch; i++)
            {
                for (int j = 0; j < waveAmount / largemismatch; j++)
                {
                    endTime = micros();
                    while (endTime - 0 > degreeToDelay(curdeg - i * divVar))
                    {
                        digitalWrite(selectedPin, HIGH);
                    }
                    endTime = 0;

                    for (int i = 0; i < 2; i++)
                    {
                        endTime = micros();
                        while (endTime - 0 > getWavePeriod() - degreeToDelay((curdeg - i * divVar) / 2))
                        {
                            digitalWrite(selectedPin, LOW);
                        }
                        endTime = 0;
                    }
                }
            }

            if (mismatchremainder == 0 && remainder != 0)
            {
                for (int i = 0; i < remainder; i++)
                {
                    endTime = micros();
                    while (endTime - 0 > degreeToDelay(degree))
                    {
                        digitalWrite(selectedPin, HIGH);
                    }
                    endTime = 0;

                    for (int i = 0; i < 2; i++)
                    {
                        endTime = micros();
                        while (endTime - 0 > getWavePeriod() - degreeToDelay(degree / 2))
                        {
                            digitalWrite(selectedPin, LOW);
                        }
                        endTime = 0;
                    }
                }
            }
        }
        else
        {
            if (mismatchremainder != 0)
            {
                for (int i = 0; i < remainder; i++)
                {
                    endTime = micros();
                    while (endTime - 0 > degreeToDelay(curdeg + mismatchremainder))
                    {
                        digitalWrite(selectedPin, HIGH);
                    }
                    endTime = 0;

                    for (int i = 0; i < 2; i++)
                    {
                        endTime = micros();
                        while (endTime - 0 > getWavePeriod() - degreeToDelay((curdeg + mismatchremainder) / 2))
                        {
                            digitalWrite(selectedPin, LOW);
                        }
                        endTime = 0;
                    }
                }
            }

            for (int i = 0; i < largemismatch; i++)
            {
                for (int j = 0; j < waveAmount / largemismatch; j++)
                {
                    endTime = micros();
                    while (endTime - 0 > degreeToDelay(curdeg + i * divVar))
                    {
                        digitalWrite(selectedPin, HIGH);
                    }
                    endTime = 0;

                    for (int i = 0; i < 2; i++)
                    {
                        endTime = micros();
                        while (endTime - 0 > getWavePeriod() - degreeToDelay((curdeg + i * divVar) / 2))
                        {
                            digitalWrite(selectedPin, LOW);
                        }
                        endTime = 0;
                    }
                }
            }
            // int hajime, sutopu = 0;

            if (mismatchremainder == 0 && remainder != 0)
            {
                for (int i = 0; i < remainder; i++)
                {
                    endTime = micros();
                    while (endTime - 0 > degreeToDelay(degree))
                    {
                        digitalWrite(selectedPin, HIGH);
                    }
                    endTime = 0;

                    for (int i = 0; i < 2; i++)
                    {
                        endTime = micros();
                        while (endTime - 0 > getWavePeriod() - degreeToDelay(degree / 2))
                        {
                            digitalWrite(selectedPin, LOW);
                        }
                        endTime = 0;
                    }
                }
            }
        }

        setCurrentDegServo(servoNum, degree);
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

    Serial.println(F("\nSensor 1\n"));
    wayangSita.walk_to_a_certain_distance_before_calibrating_value(155);
    Serial.println(F("\nSensor 2\n"));
    wayangRahwana.walk_to_a_certain_distance_before_calibrating_value(155);
    Serial.println(F("\nSensor 3\n"));
    wayangRamaWijaya.walk_to_a_certain_distance_before_calibrating_value(155);
    Serial.println(F("\nSensor 4\n"));
    wayangHanoman.walk_to_a_certain_distance_before_calibrating_value(155);
    Serial.println(F("\nSensor 5\n"));
    wayangLaksmana.walk_to_a_certain_distance_before_calibrating_value(155);
    Serial.println(F("\nSensor 6\n"));
    wayangSugriwa.walk_to_a_certain_distance_before_calibrating_value(155);
    Serial.println(F("\nSensor 7\n"));
    wayangSubali.walk_to_a_certain_distance_before_calibrating_value(155);
    Serial.println(F("\nSensor 8\n"));
    wayangWibhisana.walk_to_a_certain_distance_before_calibrating_value(155);

    Serial.println(F("\nSensor 1\n"));
    wayangSita.defaultStandPosition();
    Serial.println(F("\nSensor 2\n"));
    wayangRahwana.defaultStandPosition();
    Serial.println(F("\nSensor 3\n"));
    wayangRamaWijaya.defaultStandPosition();
    Serial.println(F("\nSensor 4\n"));
    wayangHanoman.defaultStandPosition();
    Serial.println(F("\nSensor 5\n"));
    wayangLaksmana.defaultStandPosition();
    Serial.println(F("\nSensor 6\n"));
    wayangSugriwa.defaultStandPosition();
    Serial.println(F("\nSensor 7\n"));
    wayangSubali.defaultStandPosition();
    Serial.println(F("\nSensor 8\n"));
    wayangWibhisana.defaultStandPosition();

    SoundSystem::playDialogFromACertainFolder(SoundSystem::INDICATOR_SOUND, SoundSystem::INDICATOR_SOUND_NUMBER::INDICATOR_VSLOT_CALIBRATION);
    delay(3500);

    // setAllMOSFETtoHIGH();
}

void CalibratingFunction::soundSystem()
{
    setAllMOSFETtoLOW();
    WayangDisplayLCD_in_main.disableLCD();
    SoundSystem::initSound();
    // setAllMOSFETtoHIGH();
    WayangDisplayLCD_in_main.enableLCD();
}

void CalibratingFunction::wayangHand()
{
    setAllMOSFETtoLOW();

    wayangSita.defaultHandPosition();
    wayangSita.defaultStandPosition();

    wayangRahwana.defaultHandPosition();
    wayangRahwana.defaultStandPosition();

    wayangRamaWijaya.defaultHandPosition();
    wayangRamaWijaya.defaultStandPosition();

    wayangHanoman.defaultHandPosition();
    wayangHanoman.defaultStandPosition();

    wayangLaksmana.defaultHandPosition();
    wayangLaksmana.defaultStandPosition();

    wayangSugriwa.defaultHandPosition();
    wayangSugriwa.defaultStandPosition();

    wayangSubali.defaultHandPosition();
    wayangSubali.defaultStandPosition();

    wayangWibhisana.defaultHandPosition();
    wayangWibhisana.defaultStandPosition();

    wayangAnggada.defaultHandPosition();
    wayangAnggada.defaultStandPosition();

    wayangAnila.defaultHandPosition();
    wayangAnila.defaultStandPosition();

    // setAllMOSFETtoHIGH();
}

void backToEpisodeSelection()
{
    isEpisodeTaskCreated = false;
    pageRoute = StateManagement::PAGE_ROUTE::EPISODE_PAGE;
    WayangDisplayLCD_in_main.set_selection_point(1);
    // vTaskDelay(1000 / portTICK_PERIOD_MS);
    loop_state = StateManagement::FSA_STATE::DEFAULT_LOOPING_LCD;
    delay(1);
}

int getSubPageRoute()
{
    return subPageRoute;
}

void setAllENtoHIGH()
{
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
}
