// #include <Arduino_FreeRTOS.h>
#include "Episodes.hpp"
#include "sound_system.hpp"
#include "characters/hanoman.hpp"
#include "characters/rama_wijaya.hpp"
#include "characters/sita.hpp"
#include "characters/rahwana.hpp"
#include "characters/laksmana.hpp"
#include "mainheader.hpp"
#include "characters/subali.hpp"
#include "characters/sugriwa.hpp"

Hanoman hanoman;
RamaWijaya rama_wijaya;
Sita sita;
Rahwana rahwana;
Laksmana laksmana;
Subali subali;
Sugriwa sugriwa;

// TaskHandle_t taskSugriwa;
// TaskHandle_t taskSubali;

// Execution function for pameran tanggal 2 Mei 2024 di ruang MIS depan
// void Episodes::Mei2nd_Episode()
// {

//     // Narator Opening
//     SoundSystem::play_dialog_direct(SoundSystem::DIALOG_NUMBER::NARATOR_INTRO_1);
//     // SoundSystem::hold_the_section_until_finished(123*1000);
//     static unsigned long stop_watch = millis();

//     while (millis() - stop_watch < 123 * 1000)
//     {
//         // put the movement command here
//     }

//     Serial.println("\nNarator Opening Done");
//     delay(1000);

//     // Hanuman Dialog 1
//     hanoman.walk_to_scene();         // going to the dialog position
//     rama_wijaya.walk_to_scene(1100); // going to the dialog position
//     SoundSystem::play_dialog_direct(SoundSystem::DIALOG_NUMBER::HANUMAN_1);
//     // SoundSystem::hold_the_section_until_finished(98 * 1000);
//     stop_watch = millis();
//     // starting_hanoman_talking(98);

//     if (millis() - stop_watch < 97 * 1000)
//     {
//         // put the movement command here
//         hanoman.talking(96);
//     }

//     Serial.println("\nHanuman Dialog 1 Done");
//     delay(1000);

//     // Rama Dialog 1
//     SoundSystem::play_dialog_direct(SoundSystem::DIALOG_NUMBER::RAMA_1);
//     // SoundSystem::hold_the_section_until_finished(66 * 1000);
//     stop_watch = millis();
//     // starting_rama_talking(66);

//     if (millis() - stop_watch < 65 * 1000)
//     {
//         // put the movement command here
//         rama_wijaya.talking(64);
//     }

//     Serial.println("\nRama Dialog 1 Done");
//     delay(1000);

//     // Hanuman Dialog 2
//     SoundSystem::play_dialog_direct(SoundSystem::DIALOG_NUMBER::HANUMAN_2);
//     // SoundSystem::hold_the_section_until_finished(68 * 1000);
//     stop_watch = millis();
//     // starting_hanoman_talking(68);
//     if (millis() - stop_watch < 67 * 1000)
//     {
//         // put the movement command here
//         hanoman.talking(66);
//     }

//     Serial.println("\nHanuman Dialog 2 Done");
//     delay(500);

//     /* Core where the task should run */

//     // run_both_instant();

//     hanoman.leave_from_scene();         // going back to first position
//     rama_wijaya.leave_from_scene(1100); // going back to first position
//     delay(500);

//     // Narator Ending
//     SoundSystem::play_dialog_direct(SoundSystem::DIALOG_NUMBER::NARATOR_END_1);
//     // SoundSystem::hold_the_section_until_finished(14 * 1000);
//     stop_watch = millis();

//     while (millis() - stop_watch < 14 * 1000)
//     {
//         // put the movement command here
//     }

//     Serial.println("\nDone!");
//     digitalWrite(LED_BUILTIN, LOW);
// }

static void sugriwaTaskFight1(void *pvParameters)
{
    while (1)
    {
        Serial.println("Running sugriwaTaskFight1: " + String(uxTaskGetStackHighWaterMark(NULL)));
        sugriwa.pointToFront();       // takes 900 ms
        sugriwa.lower_pointToFront(); // takes 700 ms
        sugriwa.downFront();          // takes 700 ms
        sugriwa.lower_pointToFront(); // takes 700 ms
        // vTaskDelay(200 / portTICK_PERIOD_MS);

        // deleting sugriwaTaskFight1 task
        // Serial.println("sugriwaTaskFight1 stack: " + String(uxTaskGetStackHighWaterMark(NULL)));
        vTaskDelete(NULL);
    }
}

static void subaliTaskFight1(void *pvParameters)
{
    // vTaskSuspend(mainLoopTaskHandler);
    while (1)
    {
        Serial.println("Running subaliTaskFight1: " + String(uxTaskGetStackHighWaterMark(NULL)));
        subali.pointToFront();       // takes 900 ms
        subali.lower_pointToFront(); // takes 700 ms
        subali.downFront();          // takes 700 ms
        subali.pointToFront();       // takes 900 ms
        // deleting subaliTaskFight1 task
        // Serial.println("subaliTaskFight1 stack: " + String(uxTaskGetStackHighWaterMark(NULL)));
        vTaskResume(mainLoopTaskHandler);
        vTaskDelete(NULL);
    }
}

static void subaliTaskFight2(void *pvParameters)
{
    while (1)
    {
        Serial.println("Running subaliTaskFight2: " + String(uxTaskGetStackHighWaterMark(NULL)));
        subali.pointToFront();       // takes 900 ms
        subali.lower_pointToFront(); // takes 700 ms
        subali.downFront();          // takes 700 ms
        subali.lower_pointToFront(); // takes 900 ms
        // deleting subaliTaskFight2 task
        // Serial.println("subaliTaskFight2 stack: " + String(uxTaskGetStackHighWaterMark(NULL)));
        vTaskDelete(NULL);
    }
}

static void ramaTaskFight1(void *pvParameters)
{
    while (1)
    {
        Serial.println("Running ramaTaskFight1 : " + String(uxTaskGetStackHighWaterMark(NULL)));
        rama_wijaya.pointToFront();       // takes 900 ms
        rama_wijaya.lower_pointToFront(); // takes 700 ms
        rama_wijaya.downFront();          // takes 700 ms
        rama_wijaya.pointToFront();       // takes 700 ms
        // deleting ramaTaskFight1 task
        // Serial.println("ramaTaskFight1 stack: " + String(uxTaskGetStackHighWaterMark(NULL)));
        vTaskResume(mainLoopTaskHandler);
        vTaskDelete(NULL);
    }
}

void Episodes::July29_Episode()
{
    setAllMOSFETtoLOW();
    sita.defaultStandPosition();
    sita.defaultHandPosition();

    rahwana.defaultStandPosition();
    rahwana.defaultHandPosition();

    rama_wijaya.defaultStandPosition();
    rama_wijaya.defaultHandPosition();

    // // Rama-Sita Dialogue
    SoundSystem::playMusicWayang();
    sita.walk_to_a_certain_distance_before_calibrating_value(150);        // going to the dialog position
    rama_wijaya.walk_to_a_certain_distance_before_calibrating_value(300); // going to the dialog position
    delay(3000);
    SoundSystem::pauseMusicWayang();

    // Sita 1 8s
    // delay(500);
    sita.pointToFront();
    sita.onHipBack();
    delay(50);
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::SPECIAL_EPISODE_29_JULY::RAMA_SITA__SITA_DIALOG_1);
    delay(1000);

    SoundSystem::pause();
    sita.left_lower_hand();
    delay(50);

    SoundSystem::continuePlaying();
    delay(2667);

    SoundSystem::pause();
    sita.pointToFront();
    delay(50);

    SoundSystem::continuePlaying();
    delay(3333);

    SoundSystem::pause();
    sita.defaultHandPosition();
    sita.pointToSelf();
    delay(50);

    SoundSystem::continuePlaying();
    delay(2000);

    sita.defaultHandPosition();

    // Rama 1 10s
    rama_wijaya.right_moveHandBackAbit();
    delay(50);

    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::SPECIAL_EPISODE_29_JULY::RAMA_SITA__RAMA_DIALOG_1);
    // SoundSystem::hold_the_section_until_finished(10 * 1000);
    delay(1820);

    SoundSystem::pause();
    rama_wijaya.left_pointToSelf();
    delay(50);

    SoundSystem::continuePlaying();
    delay(6450 - 1820 + 1000);

    SoundSystem::pause();
    rama_wijaya.defaultHandPosition();
    rama_wijaya.right_handOnHip();
    delay(50);

    SoundSystem::continuePlaying();
    delay(7740 - 6450 + 1500);

    SoundSystem::pause();
    rama_wijaya.left_pointToFront();
    rama_wijaya.defaultHandPosition();
    delay(50);

    SoundSystem::playMusicWayang();
    rama_wijaya.defaultStandPosition(); // going back to first position
    sita.defaultStandPosition();        // going back to first position

    delay(500);
    delay(1000);
    sita.walk_to_a_certain_distance_before_calibrating_value(100); // going to the dialog position
    SoundSystem::pauseMusicWayang();

    // Narator 1 3s
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::SPECIAL_EPISODE_29_JULY::SITA_RAHWANA__NARATOR_1);
    // SoundSystem::hold_the_section_until_finished(3 * 1000);
    delay(3000);
    rahwana.walk_to_a_certain_distance_before_calibrating_value(350); // going to the dialog position
    delay(2500);

    // Rahwana 1 44s
    rahwana.hand_movement_1();
    delay(50);

    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::SPECIAL_EPISODE_29_JULY::SITA_RAHWANA__RAHWANA_DIALOG_1);
    delay(2510);

    SoundSystem::pause();
    rahwana.hand_movement_2();
    delay(50);

    SoundSystem::continuePlaying();
    delay(5420 - 2510);

    SoundSystem::pause();
    rahwana.hand_movement_3();
    delay(50);

    SoundSystem::continuePlaying();
    delay(7920 - 5420);

    SoundSystem::pause();
    rahwana.hand_movement_4();
    delay(50);

    SoundSystem::continuePlaying();
    delay(9390 - 7920);

    SoundSystem::pause();
    rahwana.hand_movement_5();
    delay(50);

    SoundSystem::continuePlaying();
    delay(18160 - 9390);

    SoundSystem::pause();
    rahwana.hand_movement_6();
    delay(50);

    SoundSystem::continuePlaying();
    delay(33850 - 18160);

    SoundSystem::pause();
    rahwana.hand_movement_7();
    delay(50);

    SoundSystem::continuePlaying();
    delay(12000);
    rahwana.hand_movement_2();

    // Sita 2 12s
    // sita.defaultHandPosition();
    // delay(500);

    sita.pointToSelf();
    delay(50);

    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::SPECIAL_EPISODE_29_JULY::SITA_RAHWANA__SITA_DIALOG_1);
    // SoundSystem::hold_the_section_until_finished(12 * 1000);
    delay(5300);

    SoundSystem::pause();
    sita.defaultHandPosition();
    delay(50);

    SoundSystem::continuePlaying();
    delay(7330 - 5300);

    SoundSystem::pause();
    sita.pointToFront();
    delay(50);

    SoundSystem::continuePlaying();
    delay(12580 - 7330);

    SoundSystem::pause();
    sita.defaultHandPosition();
    delay(500);

    // Rahwana 2 36s
    rahwana.hand_movement_1();
    delay(50);

    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::SPECIAL_EPISODE_29_JULY::SITA_RAHWANA__RAHWANA_DIALOG_2);
    delay(2260);

    SoundSystem::pause();
    rahwana.hand_movement_2();
    delay(50);

    SoundSystem::continuePlaying();
    delay(4880 - 2260);

    SoundSystem::pause();
    rahwana.hand_movement_3();
    delay(50);

    SoundSystem::continuePlaying();
    delay(10010 - 4880);

    SoundSystem::pause();
    rahwana.hand_movement_4();
    delay(50);

    SoundSystem::continuePlaying();
    delay(15490 - 10010);

    SoundSystem::pause();
    rahwana.hand_movement_8();
    delay(50);

    SoundSystem::continuePlaying();
    delay(18390 - 15490);

    SoundSystem::pause();
    rahwana.hand_movement_9();
    delay(50);

    SoundSystem::continuePlaying();
    delay(22180 - 18390);

    SoundSystem::pause();
    rahwana.hand_movement_10();
    delay(50);

    SoundSystem::continuePlaying();
    delay(22860 - 22180);

    SoundSystem::pause();
    rahwana.hand_movement_11();
    delay(50);

    SoundSystem::continuePlaying();
    delay(33550 - 22860);

    SoundSystem::pause();
    rahwana.hand_movement_12();
    delay(50);

    SoundSystem::continuePlaying();
    delay(35960 - 33550);

    rahwana.hand_movement_13();
    delay(500);

    // Narator 2 10s
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::SPECIAL_EPISODE_29_JULY::SITA_RAHWANA__NARATOR_2);
    // SoundSystem::hold_the_section_until_finished(10 * 1000);
    delay(10500);

    // Rahwana kidnapped Sita
    SoundSystem::playMusicWayang();
    rahwana.walk_to_a_certain_distance_before_calibrating_value(370); // going to the dialog position
    // rahwana.walk_to_scene(100); // going to the dialog position

    delay(1000);

    sita.defaultStandPosition();    // going back to first position
    rahwana.defaultStandPosition(); // going back to first position
    SoundSystem::pauseMusicWayang();
    delay(1000);
    rahwana.defaultHandPosition();
    delay(50);

    // Narator 3 9s
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::SPECIAL_EPISODE_29_JULY::SITA_RAHWANA__NARATOR_3);
    // SoundSystem::hold_the_section_until_finished(9 * 1000);
    delay(9000);

    // Rama-Rahwana Dialogue

    SoundSystem::playMusicWayang();
    rama_wijaya.walk_to_a_certain_distance_before_calibrating_value(350); // going to the dialog position
    rahwana.walk_to_a_certain_distance_before_calibrating_value(150);     // going to the dialog position
    SoundSystem::pauseMusicWayang();
    delay(2000);

    // Rama 1 21s
    rama_wijaya.left_pointToFront();
    delay(50);

    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::SPECIAL_EPISODE_29_JULY::RAMA_RAHWANA__RAMA_1);
    // SoundSystem::hold_the_section_until_finished(21 * 1000);
    delay(7770);

    SoundSystem::pause();
    rama_wijaya.defaultHandPosition();
    rama_wijaya.right_handOnHip();
    delay(50);

    SoundSystem::continuePlaying();
    delay(13490 - 7770);

    SoundSystem::pause();
    rama_wijaya.defaultHandPosition();
    rama_wijaya.left_pointToSelf();
    delay(50);

    SoundSystem::continuePlaying();
    delay(10000);

    SoundSystem::pause();
    rama_wijaya.defaultHandPosition();
    rama_wijaya.left_pointToFront();
    delay(50);

    // Rahwana 1 14s
    rahwana.hand_movement_14();
    delay(50);

    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::SPECIAL_EPISODE_29_JULY::RAMA_RAHWANA__RAHWANA_1);
    delay(18100);

    rahwana.hand_movement_15();

    // FIGHT
    rama_wijaya.defaultHandPosition();
    rama_wijaya.left_pointToFront();
    delay(50);

    rahwana.walk_to_a_certain_distance_before_calibrating_value(100);
    delay(1000);

    // Rahwana 2 6s
    rahwana.hand_movement_16();
    delay(50);

    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::SPECIAL_EPISODE_29_JULY::RAMA_RAHWANA__RAHWANA_2);
    // SoundSystem::hold_the_section_until_finished(6.5 * 1000);
    delay(3500);

    SoundSystem::pause();
    rahwana.hand_movement_17();
    delay(50);

    SoundSystem::continuePlaying();
    delay(2700);

    rahwana.hand_movement_18();

    delay(500);
    sita.walk_to_a_certain_distance_before_calibrating_value(200); // going to the dialog position

    // Rama 2 3s
    delay(500);
    rama_wijaya.right_handOnHip();
    delay(50);

    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::SPECIAL_EPISODE_29_JULY::RAMA_RAHWANA__RAMA_2);
    // SoundSystem::hold_the_section_until_finished(3.5 * 1000);
    delay(3500);

    // Sita 1 3s
    // sita.defaultHandPosition();
    // delay(500);
    sita.onHipBack();
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::SPECIAL_EPISODE_29_JULY::RAMA_RAHWANA__SITA_1);
    // SoundSystem::hold_the_section_until_finished(3.5 * 1000);
    delay(3520);

    SoundSystem::playMusicWayang();
    rama_wijaya.defaultStandPosition(); // going back to first position
    sita.defaultStandPosition();        // going back to first position
    rahwana.defaultStandPosition();     // going back to first position
    SoundSystem::pauseMusicWayang();
    delay(3000);

    delay(100);
    rama_wijaya.defaultHandPosition();
    sita.defaultHandPosition();
    rahwana.defaultHandPosition();
    delay(1000);
    setAllMOSFETtoHIGH();
    SoundSystem::playDialogFromACertainFolder(SoundSystem::INDICATOR_SOUND, SoundSystem::INDICATOR_SOUND_NUMBER::INDICATOR_FINISHED_SHOWING);
    delay(2000);
}

// Function untuk testing lengan Hanuman
// void Episodes::Testing_Hanuman()
// {
//     hanoman.talking(20);
//     // hanoman.all_high();
// }

// // Function untuk testing lengan Rama Wijaya
// void Episodes::Testing_Rama()
// {
//     rama_wijaya.talking(20);
//     // rama_wijaya.all_high();
// }

/*
Function untuk begin hanoman dan rama wijaya dari yang passing parameter berupa rpm speed dari stepper lengan
serta begining nema17 untuk pergerakan horizontal
*/
// void Episodes::manual_begin()
// {
// }

// /*
// Function untuk testing pergerakan horizontal dari hanoman
// */
// void Episodes::testing_hanuman_horizontal_movement()
// {
//     hanoman.walk_to_scene();
//     delay(5);
//     hanoman.leave_from_scene();
//     delay(5);
// }

/*
Function untuk testing pergerakan horizontal dari rama wijaya
*/
void Episodes::testing_rama_wijaya_horizontal_movement()
{
    rama_wijaya.walk_to_scene(1000);
    delay(5);
    rama_wijaya.leave_from_scene(1000);
    delay(5);
}

/*
Function untuk testing pergerakan horizontal dari sita
*/

void Episodes::testing_sita_horizontal_movement()
{
    sita.walk_to_scene(1000);
    delay(5);
    sita.leave_from_scene(1000);
    delay(5);
}

void Episodes::testing_rahwana_horizontal_movement()
{
    rahwana.walk_to_scene(1000);
    delay(5);
    rahwana.leave_from_scene(1000);
    delay(5);
}

void Episodes::randomTesting()
{
    setAllMOSFETtoLOW();
    rahwana.walk_to_a_certain_distance_before_calibrating_value(200); // going to the dialog position
    delay(2500);

    // SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_2, 1);
    // rahwana.rahwana_120_bpm_deathstream();

    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::SPECIAL_EPISODE_29_JULY::SITA_RAHWANA__RAHWANA_DIALOG_1);
    rahwana.Rahwana_1();
    setAllMOSFETtoHIGH();
}

void Episodes::Episode_1()
{
    // Calibrating all wayang first
    CalibratingFunction::wayangHand();

    setAllMOSFETtoLOW();

    SoundSystem::playMusicWayang();
    sita.walk_to_a_certain_distance_before_calibrating_value(160);
    laksmana.walk_to_a_certain_distance_before_calibrating_value(160);
    // 001 (Sita1Sita-laksmana dialogue 1)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SITA1SITA_LAKS_DIALOGUE_1);
    // delay(3000); // audio test only 3s

    delay(1312);
    // movement 1, 2
    sita.pointToFront(); // takes 700 ms

    delay(4796 - 1312 - 700); // result = 2784 ms
    // movement 3
    sita.lower_pointToFront(); // takes 700 ms

    delay(7339 - 4796 - 700); // result = 1843 ms
    // movement 4, 5
    for (int i = 0; i < 4; i++)
    {
        sita.directControl(1, 70, 400);
        sita.directControl(1, 100, 400);
    } // takes 800 ms each loop

    delay(10673 - 7339 - 800 * 4);

    // movement 6, 7
    sita.pointToFront();        // takes 700 ms
    delay(12320 - 10673 - 700); // result = 1547 ms

    sita.defaultHandPosition(); // takes 1400 ms

    // 002 (01 S-L1 laksmana1F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::S_L1_LAKS1F);
    // delay(3000);

    /*You are the wife of the hero from Raghu lineage;*/
    delay(787);              // 787
    laksmana.pointToFront(); // 1487
    delay(3875 - 1487);      // 3875 (2388)

    /*you are the beloved of my brother,*/
    laksmana.lower_pointToFront(); // 4575 (700)
    laksmana.pointToFront();       // 5275 (700)
    laksmana.lower_pointToFront(); // 5975 (700)
    delay(6589 - 5975);            // 6589 (614)

    /*also you are the daughter of king Janaka.*/
    laksmana.pointToFront(); // 7289 (700)
    delay(9898 - 7289);      // 9898 (2609)

    /*Why do you worry and cry so at hearing such a call?*/
    laksmana.middleFront(); // 10798 (900)
    delay(13684 - 10798);   // 13684 (2886)

    /*Do you know that it is he who calls?*/
    laksmana.lower_pointToFront(); // 14384 (700)
    delay(16604 - 14384);          // 16604 (2220)

    /*Do you know who that is? */
    laksmana.middleFront(); // 17504 (900)
    delay(18923 - 17504);   // 18923 (1419)

    /*You may ask,*/
    laksmana.pointToFront(); // 19623 (700)
    delay(20269 - 19623);    // 20269 (646)

    /*who is powerful enough in this world to fight prince Rama in battle?*/
    laksmana.downBack();   // 20969 (700)
    laksmana.middleBack(); // 21669 (700)
    delay(25323 - 21669);  // 25323 (2954)

    /*He is the most powerful person,*/
    laksmana.lower_pointToFront(); // 26023 (700)
    delay(27655 - 26023);          // 27655 (1632)

    /*the most skilled in handling all weapons.*/
    laksmana.pointToBack(); // 29055 (1400)
    delay(30722 - 29055);   // 30722 (1667)

    /*How could you have fears that he would be killed,*/
    laksmana.downBack();     // 31422 (700)
    laksmana.pointToFront(); // 32122 (700)
    delay(34010 - 32122);    // 34010 (1888)

    /*butted by a deer?*/
    laksmana.onHipBack(); // 35210 (1200)
    delay(36072 - 35210); // 36072 (862)

    /*That call was not his,*/
    // laksmana.middleFront();              // 36972 (900)
    laksmana.directControl(4, 110, 400); //1800
    laksmana.directControl(3, 180, 1000);
    laksmana.directControl(4, 120, 400);

    laksmana.directControl(4, 115, 400); // 37372 (400)
    laksmana.directControl(4, 120, 400); // 37772 (400)
    // laksmana.directControl(4, 115, 400); // 38172 (400)
    // laksmana.directControl(4, 120, 400); // 38572 (400)
    delay(38746 - 38572 - 100);                // 38746 (174-100)

    /*it was the call of an evil demon, */
    laksmana.pointToFront(); // 39446 (700)
    delay(41447 - 39446);    // 41447 (2001)

    /*it was a trick with the purpose of deceiving us.*/
    laksmana.lower_pointToFront(); // 42147 (700)
    delay(44700 - 42147 - 700);    // 44000 (1853)
    laksmana.downFront();          // 44700 (700)

    /*I say, it was the cry of the deer*/
    laksmana.pointToSelf(); // 45400 (700)
    delay(48296 - 45400);   // 48296 (2896)
    laksmana.downFront();   // 48996 (700)

    /*which was hit by an arrow,*/
    laksmana.lower_pointToFront(); // 49696 (700)
    delay(50930 - 49696);          // 50930 (1234)

    /*sounding like the voice of Rama. */
    laksmana.middleFront(); // 51830 (900)
    delay(53233 - 51830);   // 53233 (1403)

    /*return to default position*/
    laksmana.downFront();
    laksmana.downBack();
    laksmana.onHipBack();

    // 003 (Sita2Sita-laksmana dialogue 1)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SITA2SITA_LAKS_DIALOGUE_1);
    // delay(3000);

    // (1114) My brother Laksmana. (2184)

    delay(1114);
    sita.pointToFront(); // takes 700 ms

    // (2562) What does this mean? (3546)

    delay(2562 - 1114 - 700);
    sita.lower_pointToFront(); // takes 700 ms

    // (4189) This is the first time that you do not obey my orders. (7113)

    delay(4198 - 2562 - 700);
    sita.middleFront(); // takes 900 ms

    // (8038) In the past you were very faithful to your brother, (10513)

    delay(8038 - 4189 - 900);
    for (int i = 0; i < 3; i++)
    {
        sita.directControl(1, 45, 400);
        sita.directControl(1, 0, 400);
    } // takes 800 ms each loop

    // (11095) but now he is in trouble, (12326)

    delay(11095 - 8038 - 800 * 3);
    sita.downFront();          // takes 700 ms
    sita.lower_pointToFront(); // takes 700 ms

    // (12747) shame on you, (13502)

    delay(12747 - 11095 - 700 - 700);
    sita.pointToFront(); // takes 700 ms

    // (14078) you do not want to help. (15167)

    delay(14078 - 12747 - 700);
    sita.lower_pointToFront(); // takes 700 ms

    // (15990) You think about Rama like this. (17638)

    delay(15990 - 14078 - 700);
    sita.downFront();   // takes 700 ms
    sita.middleFront(); // takes 900 ms

    // (18440)  ‘Let him be killed by the deer. (19962)

    // (20309) It will be very lucky! (21771)

    // ***MAY NOT SMOOTH MOVEMENT***

    delay(18440 - 15990 - 700 - 900);
    for (int i = 0; i < 4; i++)
    {
        sita.directControl(1, 45, 400);
        sita.directControl(1, 0, 400);
    } // takes 800 ms each loop

    // (22215) I will take his place and marry Sita. (24250)

    delay(22215 - 18440 - 800 * 4);
    sita.pointToSelf(); // takes 1400 ms

    // (24956) Who will be her protector, (26144)

    delay(24956 - 22215 - 1400);
    sita.downFront();          // takes 700 ms
    sita.lower_pointToFront(); // takes 700 ms

    // (26422) no one else except me.’ (28075)

    delay(26422 - 24956 - 700 - 700);
    sita.pointToSelf(); // takes 1400 ms

    // (28594) you said this to yourself, didn't you? (30247)

    delay(28594 - 26422 - 1400);
    sita.downFront();   // takes 700 ms
    sita.middleFront(); // takes 900 ms

    // (31045) Debased and foolish Laksmana, (32697)

    delay(31045 - 28594 - 700 - 900);
    sita.downFront();    // takes 700 ms
    sita.pointToFront(); // takes 700 ms

    // (33087) do you think I am wicked, (34225)

    // (34832) capable of such evil, (36212)

    // (36447) such lewdness? (37319)

    delay(33087 - 31045 - 700 - 700);
    // sita.oscillate(37913 - 33087); // takes 4826 ms ~~ 4200 ms
    for (int i = 0; i < 6; i++)
    {
        sita.directControl(1, 55, 400);
        sita.directControl(1, 10, 400);
    } // takes 800 ms each loop

    // (37913) I do not have any intention of marrying again, (40389)

    delay(37913 - 33087 - 800 * 6);
    sita.downFront(); // takes 700 ms

    // (40840) just this once. (41901)

    delay(40840 - 37913 - 700);
    sita.lower_pointToFront(); // takes 700 ms

    // (42759) I will only serve Rama, nobody else. (45432)

    delay(42759 - 40840 - 700);
    sita.pointToSelf(); // takes 1400 ms

    // (46341) If my lord and master died, (48024)

    // (48476) if Rama is killed in battle (50462)

    delay(46341 - 42759 - 1400);
    // sita.oscillate(50722 - 46341); // takes 4381 ms ~~ 4200 ms
    sita.downBack(); // takes 700 ms
    // sita.middleFrontBack(); // takes 700 ms
    // for (int i = 0; i < 3; i++)
    // {
    //     sita.directControl(3, 90, 400);
    //     sita.directControl(3, 120, 400);
    // } // takes 800 ms each loop

    // (50722) butted by the deer, (51570)

    delay(50722 - 46341 - 700);
    sita.downFront(); // takes 700 ms

    // (51781) I will sever my neck (52913)

    // (53241) and burn myself. (54287)

    // (54961) I will follow my husband; (56378)

    delay(51781 - 50722 - 700);
    sita.pointToSelf(); // takes 1400 ms

    // (56657) I will not take refuge with you. (58501)

    delay(56657 - 51781 - 1400);
    sita.downFront();    // takes 700 ms
    sita.pointToFront(); // take 700 ms

    delay(58501 - 56657 - 700 - 700);

    // 004 (02 S-L1 laksmana2F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::S_L1_LAKS2F);
    // delay(3000);

    delay(1188);
    /*You suspect me of being wicked,*/
    laksmana.pointToFront();             // 1888 (700)
    laksmana.directControl(3, 170, 400); // 2288 (400)
    laksmana.directControl(3, 180, 400); // 2688 (400)
    laksmana.directControl(3, 170, 400); // 3088 (400)
    laksmana.directControl(3, 180, 400); // 3488 (400)
    delay(3670 - 3488);                  // 3670 (182)

    /*having the intention to betray my older brother. */
    laksmana.lower_pointToFront(); // 4370 (700)
    delay(1000);                   // 5370 (1000)
    laksmana.downFront();          // 6070 (700)
    delay(6787 - 6070);            // 6787 (717)

    /*My mind is pure, truthful, and not wicked.*/
    laksmana.pointToSelf(); // 7487 (700)
    delay(10564 - 7487);    // 10564 (3077)

    /* Let all the deities bear witness to the purity of my heart.*/
    laksmana.directControl(3, 0, 1200);   // 11764 (1200)
    laksmana.directControl(4, 110, 400);  // 12244 (480) -> 400
    laksmana.directControl(3, 180, 1200); // 13444 (1200)
    laksmana.directControl(4, 140, 400);  // 13924 (480) -> 400
    delay(16175 - 13924 + 160);           // 16175 (2251)

    /*Let me fall into hell,*/
    laksmana.directControl(3, 120, 1000); // 17175 (1000)
    laksmana.directControl(4, 140, 400);  // 17575 (400)
    delay(18385 - 17575);                 // 18385 (810)

    /*let me be overcome by misfortunes, */
    laksmana.directControl(3, 0, 1000);  // 19385 (1000)
    laksmana.directControl(4, 110, 400); // 19785 (400)
    delay(21214 - 19785);                // 21214 (1429)

    /*if I am treacherous.*/
    laksmana.pointToSelf(); // 21914 (700)
    delay(24277 - 21914);   // 24277 (2363)

    /*O, daughter of Janaka, */
    laksmana.directControl(3, 0, 500);   // 25277 (1000)
    laksmana.directControl(4, 110, 400); // 25677 (400)
    laksmana.directControl(3, 180, 500); // 26677 (1000)
    laksmana.directControl(4, 120, 400); // 27077 (400)
    delay(26796 - 26077);                // 26796 (719)

    /*you have uttered bad words, */
    laksmana.pointToFront(); // 27496 (700)
    delay(29186 - 26796);    // 29186 (2390)

    /*as if you meant it when you accused me of wanting you to be my wife.*/
    laksmana.lower_pointToFront();       // 29886 (700)
    laksmana.directControl(3, 130, 400); // 30286 (400)
    laksmana.directControl(3, 120, 400); // 30686 (400)
    laksmana.directControl(3, 130, 400); // 31086 (400)
    laksmana.directControl(3, 120, 400); // 31486 (400)
    laksmana.directControl(3, 130, 400); // 31886 (400)
    laksmana.directControl(3, 120, 400); // 32286 (400)
    laksmana.directControl(3, 130, 400); // 32686 (400)
    laksmana.directControl(3, 120, 400); // 33086 (400)
    delay(33867 - 33086);                // 33867 (781)

    /*Because of your bad words, */
    laksmana.pointToFront(); // 34567 (700)
    delay(36000 - 33867);    // 36000 (2133)

    /*may you find great sorrow. */
    laksmana.lower_pointToFront();       // 36700 (700)
    laksmana.directControl(3, 130, 400); // 37100 (400)
    laksmana.directControl(3, 120, 400); // 37500 (400)
    laksmana.directControl(3, 130, 400); // 37900 (400)
    laksmana.directControl(3, 120, 400); // 38300 (400)
    laksmana.directControl(3, 130, 400); // 38700 (400)
    delay(63);                           // 38763 (63)

    /*You will be captured by the enemy,*/
    laksmana.middleFront(); // 39663 (900)
    delay(41139 - 39663);   // 41139 (1476)

    /*after my leave!*/
    laksmana.downFront(); // 41839 (700)

    /*return to default position*/
    laksmana.defaultHandPosition();
    sita.defaultHandPosition();

    SoundSystem::playMusicWayang();
    laksmana.defaultStandPosition();
    sita.defaultStandPosition();

    delay(1000);
    sita.walk_to_a_certain_distance_before_calibrating_value(160);
    rahwana.walk_to_a_certain_distance_before_calibrating_value(200);

    // 005 (005SitaRahwanadialogueRahwana1)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SITA_RAHWANA_DIALOGUE_RAHWANA_1);
    // delay(3000);
    /*Who are you, o beautiful one,*/
    rahwana.pointToFront(); // 900
    delay(2660 - 900);

    /*who enters the forest to pick flowers. */
    rahwana.downFront(); // 700
    delay(5682 - 2660 - 700 - 500);

    /*How unparalleled is your beauty,*/
    rahwana.middleFront(); // 1200
    delay(7910 - 5682 - (1200 - 500));

    /*most perfect.*/
    rahwana.pointToFront(); // 700
    delay(9579 - 7910 - 700);

    /*Even an extremely poor ascetic who has overcome his sensual impulses,*/
    rahwana.pointToFront();     // 700
    for (int i = 0; i < 3; i++) // 800*3
    {
        rahwana.directControl(3, 160, 400);
        rahwana.directControl(3, 180, 400);
    }
    rahwana.directControl(3, 160, 400); // 400
    delay(13390 - 9579 - 700 - (800 * 3) - 400);

    /* would be crazy about you and fall heels over ears */
    rahwana.downFront();   // 700
    delay(400);            // 400
    rahwana.middleFront(); // 1200
    delay(16906 - 13390 - 700 - 400 - 1200);

    /*in love with you */
    rahwana.pointToFront(); // 700
    rahwana.downFront();    // 700
    // delay(19101-16906-700-700);

    /*My name is Rawana, */ //(18306)
    rahwana.pointToSelf();  // 1100
    delay(20828 - 18306 - 1100);

    /*I am the king ruling over the country of Lenka, */
    rahwana.directControl(3, 0, 740);   // 740
    rahwana.directControl(4, 120, 600); // 600
    rahwana.directControl(3, 180, 740); // 740
    rahwana.directControl(4, 140, 300); // 300
    delay(24113 - 20828 - 740 - 600 - 740 - 300);

    /*my palace is on the beach and there are */
    rahwana.lower_pointToFront(); // 700
    delay(26298 - 24113 - 700);

    /*plenty of brilliant jewels*/
    rahwana.pointToFront(); // 700
    delay(28573 - 26298 - 700);

    /*and precious stones decorating it,*/
    rahwana.lower_pointToFront(); // 700
    delay(30925 - 28573 - 700);

    /*making it as glorious as the moon. */
    rahwana.middleFront();              // 1200
    rahwana.directControl(3, 160, 400); // 400
    rahwana.directControl(3, 180, 400); // 400
    rahwana.directControl(3, 160, 400); // 400
    rahwana.directControl(3, 180, 400); // 400
    delay(34625 - 30925 - 1200 - (400 * 4));

    /*you may rule over it,*/
    rahwana.pointToFront(); // 700
    delay(36311 - 34625 - 700 - 700);
    rahwana.downFront(); // 700

    /*and share a luxurious life with me. */
    rahwana.pointToSelf(); // 1100
    delay(39143 - 36311 - 1100 - 700);
    rahwana.downFront(); // 700

    /*Have no doubt,*/
    rahwana.lower_pointToFront(); // 700
    delay(40529 - 39143 - 700);

    /*everything you wish for is there.*/
    rahwana.pointToFront(); // 700
    delay(42971 - 40529 - 700 - 700);

    /*what do you think?*/
    rahwana.middleFront(); // 1200
    delay(44024 - 42971 - (1200 - 700));

    /*O beautiful one? */
    rahwana.pointToFront(); // 700

    // rahwana.Rahwana_1();

    // 006 (006SitaRahwanadialogueSita1)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SITA_RAHWANA_DIALOGUE_SITA_1);
    // delay(3000);

    // (74)I am sorry, I cannot accept for I am already betrothed to Rama, (4700)

    delay(74);
    sita.pointToSelf(); // takes 1400 ms

    // (5162)son of king Dasaratha (6668)

    delay(5162 - 74 - 1400);
    sita.downFront();    // takes 700 ms
    sita.pointToFront(); // takes 700 ms

    // (7272)and it is the duty of a wife to be loyal to her husband and no other. (12304)

    delay(7272 - 5162 - 700 - 700);
    sita.downFront(); // takes 700 ms
    delay(12304 - 7272 - 700);

    // 007 (007SitaRahwanadialogueRahwana2)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SITA_RAHWANA_DIALOGUE_RAHWANA_2);
    // delay(3000);

    /*I know that Rama,*/
    delay(464);
    rahwana.pointToFront(); // 700
    delay(3158 - 464 - 700);

    /*he is worthless. */
    rahwana.lower_pointToFront(); // 700
    delay(5451 - 3158 - 700);

    /*Why do you want to stay with him in this extreme destitution.*/
    rahwana.pointToFront();     // 700
    for (int i = 0; i < 5; i++) // 800*5
    {
        rahwana.directControl(3, 160, 400); // 400
        rahwana.directControl(3, 180, 400); // 400
    }

    delay(11047 - 5451 - 700 - (800 * 5) - 500);

    /*He is debased */
    rahwana.middleFront(); // 1200
    delay(12527 - 11047 - (1200 - 500));

    /*and inferior to all his clever brothers.*/
    rahwana.lower_pointToFront(); // 700
    for (int i = 0; i < 3; i++)   // 800*3
    {
        rahwana.directControl(3, 100, 400); // 400
        rahwana.directControl(3, 120, 400); // 400
    }
    rahwana.directControl(3, 100, 400); // 400
    delay(17084 - 12527 - 700 - (800 * 3) - 400);

    /*He is the eldest, */
    rahwana.lower_pointToFront(); // 700
    delay(18878 - 17084 - 700);

    /*fit to be king*/
    rahwana.pointToFront(); // 700
    delay(20968 - 18878 - 700);

    /*yet he is banished into the forests. */
    rahwana.downFront(); // 700
    delay(24973 - 20968 - 700 - 700);

    /*I*/
    rahwana.pointToSelf(); // 1100
    delay(25687 - 24973 - (1100 - 700));

    /*am victorious over deities,*/
    rahwana.directControl(3, 0, 740);   // 740
    rahwana.directControl(4, 120, 600); // 600
    rahwana.directControl(3, 180, 740); // 740
    rahwana.directControl(4, 140, 300); // 300
    delay(28938 - 25687 - 740 - 600 - 740 - 300);

    /*men and animals.*/
    rahwana.lower_pointToFront(); // 700
    delay(31492 - 28938 - 700);

    /*God Waisrawana is defeated and has submitted.*/
    rahwana.pointToFront();     // 700
    for (int i = 0; i < 3; i++) // 800*3
    {
        rahwana.directControl(3, 160, 400); // 400
        rahwana.directControl(3, 180, 400); // 400
    }
    delay(35933 - 31492 - 700 - (800 * 3) - 700);

    /*God Yama has begged for his life */
    rahwana.middleFront();      // 1200
    for (int i = 0; i < 2; i++) // 800*2
    {
        rahwana.directControl(3, 115, 400); // 400
        rahwana.directControl(3, 135, 400); // 400
    }
    delay(39230 - 35933 - (1200 - 700) - (800 * 2));

    /*out of fear of death.*/
    rahwana.lower_pointToFront(); // 700
    delay(42104 - 39230 - 700);

    /*the king of the gods,*/
    rahwana.pointToFront(); // 700
    delay(44275 - 42104 - 700 - 700);

    /*God Indra,*/
    rahwana.middleFront(); // 1200
    delay(45732 - 44275 - (1200 - 700));

    /*has paid tribute.*/
    rahwana.downFront(); // 700
    delay(48286 - 45732 - 700 - 700);

    /*All of them respect me. */
    rahwana.pointToSelf(); // 1100
    delay(50051 - 48286 - (1100 - 700));

    /*I say it is perfectly fitting*/
    rahwana.downFront();   // 700
    rahwana.middleFront(); // 1200
    delay(54195 - 50051 - 700 - 1200);

    /*that we love each other*/
    rahwana.pointToFront(); // 700
    delay(55734 - 54195 - 700);

    /*I am young and powerful, */
    rahwana.downFront();   // 700
    rahwana.pointToSelf(); // 1100
    delay(58706 - 55734 - 700 - 1100);

    /*you are a beautiful lady*/
    rahwana.downFront();   // 700
    rahwana.middleFront(); // 1200
    delay(61701 - 58706 - 700 - 1200);

    /*in the prime of womanhood. */
    rahwana.pointToFront(); // 700
    delay(64917 - 61701 - 700);

    /*Rama is worthless my dear, */
    rahwana.lower_pointToFront(); // 700
    delay(67663 - 64917 - 700);

    /*leave him!*/
    rahwana.downFront(); // 700
    delay(71024 - 67663 - 700);

    /*grr*/
    rahwana.lower_pointToFront(); // 700
    delay(72435 - 71024 - 700 - 700);

    /*If you won’t give me an answer*/
    rahwana.middleFront(); // 1200
    delay(75093 - 72435 - (1200 - 700));

    /*then i shall show you my might! */
    rahwana.pointToFront(); // 700
    delay(76693 - 75093 - 700);
    rahwana.downFront(); // 700
    delay(2000);

    /*insert kidnapping sequence below*/
    SoundSystem::playMusicWayang();
    rahwana.pointToFront();
    rahwana.walk_to_a_certain_distance_before_calibrating_value(340);
    delay(1000);

    sita.defaultStandPosition();
    rahwana.defaultHandPosition();
    rahwana.defaultStandPosition();

    // 008 (03 L-R1 laksmana1F)
    rama_wijaya.walk_to_a_certain_distance_before_calibrating_value(160);
    laksmana.walk_to_a_certain_distance_before_calibrating_value(160);

    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::L_R1_LAKS1F);
    // delay(3000);
    delay(329);
    /*Brother,*/
    laksmana.middleFront(); // 1029 (700)
    delay(1431 - 1029);     // 1431 (402)

    /*an injured bird told me that it saw Sita got kidnapped by a notorious demon called Rawana */
    laksmana.pointToFront();             // 2131 (700)
    laksmana.directControl(3, 170, 400); // 2531 (400)
    laksmana.directControl(3, 180, 400); // 2931 (400)
    laksmana.directControl(3, 170, 400); // 3331 (400)
    laksmana.directControl(3, 180, 400); // 3731 (400)
    laksmana.lower_pointToFront();       // 4431 (700)
    for (int i = 0; i < 3; i++)          // 6831 (800*3)
    {
        laksmana.directControl(3, 130, 400);
        laksmana.directControl(3, 120, 400);
    }
    laksmana.downFront(); // 7531 (700)
    delay(8188 - 7531);   // 8188 (657)

    /*and that they are in Lenka across the ocean. */
    laksmana.pointToBack(); // 9588 (1400)
    delay(11394 - 9588);    // 11394 (1806)

    /*It advised me that we should seek Sugriwa through the Resyamuka mountain*/
    laksmana.pointToSelf();     // 12094 (700)
    for (int i = 0; i < 3; i++) // 15294 (800*4)
    {
        laksmana.directControl(1, 10, 400);
        laksmana.directControl(1, 0, 400);
    }
    delay(16292 - 15294 - 700); // 15592 (998)

    /*for he may be able to help us with his monkey troops. */
    laksmana.downFront();       // 16292 (700)
    laksmana.middleFront();     // 17192 (900)
    for (int i = 0; i < 3; i++) // 19592 (800*3)
    {
        laksmana.directControl(3, 170, 400);
        laksmana.directControl(3, 180, 400);
    }
    delay(19775 - 19592); // 19775 (183)

    /*return to default position*/
    laksmana.downFront();
    laksmana.downBack();
    laksmana.onHipBack();

    // 009 (Rama1laksmana-Rama Diaglogue(in place of narrator for context))
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::RAMA1LAKS_RAMA_DIALOGUE_IN_PLACE_NARATOR);
    // delay(3000);

    // (1139) Yes, let us head to Resyamuka and introduce ourselves. (5074)
    delay(1139);
    rama_wijaya.pointToFront(); // takes 1200 ms
    rama_wijaya.downFront();    // takes 700 ms
    rama_wijaya.pointToSelf();  // takes 900 ms

    rama_wijaya.downFront();                     // takes 700 ms
    delay(5074 - 1139 - 1200 - 700 - 900 - 700); // result = 438

    SoundSystem::playMusicWayang();
    rama_wijaya.defaultStandPosition();
    laksmana.defaultStandPosition();

    delay(1000);
    rama_wijaya.walk_to_a_certain_distance_before_calibrating_value(160);
    hanoman.walk_to_a_certain_distance_before_calibrating_value(160);

    // 010 (04 H-R1 Hanuman1F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::H_R1_HANUMAN1F);
    // delay(3000);

    // (429) O excellent ones. (2307) [Front Middle-Front]

    delay(429);
    hanoman.middleFront(); // takes 1200 ms

    // (2634) You are marvelous, (4267) [Front Point to front]

    delay(2634 - 429 - 1200);
    hanoman.downFront();    // takes 700 ms
    hanoman.pointToFront(); // takes 900 ms

    // (4523) you dare, (5540) [Front Low point to front]

    delay(4523 - 2634 - 700 - 900);
    hanoman.lower_pointToFront(); // takes 700 ms

    // (5654) and are able to come here. (7701) [Front point to front]

    delay(5654 - 4523 - 700);
    hanoman.pointToFront(); // takes 900 ms

    // (8317) The mountain of Resyamuka is impassible, (11393) [Back point to back, Front Down]

    delay(8317 - 5654 - 900);
    hanoman.downBack();    // takes 700 ms
    hanoman.pointToBack(); // takes 1400 ms
    hanoman.downFront();   // takes 700 ms

    // (11909) even God Maheswara is reluctant to come here. (15287) [Back hip, Front point to front]

    delay(11909 - 8317 - 700 - 1400 - 700);
    hanoman.downBack();     // takes 700 ms
    hanoman.onHipBack();    // takes 900 ms
    hanoman.pointToFront(); // takes 900 ms

    // (16118) What is your purpose (17263) [Front Middle-Front]

    delay(16118 - 11909 - 700 - 900 - 900);
    hanoman.middleFront(); // takes 1200 ms

    // (17435) both of you? (18222) [Front Point to front, Oscillate]

    delay(17435 - 16118 - 1200);
    hanoman.pointToFront(); // takes 900 ms
    for (int i = 0; i < 2; i++)
    {
        hanoman.directControl(3, 170, 100);
        hanoman.directControl(3, 180, 100);
    } // takes 200 ms per one loop

    // (18867) There are many things that are highly dangerous here. (22205) [Front Middle-Front, oscillate]

    delay(18867 - 17435 - 900 - 200 * 2);
    hanoman.middleFront(); // takes 1200 ms
    for (int i = 0; i < 3; i++)
    {
        hanoman.directControl(3, 125, 400);
        hanoman.directControl(3, 135, 400);
    } // takes 800 ms per one loop

    // (22702) In the caves there are demons and imps, (25657) [Front Down, Back low point to back]

    delay(22702 - 18867 - 1200 - 800 * 3);
    hanoman.downFront();      // takes 700 ms
    hanoman.lowPointToBack(); // takes 700 ms

    // (26238) and the path you come through (28084) [Back hip, Front point to front]

    delay(26238 - 22702 - 700 - 700);
    hanoman.onHipBack();    // takes 900 ms
    hanoman.pointToFront(); // takes 900 ms

    // (28299) is thick with undergrowth and difficult to pass. (31694) [Front Middle-Front]

    delay(28299 - 26238 - 900 - 900);
    hanoman.downFront();   // takes 700 ms
    hanoman.middleFront(); // takes 1200 ms

    // (32293) Nobody but you have come here. (34495) [Front point to front]

    delay(32293 - 28299);
    hanoman.downFront();    // takes 700 ms
    hanoman.pointToFront(); // takes 900 ms

    delay(34495 - 32293 - 700 - 900);
    hanoman.downFront(); // takes 700 ms

    // 011 (Rama1Hanuman-Rama dialogue_E)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::RAMA1HANUMAN_RAMA_DIALOGUE_E);
    // delay(3000);

    // (1182) O, holy man, (2568)

    delay(1182);
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (3137) my purpose is like this. (4616)

    delay(3137 - 1182 - 1200);
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.middleFront(); // takes 1200 ms

    // (5124) Come near and listen. (6268)

    delay(5124 - 3137 - 700 - 1200);
    rama_wijaya.downFront();          // takes 700 ms
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (6801) I will tell you also about the reason of my travel. (9659)

    delay(6801 - 5124 - 700 - 700);
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.pointToSelf(); // takes 900 ms

    // (10458) The wealthy king Dasaratha, (12011)

    delay(10458 - 6801 - 700 - 900);
    rama_wijaya.downFront();    // takes 700 ms
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (12555) well known throughout the world, (13997)

    delay(12555 - 10458 - 700 - 1200);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (14498) possessing all kinds of luxury, (16448)

    delay(14498 - 12555 - 700);
    rama_wijaya.downFront(); // takes 700 ms

    // (16881) has many sons. (17951)

    delay(16881 - 14498 - 700);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (18780) All my brothers (19721)

    delay(18780 - 16881 - 700);
    rama_wijaya.middleFront(); // takes 900 ms

    // (19907) are excellent and powerful. (21398)

    delay(19907 - 18780 - 900);
    rama_wijaya.downFront();          // takes 700 ms
    delay(1000);                      // takes 1000 ms
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (22406) I am the exception, (23923)

    // (24387) the unfortunate. (25346)

    delay(22406 - 19907 - 700 - 1000 - 700);
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.pointToSelf(); // takes 900 ms

    // (26076) His orders to go to the impassible forests, (28984)

    delay(26076 - 22406 - 700 - 900);
    rama_wijaya.downFront();    // takes 700 ms
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (29529) is the reason that we both are here. (31682)

    delay(29529 - 26076 - 700 - 1200);
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.pointToSelf(); // takes 900 ms

    // (32573) I have been to the hermitage of the sage Sutiksna. (35630)

    delay(32573 - 29529 - 700 - 900);
    rama_wijaya.downFront();    // takes 700 ms
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (36472) There I stayed a while to care for the hermitage. (39844)

    delay(36472 - 32573 - 700 - 1200);
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.middleFront(); // takes 1200 ms

    // (40679) My wife Sita went with me formerly. (43080)

    delay(40679 - 36472 - 700 - 1200);
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.pointToSelf(); // takes 900 ms

    // (43823) Then the wicked Rawana abducted her (46131)

    delay(43823 - 40679 - 700 - 900);
    rama_wijaya.downFront();          // takes 700 ms
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (46558) and fled away so quickly. (48371)

    delay(46558 - 43823 - 700 - 700);
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.middleFront(); // takes 1200 ms

    // (49361) I have come here to look for Sita. (51471)

    delay(49361 - 46558 - 700 - 1200);
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.pointToSelf(); // takes 900 ms

    // (52133) That is the reason why I go everywhere through the forests. (55252)

    delay(52133 - 49361 - 700 - 900);
    rama_wijaya.downFront();    // takes 700 ms
    rama_wijaya.pointToFront(); // takes 1200 ms

    delay(55252 - 52133 - 700 - 1200);
    rama_wijaya.downFront(); // takes 700 ms

    // 012 (05 H-R1 Hanuman2F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::H_R1_HANUMAN2F);
    // delay(3000);
    delay(630);

    /*O, Raghawa,*/
    hanoman.middleFront(); // 1830 (1200)
    hanoman.downFront();   // 2530 (700)

    /* I have been ordered to come here- */
    hanoman.pointToSelf(); // 3430 (900)
    delay(4094 - 3430);    // 4094 (664)

    /*The king of the monkeys Sugriwa gave me orders to look for you.*/
    hanoman.middleBack();     // 5494 (1400)
    delay(8162 - 5494 - 700); // 7462 (1968)

    /*The situation is like this.*/
    hanoman.downFront();          // 8162 (700)
    hanoman.lower_pointToFront(); // 8862 (700)
    hanoman.downBack();           // 9562 (700)
    delay(10514 - 9562 - 700);    // 9814 (252)

    /*There is a great monkey, unequalled in power called Bali.*/
    hanoman.downFront();   // 10514 (700)
    hanoman.middleFront(); // 11714 (1200)
    hanoman.onHipBack();   // 12614 (900)
    delay(15273 - 12614);  // 15273 (2659)

    /*Even God Aditya is inferior to him in power.*/
    hanoman.pointToFront();     // 16173 (900)
    for (int i = 0; i < 3; i++) // 18573 (2400)
    {
        hanoman.directControl(3, 170, 400);
        hanoman.directControl(3, 180, 400);
    }
    delay(19453 - 18573); // 19453 (880)

    /*He was savagely outrageous towards my master*/
    hanoman.downFront();   // 20153 (700)
    hanoman.pointToBack(); // 21553 (1400)
    delay(22688 - 21553);  // 22688 (1135)

    /*and insulted him.*/
    hanoman.lowPointToBack(); // 23388 (700)
    delay(24763 - 23388);     // 24763 (1375)

    /*Out of fear the monkey-king Bali,*/
    hanoman.downBack();    // 25463 (700)
    hanoman.middleFront(); // 26663 (1200)
    delay(27691 - 26663);  // 27691 (1028)

    /*my master went to the region of Malaya. */
    hanoman.downFront();   // 28391 (700)
    hanoman.pointToBack(); // 29791 (1400)
    delay(31040 - 29791);  // 31040 (1249)

    /*He ordered me to look for you, */
    hanoman.pointToSelf(); // 31940 (900)
    delay(33058 - 31940);  // 33058 (1118)

    /*as he intends to be friends with you,*/
    hanoman.middleBack(); // 34458 (1400)
    delay(35707 - 34458); // 35707 (1249)

    /*to stay and serve at your feet, */
    hanoman.pointToBack();      // 37107 (1400)
    delay(38619 - 37107 - 800); // 37819 (802)

    /*o, lord. */
    hanoman.directControl(3, 170, 400); // 38219 (400)
    hanoman.directControl(4, 95, 400);  // 38619 (400)
    delay(40258 - 38619);               // 40258 (1639)

    /*I suggest that you may grant him a favor*/
    hanoman.directControl(4, 80, 400);  // 40658 (400)
    hanoman.directControl(3, 150, 400); // 41058 (400)
    delay(42949 - 41058);               // 42949 (1891)

    /*and make him your ally,*/
    hanoman.downFront();          // 43649 (700)
    hanoman.lower_pointToFront(); // 44349 (700)
    delay(45225 - 44349);         // 45225 (876)

    /*because he is powerful,*/
    hanoman.directControl(3, 120, 400); // 45625 (400)
    delay(46965 - 45625);               // 46965 (1340)

    /*noble,*/
    hanoman.directControl(3, 100, 400); // 47365 (400)
    delay(47716 - 47365);               // 47716 (351)

    /*and goodhearted.*/
    hanoman.lower_pointToFront(); // 48416 (700)
    delay(49691 - 48416);         // 49691 (1275)

    /*Let him follow you and love you and carry out all your orders*/
    hanoman.pointToFront();     // 50591 (900)
    for (int i = 0; i < 4; i++) // 53791 (3200)
    {
        hanoman.directControl(3, 135, 400);
        hanoman.directControl(3, 180, 400);
    }
    delay(54515 - 53791); // 54515 (724)

    /*Let him take part as commander in the battlefield*/
    hanoman.lower_pointToFront(); // 55215 (700)
    for (int i = 0; i < 3; i++)   // 57615 (2400)
    {
        hanoman.directControl(3, 135, 400);
        hanoman.directControl(3, 90, 400);
    }
    delay(350); // 57965 (350)

    /*to kill Dasamukha.*/
    hanoman.directControl(1, 45, 400);
    hanoman.directControl(1, 0, 400);
    hanoman.directControl(1, 45, 400);
    hanoman.directControl(1, 0, 240);

    /*return to default position*/
    hanoman.downFront();
    hanoman.downBack();
    hanoman.onHipBack();

    SoundSystem::playMusicWayang();
    rama_wijaya.defaultStandPosition();
    hanoman.defaultStandPosition();

    setAllMOSFETtoHIGH();
    SoundSystem::playDialogFromACertainFolder(SoundSystem::INDICATOR_SOUND, SoundSystem::INDICATOR_SOUND_NUMBER::INDICATOR_FINISHED_SHOWING);
    delay(2000);
}

void Episodes::Episode_2()
{
    CalibratingFunction::wayangHand();

    setAllMOSFETtoLOW();

    SoundSystem::playMusicWayang();

    delay(1000);
    sugriwa.walk_to_a_certain_distance_before_calibrating_value(250);
    rama_wijaya.walk_to_a_certain_distance_before_calibrating_value(135);

    // 013 (06 S-R1 Sugriwa1F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::S_R1_SUGRIWA1F);
    // delay(3000);

    /*O, Raghawa!*/
    sugriwa.middleFront(); // 1200
    delay(1861 - 1200);

    /*The monkey king Bali is extremely powerful. */
    sugriwa.pointToFront(); // 900
    delay(5146 - 1861 - 900);

    /*There is no match for him in this threefold world.*/
    sugriwa.middleFront();             // 1200
    sugriwa.directControl(2, 80, 400); // 400
    sugriwa.directControl(2, 60, 400); // 400
    sugriwa.directControl(2, 80, 400); // 400
    sugriwa.directControl(2, 60, 400); // 400
    delay(9927 - 5146 - 1200 - 1600);

    /*It is not out of disdain that I talk to you like this, my lord,*/
    sugriwa.lower_pointToFront();       // 700
    sugriwa.directControl(1, 110, 400); // 400
    sugriwa.directControl(1, 90, 400);  // 400
    delay(12117 - 9927 - 700 - 800);
    sugriwa.downFront(); // 700
    delay(14600 - 12117 - 700);

    /*but it is because of out friendship*/
    sugriwa.pointToFront(); // 900
    delay(16806 - 14600 - 900 - 700);
    sugriwa.downFront(); // 700

    /* that I wish to explain the matter.*/
    sugriwa.pointToSelf(); // 900
    delay(19982 - 16806 - 900 - 500);

    /*Although Bali is famed for his power, */
    sugriwa.pointToBack(); // 1400
    sugriwa.downFront();   // 700
    delay(23332 - 19982 - 1400 - 700 + 500);

    /*he will certainly be killed by your irresistible arrows.*/
    sugriwa.pointToFront(); // 900
    sugriwa.downBack();     // 700
    sugriwa.onHipBack();    // 900
    delay(27727 - 23332 - 900 - 700 - 900);

    /*Well!*/
    sugriwa.downFront(); // 700
    delay(28800 - 27727 - 700);

    /*This is the story of how he obtained that extraordinary power in the world.*/
    sugriwa.middleFront(); // 1200
    delay(34590 - 28800 - 1200);

    /*It was a boon from a compassionate monk. */
    sugriwa.pointToBack(); // 1400
    delay(37961 - 34590 - 1400 - 500);

    /*He became more and more powerful */
    sugriwa.middleFront(); // 1400
    sugriwa.downBack();    // 700
    sugriwa.onHipBack();   // 900
    delay(40852 - 37961 - 1400 - 700 - 900 + 500);

    /*and finally irresistible.*/
    sugriwa.lower_pointToFront(); // 700
    delay(43472 - 40852 - 700);

    /*He is equal to the Sun,*/
    sugriwa.pointToFront(); // 900
    delay(45762 - 43472 - 900);

    /*whilst his opponents are Darkness. */
    sugriwa.lower_pointToFront();       // 700
    sugriwa.directControl(1, 110, 400); // 400
    sugriwa.directControl(1, 90, 400);  // 400
    sugriwa.directControl(1, 110, 400); // 400
    sugriwa.directControl(1, 90, 400);  // 400
    delay(49326 - 45762 - 700 - 1600 - 700);
    sugriwa.downFront(); // 700

    /*I am sad and afraid to see his power. */
    sugriwa.pointToSelf(); // 900
    delay(53635 - 49326 - 900);

    /*Formerly I had no idea that he could ever be killed.*/
    sugriwa.downBack();   // 700
    sugriwa.middleBack(); // 1400
    delay(58244 - 53635 - 700 - 1400 - 700);
    sugriwa.downFront();

    /*But now you, my lord, have come.*/
    sugriwa.middleFront(); // 1200
    sugriwa.downBack();    // 700
    sugriwa.onHipBack();   // 900
    delay(61669 - 58244 - 1200 - 700 - 900);

    /*You are unsurpassingly powerful,*/
    sugriwa.pointToFront();            // 900
    sugriwa.directControl(1, 20, 400); // 400
    sugriwa.directControl(1, 0, 400);  // 400
    sugriwa.directControl(1, 20, 400); // 400
    sugriwa.directControl(1, 0, 400);  // 400
    delay(64601 - 61669 - 900 - 1600);

    /*and I think,*/
    sugriwa.lower_pointToFront(); // 700
    delay(65888 - 64601 - 700);

    /*he will be killed by you. */
    sugriwa.pointToFront();            // 900
    sugriwa.directControl(1, 20, 400); // 400
    sugriwa.directControl(1, 0, 400);  // 400
    delay(68221 - 65888 - 900 - 800);

    /*I think we should go immediately to Kiskindha, */
    sugriwa.downFront();   // 700
    sugriwa.pointToSelf(); // 900
    delay(72351 - 68221 - 700 - 900 - (700));

    /* I will challenge him */
    sugriwa.pointToBack(); // 1400
    delay(73660 - 72351 - 700 - (600));
    sugriwa.downBack();

    /*and you will shoot him whilst we duel.*/
    sugriwa.downFront();    // 700
    sugriwa.pointToFront(); // 900
    delay(75908 - 73660 - 700 - 900 - (100));

    // /*return to default position*/
    sugriwa.defaultHandPosition();

    SoundSystem::playMusicWayang();
    sugriwa.defaultStandPosition();
    rama_wijaya.defaultStandPosition();

    delay(1000);
    sugriwa.walk_to_a_certain_distance_before_calibrating_value(235);
    // rama just hides
    // rama_wijaya.walk_to_a_certain_distance_before_calibrating_value(135);

    // 014 (07 Duel1 Sugriwa1F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::DUEL1_SUGRIWA1F);
    // delay(3000);

    // (315) BALI!! (1274) [Front point to front]
    delay(315);
    sugriwa.pointToFront(); // takes 900 ms

    // (1439) I challenge you to a duel, (3364) [Front low point to front]

    // (3779) come out here and fight me. (5454) [Back point to back, Front point to front]
    delay(1439 - 315 - 900);
    for (int i = 0; i < 6; i++)
    {
        sugriwa.directControl(1, 45, 400);
        sugriwa.directControl(1, 0, 400);
    } // takes 800 ms each loop

    // (5819) *roar* (7021) [Horizontal oscillation]
    delay(7021 - 1439 - 800 * 6);
    sugriwa.downFront(); // takes 700 ms

    SoundSystem::playMusicWayang();
    subali.walk_to_a_certain_distance_before_calibrating_value(160);

    // 015 (Subali round 1 rage)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SUBALI_ROUND_1_RAGE);
    // delay(3000);
    Serial.println("Current stack size: " + String(uxTaskGetStackHighWaterMark(NULL)));
    // (717) you DARE challenge me? (2349) [Front point to front]
    delay(717);
    subali.pointToFront(); // takes 900 ms

    // (2887) *roars in response* (3989) [Horizontal oscillation]
    delay(2887 - 717 - 900);
    for (int i = 0; i < 1; i++)
    {
        subali.directControl(3, 135, 400);
        subali.directControl(3, 180, 400);
    } // takes 800 ms each loop

    delay(3989 - 2887 - 800 * 1);
    subali.downFront(); // takes 700 ms

    SoundSystem::playMusicWayang();
    subali.walk_to_a_certain_distance_before_calibrating_value(170);

    Serial.println("Current stack size: " + String(uxTaskGetStackHighWaterMark(NULL)));

    xTaskCreate(sugriwaTaskFight1, "sugriwaTaskFight1", 1024, NULL, 1, NULL);
    xTaskCreate(subaliTaskFight1, "subaliTaskFight1", 1024, NULL, 1, NULL);

    // vTaskStartScheduler();

    vTaskSuspend(mainLoopTaskHandler);
    // sugriwa.pointToFront();       // takes 900 ms
    // subali.pointToFront();        // takes 900 ms
    // sugriwa.lower_pointToFront(); // takes 700 ms
    // subali.lower_pointToFront();  // takes 700 ms
    // sugriwa.downFront();          // takes 700 ms
    // subali.downFront();           // takes 700 ms
    // sugriwa.lower_pointToFront(); // takes 700 ms
    // subali.pointToFront();        // takes 900 ms

    // Sugriwa fight Subali 1st loss

    // delay(5000);

    sugriwa.walk_to_a_certain_distance_before_calibrating_value(170);
    subali.downFront(); // takes 700 ms
    subali.walk_to_a_certain_distance_before_calibrating_value(225);

    // 016 (08 Duel1 Sugriwa2F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::DUEL1_SUGRIWA2F);
    // delay(3000);

    // (594) I yield! (1353) [Front point to front, Back Middle-Front, Horizontal move back]
    delay(594);

    // (1653) I yield! (2412) [Horizontal move back]
    delay(1653 - 594 - 900);
    sugriwa.lower_pointToFront(); // takes 700 ms

    delay(2412 - 1653 - 700);
    sugriwa.downFront(); // takes 700 ms

    SoundSystem::playMusicWayang();
    sugriwa.defaultStandPosition();
    rama_wijaya.defaultStandPosition();
    subali.defaultStandPosition();

    delay(1000);
    sugriwa.walk_to_a_certain_distance_before_calibrating_value(250);
    rama_wijaya.walk_to_a_certain_distance_before_calibrating_value(135);

    // 017 (09 DuAft1 Sugriwa1F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::DUAFT1_SUGRIWA1F);
    // delay(3000);

    // (315) O, my lord, (1453) [Front low point to front]
    delay(315);
    sugriwa.lower_pointToFront(); // takes 700 ms

    // (1818) why did you not keep your promise, (3836) [Front Middle-Front]
    delay(1818 - 315 - 700);
    sugriwa.downFront();   // takes 700 ms
    sugriwa.middleFront(); // takes 1200 ms

    // (4323) you lied. (5024) [Front point to front]
    delay(4323 - 1818 - 700 - 1200);
    sugriwa.downFront();    // takes 700 ms
    sugriwa.pointToFront(); // takes 900 ms

    // (6005) Why did you just watch our fight without doing anything? (8968) [Front Middle-Front]
    delay(6005 - 4323 - 700 - 900);
    sugriwa.downFront();   // takes 700 ms
    sugriwa.middleFront(); // takes 1200 ms

    delay(8968 - 6005 - 700 - 1200);
    sugriwa.downFront(); // takes 700 ms

    // 018 (Rama1Sugriwa-Rama-Subali dialogue)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::RAMA1SUGRIWA_RAMA_SUBALI_DIALOGUE);
    // delay(3000);

    // (1231) This is the reason, why I stood idle, (3242)

    delay(1231);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (3917) as if I do not care. (5229)

    delay(3917 - 1231 - 700);
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.middleFront(); // takes 1200 ms

    // (5928) When you were fighting with Bali (7333)

    delay(5928 - 3917 - 700 - 1200);
    rama_wijaya.downFront();          // takes 700 ms
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (7580) I saw you and Bali look alike. (9597)

    delay(7580 - 5928 - 700 - 700);
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.middleFront(); // takes 1200 ms

    // (10501) I could not distinguish you from him, (12264)

    delay(10501 - 7580 - 700 - 1200);
    rama_wijaya.downFront();    // takes 700 ms
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (12747) and this became more and more confused. (15628)

    delay(12747 - 10501 - 700 - 1200);
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.onHipBack();   // takes 900 ms
    rama_wijaya.middleFront(); // takes 1200 ms

    // (16683) That is the reason I appeared to forget my promise to my friend. (19857)

    delay(16683 - 12747 - 700 - 900 - 1200);
    rama_wijaya.downFront();    // takes 700 ms
    rama_wijaya.downBack();     // takes 700 ms
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (20686) Now, do this! (21825)

    delay(20686 - 16683 - 700 - 700 - 1200);
    rama_wijaya.downFront(); // takes 700 ms

    // (22549) Wear leaves around your body as an identification. (25556)

    delay(22549 - 20686 - 700);
    rama_wijaya.middleFront(); // takes 1200 ms
    for (int i = 0; i < 3; i++)
    {
        rama_wijaya.directControl(1, 30, 400);
        rama_wijaya.directControl(1, 0, 400);
    } // takes 800 ms each loop

    // (26460) After you have them on, (27790)

    delay(26460 - 22549 - 1200 - 800 * 3);
    rama_wijaya.downFront();          // takes 700 ms
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (28136) fight again, (28811)

    delay(28136 - 26460 - 700 - 700);
    rama_wijaya.directControl(1, 0, 400); // takes 400 ms

    // (29195) do not be afraid. (30104)

    delay(29195 - 28136 - 400);
    rama_wijaya.directControl(1, 90, 400); // takes 400 ms

    // (30792) For sure Bali will be killed (32301)

    delay(30792 - 29195 - 400);
    rama_wijaya.directControl(1, 0, 400); // takes 400 ms

    // (32548) and you will not be hit. (33693)

    delay(32548 - 30792 - 400);
    rama_wijaya.directControl(1, 90, 400); // takes 400 ms

    delay(33693 - 32548 - 400);
    rama_wijaya.downFront(); // takes 700 ms
    rama_wijaya.onHipBack(); // takes 900 ms

    SoundSystem::playMusicWayang();
    rama_wijaya.defaultHandPosition();

    rama_wijaya.defaultStandPosition();
    sugriwa.defaultStandPosition();
    delay(500);

    sugriwa.walk_to_a_certain_distance_before_calibrating_value(235);
    // rama hides
    // rama_wijaya.walk_to_a_certain_distance_before_calibrating_value(135);

    // 019 (10 Duel2 Sugriwa1F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::DUEL2_SUGRIWA1F);
    // delay(3000);

    // (565) BALI!! (1281)
    delay(565);
    sugriwa.pointToFront(); // takes 900 ms

    // (1510) This is not (2312)
    delay(1510 - 565 - 900);
    sugriwa.lower_pointToFront(); // takes 700 ms

    // (2519) over, (3214)
    delay(2519 - 1510 - 700);
    sugriwa.pointToFront(); // takes 900 ms

    // (3528) come out here and fight me. (5275)

    // (5690) *roar* (7365)
    delay(3528 - 2519 - 900);
    for (int i = 0; i < 4; i++)
    {
        sugriwa.directControl(1, 45, 400);
        sugriwa.directControl(1, 0, 400);
    } // takes 800 ms each loop

    delay(7365 - 3528 - 800 * 4);
    sugriwa.downFront(); // takes 700 ms

    // 020 (Subali round 2 rage)
    SoundSystem::playMusicWayang();
    subali.walk_to_a_certain_distance_before_calibrating_value(160);

    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SUBALI_ROUND_2_RAGE);
    // delay(3000);

    // (1046) You dare challenge me again (2827)
    delay(1046);
    subali.pointToFront(); // takes 900 ms

    // (3267) even though you already lost once? (5176)
    delay(3267 - 1046 - 900);
    subali.lower_pointToFront(); // takes 700 ms

    // (5659) How pathetic (6440)
    delay(5659 - 3267 - 700);
    subali.pointToFront(); // takes 900 ms

    // (6974) *roar* (7858)
    delay(6974 - 5659 - 900);
    for (int i = 0; i < 1; i++)
    {
        subali.directControl(3, 135, 400);
        subali.directControl(3, 180, 400);
    } // takes 800 ms each loop

    delay(7858 - 6974 - 800 * 1);
    subali.downFront(); // takes 700 ms

    SoundSystem::playMusicWayang();
    subali.walk_to_a_certain_distance_before_calibrating_value(170);

    xTaskCreate(sugriwaTaskFight1, "sugriwaTaskFight1", 1024, NULL, 1, NULL);
    xTaskCreate(subaliTaskFight1, "subaliTaskFight1", 1024, NULL, 1, NULL);

    vTaskSuspend(mainLoopTaskHandler);

    // sugriwa.pointToFront();       // takes 900 ms
    // subali.pointToFront();        // takes 900 ms
    // sugriwa.lower_pointToFront(); // takes 700 ms
    // subali.lower_pointToFront();  // takes 700 ms
    // sugriwa.downFront();          // takes 700 ms
    // subali.downFront();           // takes 700 ms
    // sugriwa.lower_pointToFront(); // takes 700 ms
    // subali.pointToFront();        // takes 900 ms

    // Sugriwa fight Subali 1st loss
    // xTaskCreate(sugriwaTaskFight1, "sugriwaTaskFight1", 128, NULL, 1, NULL);
    // xTaskCreate(subaliTaskFight1, "subaliTaskFight1", 128, NULL, 1, NULL);
    // delay(5000);

    sugriwa.defaultStandPosition();
    subali.downFront(); // takes 700 ms
    subali.walk_to_a_certain_distance_before_calibrating_value(225);
    rama_wijaya.walk_to_a_certain_distance_before_calibrating_value(225);

    xTaskCreate(subaliTaskFight2, "subaliTaskFight2", 1024, NULL, 1, NULL);
    xTaskCreate(ramaTaskFight1, "ramaTaskFight1", 1024, NULL, 1, NULL);

    vTaskSuspend(mainLoopTaskHandler);
    // rama_wijaya.pointToFront();       // takes 900 ms
    // subali.pointToFront();            // takes 900 ms
    // rama_wijaya.lower_pointToFront(); // takes 700 ms
    // subali.lower_pointToFront();      // takes 700 ms
    // rama_wijaya.downFront();          // takes 700 ms
    // subali.downFront();               // takes 700 ms
    // rama_wijaya.pointToFront();       // takes 900 ms
    // subali.lower_pointToFront();      // takes 700 ms
    subali.walk_to_a_certain_distance_before_calibrating_value(170);
    subali.downFront(); // takes 700 ms
    rama_wijaya.downFront();

    // 021 (Subali bacotin rama_E)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SUBALI_BACOTIN_RAMA_E);
    // delay(3000);

    // (897) Ah Rama, (1806)
    delay(897);
    subali.pointToFront(); // takes 900 ms

    // (2460) wicked, debased and silly. (4237)
    delay(2460 - 897 - 900);
    subali.lower_pointToFront(); // takes 700 ms

    // (4757) You look peaceful, but you are very mean. (6741)
    delay(4757 - 2460 - 700);
    subali.pointToFront(); // takes 900 ms

    // (7350) May all kinds of sins befall you, (9391)
    delay(7350 - 4757 - 900);
    subali.downFront();   // takes 700 ms
    subali.middleFront(); // takes 1200 ms

    // (9968) because you shot at one who only fights with his brother (13119)
    delay(9968 - 7350 - 700 - 1200);
    subali.pointToFront(); // takes 900 ms

    // (13517) and does nothing to you. (14597)
    delay(13517 - 9968 - 900);
    subali.downFront(); // takes 700 ms

    // (15272) O, you are wicked beyond limits. (17006)
    delay(15272 - 13517 - 700);
    subali.lower_pointToFront(); // takes 700 ms

    // (17710) You do not uphold the good name of your father. (19619)
    delay(17710 - 15272 - 700);
    subali.pointToFront(); // takes 900 ms

    // (20589) You know I have not done anything wrong. (22348)
    delay(20589 - 17710 - 900 - 700);
    subali.downFront();   // takes 700 ms
    subali.pointToSelf(); // takes 900 ms

    // (22972) You are extremely depraved, (24108)
    delay(22972 - 20589 - 900 - 700);
    subali.downFront();          // takes 700 ms
    subali.lower_pointToFront(); // takes 700 ms

    // (24599) your mind is corrupt. (25466)
    delay(24599 - 22972 - 700);
    subali.pointToFront(); // takes 900 ms

    // (26316) If you follow the ascetics, (27533)
    delay(26316 - 24599 - 900);
    subali.lower_pointToFront(); // takes 700 ms

    // (27776) then the main dharmma is to be a teacher (29933)
    delay(27776 - 26316 - 700);
    subali.pointToFront(); // takes 900 ms

    // (30339) for the people inferior to him, (31757)
    delay(30339 - 27776 - 900);
    subali.downFront(); // takes 700 ms

    // (32111) to be a cure for discord, (33298)
    delay(32111 - 30339 - 700);
    subali.middleFront(); // takes 1200 ms

    // (33828) a mediator for brothers in disagreement. (35929)
    delay(33828 - 32111 - 1200);
    subali.lower_pointToFront(); // takes 700 ms

    // (36386) He should best be a cure for me who has done wrong. (39440)
    delay(36386 - 33828 - 700);
    subali.pointToFront(); // takes 900 ms

    // (40302) Besides, (40823)
    delay(40302 - 36386 - 900 - 100);
    subali.lower_pointToFront(); // takes 700 ms

    // (40998) you take the wrong side. (42092)
    delay(40998 - 40302 - 600);
    subali.pointToFront(); // takes 900 ms

    // (42613) That is foolish. (43501)
    delay(42613 - 40998 - 900);
    subali.downFront(); // takes 700 ms

    // (44347) You think you have the judicious insight, (46367)
    delay(44347 - 42613 - 700);
    subali.middleFront(); // takes 1200 ms

    // (47105) but (47212)

    // (47584) in fact you are foolish. (48908)
    delay(47105 - 44347 - 1200);
    subali.pointToFront(); // takes 900 ms

    // (48510) You think it is good for you, (51188)
    delay(48510 - 47105 - 900);
    subali.downFront(); // takes 700 ms

    // (51654) now (51931)

    // (52281) that I am dead. (53311)
    delay(51654 - 48510 - 700);
    subali.pointToSelf(); // takes 900 ms

    // (54118) You are wrong, (54946)
    delay(54118 - 51654 - 900 - 200);
    subali.downFront();          // takes 700 ms
    subali.lower_pointToFront(); // takes 700 ms

    // (55395) because your act (56082)
    delay(55395 - 54118 - 700 - 500);
    subali.pointToFront(); // takes 900 ms

    // (56638) is an act of murder. (57923)
    delay(56638 - 55395 - 900);
    subali.lower_pointToFront(); // takes 700 ms

    // (58602) And you were known formerly to be of good conduct, (60618)
    delay(58602 - 56638 - 700);
    subali.pointToFront(); // takes 900 ms

    // (61455) to be a protector of the world (62783)
    delay(61455 - 58602 - 900);
    subali.middleBack(); // 1400

    // (63560) and to care for the people. (64876)
    delay(63560 - 61455 - 1400 - 700);
    subali.downFront();   // 700
    subali.pointToBack(); // 1400

    // (65427) Your merits and cancelled out, (66926)
    delay(65427 - 63560 - 1400);
    subali.downBack();           // 700
    subali.lower_pointToFront(); // 700

    // (67558) because of killing a monkey. (68591)
    delay(67558 - 65427 - 700 - 700);
    subali.pointToFront(); // 900

    // (69334) Are you not ashamed in front of your younger brother? (71461)
    delay(69334 - 67558 - 900);
    subali.downFront();      // 700
    subali.lowPointToBack(); // 700

    // (72614) Even though I am in fact fighting with my brother, (74899)
    delay(72614 - 69334 - 700 - 700);
    subali.pointToSelf(); // 900

    // (75082) in the future we might come together again, (77064)
    delay(75082 - 72614 - 900);
    subali.downBack();   // 700
    subali.middleBack(); // 1400

    // (77649) you love Sugriwa, a monkey of improper and debased nature. (80792)
    delay(77649 - 75082 - 700 - 1400);
    subali.downBack();     // 700
    subali.downFront();    // 700
    subali.pointToFront(); // 900
    delay(500);

    subali.downFront(); // 700

    // 022 (Rama2Sugriwa-Rama-Subali dialogue_E)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::RAMA2SUGRIWA_RAMA_SUBALI_DIALOGUE_E);
    // delay(3000);

    // (1085) Hey, monkey, (1828)

    delay(1085);
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (2533) you regard yourself as smart. (4230)

    delay(2533 - 1085 - 1200);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (4954) I do not sin by killing you. (6440)

    delay(4954 - 2533 - 700);
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.middleFront(); // takes 1200 ms

    // (7213) The nature of a ksatriya is my guidance. (9852)

    delay(7213 - 4954 - 700 - 1200);
    for (int i = 0; i < 4; i++)
    {
        rama_wijaya.directControl(1, 10, 400);
        rama_wijaya.directControl(1, 0, 400);
    } // takes 800 ms each loop

    // (10476) It is not murder to kill any animal. (12641)

    delay(10476 - 7213 - 800 * 4);
    rama_wijaya.downFront();    // takes 700 ms
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (13504) All the ksatriyas in the past I take as an example, (16826)

    delay(13504 - 10476 - 700 - 1200);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (17429) they did not sin. (18360)

    delay(17429 - 13504 - 700);
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (19273) Furthermore, (19918)

    // (20205) in fact (20649)

    delay(19273 - 17429 - 1200);
    rama_wijaya.middleFront(); // takes 1200 ms

    // (21161) animals may be killed in any way, (23279)

    delay(21161 - 19273 - 1200);
    rama_wijaya.directControl(1, 30, 400); // takes 400 ms

    // (23856) they can be trapped (24655)

    delay(23856 - 21161 - 400);
    rama_wijaya.directControl(1, 0, 400); // takes 400 ms

    // (24958) with pitfalls, (25722)

    delay(24958 - 23856 - 400);
    rama_wijaya.directControl(1, 30, 400); // takes 400 ms

    // (25996) snares (26465)

    delay(25996 - 24958 - 400);
    rama_wijaya.directControl(1, 0, 400); // takes 400 ms

    // (26651) and mantraps. (27473)

    delay(26651 - 25996 - 400);
    rama_wijaya.directControl(1, 30, 400); // takes 400 ms

    // (28396) All the game in the vast forest whether it is good (31014)

    delay(28396 - 26651 - 400);
    rama_wijaya.downFront(); // takes 700 ms
    // rama_wijaya.middleFrontBack(); // takes 1200 ms

    // (31411) or bad may be killed. (32727)

    delay(31411 - 28396 - 700);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (33649) But if you say you are not an animal but a human being, (36732)

    delay(33649 - 31411 - 700);
    rama_wijaya.downBack();  // takes 700 ms
    rama_wijaya.onHipBack(); // takes 900 ms

    // (36941) then follow my conduct (37983)

    // (38380) as a human being. (39311)

    delay(36941 - 33649 - 700 - 900);
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.pointToSelf(); // takes 900 ms

    // (39931) Even then I would not have sinned in any way, (42702)

    delay(39931 - 36941 - 700 - 900);
    rama_wijaya.downFront();    // takes 700 ms
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (43127) because I have killed (44174)

    // (44391) an adulterous man. (45589)

    delay(43127 - 39931 - 700 - 1200);
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.pointToSelf(); // takes 900 ms

    // (46589) I have heard about your conducts. (48187)

    delay(46589 - 43127 - 700 - 900);
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.middleFront(); // takes 1200 ms

    // (48650) You drove away Sugriwa and you stole his wife Tara. (51820)

    delay(48650 - 46589 - 700 - 1200);
    for (int i = 0; i < 4; i++)
    {
        rama_wijaya.directControl(1, 30, 400);
        rama_wijaya.directControl(1, 0, 400);
    } // takes 800 ms each loop

    // (52482) O, you will always be condemned by the world. (55499)

    delay(52482 - 48650 - 800 * 4);
    rama_wijaya.downFront();    // takes 700 ms
    rama_wijaya.pointToFront(); // takes 1200 ms

    delay(55499 - 52482 - 700 - 1200);
    delay(1000);
    rama_wijaya.downFront(); // takes 700 ms

    // 023 (Subali tobat_E)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SUBALI_TOBAT_E);
    // delay(3000);

    /*(944) O, Raghawa (1806) */
    delay(944);
    subali.pointToFront(); // 900

    /*(2237) how noble you are, (3231)  */
    delay(2237 - 944 - 900);
    subali.lower_pointToFront(); // 700

    /*(3696) that you kill any evildoer who commits evil in the world. (7019)  */
    delay(3696 - 2237 - 700);
    subali.pointToFront();             // 900
    subali.directControl(3, 160, 400); // 400
    subali.directControl(3, 180, 400); // 400
    subali.directControl(3, 160, 400); // 400
    subali.directControl(3, 180, 400); // 400

    /*(8037) But (8277)

    (8772) may your benevolence be without limit, (10861)  */
    delay(8037 - 3696 - 900 - 1600);
    subali.downFront();      // 700
    subali.lowPointToBack(); // 700

    /*(11784) may you save the life of my child. (13305) */
    delay(11784 - 8037 - 700 - 700);
    subali.pointToSelf(); // 900

    /*(14185) As for you my brother, (15197)  */
    delay(14185 - 11784 - 900);
    subali.downFront();          // 700
    subali.lower_pointToFront(); // 700

    /*(16024) come near! Sugriwa, (17258) */
    delay(16024 - 14185 - 700 - 700);
    subali.pointToFront(); // 900

    /*(17879) I ask leave to die. (19034)  */
    delay(17879 - 16024 - 900);
    subali.downFront(); // 700

    /*(19799) In the future incarnations, (21099)  */
    delay(19799 - 17879 - 700 - (700));
    subali.downBack();     // 700
    subali.pointToFront(); // 900

    /*(21567) by the grace of the gods, (22585)  */
    delay(21567 - 19799 - (700) - 900);
    subali.downFront();   // 700
    subali.pointToBack(); // 1400

    /*(23000) may we be brothers again. (24317) */
    delay(23000 - 21567 - 1400);
    subali.pointToSelf(); // 900

    /*(25242) Let us in the future be of the same abode, (27529)  */
    delay(25242 - 23000 - 900);
    subali.downFront();    // 700
    subali.pointToFront(); // 900

    /*(28206) whether it will be a mountain of a tree with ripe fruits and plenty of honey, (32653)  */
    delay(28206 - 25242 - 700 - 900);
    subali.downBack();           // 700
    subali.lower_pointToFront(); // 700

    /*(33192) never exhausted to be enjoyed forever. (35288) */
    delay(33192 - 28206 - 700 - 700);
    subali.pointToFront(); // 900

    /*(35997) My conduct was very wrong, (37168)  */
    delay(35997 - 33192 - 900 - (700));
    subali.downFront();   // 700
    subali.pointToSelf(); // 900

    /*(38504) but the reason was not evil. (39811)  */
    delay(38504 - 35997 - 900 - (700));
    subali.downFront();    // 700
    subali.pointToFront(); // 900

    /*(40635) It was the trick of the gods (41996) */
    delay(40635 - 38504 - 900);
    subali.middleBack(); // 1400

    /*(42203) that we, (42691)  */
    /*(42960) brothers are fighting each other. (44325)  */
    delay(42203 - 40635 - 1400);
    subali.downFront();   // 700
    subali.pointToSelf(); // 900

    /*(44960) Let it be so! (45709)  */
    delay(44960 - 42203 - 700 - 900 - (700));
    subali.downFront();          // 700
    subali.lower_pointToFront(); // 700

    /*(46286) Because it is God’s will. (47695) */
    delay(46286 - 44960 - 700);
    subali.pointToBack(); // 1400

    /*(48122) Besides (48641)

    (48826) the powerful god Acintya (50217)  */
    delay(48122 - 46286 - 1400);
    subali.lowPointToBack(); // 700

    /*(50488) does not permit us (51463)  */
    delay(50488 - 48122 - 700);
    subali.downFront(); // 700

    /*(51598) to live together in happiness. (52823)*/
    delay(51598 - 50488 - 700);
    subali.downBack();           // 700
    subali.lower_pointToFront(); // 700

    /*(53490) So I will go ahead (54707) */
    delay(53490 - 51598 - 700 - 700 - (100));
    subali.downFront();   // 700
    subali.pointToSelf(); // 900

    /*(55062) to find heavenly bliss, (56509)  */
    delay(55062 - 53490 - 700 - 900 + 100);
    subali.downFront();          // 700
    subali.lower_pointToFront(); // 700

    /*(56757) to follow the decree of the gods. (58567) */
    delay(56757 - 55062 - 700 - 700);
    subali.pointToFront(); // 900
    delay(58567 - 56757 - 900);
    delay(2000);

    /*lower arms*/
    subali.downFront();

    SoundSystem::playMusicWayang();
    rama_wijaya.defaultHandPosition();
    subali.defaultHandPosition();
    sugriwa.defaultHandPosition();

    rama_wijaya.defaultStandPosition();
    sugriwa.defaultStandPosition();
    subali.defaultStandPosition();

    delay(1000);
    sugriwa.walk_to_a_certain_distance_before_calibrating_value(270);
    rama_wijaya.walk_to_a_certain_distance_before_calibrating_value(150);

    // 024 (11 S-R2 Sugriwa1F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::S_R2_SUGRIWA1F);
    // delay(3000);

    /*Ah, my lord, */
    delay(358);
    sugriwa.pointToFront(); // 900
    delay(1746 - 358 - 900);

    /*how great and unlimited is your mercy towards us,*/
    sugriwa.lower_pointToFront();       // 700
    sugriwa.directControl(1, 110, 400); // 400
    sugriwa.directControl(1, 90, 400);  // 400
    sugriwa.directControl(1, 110, 400); // 400
    sugriwa.directControl(1, 90, 400);  // 400
    sugriwa.downFront();                // 700
    delay(5217 - 1746 - 700 - 1600 - 700);

    /*but we cannot return it right away. */
    sugriwa.pointToSelf(); // 900
    delay(7794 - 5217 - 900);

    /*Let it be delayed for a while,*/
    sugriwa.pointToBack(); // 1400
    delay(10242 - 7794 - 1400 - 700);
    sugriwa.downBack(); // 700

    /*because the rainy season has come,*/
    sugriwa.downFront();    // 700
    sugriwa.pointToFront(); // 900
    delay(12876 - 10242 - 700 - 900);

    /*and the monkeys are troubled by the cold. */
    sugriwa.lower_pointToFront(); // 700
    sugriwa.onHipBack();          // 900
    delay(15853 - 12876 - 700 - 900);

    /*with the dry season*/
    sugriwa.pointToFront();             // 900
    delay(17262 - 15853 - 900 - (500)); // slightly faster to avoid delay -
    sugriwa.downFront();                // 700

    /*we will search for Sita and destroy the enemy.*/
    sugriwa.pointToSelf(); // 900
    sugriwa.pointToBack(); // 1400
    delay(19925 - 17262 - 900 - 1400);
    delay(2000);

    /*return to default position*/
    sugriwa.mathentengA();

    // 025 (Rama1Sugriwa-Rama dialogue 2_E)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::RAMA1SUGRIWA_RAMA_DIALOGUE_2_E);
    // delay(3000);

    // (892) Very well, (1742)
    delay(892);
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (2387) I shall wait for you and your troops (4446)
    delay(2387 - 892 - 1200);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (4700) on the mountain of Malyawan. (6128)
    delay(4700 - 2387 - 700);
    rama_wijaya.pointToFront(); // takes 1200 ms

    delay(6128 - 4700 - 1200);
    rama_wijaya.downFront(); // takes 700 ms

    SoundSystem::playMusicWayang();
    rama_wijaya.defaultStandPosition();
    sugriwa.defaultStandPosition();

    delay(1000);
    rama_wijaya.walk_to_a_certain_distance_before_calibrating_value(200);

    // 026 (Rama Sadboi_E)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::RAMA_SADBOI_E);
    // delay(3000);

    // (1769) Ah, the breeze is blowing from north to the south, (4908)
    delay(1769);
    rama_wijaya.middleFront(); // takes 1200 ms
    for (int i = 0; i < 3; i++)
    {
        rama_wijaya.directControl(1, 45, 400);
        rama_wijaya.directControl(1, 0, 400);
    } // takes 800 ms each loop

    // (5399) taking along the fragrance (6925)
    delay(5399 - 1769 - 1200 - (800 * 3));
    rama_wijaya.downFront();          // takes 700 ms
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (7077) of the lovely kadamba flowers. (9089)
    delay(7077 - 5399 - 700 - 700);
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (9975) Even the passionless in the forests would truly be thrown into confusion. (14309)
    delay(9975 - 7077 - 1200);
    for (int i = 0; i < 6; i++)
    {
        rama_wijaya.directControl(1, 45, 400);
        rama_wijaya.directControl(1, 0, 400);
    } // takes 800 ms each loop

    // (15092) Sad is the heart of the pessimist (17360)
    delay(15092 - 9975 - (800 * 6));
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.middleFront(); // takes 1200 ms

    // (17731) who sees only darkness all around, (20081)

    // (20761) darkness (21287)

    // (21707) what in no way will lift. (23406)
    delay(17731 - 15092 - 700 - 1200);
    for (int i = 0; i < 8; i++)
    {
        rama_wijaya.directControl(1, 45, 400);
        rama_wijaya.directControl(1, 0, 400);
    } // takes 800 ms each loop

    // (24147) It is like the prison (25229)
    delay(24147 - 17731 - (800 * 8));
    rama_wijaya.downFront(); // takes 700 ms

    // (25538) of the god of love. (26637)
    delay(25538 - 24147 - 700);
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (27156) It is tenuous, (28020)
    delay(27156 - 25538 - 1200);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (28495) hard to grasp, (29288)
    delay(28495 - 27156 - 700);
    rama_wijaya.downFront(); // takes 700 ms

    // (29690) but it exists. (30676)
    delay(29690 - 28495 - 700);
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (31506) Besides (32107)
    delay(31506 - 29690 - 1200);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (32439) the lightning is tormenting my dazzled eyes. (35124)
    delay(32439 - 31506 - 700);
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (35769) I am sad (36396)

    // (36825) and startled by its flashes. (38573)
    delay(35769 - 32439 - 1200);
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.pointToSelf(); // takes 900 ms

    // (39506) Just one flash (40389)
    delay(39506 - 35769 - 700 - 900);
    rama_wijaya.downFront(); // takes 700 ms

    // (40570) and quickly it disappears. (42189)
    delay(40570 - 39506 - 700);
    rama_wijaya.middleFront(); // takes 1200 ms

    // (42867) O, it is highly irritating and agonizing. (46267)
    delay(42867 - 40570 - 1200);
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.pointToSelf(); // takes 900 ms

    // (47258) Janaki (47935)

    // (48339) how unhappy you must be. (49884)
    delay(47258 - 42867 - 700 - 900);
    rama_wijaya.downFront();    // takes 700 ms
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (50436) You were never separated from me for long. (52745)
    delay(50436 - 47258 - 700 - 1200);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (53217) Ah! (53537)

    // (53945) How cruel is Fate (55058)
    delay(53217 - 50436 - 700);
    rama_wijaya.downFront();    // takes 700 ms
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (55538) who allows you to be separated violently from me. (58352)
    delay(55538 - 53217 - 700 - 1200);
    for (int i = 0; i < 4; i++)
    {
        rama_wijaya.directControl(1, 45, 400);
        rama_wijaya.directControl(1, 0, 400);
    } // takes 800 ms each loop

    // (59252) My longing is terrible, (60621)

    // (61144) beyond description. (62319)
    delay(59252 - 55538 - (800 * 4));
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.pointToSelf(); // takes 900 ms

    // (62883) My eyes ache severely when I look into the sky (66010)
    delay(62883 - 59252 - 700 - 900);
    for (int i = 0; i < 4; i++)
    {
        rama_wijaya.directControl(1, 52, 400);
        rama_wijaya.directControl(1, 22, 400);
    } // takes 800 ms each loop

    // (66223) or to the woods. (67126)
    delay(66223 - 62883 - (800 * 4));
    rama_wijaya.downFront(); // takes 700 ms

    // (67651) All gives rise to memories. (69594)
    delay(67651 - 66223 - 700);
    rama_wijaya.middleFront(); // takes 1200 ms

    // (70409) I wish (71045)
    delay(70409 - 67651 - 1200);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (71288) that the night would be brief, (72636)
    delay(71288 - 70409 - 700);
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (72975) and it always daytime be. (74274)
    delay(72975 - 71288 - 1200);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (75254) Ah, (75645)
    delay(75254 - 72975 - 700);
    rama_wijaya.downFront(); // takes 700 ms

    // (76143) I am weak (76727)
    delay(76143 - 75254 - 700);
    rama_wijaya.pointToSelf(); // takes 900 ms

    // (77456) and in grief, (78216)
    delay(77456 - 76143 - 900);
    rama_wijaya.downFront(); // takes 700 ms

    // (78528) at night the memory of you is haunting me. (80847)
    delay(78528 - 77456 - 700);
    rama_wijaya.middleFront(); // takes 1200 ms

    // (82046) O, I wake up at night (83626)

    // (84029) seized by the agony of love, (85763)

    // (86311) kept awake I could not fall in slumber, (88826)
    delay(82046 - 78528 - 1200);
    for (int i = 0; i < 9; i++)
    {
        rama_wijaya.directControl(1, 45, 400);
        rama_wijaya.directControl(1, 0, 400);
    } // takes 800 ms each loop

    // (89380) I have lost my taste and feeling (91336)

    // (91647) because of my suffering,
    delay(89380 - 82046 - (800 * 9));
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.pointToSelf(); // takes 900 ms

    // (93430) Ah there is no cure for the pangs of yearning. (96438)
    delay(93430 - 89380 - 700 - 900);
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.middleFront(); // takes 1200 ms

    delay(96438 - 93430 - 700 - 1200);
    rama_wijaya.downFront(); // takes 700 ms

    SoundSystem::playMusicWayang();
    laksmana.walk_to_a_certain_distance_before_calibrating_value(200);

    // 027 (Rama telling laksmana to bacot sugriwa_E)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::RAMA_TELLING_LAKSMANA_BACOT_SUGRIWA_E);
    // delay(3000);

    // (1038) My brother, (1618)
    delay(1038);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (1993) look at the sky! (2992)
    delay(1993 - 1038 - 700);
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (3528) Beautiful swans are flying heading for a lake that they sound so happy. (7233)
    delay(3528 - 1993 - 1200);
    for (int i = 0; i < 5; i++)
    {
        rama_wijaya.directControl(1, 45, 400);
        rama_wijaya.directControl(1, 0, 400);
    } // takes 800 ms each loop

    // (7947) Clearly the dry season has come, (9874)
    delay(7947 - 3528 - (800 * 5));
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.middleFront(); // takes 1200 ms

    // (10448) the time agreed upon. (11703)
    delay(10448 - 7947 - 700 - 1200);
    rama_wijaya.directControl(1, 45, 400); // takes 400 ms
    rama_wijaya.directControl(1, 0, 400);  // takes 400 ms
    rama_wijaya.downFront();               // takes 700 ms

    // (12142) Ah! The king of the apes has lied, (14017)
    delay(12142 - 10448 - 400 - 400 - 700);
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (14577) he has not held to his promise. (16268)
    delay(14577 - 12142 - 1200);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (16826) He dares to make an offence, (18226)
    delay(16826 - 14577 - 700);
    rama_wijaya.directControl(1, 130, 400); // takes 400 ms
    rama_wijaya.directControl(1, 100, 400); // takes 400 ms
    rama_wijaya.directControl(1, 130, 400); // takes 400 ms
    rama_wijaya.directControl(1, 100, 400); // takes 400 ms

    // (18536) that ape is negligent. (19817)
    delay(18536 - 16826 - 400 - 400 - 400 - 400);
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (20383) He does not come, (21384)
    delay(20383 - 18536 - 1200);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (21663) his promise formerly is a gross deception. (23762)
    delay(21663 - 20383 - 700);
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.middleFront(); // takes 1200 ms

    // (24442) He has enjoyed luxury all the time, (26515)
    delay(24442 - 21663 - 700 - 1200);
    for (int i = 0; i < 2; i++)
    {
        rama_wijaya.directControl(1, 45, 500);
        rama_wijaya.directControl(1, 0, 500);
    } // takes 1000 ms each loop

    // (26837) without looking at the sky from time to time (29022)
    delay(26837 - 24442 - (1000 * 2));
    rama_wijaya.downFront();    // takes 700 ms
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (29324) to see whether it has cleared or not. (31262)
    delay(29324 - 26837 - 700 - 1200);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (31908) It is clear now, (32774)

    // (33000) with stars even. (34102)
    delay(31908 - 29324 - 700);
    rama_wijaya.downBack();     // takes 700 ms
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (34519) Ah! He is really blind not to see them. (36798)
    delay(34519 - 31908 - 700 - 1200);
    rama_wijaya.middleBack();   // takes 1200 ms
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (37542) He is preoccupied with the reunion with his wife and children. (40890)
    delay(37542 - 34519 - 1200 - 1200);
    for (int i = 0; i < 4; i++)
    {
        rama_wijaya.directControl(3, 135, 400);
        rama_wijaya.directControl(3, 180, 400);
    } // takes 800 ms each loop
    rama_wijaya.downBack(); // takes 700 ms

    // (41659) That makes him thoughtless. (42831)
    delay(41659 - 37542 - (800 * 4) - 700);
    rama_wijaya.pointToBack(); // takes 1400 ms

    // (43214) My younger brother, (44111)
    delay(43214 - 41659 - 1400);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (44402) go to him quickly. (45395)
    delay(44402 - 43214 - 700);
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (45801) Do not be afraid. (46659)
    delay(45801 - 44402 - 1200);
    rama_wijaya.downFront(); // takes 700 ms

    // (47167) Speak to that stupid ape with harsh words until it hurts, (50215)
    delay(47167 - 45801 - 700);
    rama_wijaya.middleBack(); // takes 1200 ms
    for (int i = 0; i < 2; i++)
    {
        rama_wijaya.directControl(3, 135, 400);
        rama_wijaya.directControl(3, 180, 400);
    } // takes 800 ms each loop

    // (50614) because he has done first by not respecting you, lying to you. (53883)
    delay(50614 - 47167 - (800 * 2) - 1200);
    for (int i = 0; i < 5; i++)
    {
        rama_wijaya.directControl(3, 135, 400);
        rama_wijaya.directControl(3, 180, 400);
    } // takes 800 ms each loop

    // (54729) He does not remember at all where all that luxury came from. (58059)
    delay(54729 - 50614 - (800 * 5));
    for (int i = 0; i < 3; i++)
    {
        rama_wijaya.directControl(3, 135, 400);
        rama_wijaya.directControl(3, 180, 400);
    } // takes 800 ms each loop
    rama_wijaya.downBack(); // takes 700 ms

    // (58406) Ah! He is stupid. (59612)
    delay(58406 - 54729 - (800 * 3) - 700);
    rama_wijaya.pointToBack(); // takes 1400 ms

    // (60029) Therefore go! (60924)
    delay(60029 - 58406 - 1400);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (61173) Tell him that he is sinful. (62555)
    delay(61173 - 60029 - 700);
    rama_wijaya.pointToFront(); // takes 1200 ms

    delay(62555 - 61173 - 1200);
    rama_wijaya.defaultHandPosition();

    SoundSystem::playMusicWayang();
    laksmana.defaultStandPosition();
    rama_wijaya.defaultStandPosition();

    delay(1000);
    sugriwa.walk_to_a_certain_distance_before_calibrating_value(270);
    rama_wijaya.walk_to_a_certain_distance_before_calibrating_value(150);

    // 028 (12 SApol Sugriwa1F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SApol_Sugriwa1F);
    // delay(3000);

    /*I am a negligent slave,*/
    delay(644);
    sugriwa.pointToSelf();    // 900
    sugriwa.lowPointToBack(); // 700
    delay(2891 - 644 - 900 - 700);

    /*indulging in luxury instead of coming to you.*/
    sugriwa.downBack();   // 700
    sugriwa.middleBack(); // 1400
    delay(6527 - 2891 - 700 - 1400 - 700);
    sugriwa.downFront(); // 700

    /*Please*/
    sugriwa.lower_pointToFront(); // 700
    delay(7257 - 6527 - 700);

    /*accept my humble apologies.*/
    sugriwa.downFront();   // 700
    sugriwa.pointToSelf(); // 900
    sugriwa.downBack();    // 700
    delay(9608 - 7257 - 700 - 900 - 700);

    /*it is very bad of me*/
    sugriwa.downFront();          // 700
    sugriwa.lower_pointToFront(); // 700
    delay(11902 - 9608 - 700 - 700);

    /*I was lost in the luxury you gave me, */
    sugriwa.downFront();   // 700
    sugriwa.pointToSelf(); // 900
    delay(14851 - 11902 - 700 - 900);

    /*until I became neglectful of the agreement to come*/
    sugriwa.middleBack(); // 1400
    delay(18351 - 14851 - 1400);

    /*when the dry season has come*/
    sugriwa.lowPointToBack(); // 700
    delay(20813 - 18351 - 700);

    /*because I am too pre-occupied.*/
    sugriwa.downBack();           // 700
    sugriwa.downFront();          // 700
    sugriwa.lower_pointToFront(); // 700
    delay(23797 - 20813 - 700 - 700 - 700);

    /*Now I will order the monkeys to depart.*/
    sugriwa.downFront();   // 700
    sugriwa.pointToSelf(); // 900
    delay(26860 - 23797 - 700 - 900 - 700);
    sugriwa.downFront(); // 700

    /*Do not worry.*/
    sugriwa.lower_pointToFront(); // 700
    delay(28399 - 26860 - 700);

    /*Order the monkeys to search*/
    sugriwa.pointToFront(); // 900
    delay(30253 - 28399 - 900);

    /*all the mountains and forests,*/
    sugriwa.lower_pointToFront(); // 700
    delay(33116 - 30253 - 700 - 700);
    sugriwa.downFront(); // 700

    /* how impassible the forests may be, */
    sugriwa.middleBack(); // 1400
    delay(35907 - 33116 - 1400);

    /*the search will be carried out.*/
    sugriwa.pointToBack(); // 1400
    delay(38705 - 35907 - 1400 - 700);
    sugriwa.downBack(); // 700

    /*Wherever Sita be staying,*/
    sugriwa.middleFront(); // 1200
    delay(40810 - 38705 - 1200);

    /*she will be found*/
    sugriwa.pointToFront(); // 900
    delay(41948 - 40810 - 900);
    delay(2000);
    sugriwa.downFront(); // 700

    // 029 (13 SApol Sugriwa2F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SApol_Sugriwa2F);
    // delay(3000);
    /* Hanuman, */
    sugriwa.pointToBack(); // 1400
    delay(1632 - 1400);

    SoundSystem::pauseMusicWayang();
    hanoman.walk_to_a_certain_distance_before_calibrating_value(135);
    SoundSystem::continuePlaying();

    /*gather all the monkey troops and have them march to Malyawan.*/
    sugriwa.downBack();   // 700
    sugriwa.middleBack(); // 1400
    delay(5239 - 1632 - 700 - 1400);
    delay(1000);

    /*return to default position*/
    sugriwa.mathentengA();

    // 030 (14 SApol Hanuman1F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SApol_Hanuman1F);
    // delay(3000);

    /*At once, my lord. */
    hanoman.pointToSelf();              // 900 (900)
    hanoman.directControl(3, 170, 400); // 1300 (400)
    hanoman.directControl(4, 95, 400);  // 1700 (400)
    delay(2000);

    /*return to default position*/
    hanoman.directControl(4, 80, 400);
    hanoman.directControl(3, 150, 400);
    hanoman.downFront();

    SoundSystem::playMusicWayang();
    hanoman.defaultStandPosition();

    // 031 (15 SApol Sugriwa3F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SApol_Sugriwa3F);
    // delay(3000);
    /*O, my lord, */
    delay(594);
    sugriwa.pointToFront(); // 900
    delay(2161 - 544 - 900 - 700);
    sugriwa.downFront();

    /*please accept my humble apologies because I have not been truthful */
    sugriwa.pointToSelf(); // 900
    sugriwa.pointToBack(); // 1400
    delay(7536 - 2161 - 900 - 1400 - (50));

    /*and have lied to you.*/
    sugriwa.downBack();     // 700
    sugriwa.downFront();    // 700
    sugriwa.pointToFront(); // 900
    delay(10006 - 7536 - 700 - 700 - 900);
    sugriwa.downFront(); // 700

    /*I forget about my promise to come,*/
    sugriwa.pointToSelf(); // 900
    sugriwa.pointToBack(); // 1400
    delay(13348 - 10006 - 900 - 1400 - (700));

    /* and kept away,*/
    sugriwa.lowPointToBack(); // 700
    delay(15030 - 13348 - 700 - 700);
    sugriwa.downBack(); // 700

    /* living in luxury, */
    sugriwa.middleBack(); // 1400
    delay(16891 - 15030 - 1400);

    /*as if I have attained it myself.*/
    sugriwa.downBack();    // 700
    sugriwa.downFront();   // 700
    sugriwa.middleFront(); // 1200
    delay(19904 - 16891 - 700 - 700 - 1200);

    /*I have not thought about your mercy towards me.*/
    sugriwa.downFront();   // 700
    sugriwa.pointToSelf(); // 900
    sugriwa.pointToBack(); // 1400
    delay(23747 - 19904 - 700 - 900 - 1400);

    /*I am stupid, */
    sugriwa.lowPointToBack(); // 700
    delay(25658 - 23747 - 700);

    /*I am too slothful.*/
    sugriwa.downBack(); // 700
    delay(27812 - 25658 - 700 - 700);
    sugriwa.downFront(); // 700

    /*I am really foolish not to remember friendship,*/
    sugriwa.lower_pointToFront(); // 700
    delay(31563 - 27812 - 700);

    /*and not to realize that I have been cared for,*/
    sugriwa.pointToFront(); // 900
    delay(35241 - 31563 - 700 - 900);

    /* the more so to return the favor.*/
    sugriwa.lower_pointToFront(); // 700
    delay(38483 - 35241 - 700 - 800);
    sugriwa.downFront(); // 700

    /*Therefore forgive me my lord,*/
    sugriwa.pointToSelf(); // 900
    sugriwa.pointToBack(); // 1400
    delay(40702 - 38483 - 900 - 1400 + (100));

    /*as I am stupid, */
    sugriwa.lowPointToBack(); // 700
    delay(42234 - 40702 - 700);

    /*debased and dumb.*/
    sugriwa.downBack(); // 700
    delay(44624 - 42234 - 700 - 700);
    sugriwa.downFront(); // 700

    /*It is because my lord has reminded me,*/
    sugriwa.pointToFront(); // 900
    delay(47501 - 44624 - 700 - 900);

    /*that you foolish slave has come now.*/
    sugriwa.lower_pointToFront(); // 700
    delay(50135 - 47501 - 700);
    delay(2000);

    /*lower hands (default position would be disrespectful)*/
    sugriwa.downFront();

    // 032 (Rama forgives sugriwa)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::RAMA_FORGIVES_SUGRIWA);
    // delay(3000);

    // (820) I forgive you, (1847)

    delay(820);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (1985) for bringing numerous troops to aid me (4166)

    delay(1985 - 820 - 700);
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (4519) and they all seem very powerful and vigorous. (7174)

    delay(4519 - 1985 - 1200);
    rama_wijaya.directControl(1, 45, 500);
    rama_wijaya.directControl(1, 0, 500);
    rama_wijaya.directControl(1, 45, 500);
    rama_wijaya.directControl(1, 0, 500);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (7550) Surely Rawana will be destroyed. (9353)

    delay(7550 - 4519 - 700 - 500 * 4);
    rama_wijaya.pointToFront(); // takes 1200 ms

    delay(9353 - 7550 - 1200);
    rama_wijaya.downFront(); // takes 700 ms

    SoundSystem::playMusicWayang();
    rama_wijaya.defaultHandPosition();
    sugriwa.defaultHandPosition();

    rama_wijaya.defaultStandPosition();
    sugriwa.defaultStandPosition();

    setAllMOSFETtoHIGH();
    SoundSystem::playDialogFromACertainFolder(SoundSystem::INDICATOR_SOUND, SoundSystem::INDICATOR_SOUND_NUMBER::INDICATOR_FINISHED_SHOWING);
    delay(2000);
}

void Episodes::Episode_3()
{
    CalibratingFunction::wayangHand();

    setAllMOSFETtoLOW();

    SoundSystem::playMusicWayang();

    delay(1000);
    rahwana.walk_to_a_certain_distance_before_calibrating_value(350); // going to the dialog position
    sita.walk_to_a_certain_distance_before_calibrating_value(100); // going to the dialog position


    /*insert 001_Sita-Rawana-Hanuman_Rawana1v here*/

    delay(821);
    // (821) Hey Maithili, (1930)  
    rahwana.pointToFront(); // takes 900 ms
    delay(2516-821-900);

    // (2516) you are very cruel towards me. (4681)  
    rahwana.middleFront(); // takes 1200 ms
    delay(5486-2516-1200);

    // (5486) Let me fall into hell if I lie. (7893)  
    rahwana.downFront(); // takes 700 ms
    delay(8862-5486-1200);

    // (8862) You are the only one, my dear, (11206)  
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(11644-8862-700-(700));
    rahwana.downFront(); // takes 700 ms

    // (11644) who always stays in my mind. (13410) 
    rahwana.pointToSelf(); // takes 1100 ms
    delay(14481-11644-1100-(700));
    rahwana.downFront(); // takes 700 ms

    // (14481) Janakatmaja, (15583)  
    rahwana.middleFront(); // takes 1200 ms
    delay(16317-14481-1200);

    // (16317) you hurt me more and more. (18162)  
    rahwana.directControl(3, 180, 500); // takes 500 ms
    rahwana.directControl(4, 140, 200); // takes 200 ms
    delay(18888-16317-500-200);

    // (18888) You should not be so cruel in all your deeds, my dear. (22342)  
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(23382-18888-700-(700));
    rahwana.downFront(); // takes 700 ms

    // (23382) Now my longing for you is profound. (25804)  
    rahwana.pointToFront(); // takes 1200 ms
    delay(26570-23382-1200-(700));
    rahwana.downFront(); // takes 700 ms

    // (26570) I prefer to die, (28024)  
    rahwana.pointToSelf(); // takes 1100 ms
    delay(28485-26570-1100);

    // (28485) than be tortured like this, (30532)  
    rahwana.downFront(); // takes 700 ms
    delay(31376-28485-700);

    // (31376) because you have no pity for me. (33478) 
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(34478-31376-700);
    rahwana.downFront(); // takes 700 ms


    /*sita silence */
    delay(5000);

    /*insert 002_Sita-Rawana-Hanuman_Rawana2v here*/

    delay(516); 
    // (516) Janakatmaja! (1649) 
    rahwana.pointToFront(); // takes 900 ms
    delay(2209-516-900);

    // (2209) What is the use of remaining silent? (4531)  
    rahwana.lower_pointToFront(); // takes 700 ms
    for (int i=0; i<2; i++){ // takes 800 ms *2
        rahwana.directControl(3, 150, 400); // takes 400 ms
        rahwana.directControl(3, 120, 400); // takes 400 ms
    }
    delay(5153-2209-700-(800*2));

    // (5153) That is not the way to stop me from asking, (7721)  
    rahwana.downFront(); // takes 700 ms
    delay(8282-5153-700);

    // (8282) because I do not think I am wrong, my dear. (11002)
    rahwana.pointToSelf(); // takes 1100 ms  
    delay(11781-8282-1100);

    // (11781) I am only following the behavior of a raksasa, (14815)  
    rahwana.downFront(); // takes 700 ms
    delay(15336-11781-700);

    // (15336) nothing else. (16295) 
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(17411-15336-700);

    // (17411) I have reserved for you a jeweled pavilion. (20019)  
    rahwana.middleFront(); // takes 1200 ms
    delay(20785-17411-1200);

    // (20787) Let us sleep there and have fun together, my dear. (23658)  
    rahwana.directControl(3, 180, 500); // takes 500 ms
    rahwana.directControl(4, 140, 200); // takes 200 ms
    delay(24650-20787-500-200);

    // (24650) Is it not very cold to sleep on the ground? (27321) 
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(28256-24650-700);

    // (28256) You are in my heart, (29478)  
    rahwana.pointToFront(); // takes 900
    delay(29826-28256-900);

    // (29826) you alone, (30634)  
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(31088-29826-700);

    // (31088) so that you will not be far wherever I go. (33634) 
    rahwana.middleFront(); // takes 1200 ms
    delay(34323-31088-1200-(700)); 
    rahwana.downFront(); // takes 700 ms

    // (34323) Or let me stay in your heart, (36095)  
    rahwana.pointToSelf(); // takes 1100 ms
    delay(36235-34323-1100-(700));
    rahwana.downFront(); // takes 700 ms

    // (36235) so that I will not be far from you, my beloved. (39247) 
    rahwana.pointToFront(); // takes 900 ms
    delay(40424-36235-900);

    // (40424) Please, (41075)  
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(41731-40424-700);

    // (41731) listen to my words my dear, (43609) 
    rahwana.pointToFront(); // takes 1200 ms
    delay(44285-41731-1200); 

    // (44249) they are true. (45291)  
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(45880-44249-700);

    // (45880) No one else shall I serve (48241) and love. (48987)  
    rahwana.middleFront(); // takes 1200 ms
    delay(48241-45880-1200);
    rahwana.directControl(3, 180, 500); // takes 500 ms
    rahwana.directControl(4, 140, 200); // takes 200 ms
    delay(49834-48241-500-200);

    // (49834) Besides, (50641)  
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(51045-49834-700);

    // (51045) your life at my side will be a success. (54017)  
    rahwana.pointToFront(); // takes 900 ms
    delay(54662-51045-900);

    // (54662) What is the use grieving over Raghuputra? (57727) 
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(58333-54662-700);

    // (59097) If milk could be obtained from squeezing sand, (62529)  
    rahwana.middleFront(); // takes 1200 ms
    delay(63219-59097-1200);

    // (63219) then you will find happiness with Raghawa. (65630)  
    rahwana.directControl(3, 180, 500); // takes 500 ms
    rahwana.directControl(4, 140, 200); // takes 200 ms
    delay(66493-63219-500-200);

    // (66493) Therefore do not deprecate my words, my dear. (69432)  
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(70205-66493-700-(700));
    rahwana.downFront(); // takes 700 ms

    // (70205) Let me be your protector and lord. (72577) 
    rahwana.pointToSelf(); // takes 1100 ms
    delay(73918-70205-1100-(700));
    rahwana.downFront(); // takes 700 ms

    // (73918) If I am happy with your service, (75948)  
    rahwana.middleFront(); // takes 1200 ms
    delay(76435-73918-1200);

    // (76435) I will make you the queen of the threefold world. (79749)  
    rahwana.directControl(3, 180, 500); // takes 500 ms
    rahwana.directControl(4, 140, 200); // takes 200 ms
    delay(80574-76435-500-200);

    // (80574) What is the use of all this weeping? (83476)  
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(83977-80574-700);

    // (83977) Stop it! (84785)  
    rahwana.downFront(); // takes 700 ms
    delay(85615-83977-700);

    // (85615) I will be the cure, (86983)  
    rahwana.pointToSelf(); // takes 1100 ms
    delay(87437-85615-1100-(700));
    rahwana.downFront(); // takes 700 ms

    // (87437) I will heal your depressed heart. (89764)
    rahwana.middleFront(); // takes 1200 ms
    delay(90762-87437-1200); 

    // (90762) You may reign over my demon-army. (93538)  
    rahwana.directControl(3, 180, 500); // takes 500 ms
    rahwana.directControl(4, 140, 200); // takes 200 ms
    delay(94138-90762-500-200);

    // (94138) All what you wish, (95473)  
    rahwana.downFront(); // takes 700 ms
    delay(95719-94138-700);

    // (95719) I will give to you. (96897)  
    rahwana.pointToSelf(); // takes 1100 ms
    delay(97727-95719-1100-(700));
    rahwana.downFront(); // takes 700 ms

    // (97727) If you want Indra to wait upon you, (100043)  
    rahwana.pointToFront(); // takes 900 ms
    delay(100441-97727-900);

    // (100441) just say so. (101540) 
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(102376-100441-700); 

    // (102376) Do not worry, (103290)  
    rahwana.middleFront(); // takes 1200 ms
    delay(103648-102376-1200);

    // (103648) if that is what you want. (105219) 
    rahwana.directControl(3, 180, 500); // takes 500 ms
    rahwana.directControl(4, 140, 200); // takes 200 ms
    delay(105219-103648-500-200);

    delay(2000);
    rahwana.downFront(); // takes 700 ms
    delay(2000);

    /*insert 003_Sita-Rahwana-Hanuman_Sita1 here*/

    /*insert 004_Sita-Rawana-Hanuman_Rawana3v here*/
    delay(370);
    // (370) Janakatmaja, (1518)  
    rahwana.middleFront(); // takes 1200 ms
    delay(2115-370-1200);

    // (2115) look carefully at what this is, (4942)  
    rahwana.directControl(3, 180, 500); // takes 500 ms
    rahwana.directControl(4, 140, 200); // takes 200 ms
    delay(5867-2115-500-200);

    // (5867) which is like death in my perilous hand. (8820)  
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(10157-5867-700);

    // (10157) If you do not obey the order of Rawana, (13341)  
    rahwana.downFront(); // takes 700 ms
    delay(14340-10157-700);

    // (14340) for sure it will fall upon your neck (17843) savagely. (19018)
    rahwana.pointToFront(); // takes 900 ms
    delay(17843-14340-700);
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(19018-17843-700);
    rahwana.downFront(); // takes 700 ms 

    // *Leaves from scene* 
    rahwana.defaultStandPosition();

    /*insert 005_Sita-Rahwana-Hanuman_Sita2*/
    
}

void Episodes::Episode_4()
{
}

void Episodes::Episode_5()
{
}

void Episodes::Episode_1_task(void *pvParameters)
{
    Serial.println("Episode 1");
    // Episode_1();
    while (1)
    {
        vTaskResume(mainLoopTaskHandler);
        vTaskDelete(NULL);
    }
}

void Episodes::Episode_2_task(void *pvParameters)
{
    Serial.println("Episode 2");
    // Episode_2();
    while (1)
    {
        vTaskResume(mainLoopTaskHandler);
        vTaskDelete(NULL);
    }
}
