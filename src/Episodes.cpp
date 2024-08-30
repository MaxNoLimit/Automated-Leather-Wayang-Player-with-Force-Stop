#include "Episodes.hpp"
#include "sound_system.hpp"
#include "characters/hanoman.hpp"
#include "characters/rama_wijaya.hpp"
#include "characters/sita.hpp"
#include "characters/rahwana.hpp"
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
    sita.walk_to_a_certain_distance_before_calibrating_value(150);         // going to the dialog position
    rama_wijaya.walk_to_a_certain_distance_before_calibrating_value(300); // going to the dialog position
    delay(3000);
    SoundSystem::pauseMusicWayang();

    // Sita 1 8s
    // delay(500);
    sita.left_pointToFront();
    sita.right_handOnHip();
    delay(50);
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::SPECIAL_EPISODE_29_JULY::RAMA_SITA__SITA_DIALOG_1);
    delay(1000);

    SoundSystem::pause();
    sita.left_lower_hand();
    delay(50);

    SoundSystem::continuePlaying();
    delay(2667);

    SoundSystem::pause();
    sita.left_pointToFront();
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
    sita.defaultStandPosition();       // going back to first position

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
    sita.left_pointToFront();
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

    sita.defaultStandPosition();     // going back to first position
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
    sita.right_handOnHip();
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::SPECIAL_EPISODE_29_JULY::RAMA_RAHWANA__SITA_1);
    // SoundSystem::hold_the_section_until_finished(3.5 * 1000);
    delay(3520);

    SoundSystem::playMusicWayang();
    rama_wijaya.defaultStandPosition(); // going back to first position
    sita.defaultStandPosition();         // going back to first position
    rahwana.defaultStandPosition();      // going back to first position
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