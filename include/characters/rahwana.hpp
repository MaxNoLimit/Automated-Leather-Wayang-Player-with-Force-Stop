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

    // Command list for hand movement
    
    void pointToFront();
    void lower_pointToFront();
    void middleFront();
    void downFront();
    void pointToSelf();

    void directControl(int num, int angle, int duration);
};