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
    laksmana.middleBack(); // 22369 (1400)
    delay(25323 - 22369);  // 25323 (2954)

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
    laksmana.middleFront();              // 36972 (900)
    laksmana.directControl(4, 115, 400); // 37372 (400)
    laksmana.directControl(4, 120, 400); // 37772 (400)
    laksmana.directControl(4, 115, 400); // 38172 (400)
    laksmana.directControl(4, 120, 400); // 38572 (400)
    delay(38746 - 38572);                // 38746 (174)

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
    sita.oscillate(11095 - 8038); // takes 3057 ~~ 2800

    // (11095) but now he is in trouble, (12326)

    delay((11095 - 8038) - 2800);
    sita.middleFront(); // takes 900 ms

    // (12747) shame on you, (13502)

    delay(12747 - 11095 - 900);
    sita.pointToFront(); // takes 700 ms

    // (14078) you do not want to help. (15167)

    delay(14078 - 12747 - 700);
    sita.middleFront(); // takes 900 ms

    // (15990) You think about Rama like this. (17638)

    delay(15990 - 14078 - 900);
    sita.downFront(); // takes 700 ms

    // (18440)  ‘Let him be killed by the deer. (19962)

    // (20309) It will be very lucky! (21771)

    // ***MAY NOT SMOOTH MOVEMENT***

    delay(18440 - 15990 - 700);
    sita.oscillate(22215 - 18440); // takes 3775 ms ~~ 3500 ms

    // (22215) I will take his place and marry Sita. (24250)

    delay(22215 - 18440 - 3500);
    sita.pointToSelf(); // takes 2100 ms

    // (24956) Who will be her protector, (26144)

    delay(24956 - 22215 - 2100);
    sita.downFront();          // takes 700 ms
    sita.lower_pointToFront(); // takes 700 ms

    // (26422) no one else except me.’ (28075)

    delay(26422 - 24956 - 700 - 700);
    sita.pointToSelf(); // takes 2100 ms

    // (28594) you said this to yourself, didn't you? (30247)

    delay(28594 - 26422 - 2100);
    sita.downFront();   // takes 700 ms
    sita.middleFront(); // takes 900 ms

    // (31045) Debased and foolish Laksmana, (32697)

    delay(31045 - 28594 - 700 - 900);
    sita.pointToFront(); // takes 700 ms

    // (33087) do you think I am wicked, (34225)

    // (34832) capable of such evil, (36212)

    // (36447) such lewdness? (37319)

    delay(33087 - 31045 - 700);
    sita.oscillate(37913 - 33087); // takes 4826 ms ~~ 4200 ms

    // (37913) I do not have any intention of marrying again, (40389)

    delay(37913 - 33087 - 4200);
    sita.downFront(); // takes 700 ms

    // (40840) just this once. (41901)

    delay(40840 - 37913 - 700);
    sita.lower_pointToFront(); // takes 700 ms

    // (42759) I will only serve Rama, nobody else. (45432)

    delay(42759 - 40840 - 700);
    sita.downFront();   // takes 700 ms
    sita.pointToSelf(); // takes 2100 ms

    // (46341) If my lord and master died, (48024)

    // (48476) if Rama is killed in battle (50462)

    delay(46341 - 42759 - 700 - 2100);
    sita.oscillate(50722 - 46341); // takes 4381 ms ~~ 4200 ms

    // (50722) butted by the deer, (51570)

    delay(50722 - 46341 - 4200);
    sita.downFront(); // takes 700 ms

    // (51781) I will sever my neck (52913)

    // (53241) and burn myself. (54287)

    // (54961) I will follow my husband; (56378)

    delay(51781 - 50722 - 700);
    sita.pointToSelf(); // takes 2100 ms

    // (56657) I will not take refuge with you. (58501)

    delay(56657 - 51781 - 2100);
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
    laksmana.directControl(4, 110, 480);  // 12244 (480)
    laksmana.directControl(3, 180, 1200); // 13444 (1200)
    laksmana.directControl(4, 140, 480);  // 13924 (480)
    delay(16175 - 13924);                 // 16175 (2251)

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
    laksmana.directControl(3, 0, 1000);   // 25277 (1000)
    laksmana.directControl(4, 110, 400);  // 25677 (400)
    laksmana.directControl(3, 180, 1000); // 26677 (1000)
    laksmana.directControl(4, 120, 400);  // 27077 (400)
    delay(26796 - 27077);                 // 26796 (719)

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
    laksmana.downFront();
    laksmana.downBack();
    laksmana.onHipBack();

    // 005 (005SitaRahwanadialogueRahwana1)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SITA_RAHWANA_DIALOGUE_RAHWANA_1);
    // delay(3000);

    rahwana.Rahwana_1();

    // 006 (006SitaRahwanadialogueSita1)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SITA_RAHWANA_DIALOGUE_SITA_1);
    // delay(3000);

    // (74)I am sorry, I cannot accept for I am already betrothed to Rama, (4700)

    delay(74);
    sita.pointToSelf(); // takes 2100 ms

    // (5162)son of king Dasaratha (6668)

    delay(5162 - 74 - 2100);
    sita.downFront();    // takes 700 ms
    sita.pointToFront(); // takes 700 ms

    // (7272)and it is the duty of a wife to be loyal to her husband and no other. (12304)

    delay(7272 - 5162 - 700 - 700);
    sita.downFront(); // takes 700 ms

    // 007 (007SitaRahwanadialogueRahwana2)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SITA_RAHWANA_DIALOGUE_RAHWANA_2);
    delay(3000);

    // 008 (03 L-R1 laksmana1F)
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
    //delay(3000);
    delay(630);

    /*O, Raghawa,*/
    hanoman.middleFront(); //1830 (1200)
    hanoman.downFront(); //2530 (700)

    /* I have been ordered to come here- */
    hanoman.pointToSelf(); //3430 (900)
    delay(4094-3430); //4094 (664)

    /*The king of the monkeys Sugriwa gave me orders to look for you.*/
    hanoman.middleBack(); //5494 (1400)
    delay(8162-5494-700); //7462 (1968)

    /*The situation is like this.*/
    hanoman.downFront(); //8162 (700)
    hanoman.lower_pointToFront(); //8862 (700)
    hanoman.downBack(); //9562 (700)
    delay(10514-9562-700); //9814 (252)

    /*There is a great monkey, unequalled in power called Bali.*/
    hanoman.downFront(); //10514 (700)
    hanoman.middleFront(); //11714 (1200)
    hanoman.onHipBack(); //12614 (900)
    delay(15273-12614); //15273 (2659)

    /*Even God Aditya is inferior to him in power.*/
    hanoman.pointToFront(); //16173 (900)
    for (int i=0; i<3; i++) //18573 (2400)
    {
        hanoman.directControl(3, 170, 400);
        hanoman.directControl(3, 180, 400);
    }
    delay(19453-18573); //19453 (880)

    /*He was savagely outrageous towards my master*/
    hanoman.downFront(); //20153 (700)
    hanoman.pointToBack(); //21553 (1400)
    delay(22688-21553); //22688 (1135)

    /*and insulted him.*/
    hanoman.lowPointToBack(); //23388 (700)
    delay(24763-23388); //24763 (1375)

    /*Out of fear the monkey-king Bali,*/
    hanoman.downBack(); //25463 (700)
    hanoman.middleFront(); //26663 (1200)
    delay(27691-26663); //27691 (1028)

    /*my master went to the region of Malaya. */
    hanoman.downFront(); //28391 (700)
    hanoman.pointToBack(); //29791 (1400)
    delay(31040-29791); //31040 (1249)

    /*He ordered me to look for you, */
    hanoman.pointToSelf(); //31940 (900)
    delay(33058-31940); //33058 (1118)

    /*as he intends to be friends with you,*/
    hanoman.middleBack(); //34458 (1400)
    delay(35707-34458); //35707 (1249)

    /*to stay and serve at your feet, */
    hanoman.pointToBack(); //37107 (1400)
    delay(38619-37107-800); //37819 (802)

    /*o, lord. */
    hanoman.directControl(3, 170, 400); //38219 (400)
    hanoman.directControl(4, 95, 400); //38619 (400)
    delay(40258-38619); //40258 (1639)

    /*I suggest that you may grant him a favor*/
    hanoman.directControl(4, 80, 400); //40658 (400)
    hanoman.directControl(3, 150, 400); //41058 (400)
    delay(42949-41058); //42949 (1891)

    /*and make him your ally,*/
    hanoman.downFront(); //43649 (700)
    hanoman.lower_pointToFront(); //44349 (700)
    delay(45225-44349); //45225 (876)

    /*because he is powerful,*/
    hanoman.directControl(3, 120, 400); //45625 (400)
    delay(46965-45625); //46965 (1340)

    /*noble,*/
    hanoman.directControl(3, 100, 400); //47365 (400)
    delay(47716-47365); //47716 (351)

    /*and goodhearted.*/
    hanoman.lower_pointToFront(); //48416 (700)
    delay(49691-48416); //49691 (1275)

    /*Let him follow you and love you and carry out all your orders*/
    hanoman.pointToFront(); //50591 (900)
    for(int i=0; i<4; i++) //53791 (3200)
    {
        hanoman.directControl(3, 170, 400);
        hanoman.directControl(3, 180, 400);
    }
    delay(54515-53791); //54515 (724)

    /*Let him take part as commander in the battlefield*/
    hanoman.lower_pointToFront(); //55215 (700)
    for(int i=0; i<3; i++) //57615 (2400)
    {
        hanoman.directControl(3, 100, 400);
        hanoman.directControl(3, 90, 400);
    }
    delay(350);//57965 (350)

    /*to kill Dasamukha.*/
    hanoman.directControl(1, 10, 400);
    hanoman.directControl(1, 0, 400);
    hanoman.directControl(1, 10, 400);
    hanoman.directControl(1, 0, 240);

    /*return to default position*/
    hanoman.downFront();
    hanoman.downBack();
    hanoman.onHipBack();


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
    // delay(3000);

    /*At once, my lord. */
    hanoman.pointToSelf(); //900 (900)
    hanoman.directControl(3, 170, 400); //1300 (400)
    hanoman.directControl(4, 95, 400); //1700 (400)
    delay(2000);

    /*return to default position*/
    hanoman.directControl(4, 80, 400);
    hanoman.directControl(3, 150, 400);
    hanoman.downFront();

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