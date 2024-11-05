#include "characters/hanoman.hpp"
#include "a4988_nema.hpp"
#include "distanceSensorVL53L0X.hpp"

WayangHandServo Servo_Hanuman(whatSideServo::RIGHT);
HorizontalController HC_hanoman;

void Hanoman::defaultHandPosition()
{
    // digitalWrite(WAYANG_HAND_4, HIGH);
    // // Servo_Hanuman.moveWhatServo(4, 100, 500);
    // // Servo_Hanuman.moveWhatServo(2, 140, 500);
    // Servo_Hanuman.defaultPosition();
    // // Servo_Hanuman.moveWhatServo(4, 110, 200);
    // downFront();
    // downBack();
    // onHipBack();
    // Servo_Hanuman.resetArray();

    // digitalWrite(WAYANG_HAND_4, LOW);
    mathenthengA();
}
void Hanoman::defaultStandPosition()
{
    walk_to_a_certain_distance_before_calibrating_value(0);
}

void Hanoman::leave_from_scene(int distanceValue)
{
    HC_hanoman.step_for_n_dir(4, distanceValue, "ccw");
}

void Hanoman::walk_to_a_certain_distance(int desiredDistance)
{

    int readValue = getDistanceSensorNum(4);
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
        int finalReadValue = getDistanceSensorNum(4);
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
        int finalReadValue = getDistanceSensorNum(4);
        Serial.print(finalReadValue);
        Serial.println("mm \n");
        if (finalReadValue < desiredDistance * 0.9)
        {
            walk_to_a_certain_distance(desiredDistance);
        }
    }
}

void Hanoman::walk_to_a_certain_distance_before_calibrating_value(int desiredDistance)
{
    int desiredDistanceAfterCalibratingValue = desiredDistance + 17;
    Serial.println("\ndesiredDistance: ");
    Serial.print(desiredDistanceAfterCalibratingValue);
    Serial.println("mm \n");
    walk_to_a_certain_distance(desiredDistanceAfterCalibratingValue);
}

void Hanoman::walk_to_scene(int distanceValue)
{
    HC_hanoman.step_for_n_dir(4, distanceValue, "cw");
}

// takes 900 ms
void Hanoman::pointToFront()
{
    digitalWrite(WAYANG_HAND_4, HIGH);
    Servo_Hanuman.moveWhatServo(3, 30, 200);
    Servo_Hanuman.moveWhatServo(4, 120, 200);
    Servo_Hanuman.moveWhatServo(3, 180, 300);
    Servo_Hanuman.moveWhatServo(4, 140, 200);
    digitalWrite(WAYANG_HAND_4, LOW);
}

// takes 700 ms
void Hanoman::lower_pointToFront()
{
    digitalWrite(WAYANG_HAND_4, HIGH);
    Servo_Hanuman.moveWhatServo(3, 90, 500);
    Servo_Hanuman.moveWhatServo(4, 140, 200);
    digitalWrite(WAYANG_HAND_4, LOW);
}

// takes 1200 ms
void Hanoman::middleFront()
{
    digitalWrite(WAYANG_HAND_4, HIGH);
    Servo_Hanuman.moveWhatServo(3, 30, 500);
    Servo_Hanuman.moveWhatServo(4, 110, 200);
    Servo_Hanuman.moveWhatServo(3, 135, 500);
    digitalWrite(WAYANG_HAND_4, LOW);
}

// takes 700 ms
void Hanoman::downFront()
{
    digitalWrite(WAYANG_HAND_4, HIGH);
    Servo_Hanuman.moveWhatServo(3, 0, 500);
    Servo_Hanuman.moveWhatServo(4, 120, 200);
    digitalWrite(WAYANG_HAND_4, LOW);
}

// takes 1400 ms
void Hanoman::pointToBack()
{
    digitalWrite(WAYANG_HAND_4, HIGH);
    Servo_Hanuman.moveWhatServo(1, 90, 500);
    Servo_Hanuman.moveWhatServo(2, 60, 200);
    Servo_Hanuman.moveWhatServo(1, 0, 500);
    Servo_Hanuman.moveWhatServo(2, 40, 200);
    digitalWrite(WAYANG_HAND_4, LOW);
}

// takes 700 ms
void Hanoman::downBack()
{
    digitalWrite(WAYANG_HAND_4, HIGH);
    Servo_Hanuman.moveWhatServo(1, 160, 500);
    Servo_Hanuman.moveWhatServo(2, 110, 200);
    digitalWrite(WAYANG_HAND_4, LOW);
}

// takes 900 ms
void Hanoman::onHipBack()
{
    digitalWrite(WAYANG_HAND_4, HIGH);
    Servo_Hanuman.moveWhatServo(2, 130, 200);
    Servo_Hanuman.moveWhatServo(1, 80, 500);
    Servo_Hanuman.moveWhatServo(2, 100, 200);
    digitalWrite(WAYANG_HAND_4, LOW);
}

// takes 900 ms
void Hanoman::pointToSelf()
{
    digitalWrite(WAYANG_HAND_4, HIGH);
    Servo_Hanuman.moveWhatServo(4, 60, 200);
    Servo_Hanuman.moveWhatServo(3, 150, 500);
    Servo_Hanuman.moveWhatServo(4, 80, 200);
    digitalWrite(WAYANG_HAND_4, LOW);
}

// takes 700 ms
void Hanoman::middleFrontBack()
{
    digitalWrite(WAYANG_HAND_4, HIGH);
    Servo_Hanuman.moveWhatServo(1, 90, 500);
    Servo_Hanuman.moveWhatServo(2, 120, 200);
    digitalWrite(WAYANG_HAND_4, LOW);
}

// takes 700 ms
void Hanoman::lowPointToBack()
{
    digitalWrite(WAYANG_HAND_4, HIGH);
    Servo_Hanuman.moveWhatServo(1, 110, 500);
    Servo_Hanuman.moveWhatServo(2, 60, 200);
    // Servo_Hanuman.moveWhatServo(1, 45, 2000);
    // Servo_Hanuman.moveWhatServo(2, 40, 500);
    digitalWrite(WAYANG_HAND_4, LOW);
}

// takes 1400 ms
void Hanoman::middleBack()
{
    digitalWrite(WAYANG_HAND_4, HIGH);
    Servo_Hanuman.moveWhatServo(1, 90, 500);
    Servo_Hanuman.moveWhatServo(2, 70, 200);
    Servo_Hanuman.moveWhatServo(1, 0, 500);
    Servo_Hanuman.moveWhatServo(2, 90, 200);
    // Servo_Hanuman.moveWhatServo(2, 40, 500);
    digitalWrite(WAYANG_HAND_4, LOW);
}

// takes the duration value
void Hanoman::directControl(int num, int angle, int duration)
{
    digitalWrite(WAYANG_HAND_4, HIGH);
    Servo_Hanuman.moveWhatServo(num, angle, duration);
    digitalWrite(WAYANG_HAND_4, LOW);
}

// takes 2300 ms
void Hanoman::mathenthengA()
{
    Servo_Hanuman.resetArray();
    downBack();
    downFront();
    onHipBack();
}

// takes 2300 ms
void Hanoman::mathenthengC()
{
    Servo_Hanuman.resetArray();
    downBack();
    downFront();
    digitalWrite(WAYANG_HAND_4, HIGH);
    Servo_Hanuman.moveWhatServo(2, 130, 200);
    Servo_Hanuman.moveWhatServo(1, 80, 500);
    Servo_Hanuman.moveWhatServo(2, 120, 200);
    digitalWrite(WAYANG_HAND_4, LOW);
}