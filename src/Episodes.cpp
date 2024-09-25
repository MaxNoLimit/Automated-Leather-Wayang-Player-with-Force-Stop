#include "Episodes.hpp"
#include "sound_system.hpp"
#include "characters/hanoman.hpp"
#include "characters/rama_wijaya.hpp"
#include "characters/sita.hpp"
#include "characters/rahwana.hpp"
#include "characters/laksmana.hpp"
#include "mainheader.hpp"

// TaskHandle_t Hanoman_talking;
// TaskHandle_t Rama_talking;
// TaskHandle_t Dub_delay;

// TaskHandle_t RahwanaHandler;

// void TaskRahwanaMovement1(void *parameter);

// void hanoman_talking_loop(void *parameter);
// void rama_talking_loop(void *parameter);
// void gap_for_dub_delay(void *parameter);

Hanoman hanoman;
RamaWijaya rama_wijaya;
Sita sita;
Rahwana rahwana;
Laksmana laksmana;

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

// void TaskRahwanaMovement1(void *parameter)
// {
//     while (1)
//     {
//         rahwana.Rahwana_1();
//         vTaskDelete(NULL);
//     }
// }

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

    SoundSystem::playDialogFromACertainFolder(SoundSystem::EXTRA_MUSIC_WAYANG, SoundSystem::MUSIC_NUMBER::MUSIC_GAMELAN);
    sita.walk_to_a_certain_distance_before_calibrating_value(200);
    laksmana.walk_to_a_certain_distance_before_calibrating_value(200);
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
    sita.oscillate(3298);       // takes 2800 ms
    delay(10673 - 7339 - 2800); // result = 1534 ms

    // movement 6, 7
    sita.pointToFront();        // takes 700 ms
    delay(12320 - 10673 - 700); // result = 1547 ms

    sita.defaultHandPosition(); // takes 2000 ms

    /*
    1 movement duration = (2580 - 1312) ms = 1268 ms
    delay(2939 - 2580); = 359 ms
    2 movement duration = (4263 - 2939) ms = 1324 ms
    delay(4796 - 4263); = 553 ms
    1268 + 359 + 1324 + 553 = 3504 ms
    DONE

    3 movement duration = (6405 - 4796) ms = 1609 ms
    delay(7339 - 6405); = 934 ms
    DONE

    4 movement duration = (8638 - 7339) ms = 1299 ms
    delay(8942 - 8638); = 304 ms
    5 movement duration = (10080 - 8942) ms = 1138 ms
    delay(10637 - 10080); = 557 ms
    1299 + 304 + 1138 + 557 = 3298 ms
    DONE

    6 movement duration = (11163 - 10637) ms = 526 ms
    delay(11559 - 11163); = 396 ms
    7 movement duration = (12320 - 11559) ms = 761 ms
    526 + 396 + 761 = 1683 ms
    DONE
    */

    // 002 (01 S-L1 laksmana1F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::S_L1_LAKS1F);
    // delay(3000);
    
    /*You are the wife of the hero from Raghu lineage;*/
    delay(787);                    // 787
    laksmana.pointToFront(); // 1487
    delay(3875 - 1487);            // 3875 (2388)

    /*you are the beloved of my brother,*/
    laksmana.lower_pointToFront(); // 4575 (700)
    laksmana.pointToFront();       // 5275 (700)
    laksmana.lower_pointToFront(); // 5975 (700)
    delay(6589 - 5975);                  // 6589 (614)

    /*also you are the daughter of king Janaka.*/
    laksmana.pointToFront(); // 7289 (700)
    delay(9898 - 7289);            // 9898 (2609)

    /*Why do you worry and cry so at hearing such a call?*/
    laksmana.middleFront(); // 10798 (900)
    delay(13684 - 10798);         // 13684 (2886)

    /*Do you know that it is he who calls?*/
    laksmana.lower_pointToFront(); // 14384 (700)
    delay(16604 - 14384);                // 16604 (2220)

    /*Do you know who that is? */
    laksmana.middleFront(); // 17504 (900)
    delay(18923 - 17504);         // 18923 (1419)

    /*You may ask,*/
    laksmana.pointToFront(); // 19623 (700)
    delay(20269 - 19623);          // 20269 (646)

    /*who is powerful enough in this world to fight prince Rama in battle?*/
    laksmana.downBack();     // 20969 (700)
    laksmana.middleBack();  // 22369 (1400)
    delay(25323 - 22369);        // 25323 (2954)

    /*He is the most powerful person,*/
    laksmana.lower_pointToFront(); // 26023 (700)
    delay(27655 - 26023);                // 27655 (1632)

    /*the most skilled in handling all weapons.*/
    laksmana.pointToBack(); // 29055 (1400)
    delay(30722 - 29055);         // 30722 (1667)

    /*How could you have fears that he would be killed,*/
    laksmana.downBack();     // 31422 (700)
    laksmana.pointToFront(); // 32122 (700)
    delay(34010 - 32122);          // 34010 (1888)

    /*butted by a deer?*/
    laksmana.onHipBack(); // 35210 (1200)
    delay(36072 - 35210);       // 36072 (862)

    /*That call was not his,*/
    laksmana.middleFront(); // 36972 (900)
    laksmana.directControl(4, 115, 400); //37372 (400)
    laksmana.directControl(4, 120, 400); //37772 (400)
    laksmana.directControl(4, 115, 400); //38172 (400)
    laksmana.directControl(4, 120, 400); //38572 (400)
    delay(38746-38572); //38746 (174)

    /*it was the call of an evil demon, */
    laksmana.pointToFront(); //39446 (700)
    delay(41447-39446); //41447 (2001)

    /*it was a trick with the purpose of deceiving us.*/
    laksmana.lower_pointToFront(); //42147 (700)
    delay(44700-42147-700); //44000 (1853)
    laksmana.downFront(); //44700 (700)

    /*I say, it was the cry of the deer*/
    laksmana.pointToSelf(); //45400 (700)
    delay(48296-45400); //48296 (2896)
    laksmana.downFront(); //48996 (700)

    /*which was hit by an arrow,*/
    laksmana.lower_pointToFront(); //49696 (700)
    delay(50930-49696); //50930 (1234)
    
    /*sounding like the voice of Rama. */
    laksmana.middleFront(); //51830 (900)
    delay(53233-51830); //53233 (1403)

    /*return to default position*/
    laksmana.defaultHandPosition(); 

    // 003 (Sita2Sita-laksmana dialogue 1)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SITA2SITA_LAKS_DIALOGUE_1);
    delay(3000);

    // 004 (02 S-L1 laksmana2F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::S_L1_LAKS2F);
    delay(3000);

    // 005 (005SitaRahwanadialogueRahwana1)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SITA_RAHWANA_DIALOGUE_RAHWANA_1);
    delay(3000);

    // 006 (006SitaRahwanadialogueSita1)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SITA_RAHWANA_DIALOGUE_SITA_1);
    delay(3000);

    // 007 (007SitaRahwanadialogueRahwana2)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SITA_RAHWANA_DIALOGUE_RAHWANA_2);
    delay(3000);

    // 008 (03 L-R1 laksmana1F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::L_R1_LAKS1F);
    delay(3000);

    // 009 (Rama1laksmana-Rama Diaglogue(in place of narrator for context))
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::RAMA1LAKS_RAMA_DIALOGUE_IN_PLACE_NARATOR);
    delay(3000);

    // 010 (04 H-R1 Hanuman1F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::H_R1_HANUMAN1F);
    delay(3000);

    // 011 (Rama1Hanuman-Rama dialogue_E)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::RAMA1HANUMAN_RAMA_DIALOGUE_E);
    delay(3000);

    // 012 (05 H-R1 Hanuman2F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::H_R1_HANUMAN2F);
    delay(3000);

    // 013 (06 S-R1 Sugriwa1F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::S_R1_SUGRIWA1F);
    delay(3000);

    // 014 (07 Duel1 Sugriwa1F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::DUEL1_SUGRIWA1F);
    delay(3000);

    // 015 (Subali round 1 rage)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SUBALI_ROUND_1_RAGE);
    delay(3000);

    // 016 (08 Duel1 Sugriwa2F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::DUEL1_SUGRIWA2F);
    delay(3000);

    // 017 (09 DuAft1 Sugriwa1F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::DUAFT1_SUGRIWA1F);
    delay(3000);

    // 018 (Rama1Sugriwa-Rama-Subali dialogue)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::RAMA1SUGRIWA_RAMA_SUBALI_DIALOGUE);
    delay(3000);

    // 019 (10 Duel2 Sugriwa1F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::DUEL2_SUGRIWA1F);
    delay(3000);

    // 020 (Subali round 2 rage)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SUBALI_ROUND_2_RAGE);
    delay(3000);

    // 021 (Subali bacotin rama_E)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SUBALI_BACOTIN_RAMA_E);
    delay(3000);

    // 022 (Rama2Sugriwa-Rama-Subali dialogue_E)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::RAMA2SUGRIWA_RAMA_SUBALI_DIALOGUE_E);
    delay(3000);

    // 023 (Subali tobat_E)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SUBALI_TOBAT_E);
    delay(3000);

    // 024 (11 S-R2 Sugriwa1F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::S_R2_SUGRIWA1F);
    delay(3000);

    // 025 (Rama1Sugriwa-Rama dialogue 2_E)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::RAMA1SUGRIWA_RAMA_DIALOGUE_2_E);
    delay(3000);

    // 026 (Rama Sadboi_E)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::RAMA_SADBOI_E);
    delay(3000);

    // 027 (Rama telling laksmana to bacot sugriwa_E)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::RAMA_TELLING_LAKSMANA_BACOT_SUGRIWA_E);
    delay(3000);

    // 028 (12 SApol Sugriwa1F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SApol_Sugriwa1F);
    delay(3000);

    // 029 (13 SApol Sugriwa2F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SApol_Sugriwa2F);
    delay(3000);

    // 030 (14 SApol Hanuman1F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SApol_Hanuman1F);
    delay(3000);

    // 031 (15 SApol Sugriwa3F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SApol_Sugriwa3F);
    delay(3000);

    // 032 (Rama forgives sugriwa)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::RAMA_FORGIVES_SUGRIWA);
    delay(3000);

    setAllMOSFETtoHIGH();
    SoundSystem::playDialogFromACertainFolder(SoundSystem::INDICATOR_SOUND, SoundSystem::INDICATOR_SOUND_NUMBER::INDICATOR_FINISHED_SHOWING);
    delay(2000);
}

void Episodes::Episode_2()
{
}

void Episodes::Episode_3()
{
}

void Episodes::Episode_4()
{
}

void Episodes::Episode_5()
{
}