#include "characters/hanoman.hpp"
#include "a4988_nema.hpp"
#include "distanceSensorVL53L0X.hpp"

WayangHandServo Servo_Hanuman(whatSideServo::RIGHT);
HorizontalController HC_hanoman;

void Hanoman::defaultHandPosition()
{
    digitalWrite(WAYANG_HAND_4, HIGH);
    Servo_Hanuman.moveWhatServo(4, 100, 1000);
    Servo_Hanuman.moveWhatServo(2, 100, 1000);
    Servo_Hanuman.defaultPosition();
    Servo_Hanuman.moveWhatServo(4, 110, 1000);
    Servo_Hanuman.moveWhatServo(2, 110, 2000);
    Servo_Hanuman.moveWhatServo(1, 80, 1000);

    digitalWrite(WAYANG_HAND_4, LOW);
}
void Hanoman::defaultStandPosition()
{
    walk_to_a_certain_distance_before_calibrating_value(28);
}

void Hanoman::leave_from_scene(int distanceValue)
{
    HC_hanoman.step_for_n_dir(4, distanceValue, "ccw");
}

void Hanoman::walk_to_a_certain_distance(int desiredDistance)
{
    if (!getSensorStatus(4))
    {
        beginSensor4();
    }

    int readValue = getDistanceSensor4();
    if (readValue > 1000)
    {
        readValue = 800;
    }

    Serial.println("readValue 1: ");
    Serial.print(readValue);
    Serial.println("mm \n");
    float difference = readValue - desiredDistance;
    Serial.print(difference);
    Serial.println("mm \n");
    if (difference > 0)
    {
        // difference = difference + 10;
        float result = difference / 0.3;
        int result_int = (int)result + 1;
        Serial.print(result_int);
        Serial.println(" steps\n");
        leave_from_scene(result_int);
        Serial.println("readValue 2: ");
        int finalReadValue = getDistanceSensor4();
        Serial.print(finalReadValue);
        Serial.println("mm \n");
        if (finalReadValue > desiredDistance)
        {
            walk_to_a_certain_distance(desiredDistance);
        }
    }
    else if (difference < 0)

    {
        // difference = difference - 10;
        float result = difference / 0.3;
        int result_int = (int)result - 1;
        Serial.print(result_int);
        Serial.println(" steps\n");
        result_int = abs(result_int);
        walk_to_scene(result_int);
        Serial.println("readValue 2: ");
        int finalReadValue = getDistanceSensor4();
        Serial.print(finalReadValue);
        Serial.println("mm \n");
        if (finalReadValue < desiredDistance)
        {
            walk_to_a_certain_distance(desiredDistance);
        }
    }
}

void Hanoman::walk_to_a_certain_distance_before_calibrating_value(int desiredDistance)
{
    int desiredDistanceAfterCalibratingValue = desiredDistance + (float)desiredDistance * 0.155;
    Serial.println("\ndesiredDistance: ");
    Serial.print(desiredDistanceAfterCalibratingValue);
    Serial.println("mm \n");
    walk_to_a_certain_distance(desiredDistanceAfterCalibratingValue);
}

void Hanoman::walk_to_scene(int distanceValue)
{
    HC_hanoman.step_for_n_dir(4, distanceValue, "cw");
}


void Hanoman::pointToFront(){

}

void Hanoman::lower_pointToFront(){

}

void Hanoman::middleFront(){

}

void Hanoman::downFront(){

}

void Hanoman::pointToBack(){

}

void Hanoman::downBack(){

}

void Hanoman::onHipBack(){

}

void Hanoman::pointToSelf(){

}

void Hanoman::middleFrontBack(){

}

void Hanoman::lowPointToBack(){

}

void Hanoman::middleBack(){

}