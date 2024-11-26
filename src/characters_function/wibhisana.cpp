#include "characters/wibhisana.hpp"
#include "a4988_nema.hpp"
#include "distanceSensorVL53L0X.hpp"

WayangHandServo Servo_Wibhisana(whatSideServo::LEFT);
HorizontalController HC_wibhisana;

void Wibhisana::defaultHandPosition()
{
    // digitalWrite(WAYANG_HAND_8, HIGH);
    // // Servo_Wibhisana.moveWhatServo(4, 100, 500);
    // // Servo_Wibhisana.moveWhatServo(2, 140, 500);
    // // Servo_Wibhisana.defaultPosition();
    // // Servo_Wibhisana.moveWhatServo(4, 110, 200);
    // downFront();
    // downBack();
    // onHipBack();
    // directControl(2, 70, 200);
    // Servo_Wibhisana.resetArray();

    // digitalWrite(WAYANG_HAND_8, LOW);
    mathentengA();
}

void Wibhisana::defaultStandPosition()
{
    walk_to_a_certain_distance_before_calibrating_value(0);
}

void Wibhisana::leave_from_scene(int distanceValue)
{
    HC_wibhisana.step_for_n_dir(8, distanceValue, "cw");
}

void Wibhisana::walk_to_scene(int distanceValue)
{
    HC_wibhisana.step_for_n_dir(8, distanceValue, "ccw");
}

void Wibhisana::walk_to_a_certain_distance(int desiredDistance)
{

    int readValue = getDistanceSensorNum(8);
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
        int finalReadValue = getDistanceSensorNum(8);
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
        Serial.println("readValue 2: ");
        int finalReadValue = getDistanceSensorNum(8);
        Serial.print(finalReadValue);
        Serial.println("mm \n");
        if (finalReadValue < desiredDistance * 0.8)
        {
            walk_to_a_certain_distance(desiredDistance);
        }
    }
}

void Wibhisana::walk_to_a_certain_distance_before_calibrating_value(int desiredDistance)
{
    int desiredDistanceAfterCalibratingValue = desiredDistance + 45;
    Serial.println("\ndesiredDistance: ");
    Serial.print(desiredDistanceAfterCalibratingValue);
    Serial.println("mm \n");
    walk_to_a_certain_distance(desiredDistanceAfterCalibratingValue);
}

// takes 900 ms
void Wibhisana::pointToFront()
{
    digitalWrite(WAYANG_HAND_8, HIGH);
    // Servo_Wibhisana.moveWhatServo(1, 150, 200);
    Servo_Wibhisana.moveWhatServo(2, 75, 200);
    Servo_Wibhisana.moveWhatServo(1, 5, 500);
    Servo_Wibhisana.moveWhatServo(2, 35, 200);
    digitalWrite(WAYANG_HAND_8, LOW);
}

// takes 700 ms
void Wibhisana::lower_pointToFront()
{
    digitalWrite(WAYANG_HAND_8, HIGH);
    Servo_Wibhisana.moveWhatServo(1, 90, 500);
    Servo_Wibhisana.moveWhatServo(2, 80, 200);
    digitalWrite(WAYANG_HAND_8, LOW);
}

// takes 1200 ms
void Wibhisana::middleFront()
{
    digitalWrite(WAYANG_HAND_8, HIGH);
    Servo_Wibhisana.moveWhatServo(1, 100, 500);
    Servo_Wibhisana.moveWhatServo(2, 80, 200);
    Servo_Wibhisana.moveWhatServo(1, 5, 500);
    digitalWrite(WAYANG_HAND_8, LOW);
}

// takes 700 ms
void Wibhisana::downFront()
{
    digitalWrite(WAYANG_HAND_8, HIGH);
    Servo_Wibhisana.moveWhatServo(1, 130, 500);
    Servo_Wibhisana.moveWhatServo(2, 70, 200);
    digitalWrite(WAYANG_HAND_8, LOW);
}

// takes 1400 ms
void Wibhisana::pointToBack()
{
    digitalWrite(WAYANG_HAND_8, HIGH);
    Servo_Wibhisana.moveWhatServo(3, 90, 500);
    Servo_Wibhisana.moveWhatServo(4, 120, 200);
    Servo_Wibhisana.moveWhatServo(3, 180, 500);
    Servo_Wibhisana.moveWhatServo(4, 140, 200);
    digitalWrite(WAYANG_HAND_8, LOW);
}

// takes 700 ms
void Wibhisana::downBack()
{
    digitalWrite(WAYANG_HAND_8, HIGH);
    Servo_Wibhisana.moveWhatServo(3, 80, 500);
    Servo_Wibhisana.moveWhatServo(4, 50, 200);
    digitalWrite(WAYANG_HAND_8, LOW);
}

// takes 700 ms
void Wibhisana::onHipBack()
{
    digitalWrite(WAYANG_HAND_8, HIGH);
    // Servo_Wibhisana.moveWhatServo(4, 80, 200);
    Servo_Wibhisana.moveWhatServo(3, 160, 500);
    Servo_Wibhisana.moveWhatServo(4, 95, 200);
    digitalWrite(WAYANG_HAND_8, LOW);
}

// takes 2100 ms
void Wibhisana::mathentengA()
{
    Servo_Wibhisana.resetArray();
    downBack();
    onHipBack();
    downFront();
}

// takes 2300 ms
void Wibhisana::mathentengC()
{
    Servo_Wibhisana.resetArray();
    downBack();
    downFront();
    digitalWrite(WAYANG_HAND_8, HIGH);
    // Servo_Wibhisana.moveWhatServo(4, 105, 200);
    Servo_Wibhisana.moveWhatServo(3, 180, 500);
    Servo_Wibhisana.moveWhatServo(4, 110, 200);
    Servo_Wibhisana.moveWhatServo(2, 60, 200);
    digitalWrite(WAYANG_HAND_8, LOW);
}

// takes 900 ms
void Wibhisana::pointToSelf()
{
    digitalWrite(WAYANG_HAND_8, HIGH);
    // Servo_Wibhisana.moveWhatServo(1, 135, 500);
    Servo_Wibhisana.moveWhatServo(2, 120, 200);
    Servo_Wibhisana.moveWhatServo(1, 20, 500);
    Servo_Wibhisana.moveWhatServo(2, 100, 200);
    digitalWrite(WAYANG_HAND_8, LOW);
}

// takes 700 ms
void Wibhisana::middleFrontBack()
{
    digitalWrite(WAYANG_HAND_8, HIGH);
    Servo_Wibhisana.moveWhatServo(3, 90, 500);
    Servo_Wibhisana.moveWhatServo(4, 60, 200);
    digitalWrite(WAYANG_HAND_8, LOW);
}

// takes 700 ms
void Wibhisana::lowPointToBack()
{
    digitalWrite(WAYANG_HAND_8, HIGH);
    Servo_Wibhisana.moveWhatServo(3, 135, 500);
    Servo_Wibhisana.moveWhatServo(4, 125, 200);
    // Servo_Wibhisana.moveWhatServo(1, 45, 2000);
    // Servo_Wibhisana.moveWhatServo(2, 40, 500);
    digitalWrite(WAYANG_HAND_8, LOW);
}

// takes 1400 ms
void Wibhisana::middleBack()
{
    digitalWrite(WAYANG_HAND_8, HIGH);
    Servo_Wibhisana.moveWhatServo(3, 90, 500);
    Servo_Wibhisana.moveWhatServo(4, 110, 200);
    Servo_Wibhisana.moveWhatServo(3, 180, 500);
    Servo_Wibhisana.moveWhatServo(4, 115, 200);
    // Servo_Wibhisana.moveWhatServo(2, 40, 500);
    digitalWrite(WAYANG_HAND_8, LOW);
}

// takes the duration value
void Wibhisana::directControl(int num, int angle, int duration)
{
    digitalWrite(WAYANG_HAND_8, HIGH);
    Servo_Wibhisana.moveWhatServo(num, angle, duration);
    digitalWrite(WAYANG_HAND_8, LOW);
}