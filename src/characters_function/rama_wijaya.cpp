#include "characters/rama_wijaya.hpp"
#include "a4988_nema.hpp"
#include "distanceSensorVL53L0X.hpp"

WayangHandServo Servo_RamaWijaya(whatSideServo::LEFT);
HorizontalController HC_rama_wijaya;

void RamaWijaya::defaultStandPosition()
{
    walk_to_a_certain_distance_before_calibrating_value(0);
}

void RamaWijaya::defaultHandPosition()
{
    anjujur();
}

void RamaWijaya::walk_to_scene(int distanceValue)
{
    HC_rama_wijaya.step_for_n_dir(3, distanceValue, "ccw");
}

void RamaWijaya::leave_from_scene(int distanceValue)
{
    HC_rama_wijaya.step_for_n_dir(3, distanceValue, "cw");
}

void RamaWijaya::walk_to_a_certain_distance(int desiredDistance)
{
    int readValue = getDistanceSensorNum(3);
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
        float result = difference / conv_value;
        int result_int = (int)result + 1;
        Serial.print(result_int);
        Serial.println(" steps\n");
        leave_from_scene(result_int);
        Serial.println("readValue 2: ");
        int finalReadValue = getDistanceSensorNum(3);
        ;
        Serial.print(finalReadValue);
        Serial.println("mm \n");
        if (finalReadValue > desiredDistance * 1.2)
        {
            walk_to_a_certain_distance(desiredDistance);
        }
    }
    else if (difference < 0)

    {
        // difference = difference - 10;
        float result = difference / conv_value;
        int result_int = (int)result + 1;
        Serial.print(result_int);
        Serial.println(" steps\n");
        result_int = abs(result_int);
        walk_to_scene(result_int);
        Serial.println("readValue 3: ");
        int finalReadValue = getDistanceSensorNum(3);
        ;
        Serial.print(finalReadValue);
        Serial.println("mm \n");
        if (finalReadValue < desiredDistance * 0.8)
        {
            walk_to_a_certain_distance(desiredDistance);
        }
    }
}

void RamaWijaya::walk_to_a_certain_distance_before_calibrating_value(int desiredDistance)
{
    int desiredDistanceAfterCalibratingValue = desiredDistance + 28;
    Serial.println("\ndesiredDistance: ");
    Serial.print(desiredDistanceAfterCalibratingValue);
    Serial.println("mm \n");
    walk_to_a_certain_distance(desiredDistanceAfterCalibratingValue);
}

// takes 1200 ms
void RamaWijaya::pointToFront()
{
    digitalWrite(WAYANG_HAND_3, HIGH);
    Servo_RamaWijaya.moveWhatServo(1, 30, 500);
    Servo_RamaWijaya.moveWhatServo(1, 0, 500);
    Servo_RamaWijaya.moveWhatServo(2, 9, 200);
    digitalWrite(WAYANG_HAND_3, LOW);
}

// takes 700 ms
void RamaWijaya::lower_pointToFront()
{
    digitalWrite(WAYANG_HAND_3, HIGH);
    Servo_RamaWijaya.moveWhatServo(1, 100, 500);
    Servo_RamaWijaya.moveWhatServo(2, 10, 200);
    digitalWrite(WAYANG_HAND_3, LOW);
}

// takes 1200 ms
void RamaWijaya::middleFront()
{
    digitalWrite(WAYANG_HAND_3, HIGH);
    Servo_RamaWijaya.moveWhatServo(2, 40, 200);
    Servo_RamaWijaya.moveWhatServo(1, 30, 500);
    Servo_RamaWijaya.moveWhatServo(1, 0, 500);
    digitalWrite(WAYANG_HAND_3, LOW);
}

// takes 700 ms
void RamaWijaya::downFront()
{
    digitalWrite(WAYANG_HAND_3, HIGH);
    Servo_RamaWijaya.moveWhatServo(1, 180, 500);
    Servo_RamaWijaya.moveWhatServo(2, 70, 200);
    digitalWrite(WAYANG_HAND_3, LOW);
}

// takes 1400 ms
void RamaWijaya::pointToBack()
{
    digitalWrite(WAYANG_HAND_3, HIGH);
    Servo_RamaWijaya.moveWhatServo(3, 90, 500);
    Servo_RamaWijaya.moveWhatServo(4, 120, 200);
    Servo_RamaWijaya.moveWhatServo(3, 180, 500);
    Servo_RamaWijaya.moveWhatServo(4, 140, 200);
    digitalWrite(WAYANG_HAND_3, LOW);
}

// takes 700 ms
void RamaWijaya::downBack()
{
    digitalWrite(WAYANG_HAND_3, HIGH);
    Servo_RamaWijaya.moveWhatServo(3, 20, 500);
    Servo_RamaWijaya.moveWhatServo(4, 80, 200);
    digitalWrite(WAYANG_HAND_3, LOW);
}

// takes 900 ms
void RamaWijaya::onHipBack()
{
    digitalWrite(WAYANG_HAND_3, HIGH);
    Servo_RamaWijaya.moveWhatServo(4, 60 + 10, 200);
    Servo_RamaWijaya.moveWhatServo(3, 110, 500);
    Servo_RamaWijaya.moveWhatServo(4, 70, 200);
    digitalWrite(WAYANG_HAND_3, LOW);
}

// takes 900 ms
void RamaWijaya::pointToSelf()
{
    digitalWrite(WAYANG_HAND_3, HIGH);
    Servo_RamaWijaya.moveWhatServo(2, 105, 200);
    Servo_RamaWijaya.moveWhatServo(1, 22, 500);
    Servo_RamaWijaya.moveWhatServo(2, 80, 200);
    digitalWrite(WAYANG_HAND_3, LOW);
}

// takes 1200 ms
void RamaWijaya::middleFrontBack()
{
    digitalWrite(WAYANG_HAND_3, HIGH);
    Servo_RamaWijaya.moveWhatServo(3, 30, 500);
    Servo_RamaWijaya.moveWhatServo(4, 60, 200);
    Servo_RamaWijaya.moveWhatServo(3, 125, 500);
    digitalWrite(WAYANG_HAND_3, LOW);
}

// takes 700 ms
void RamaWijaya::lowPointToBack()
{
    digitalWrite(WAYANG_HAND_3, HIGH);
    Servo_RamaWijaya.moveWhatServo(3, 90, 500);
    Servo_RamaWijaya.moveWhatServo(4, 120, 200);
    digitalWrite(WAYANG_HAND_3, LOW);
}

// takes 1200 ms
void RamaWijaya::middleBack()
{
    digitalWrite(WAYANG_HAND_3, HIGH);
    Servo_RamaWijaya.moveWhatServo(3, 90, 500);
    Servo_RamaWijaya.moveWhatServo(4, 100, 200);
    Servo_RamaWijaya.moveWhatServo(3, 180, 500);
    digitalWrite(WAYANG_HAND_3, LOW);
}

// takes duration value
void RamaWijaya::directControl(int num, int angle, int duration)
{
    digitalWrite(WAYANG_HAND_2, HIGH);
    Servo_RamaWijaya.moveWhatServo(num, angle, duration);
    digitalWrite(WAYANG_HAND_2, LOW);
}

// takes 1400 ms
void RamaWijaya::anjujur()
{
    Servo_RamaWijaya.resetArray();
    downBack();
    downFront();
}

// takes 2300 ms
void RamaWijaya::mathenthengA()
{
    anjujur();
    onHipBack();
}

// takes 2300 ms
void RamaWijaya::mathentengC()
{
    anjujur();
    digitalWrite(WAYANG_HAND_3, HIGH);
    Servo_RamaWijaya.moveWhatServo(4, 60 + 10, 200);
    Servo_RamaWijaya.moveWhatServo(3, 120, 500);
    Servo_RamaWijaya.moveWhatServo(4, 90, 200);
    digitalWrite(WAYANG_HAND_3, LOW);
}