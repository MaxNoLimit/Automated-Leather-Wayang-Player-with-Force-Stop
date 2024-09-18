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
        // 001 (Sita1Sita-Laksmana dialogue 1) 
        SITA1SITA_LAKS_DIALOGUE_1 = 1,
        // 002 (01 S-L1 Laksmana1F) 
        S_L1_LAKS1F = 2,
        // 003 (Sita2Sita-Laksmana dialogue 1) 
        SITA2SITA_LAKS_DIALOGUE_1 = 3,
        // 004 (02 S-L1 Laksmana2F) 
        S_L1_LAKS2F = 4,
        // 005 (005SitaRahwanadialogueRahwana1)
        SITA_RAHWANA_DIALOGUE_RAHWANA_1 = 5,
        // 006 (006SitaRahwanadialogueSita1)
        SITA_RAHWANA_DIALOGUE_SITA_1 = 6,
        // 007 (007SitaRahwanadialogueRahwana2)
        SITA_RAHWANA_DIALOGUE_RAHWANA_2 = 7,
        // 008 (03 L-R1 Laksmana1F) 
        L_R1_LAKS1F = 8,
        // 009 (Rama1Laksmana-Rama Diaglogue(in place of narrator for context)) 
        RAMA1LAKS_RAMA_DIALOGUE_IN_PLACE_NARATOR = 9,
        // 010 (04 H-R1 Hanuman1F)
        H_R1_HANUMAN1F = 10,
        // 011 (Rama1Hanuman-Rama dialogue_E)
        RAMA1HANUMAN_RAMA_DIALOGUE_E = 11,
        // 012 (05 H-R1 Hanuman2F)
        H_R1_HANUMAN2F = 12,
        // 013 (06 S-R1 Sugriwa1F)
        S_R1_SUGRIWA1F = 13,
        // 014 (07 Duel1 Sugriwa1F)
        DUEL1_SUGRIWA1F = 14,
        // 015 (Subali round 1 rage)
        SUBALI_ROUND_1_RAGE = 15,
        // 016 (08 Duel1 Sugriwa2F)
        DUEL1_SUGRIWA2F = 16,
        // 017 (09 DuAft1 Sugriwa1F)
        DUAFT1_SUGRIWA1F = 17,
        // 018 (Rama1Sugriwa-Rama-Subali dialogue)
        RAMA1SUGRIWA_RAMA_SUBALI_DIALOGUE = 18,
        // 019 (10 Duel2 Sugriwa1F)
        DUEL2_SUGRIWA1F = 19,
        // 020 (Subali round 2 rage)
        SUBALI_ROUND_2_RAGE = 20,
        // 021 (Subali bacotin rama_E)
        SUBALI_BACOTIN_RAMA_E = 21,
        // 022 (Rama2Sugriwa-Rama-Subali dialogue_E)
        RAMA2SUGRIWA_RAMA_SUBALI_DIALOGUE_E = 22,
        // 023 (Subali tobat_E)
        SUBALI_TOBAT_E = 23,
        // 024 (11 S-R2 Sugriwa1F)
        S_R2_SUGRIWA1F = 24,
        // 025 (Rama1Sugriwa-Rama dialogue 2_E)
        RAMA1SUGRIWA_RAMA_DIALOGUE_2_E = 25,
        // 026 (Rama Sadboi_E)
        RAMA_SADBOI_E = 26,
        // 027 (Rama telling laksmana to bacot sugriwa_E)
        RAMA_TELLING_LAKSMANA_BACOT_SUGRIWA_E = 27,
        // 028 (12 SApol Sugriwa1F)
        SApol_Sugriwa1F = 28,
        // 029 (13 SApol Sugriwa2F)
        SApol_Sugriwa2F = 29,
        // 030 (14 SApol Hanuman1F)
        SApol_Hanuman1F = 30,
        // 031 (15 SApol Sugriwa3F)
        SApol_Sugriwa3F = 31,
        // 032 (Rama forgives sugriwa) 
        RAMA_FORGIVES_SUGRIWA = 32,


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
