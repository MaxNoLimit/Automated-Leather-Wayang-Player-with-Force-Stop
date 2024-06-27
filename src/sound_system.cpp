#include "sound_system.hpp"

DFRobotDFPlayerMini sound_system;

/*
Function untuk initiation sound system dari Wayang
*/
void SoundSystem::initSound()
{
    pinMode(LED_BUILTIN, OUTPUT);
    Serial2.begin(9600);
    if (!sound_system.begin(Serial2))
    {
        Serial.println(F("Unable to begin:"));
        Serial.println(F("1.Please recheck the connection!"));
        Serial.println(F("2.Please insert the SD card!"));
        // while (true)
        // {
        //     delay(0);
        // }
    }
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println(F("DFPlayer Mini online."));

    sound_system.volume(20);
}

/*
Function untuk play suatu dialog yang ada di suatu chapter
*/
void SoundSystem::play_dialog(int chapter_number, int dialog_number)
{
    sound_system.playFolder(chapter_number, dialog_number);
    // if (sound_system.available())
    // {
    //     printDetail(sound_system.readType(), sound_system.read());
    // }
}


/*
Callback function dari example library
*/
void SoundSystem::printDetail(uint8_t type, int value)
{
    switch (type)
    {
    case TimeOut:
        Serial.println(F("Time Out!"));
        break;
    case WrongStack:
        Serial.println(F("Stack Wrong!"));
        break;
    case DFPlayerCardInserted:
        Serial.println(F("Card Inserted!"));
        break;
    case DFPlayerCardRemoved:
        Serial.println(F("Card Removed!"));
        break;
    case DFPlayerCardOnline:
        Serial.println(F("Card Online!"));
        break;
    case DFPlayerUSBInserted:
        Serial.println("USB Inserted!");
        break;
    case DFPlayerUSBRemoved:
        Serial.println("USB Removed!");
        break;
    case DFPlayerPlayFinished:
        Serial.print(F("Number:"));
        Serial.print(value);
        Serial.println(F(" Play Finished!"));
        break;
    case DFPlayerError:
        Serial.print(F("DFPlayerError:"));
        switch (value)
        {
        case Busy:
            Serial.println(F("Card not found"));
            break;
        case Sleeping:
            Serial.println(F("Sleeping"));
            break;
        case SerialWrongStack:
            Serial.println(F("Get Wrong Stack"));
            break;
        case CheckSumNotMatch:
            Serial.println(F("Check Sum Not Match"));
            break;
        case FileIndexOut:
            Serial.println(F("File Index Out of Bound"));
            break;
        case FileMismatch:
            Serial.println(F("Cannot Find File"));
            break;
        case Advertise:
            Serial.println(F("In Advertise"));
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

/*
Function untuk play audio dialog dari folder MP3 yang ada di SD card
*/
void SoundSystem::play_dialog_direct(int dialog_number)
{
    sound_system.playMp3Folder(dialog_number + 1);
}

// void SoundSystem::hold_the_section_until_finished()
// {
//     while (sound_system.readType() != DFPlayerPlayFinished)
//     {
//         // do nothing
//     }
//     Serial.println("\nDone!");
//     digitalWrite(LED_BUILTIN, LOW);
// }

// function to stop a while loop after df player finished playing current file
void SoundSystem::hold_the_section_until_finished(int delay_time)
{
    static unsigned long stop_watch = millis();

    while (millis() - stop_watch < delay_time)
    {
        // do nothing, just waiting
    }
}

void SoundSystem::playDialogFromACertainFolder(int nEpisode, int nDialog){
    sound_system.playFolder(nEpisode, nDialog);
}
