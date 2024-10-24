#include "mainheader.hpp"
#include "mainfunctions.hpp"

class Rahwana
{
public:
    void defaultStandPosition();
    void defaultHandPosition();
    void walk_to_scene(int distanceValue);

    void walk_to_a_certain_distance(int desiredDistance);
    void walk_to_a_certain_distance_before_calibrating_value(int desiredDistance);

    void leave_from_scene(int distanceValue);

    void hand_movement_test_1();
    void Rahwana_1();
    void RahwanaSelfTalk(int frontpin, int backpin, int oscdeg, int timeMillis, int periodMillis);
    void hand_movement_1();
    void hand_movement_2();
    void hand_movement_3();
    void hand_movement_4();
    void hand_movement_5();
    void hand_movement_6();
    void hand_movement_7();

    void hand_movement_8();
    void hand_movement_9();
    void hand_movement_10();
    void hand_movement_11();
    void hand_movement_12();
    void hand_movement_13();
    void hand_movement_14();
    void hand_movement_15();
    void hand_movement_16();
    void hand_movement_17();
    void hand_movement_18();

    void rahwana_120_bpm_deathstream();

    // Command list for hand movement
    
    void pointToFront();
    void lower_pointToFront();
    void middleFront();
    void downFront();
    void pointToSelf();
    // void respect();

    void directControl(int num, int angle, int duration);
};