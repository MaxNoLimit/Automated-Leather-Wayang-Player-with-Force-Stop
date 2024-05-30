#ifndef STATE_MANAGEMENT_H
#define STATE_MANAGEMENT_H

#include <Arduino.h>

namespace StateManagement
{
    enum FSA_STATE
    {
        DEFAULT_LOOPING_LCD,
        CALIBRATING_ALL_NEMA,
        MP3_REINIT,
        WAYANG_HAND_CALIBRATION,
    };

    enum PAGE_ROUTE
    {
        MENU_PAGE,
        EPISODE_PAGE,
        CALIBRATE_PAGE,
        SETTINGS_PAGE
    };

    enum SUB_EPISODE_PAGE_ROUTE{
        EPISODE123,
        EPISODE1234,
        EPISODE2345,
    };
};

#endif // STATE_MANAGEMENT_H