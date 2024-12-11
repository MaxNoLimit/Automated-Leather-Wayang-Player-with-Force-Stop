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

    enum INDICATOR_SOUND_NUMBER
    {
        INDICATOR_AUDIO_1 = 1,
        INDICATOR_VSLOT_CALIBRATION = 2,
        INDICATOR_WAYANG_HAND_CALIBRATION = 3,
        INDICATOR_FINISHED_SHOWING = 4,
    };

    enum SPECIAL_EPISODE_29_JULY
    {
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

    enum EPISODE_1_DIALOG
    {
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

    enum EPISODE_3_DIALOG
    {
        // 001_Sita-Rahwana-Hanuman_Rawana1
        SITA_RAHWANA_HANUMAN_RAHWANA1 = 1,
        // 002_Sita-Rahwana-Hanuman_Rawana2
        SITA_RAHWANA_HANUMAN_RAHWANA2 = 2,
        // 003_Sita-Rahwana-Hanuman_Sita1
        SITA_RAHWANA_HANUMAN_SITA1 = 3,
        // 004_Sita-Rahwana-Hanuman_Rawana3
        SITA_RAHWANA_HANUMAN_RAHWANA3 = 4,
        // 005_Sita-Rahwana-Hanuman_Sita2
        SITA_RAHWANA_HANUMAN_SITA2 = 5,
        // 006_Sita-Rahwana-Hanuman_Hanuman1
        SITA_RAHWANA_HANUMAN_HANUMAN1 = 6,
        // 007_Sita-Rahwana-Hanuman_Sita3
        SITA_RAHWANA_HANUMAN_SITA3 = 7,
        // 008_Sita-Rahwana-Hanuman_Hanuman2
        SITA_RAHWANA_HANUMAN_HANUMAN2 = 8,
        // 009_Sita-Rahwana-Hanuman_Hanuman3
        SITA_RAHWANA_HANUMAN_HANUMAN3 = 9,
        // 010_Hanuman-Rahwana-Wibhisana_HanumanEnter
        HANUMAN_RAHWANA_WIBHISANA_HANUMANENTER = 10,
        // 011_Hanuman-Rahwana-Wibhisana_Rahwana1
        HANUMAN_RAHWANA_WIBHISANA_RAHWANA1 = 11,
        // 012_Hanuman-Rahwana-Wibhisana_Wibhisana1
        HANUMAN_RAHWANA_WIBHISANA_WIBHISANA1 = 12,
        // 013_Hanuman-Rahwana-Wibhisana_Rahwana2
        HANUMAN_RAHWANA_WIBHISANA_RAHWANA2 = 13,
        // 014_Hanuman-Rahwana-Wibhisana_Hanuman1
        HANUMAN_RAHWANA_WIBHISANA_HANUMAN1 = 14,
        // 015_Hanuman-Rahwana-Wibhisana_Rahwana3
        HANUMAN_RAHWANA_WIBHISANA_RAHWANA3 = 15,
        // 016_Hanuman-Rahwana-Wibhisana_Hanuman2
        HANUMAN_RAHWANA_WIBHISANA_HANUMAN2 = 16,
        // 017_Hanuman-Rahwana-Wibhisana_Rahwana4
        HANUMAN_RAHWANA_WIBHISANA_RAHWANA4 = 17,
        // 018_Hanuman-Rahwana-Wibhisana_HanumanRoar
        HANUMAN_RAHWANA_WIBHISANA_HANUMANROAR = 18,
        // 019_Hanuman-Rahwana-Wibhisana_Rahwana5
        HANUMAN_RAHWANA_WIBHISANA_RAHWANA5 = 19,

    };

    enum EPISODE_4_DIALOG
    {
        // 019_Hanuman_pays_respect_Hanuman1
        HANUMAN_PAYS_RESPECT_HANUMAN1 = 1,
        // 021_Hanuman_returns_to_rama_Nila1
        HANUMAN_RETURNS_TO_RAMA_NILA1 = 2,
        // 022_Hanuman_returns_to_rama_Anggada1
        HANUMAN_RETURNS_TO_RAMA_ANGGADA1 = 3,
        // 023_Hanuman_returns_to_rama_Nila2
        HANUMAN_RETURNS_TO_RAMA_NILA2 = 4,
        // 024_Hanuman_returns_to_rama_Anggada2
        HANUMAN_RETURNS_TO_RAMA_ANGGADA2 = 5,
        // 027_Hanuman_returns_to_rama_Hanuman1
        HANUMAN_RETURNS_TO_RAMA_HANUMAN1 = 6,
        // 028_Hanuman_returns_to_rama_Rama1
        HANUMAN_RETURNS_TO_RAMA_RAMA1 = 7,
        // 029_Hanuman_returns_to_rama_Hanuman2
        HANUMAN_RETURNS_TO_RAMA_HANUMAN2 = 8,
        // 030_Hanuman_returns_to_rama_Rama2
        HANUMAN_RETURNS_TO_RAMA_RAMA2 = 9,

        // 031_Wibhisana-Rahwana_Wibhisana1
        WIBHISANA_RAHWANA_WIBHISANA1 = 10,
        // 032_Wibhisana-Rahwana_Rahwana1
        WIBHISANA_RAHWANA_RAHWANA1 = 11,
        // 032.5_wibhisana-Rahwana_Rahwana2 (punch)
        WIBHISANA_RAHWANA_RAHWANA2 = 12,
        // 033_Wibhisana-Rahwana_Wibhisana2
        WIBHISANA_RAHWANA_WIBHISANA2 = 13,
        
        // 034_Wibhisana_Defects_Hanuman1
        WIBHISANA_DEFECTS_HANUMAN1 = 14,
        // 035_Wibhisana_Defects_Wibhisana1
        WIBHISANA_DEFECTS_WIBHISANA1 = 15,
        // 036_Wibhisana_Defects_Hanuman2
        WIBHISANA_DEFECTS_HANUMAN2 = 16,
        // 037_Wibhisana_Defects_Nila1
        WIBHISANA_DEFECTS_NILA1 = 17,
        
        // 038_Rama_informed_Nila1
        RAMA_INFORMED_NILA1 = 18,
        // 039_Rama_informed_Rama1
        RAMA_INFORMED_RAMA1 = 19,
        
        // 040_Before_final_ultimatum_Sugriwa1
        BEFORE_FINAL_ULTIMATUM_SUGRIWA1 = 20,
        // 041_Before_final_ultimatum_Laksmana1
        BEFORE_FINAL_ULTIMATUM_LAKSMANA1 = 21,
        // 042_Before_final_ultimatum_Rama1
        BEFORE_FINAL_ULTIMATUM_RAMA1 = 22,
    };

    enum DIALOG_NUMBER
    {
        NARATOR_INTRO_1,
        HANUMAN_1,
        RAMA_1,
        HANUMAN_2,
        NARATOR_END_1
    };

    enum MUSIC_NUMBER
    {
        MUSIC_GAMELAN = 1,
    };

    void justInitTheSoundSystem();
    void initSound();
    void play_dialog(int chapter_number, int dialog_number); // may be 0-2999 according to the df mini player documentation
    void printDetail(uint8_t type, int value);
    void play_dialog_direct(int dialog_number);
    void playDialogFromACertainFolder(int nEpisode, int nDialog);
    void continuePlaying();
    void pause();
    void playMusicWayang();
    void pauseMusicWayang();
    void setVolume(int volume);
};

extern int volumeHardcoded;
extern int volumeHardcodedMusic;

#endif // SOUND_SYSTEM_H
