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
        SENSOR_CHECK,
        PLAY_EPISODE_1,
        PLAY_EPISODE_2,
        PLAY_EPISODE_3,
        PLAY_EPISODE_4,
        PLAY_EPISODE_5,
    };

    enum PAGE_ROUTE
    {
        MENU_PAGE,
        EPISODE_PAGE,
        CALIBRATE_PAGE,
        SETTINGS_PAGE,
        SENSOR_STATUS_PAGE,
    };

    enum SUB_EPISODE_PAGE_ROUTE{
        EPISODE123,
        EPISODE1234,
        EPISODE2345,
    };

    enum SETTINGS_PAGE_ROUTE{
        OPTION_SETTINGS,
        VOLUME_SETTINGS,
    };

    enum SUB_CALIBRATE_PAGE_ROUTE{
        CALIBRATE_1,
        CALIBRATE_2,
    };

    enum SENSOR_STATUS_PAGE_ROUTE{
        SENSOR_123 = 1,
        SENSOR_1234,
        SENSOR_2345,
        SENSOR_3456,
        SENSOR_4567,
        SENSOR_5678,
        SENSOR_6789,
        SENSOR_78910,
    };
};



#endif // STATE_MANAGEMENT_H