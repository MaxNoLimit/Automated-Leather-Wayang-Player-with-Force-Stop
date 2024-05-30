#ifndef SOUND_SYSTEM_H
#define SOUND_SYSTEM_H

#include "mainheader.hpp"
#include <DFRobotDFPlayerMini.h>

namespace SoundSystem
{
    // enum CHAPTER_NUMBER
    // {
    //     CHAPTER_1,
    //     CHAPTER_2,
    //     CHAPTER_3,
    //     CHAPTER_4
    // };
    enum DIALOG_NUMBER
    {
        NARATOR_INTRO_1,
        HANUMAN_1,
        RAMA_1,
        HANUMAN_2,
        NARATOR_END_1
    };

    void initSound();
    void play_dialog(int chapter_number, int dialog_number); // may be 0-2999 according to the df mini player documentation
    void printDetail(uint8_t type, int value);
    void play_dialog_direct(int dialog_number);
    void hold_the_section_until_finished(int delay_time);
};

#endif // SOUND_SYSTEM_H
