#include "Episodes.hpp"
#include "sound_system.hpp"
#include "characters/hanoman.hpp"
#include "characters/rama_wijaya.hpp"
#include "mainheader.hpp"

// #include "freertos/task.h"

// TaskHandle_t Hanoman_talking;
// TaskHandle_t Rama_talking;
// TaskHandle_t Dub_delay;

// void hanoman_talking_loop(void *parameter);
// void rama_talking_loop(void *parameter);
// void gap_for_dub_delay(void *parameter);

Hanoman hanoman;
RamaWijaya rama_wijaya;


void Episodes::Mei2nd_Episode()
{
    hanoman.begin(20);
    rama_wijaya.begin(20);

    // Narator Opening
    SoundSystem::play_dialog_direct(SoundSystem::DIALOG_NUMBER::NARATOR_INTRO_1);
    // SoundSystem::hold_the_section_until_finished(123*1000);
    static unsigned long stop_watch = millis();

    while (millis() - stop_watch < 123 * 1000)
    {
        // put the movement command here
    }

    Serial.println("\nNarator Opening Done");
    delay(1000);

    // Hanuman Dialog 1
    hanoman.walk_to_scene();     // going to the dialog position
    rama_wijaya.walk_to_scene(); // going to the dialog position
    SoundSystem::play_dialog_direct(SoundSystem::DIALOG_NUMBER::HANUMAN_1);
    // SoundSystem::hold_the_section_until_finished(98 * 1000);
    stop_watch = millis();
    // starting_hanoman_talking(98);

    if (millis() - stop_watch < 97 * 1000)
    {
        // put the movement command here
        hanoman.talking(96);
    }

    Serial.println("\nHanuman Dialog 1 Done");
    delay(1000);

    // Rama Dialog 1
    SoundSystem::play_dialog_direct(SoundSystem::DIALOG_NUMBER::RAMA_1);
    // SoundSystem::hold_the_section_until_finished(66 * 1000);
    stop_watch = millis();
    // starting_rama_talking(66);

    if (millis() - stop_watch < 65 * 1000)
    {
        // put the movement command here
        rama_wijaya.talking(64);
    }

    Serial.println("\nRama Dialog 1 Done");
    delay(1000);

    // Hanuman Dialog 2
    SoundSystem::play_dialog_direct(SoundSystem::DIALOG_NUMBER::HANUMAN_2);
    // SoundSystem::hold_the_section_until_finished(68 * 1000);
    stop_watch = millis();
    // starting_hanoman_talking(68);
    if (millis() - stop_watch < 67 * 1000)
    {
        // put the movement command here
        hanoman.talking(66);
    }

    Serial.println("\nHanuman Dialog 2 Done");
    delay(500);

    /* Core where the task should run */

    // run_both_instant();

    hanoman.leave_from_scene();     // going back to first position
    rama_wijaya.leave_from_scene(); // going back to first position
    delay(500);

    // Narator Ending
    SoundSystem::play_dialog_direct(SoundSystem::DIALOG_NUMBER::NARATOR_END_1);
    // SoundSystem::hold_the_section_until_finished(14 * 1000);
    stop_watch = millis();

    while (millis() - stop_watch < 14 * 1000)
    {
        // put the movement command here
    }

    Serial.println("\nDone!");
    digitalWrite(LED_BUILTIN, LOW);
}

void Episodes::Testing_Hanuman()
{
    hanoman.talking(20);
    // hanoman.all_high();
}

void Episodes::Testing_Rama()
{
    rama_wijaya.talking(20);
    // rama_wijaya.all_high();
}

void Episodes::manual_begin()
{
    hanoman.begin(10);
    rama_wijaya.begin(10);
}


void Episodes::testing_hanuman_horizontal_movement(){
    hanoman.walk_to_scene();
    delay(5);
    hanoman.leave_from_scene();
    delay(5);
    hanoman.walk_to_scene();
    delay(5);
    hanoman.leave_from_scene();
}

void Episodes::testing_rama_wijaya_horizontal_movement(){
    rama_wijaya.walk_to_scene();
    delay(5);
    rama_wijaya.leave_from_scene();
    delay(5);
    rama_wijaya.walk_to_scene();
    delay(5);
    rama_wijaya.leave_from_scene();
}
