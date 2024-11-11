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
    // digitalWrite(WAYANG_HAND_3, HIGH);
    // Servo_RamaWijaya.defaultPosition();
    // // Servo_RamaWijaya.moveWhatServo(2, 60, 2000);
    // // Servo_RamaWijaya.moveWhatServo(4, 60, 2000);
    // downBack();
    // onHipBack();
    // Servo_RamaWijaya.resetArray();
    // digitalWrite(WAYANG_HAND_3, LOW);
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

void RamaWijaya::hand_movement_test_1()
{
    digitalWrite(WAYANG_HAND_3, HIGH);
    // Servo_RamaWijaya.moveWhatServo(1, 0);
    // delay(10);
    // Servo_RamaWijaya.moveWhatServo(2, 0);
    // delay(10);
    // Servo_RamaWijaya.moveWhatServo(3, 180);
    // delay(10);
    // Servo_RamaWijaya.moveWhatServo(4, 180);
    // delay(1000);
    // Servo_RamaWijaya.moveWhatServo(1, 180);
    // delay(10);
    // Servo_RamaWijaya.moveWhatServo(2, 180);
    // delay(10);
    // Servo_RamaWijaya.moveWhatServo(3, 0);
    // delay(10);
    // Servo_RamaWijaya.moveWhatServo(4, 0);
    // delay(1000);
    digitalWrite(WAYANG_HAND_3, LOW);
}

void RamaWijaya::hand_movement_test_2()
{
}

void RamaWijaya::hand_movement_test_3()
{
}

void RamaWijaya::hand_movement_test_4()
{
}

void RamaWijaya::talking(int delay_in_sec)
{
    // digitalWrite(WAYANG_HAND_1, HIGH);
    // for (int i = 0; i < (delay_in_sec * 1000000 / 4998272) - 1; i++)
    // {
    //     rama_wijaya_stepper.rightHandSpin("ccw", 90);
    //     rama_wijaya_stepper.rightHandSpin("cw", 90);
    //     delay(2000);
    // }
    // rama_wijaya_stepper.stopAllStepper();
    // digitalWrite(WAYANG_HAND_1, LOW);
}

void RamaWijaya::right_moveHandBackAbit()
{
    digitalWrite(WAYANG_HAND_3, HIGH);
    Servo_RamaWijaya.moveWhatServo(4, 120, 2000);
    Servo_RamaWijaya.moveWhatServo(3, 90, 2000);
    Servo_RamaWijaya.moveWhatServo(4, 135, 2000);
    Servo_RamaWijaya.moveWhatServo(3, 120, 2000);
    digitalWrite(WAYANG_HAND_3, LOW);
}

void RamaWijaya::right_handOnHip()
{
    digitalWrite(WAYANG_HAND_3, HIGH);
    Servo_RamaWijaya.defaultPosition();
    Servo_RamaWijaya.moveWhatServo(4, 60, 2000);
    Servo_RamaWijaya.moveWhatServo(3, 90, 2000);
    Servo_RamaWijaya.moveWhatServo(4, 90, 2000);
    // Servo_RamaWijaya.moveWhatServo(4, 70, 2500);
    // Servo_RamaWijaya.moveWhatServo(3, 80, 2500);
    // Servo_RamaWijaya.moveWhatServo(4, 50, 2500);
    // Servo_RamaWijaya.moveWhatServo(3, 100, 2500);
    // Servo_RamaWijaya.moveWhatServo(4, 90, 2500);
    digitalWrite(WAYANG_HAND_3, LOW);
}

void RamaWijaya::left_pointToFront()
{
    digitalWrite(WAYANG_HAND_3, HIGH);
    Servo_RamaWijaya.defaultPosition();
    Servo_RamaWijaya.moveWhatServo(1, 0, 3000);
    Servo_RamaWijaya.moveWhatServo(2, 50, 2000);
    // Servo_RamaWijaya.moveWhatServo(1, 90, 3000);
    // Servo_RamaWijaya.moveWhatServo(2, 60, 3000);
    // Servo_RamaWijaya.moveWhatServo(1, 0, 3000);
    // Servo_RamaWijaya.moveWhatServo(2, 55, 3000);

    digitalWrite(WAYANG_HAND_3, LOW);
}

void RamaWijaya::left_pointToSelf()
{
    digitalWrite(WAYANG_HAND_3, HIGH);
    Servo_RamaWijaya.defaultPosition();
    Servo_RamaWijaya.moveWhatServo(2, 120, 2000);
    Servo_RamaWijaya.moveWhatServo(1, 0, 2000);
    digitalWrite(WAYANG_HAND_3, LOW);
}

void RamaWijaya::walk_to_a_certain_distance(int desiredDistance)
{

    // desiredDistance = desiredDistance + (float)desiredDistance * 0.093;
    // Serial.println("\ndesiredDistance: ");
    // Serial.print(desiredDistance);
    // Serial.println("mm \n");
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
        float result = difference / 0.3;
        int result_int = (int)result + 1;
        Serial.print(result_int);
        Serial.println(" steps\n");
        leave_from_scene(result_int);
        Serial.println("readValue 2: ");
        int finalReadValue = getDistanceSensorNum(3);;
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
        float result = difference / 0.3;
        int result_int = (int)result - 1;
        Serial.print(result_int);
        Serial.println(" steps\n");
        result_int = abs(result_int);
        walk_to_scene(result_int);
        Serial.println("readValue 3: ");
        int finalReadValue = getDistanceSensorNum(3);;
        Serial.print(finalReadValue);
        Serial.println("mm \n");
        if (finalReadValue < desiredDistance * 0.8)
        {
            walk_to_a_certain_distance(desiredDistance);
        }
    }
    else
    {
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
    // Servo_RamaWijaya.resetArray();
    // Servo_RamaWijaya.moveWhatServo(2, 70, 500);
    Servo_RamaWijaya.moveWhatServo(1, 30, 500); // this is to avoid resetArray bug that skip servo1 to 0 deg or move to highest position
    Servo_RamaWijaya.moveWhatServo(1, 0, 500);
    Servo_RamaWijaya.moveWhatServo(2, 10, 200);
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
    Servo_RamaWijaya.moveWhatServo(2, 50, 200);
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
    // Servo_RamaWijaya.defaultPosition();
    Servo_RamaWijaya.moveWhatServo(2, 105, 200);
    Servo_RamaWijaya.moveWhatServo(1, 22, 500);
    Servo_RamaWijaya.moveWhatServo(2, 80, 200);
    digitalWrite(WAYANG_HAND_3, LOW);
}

// takes 1200 ms
void RamaWijaya::middleFrontBack()
{
    digitalWrite(WAYANG_HAND_3, HIGH);
    // downBack();
    // onHipBack();
    // defaultHandPosition();
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
    // Servo_RamaWijaya.moveWhatServo(3, 180, 2000);
    // Servo_RamaWijaya.moveWhatServo(4, 150, 500);
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
void RamaWijaya::anjujur(){
    Servo_RamaWijaya.resetArray();
    downBack();
    downFront();
}

// takes 2300 ms
void RamaWijaya::mathenthengA(){
    anjujur();
    onHipBack();
}

// takes 2300 ms
void RamaWijaya::mathentengC(){
    anjujur();
    digitalWrite(WAYANG_HAND_3, HIGH);
    Servo_RamaWijaya.moveWhatServo(4, 60 + 10, 200);
    Servo_RamaWijaya.moveWhatServo(3, 120, 500);
    Servo_RamaWijaya.moveWhatServo(4, 90, 200);
    digitalWrite(WAYANG_HAND_3, LOW);
}