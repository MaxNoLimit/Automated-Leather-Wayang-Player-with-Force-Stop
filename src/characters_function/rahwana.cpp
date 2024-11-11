#include "characters/rahwana.hpp"
#include "a4988_nema.hpp"
#include "distanceSensorVL53L0X.hpp"

WayangHandServo Servo_Rahwana(whatSideServo::RIGHT);
HorizontalController HC_rahwana;

void Rahwana::defaultStandPosition()
{
    walk_to_a_certain_distance_before_calibrating_value(0);
}

void Rahwana::walk_to_a_certain_distance(int desiredDistance)
{
    int readValue = getDistanceSensorNum(2);
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
        int finalReadValue = getDistanceSensorNum(2);
        Serial.print(finalReadValue);
        Serial.println("mm \n");
        if (finalReadValue > desiredDistance * 1.1)
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
        int finalReadValue = getDistanceSensorNum(2);
        Serial.print(finalReadValue);
        Serial.println("mm \n");
        if (finalReadValue < desiredDistance * 0.9)
        {
            walk_to_a_certain_distance(desiredDistance);
        }
    }
}

void Rahwana::defaultHandPosition()
{
    digitalWrite(WAYANG_HAND_2, HIGH);
    Servo_Rahwana.resetArray();
    directControl(3, 90, 500);
    downFront();
    digitalWrite(WAYANG_HAND_2, LOW);
}

void Rahwana::walk_to_scene(int distanceValue)
{
    HC_rahwana.step_for_n_dir(2, distanceValue, "cw");
}

void Rahwana::leave_from_scene(int distanceValue)
{
    HC_rahwana.step_for_n_dir(2, distanceValue, "ccw");
}


void Rahwana::walk_to_a_certain_distance_before_calibrating_value(int desiredDistance)
{
    int desiredDistanceAfterCalibratingValue = desiredDistance + 47;
    Serial.println("\ndesiredDistance: ");
    Serial.print(desiredDistanceAfterCalibratingValue);
    Serial.println("mm \n");
    walk_to_a_certain_distance(desiredDistanceAfterCalibratingValue);
    // HC_rahwana.step_for_what_distance(2, desiredDistanceAfterCalibratingValue);
}


// takes 900 ms
void Rahwana::pointToFront()
{
    digitalWrite(WAYANG_HAND_2, HIGH);
    // Servo_Rahwana.defaultPosition();
    // Servo_Rahwana.moveWhatServo(4, 120, 2000);
    // Servo_Rahwana.moveWhatServo(3, 180, 3000);
    // Servo_Rahwana.moveWhatServo(4, 130, 2000);

    Servo_Rahwana.moveWhatServo(4, 120, 200);
    Servo_Rahwana.moveWhatServo(3, 180, 500);
    Servo_Rahwana.moveWhatServo(4, 140, 200);
    digitalWrite(WAYANG_HAND_2, LOW);
}

// takes 700 ms
void Rahwana::lower_pointToFront()
{
    digitalWrite(WAYANG_HAND_2, HIGH);
    Servo_Rahwana.moveWhatServo(3, 120, 500);
    Servo_Rahwana.moveWhatServo(4, 140, 200);
    digitalWrite(WAYANG_HAND_2, LOW);
}

// takes 1200 ms
void Rahwana::middleFront()
{
    digitalWrite(WAYANG_HAND_2, HIGH);
    Servo_Rahwana.moveWhatServo(3, 30, 500);
    Servo_Rahwana.moveWhatServo(4, 110, 200);
    Servo_Rahwana.moveWhatServo(3, 135, 500);
    digitalWrite(WAYANG_HAND_2, LOW);
}

// takes 700 ms
void Rahwana::downFront()
{
    digitalWrite(WAYANG_HAND_2, HIGH);
    Servo_Rahwana.moveWhatServo(3, 0, 500);
    Servo_Rahwana.moveWhatServo(4, 100, 200);
    digitalWrite(WAYANG_HAND_2, LOW);
}

// takes 1100 ms
void Rahwana::pointToSelf()
{
    digitalWrite(WAYANG_HAND_2, HIGH);
    // Servo_Rahwana.defaultPosition();
    Servo_Rahwana.moveWhatServo(4, 60, 200);
    Servo_Rahwana.moveWhatServo(3, 180, 500);
    Servo_Rahwana.moveWhatServo(4, 80, 400);
    digitalWrite(WAYANG_HAND_2, LOW);
}

// takes the duration value
void Rahwana::directControl(int num, int angle, int duration)
{
    digitalWrite(WAYANG_HAND_2, HIGH);
    Servo_Rahwana.moveWhatServo(num, angle, duration);
    digitalWrite(WAYANG_HAND_2, LOW);
}