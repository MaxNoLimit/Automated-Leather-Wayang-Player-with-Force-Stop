#include "characters/sugriwa.hpp"
#include "a4988_nema.hpp"
#include "distanceSensorVL53L0X.hpp"

WayangHandServo Servo_Sugriwa(whatSideServo::LEFT);
HorizontalController HC_sugriwa;

void Sugriwa::defaultHandPosition()
{
    // digitalWrite(WAYANG_HAND_6, HIGH);
    // // Servo_Sugriwa.moveWhatServo(4, 100, 500);
    // // Servo_Sugriwa.moveWhatServo(2, 140, 500);
    // // Servo_Sugriwa.defaultPosition();
    // // Servo_Sugriwa.moveWhatServo(4, 110, 200);
    // downFront();
    // downBack();
    // onHipBack();
    // directControl(2, 70, 200);
    // Servo_Sugriwa.resetArray();

    // digitalWrite(WAYANG_HAND_6, LOW);
    mathentengA();
}

void Sugriwa::defaultStandPosition()
{
    walk_to_a_certain_distance_before_calibrating_value(0);
}

void Sugriwa::leave_from_scene(int distanceValue)
{
    HC_sugriwa.step_for_n_dir(6, distanceValue, "cw");
}

void Sugriwa::walk_to_scene(int distanceValue)
{
    HC_sugriwa.step_for_n_dir(6, distanceValue, "ccw");
}

void Sugriwa::walk_to_a_certain_distance(int desiredDistance)
{

    int readValue = getDistanceSensor6();
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
        int finalReadValue = getDistanceSensor6();
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
        int finalReadValue = getDistanceSensor6();
        Serial.print(finalReadValue);
        Serial.println("mm \n");
        if (finalReadValue < desiredDistance * 0.9)
        {
            walk_to_a_certain_distance(desiredDistance);
        }
    }
}

void Sugriwa::walk_to_a_certain_distance_before_calibrating_value(int desiredDistance)
{
    int desiredDistanceAfterCalibratingValue = desiredDistance + 57;
    Serial.println("\ndesiredDistance: ");
    Serial.print(desiredDistanceAfterCalibratingValue);
    Serial.println("mm \n");
    walk_to_a_certain_distance(desiredDistanceAfterCalibratingValue);
}

// takes 900 ms
void Sugriwa::pointToFront()
{
    digitalWrite(WAYANG_HAND_6, HIGH);
    // Servo_Sugriwa.moveWhatServo(1, 150, 200);
    Servo_Sugriwa.moveWhatServo(2, 75, 200);
    Servo_Sugriwa.moveWhatServo(1, 10, 500);
    Servo_Sugriwa.moveWhatServo(2, 35, 200);
    digitalWrite(WAYANG_HAND_6, LOW);
}

// takes 700 ms
void Sugriwa::lower_pointToFront()
{
    digitalWrite(WAYANG_HAND_6, HIGH);
    Servo_Sugriwa.moveWhatServo(1, 90, 500);
    Servo_Sugriwa.moveWhatServo(2, 40, 200);
    digitalWrite(WAYANG_HAND_6, LOW);
}

// takes 1200 ms
void Sugriwa::middleFront()
{
    digitalWrite(WAYANG_HAND_6, HIGH);
    Servo_Sugriwa.moveWhatServo(2, 75, 200);
    Servo_Sugriwa.moveWhatServo(1, 10, 500);
    Servo_Sugriwa.moveWhatServo(2, 65, 200);
    digitalWrite(WAYANG_HAND_6, LOW);
}

// takes 700 ms
void Sugriwa::downFront()
{
    digitalWrite(WAYANG_HAND_6, HIGH);
    Servo_Sugriwa.moveWhatServo(1, 170, 500);
    Servo_Sugriwa.moveWhatServo(2, 90, 200);
    digitalWrite(WAYANG_HAND_6, LOW);
}

// takes 1400 ms
void Sugriwa::pointToBack()
{
    digitalWrite(WAYANG_HAND_6, HIGH);
    Servo_Sugriwa.moveWhatServo(3, 90, 500);
    Servo_Sugriwa.moveWhatServo(4, 100, 200);
    Servo_Sugriwa.moveWhatServo(3, 180, 500);
    Servo_Sugriwa.moveWhatServo(4, 120, 200);
    digitalWrite(WAYANG_HAND_6, LOW);
}

// takes 700 ms
void Sugriwa::downBack()
{
    digitalWrite(WAYANG_HAND_6, HIGH);
    Servo_Sugriwa.moveWhatServo(3, 60, 500);
    Servo_Sugriwa.moveWhatServo(4, 80, 200); // before is 80 deg
    digitalWrite(WAYANG_HAND_6, LOW);
}

// takes 700 ms
void Sugriwa::onHipBack()
{
    digitalWrite(WAYANG_HAND_6, HIGH);
    // Servo_Sugriwa.moveWhatServo(4, 80, 200);
    Servo_Sugriwa.moveWhatServo(3, 160, 500);
    Servo_Sugriwa.moveWhatServo(4, 95, 200);
    digitalWrite(WAYANG_HAND_6, LOW);
}

// takes 2100 ms
void Sugriwa::mathentengA()
{
    Servo_Sugriwa.resetArray();
    downBack();
    onHipBack();
    downFront();
}

// takes 2300 ms
void Sugriwa::mathentengC()
{
    Servo_Sugriwa.resetArray();
    downBack();
    downFront();
    digitalWrite(WAYANG_HAND_6, HIGH);
    // Servo_Sugriwa.moveWhatServo(4, 105, 200);
    Servo_Sugriwa.moveWhatServo(3, 180, 500);
    Servo_Sugriwa.moveWhatServo(4, 110, 200);
    Servo_Sugriwa.moveWhatServo(2, 60, 200);
    digitalWrite(WAYANG_HAND_6, LOW);
}

// takes 900 ms
void Sugriwa::pointToSelf()
{
    digitalWrite(WAYANG_HAND_6, HIGH);
    // Servo_Sugriwa.moveWhatServo(1, 135, 500);
    Servo_Sugriwa.moveWhatServo(2, 110, 200);
    Servo_Sugriwa.moveWhatServo(1, 20, 500);
    Servo_Sugriwa.moveWhatServo(2, 90, 200);
    digitalWrite(WAYANG_HAND_6, LOW);
}

// takes 700 ms
void Sugriwa::middleFrontBack()
{
    digitalWrite(WAYANG_HAND_6, HIGH);
    Servo_Sugriwa.moveWhatServo(3, 90, 500);
    Servo_Sugriwa.moveWhatServo(4, 60, 200);
    digitalWrite(WAYANG_HAND_6, LOW);
}

// takes 700 ms
void Sugriwa::lowPointToBack()
{
    digitalWrite(WAYANG_HAND_6, HIGH);
    Servo_Sugriwa.moveWhatServo(3, 135, 500);
    Servo_Sugriwa.moveWhatServo(4, 130, 200);
    // Servo_Sugriwa.moveWhatServo(1, 45, 2000);
    // Servo_Sugriwa.moveWhatServo(2, 40, 500);
    digitalWrite(WAYANG_HAND_6, LOW);
}

// takes 1400 ms
void Sugriwa::middleBack()
{
    digitalWrite(WAYANG_HAND_6, HIGH);
    Servo_Sugriwa.moveWhatServo(3, 90, 500);
    Servo_Sugriwa.moveWhatServo(4, 110, 200);
    Servo_Sugriwa.moveWhatServo(3, 180, 500);
    Servo_Sugriwa.moveWhatServo(4, 115, 200);
    // Servo_Sugriwa.moveWhatServo(2, 40, 500);
    digitalWrite(WAYANG_HAND_6, LOW);
}

// takes the duration value
void Sugriwa::directControl(int num, int angle, int duration)
{
    digitalWrite(WAYANG_HAND_6, HIGH);
    Servo_Sugriwa.moveWhatServo(num, angle, duration);
    digitalWrite(WAYANG_HAND_6, LOW);
}
