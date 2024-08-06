#include "mainheader.hpp"
#include "mainfunctions.hpp"

class Sita
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

    void left_raise_hand();
    void left_lower_hand();
    void left_raise_half_hand();
    void left_lower_half_hand();

    void right_raise_hand();
    void right_lower_hand();
    void right_raise_half_hand();
    void right_lower_half_hand();

    void pointToSelf();
    void right_handOnHip();
    void left_pointToFront();

    void talking(int delay_in_sec);
};