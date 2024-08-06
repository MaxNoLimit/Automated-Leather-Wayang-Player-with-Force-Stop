#ifndef SOUND_SYSTEM_H
#define SOUND_SYSTEM_H

#include "mainheader.hpp"
#include <DFRobotDFPlayerMini.h>

namespace SoundSystem
{
    // int soundVolume = 30;
    enum EPISODE_NUMBER
    {
        EPISODE_1 = 1,
        EPISODE_2 = 2,
        EPISODE_3 = 3,
        EPISODE_4 = 4,
        EPISODE_5 = 5,
        INDICATOR_SOUND = 6,
        EXTRA_MUSIC_WAYANG = 7,
    };

    enum INDICATOR_SOUND_NUMBER{
        INDICATOR_AUDIO_1 = 1,
        INDICATOR_VSLOT_CALIBRATION = 2,
        INDICATOR_WAYANG_HAND_CALIBRATION = 3,
        INDICATOR_FINISHED_SHOWING = 4,
    };

    enum SPECIAL_EPISODE_29_JULY{
        // Rama - Sita Dialogue
        RAMA_SITA__SITA_DIALOG_1 = 1,
        RAMA_SITA__RAMA_DIALOG_1 = 2,

        // Sita - Rahwana Dialogue
        SITA_RAHWANA__NARATOR_1 = 3,
        SITA_RAHWANA__RAHWANA_DIALOG_1 = 4,
        SITA_RAHWANA__SITA_DIALOG_1 = 5,
        SITA_RAHWANA__RAHWANA_DIALOG_2 = 6,
        SITA_RAHWANA__NARATOR_2 = 7,
        SITA_RAHWANA__NARATOR_3 = 8,

        // Rama - Rahwana Dialogue
        RAMA_RAHWANA__RAMA_1 = 9,
        RAMA_RAHWANA__RAHWANA_1 = 10,
        // FIGHT!
        RAMA_RAHWANA__RAHWANA_2 = 11,
        RAMA_RAHWANA__RAMA_2 = 12,
        RAMA_RAHWANA__SITA_1 = 13,
    };

    enum EPISODE_1_DIALOG{
        // Sita-Laksmana dialogue 1
        SITA_DIALOG_1_1 = 1,
        NARATOR_DIALOG_1_1 = 2,
        LAKSMANA_DIALOG_1_1 = 3,
        NARATOR_DIALOG_1_2 = 4,
        SITA_DIALOG_1_2 = 5,
        NARATTOR_DIALOG_1_3 = 6,
        LAKSMANA_DIALOG_1_2 = 7,

        // Sita-Rahwana dialogue 1
        NARATOR_DIALOGUE_1_4 = 8,
        RAHWANA_DIALOG_1_1 = 9,
        NARATOR_DIALOGUE_1_5 = 10,
        SITA_DIALOG_1_3 = 11,
        NARATOR_DIALOGUE_1_6 = 12,
        RAHWANA_DIALOG_1_2 = 13,
        RAHWANA_DIALOG_1_3 = 14,

        // Sita-Rahwana dialogue 2
        RAHWANA_DIALOG_2_1 = 15,
        NARATOR_DIALOGUE_2_1 = 16,

        // After script of May 2nd
        NARATOR_DIALOG_3_1 = 17,
        SUGRIWA_DIALOG_3_1 = 18,
        NARATOR_DIALOG_3_2 = 19,
        SUGRIWA_DIALOG_3_2 = 20,
        RAMA_DIALOG_3_1 = 21,
        NARATOR_DIALOG_3_3 = 22,
        SUBALI_DIALOG_3_1 = 23,
        NARATOR_DIALOG_3_4 = 24,
        RAMA_DIALOG_3_2 = 25,
        NARATOR_DIALOG_3_5 = 26,
        SUBALI_DIALOG_3_2 = 27,
        NARATOR_DIALOG_3_6 = 28,
        SUGRIWA_DIALOG_3_3 = 29,
        NARATOR_DIALOG_3_7 = 30,
        RAMA_DIALOG_3_3 = 31,
        NARATOR_DIALOG_3_8 = 32,
        RAMA_DIALOG_3_4 = 33,
        NARATOR_DIALOG_3_9 = 34,
        SUGRIWA_DIALOG_3_4 = 35,
        NARATOR_DIALOG_3_10 = 36,
        SUGRIWA_DIALOG_3_5 = 37,
        NARATOR_DIALOG_3_11 = 38,

    };
    
    enum DIALOG_NUMBER
    {
        NARATOR_INTRO_1,
        HANUMAN_1,
        RAMA_1,
        HANUMAN_2,
        NARATOR_END_1
    };

    enum MUSIC_NUMBER{
        MUSIC_GAMELAN = 1,
    };

    void justInitTheSoundSystem();
    void initSound();
    void play_dialog(int chapter_number, int dialog_number); // may be 0-2999 according to the df mini player documentation
    void printDetail(uint8_t type, int value);
    void play_dialog_direct(int dialog_number);
    void hold_the_section_until_finished(int delay_time);
    void playDialogFromACertainFolder(int nEpisode, int nDialog);
    void continuePlaying();
    void pause();
    void playMusicWayang();
    void pauseMusicWayang();
};

#endif // SOUND_SYSTEM_H
