#include "mainheader.hpp"
#include "mainfunctions.hpp"

class Laksmana
{
public:
    void defaultStandPosition();
    void defaultHandPosition();
    void walk_to_scene(int distanceValue);
    void leave_from_scene(int distanceValue);

    void walk_to_a_certain_distance(int desiredDistance);
    void walk_to_a_certain_distance_before_calibrating_value(int desiredDistance);
};