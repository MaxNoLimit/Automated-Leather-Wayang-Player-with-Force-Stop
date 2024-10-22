#include "mainheader.hpp"
#include "mainfunctions.hpp"

class RamaWijaya
{

public:
    void defaultStandPosition();
    void defaultHandPosition();
    void walk_to_scene(int distanceValue);
    void leave_from_scene(int distanceValue);

    void walk_to_a_certain_distance(int desiredDistance);
    void walk_to_a_certain_distance_before_calibrating_value(int desiredDistance);

    void hand_movement_test_1();
    void hand_movement_test_2();
    void hand_movement_test_3();
    void hand_movement_test_4();

    void left_pointToSelf();
    void right_moveHandBackAbit();
    void right_handOnHip();
    void left_pointToFront();

    void talking(int delay_in_sec);

    // Command list for hand movement
    void pointToFront();
    void lower_pointToFront();
    void middleFront();
    void downFront();
    void pointToBack();
    void downBack();
    void onHipBack();
    void pointToSelf();
    // void lowPointToSelf();
    void middleFrontBack();
    void lowPointToBack();
    void middleBack();
    // void respect();

    // Gerakan diam
    void anjujur();
    void mathenthengA();
    void mathentengC();

    void directControl(int num, int angle, int duration);
};