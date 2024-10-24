#include "mainheader.hpp"
#include "mainfunctions.hpp"

class Anila{
    public:
    void defaultStandPosition();
    void defaultHandPosition();

    void walk_to_scene(int distanceValue);
    void leave_from_scene(int distanceValue);

    void walk_to_a_certain_distance(int desiredDistance);
    void walk_to_a_certain_distance_before_calibrating_value(int desiredDistance);

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
    void mathentengA();
    // void mathentengB();
    void mathentengC();

    void directControl(int num, int angle, int duration);
};