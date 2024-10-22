#include "characters/anila.hpp"
#include "a4988_nema.hpp"
#include "distanceSensorVL53L0X.hpp"

WayangHandServo Servo_Anila(whatSideServo::RIGHT);
HorizontalController HC_anila;

void Anila::defaultHandPosition()
{
    // digitalWrite(WAYANG_HAND_10, HIGH);
    // // Servo_Anila.moveWhatServo(4, 100, 500);
    // // Servo_Anila.moveWhatServo(2, 140, 500);
    // // Servo_Anila.defaultPosition();
    // // Servo_Anila.moveWhatServo(4, 110, 200);
    // downFront();
    // downBack();
    // onHipBack();
    // // Servo_Anila.resetArray();

    // digitalWrite(WAYANG_HAND_10, LOW);
    mathentengA();
}

void Anila::defaultStandPosition()
{
    walk_to_a_certain_distance_before_calibrating_value(0);
}

void Anila::leave_from_scene(int distanceValue)
{
    HC_anila.step_for_n_dir(10, distanceValue, "ccw");
}

void Anila::walk_to_a_certain_distance(int desiredDistance)
{

    int readValue = getDistanceSensor7();
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
        int finalReadValue = getDistanceSensor7();
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
        int finalReadValue = getDistanceSensor7();
        Serial.print(finalReadValue);
        Serial.println("mm \n");
        if (finalReadValue < desiredDistance * 0.9)
        {
            walk_to_a_certain_distance(desiredDistance);
        }
    }
}

void Anila::walk_to_a_certain_distance_before_calibrating_value(int desiredDistance)
{
    int desiredDistanceAfterCalibratingValue = desiredDistance + (float)desiredDistance * 0.155 + 63;
    Serial.println("\ndesiredDistance: ");
    Serial.print(desiredDistanceAfterCalibratingValue);
    Serial.println("mm \n");
    walk_to_a_certain_distance(desiredDistanceAfterCalibratingValue);
}

void Anila::walk_to_scene(int distanceValue)
{
    HC_anila.step_for_n_dir(10, distanceValue, "cw");
}

void Anila::pointToFront()
{
    digitalWrite(WAYANG_HAND_10, HIGH);
    // Servo_Anila.moveWhatServo(3, 30, 200);
    Servo_Anila.moveWhatServo(4, 100, 200); // 200 ms
    Servo_Anila.moveWhatServo(3, 180, 500); // 500 ms
    Servo_Anila.moveWhatServo(4, 140, 200); // 200 ms
    digitalWrite(WAYANG_HAND_10, LOW);
}

void Anila::lower_pointToFront()
{
    digitalWrite(WAYANG_HAND_10, HIGH);
    Servo_Anila.moveWhatServo(3, 90, 500);
    Servo_Anila.moveWhatServo(4, 140, 200);
    digitalWrite(WAYANG_HAND_10, LOW);
}

void Anila::middleFront()
{
    digitalWrite(WAYANG_HAND_10, HIGH);
    Servo_Anila.moveWhatServo(3, 30, 500);
    Servo_Anila.moveWhatServo(4, 110, 200);
    Servo_Anila.moveWhatServo(3, 135, 500);
    digitalWrite(WAYANG_HAND_10, LOW);
}

void Anila::downFront()
{
    digitalWrite(WAYANG_HAND_10, HIGH);
    Servo_Anila.moveWhatServo(3, 30, 500);
    Servo_Anila.moveWhatServo(4, 120, 200);
    digitalWrite(WAYANG_HAND_10, LOW);
}

void Anila::pointToBack()
{
    digitalWrite(WAYANG_HAND_10, HIGH);
    Servo_Anila.moveWhatServo(1, 90, 500);
    Servo_Anila.moveWhatServo(2, 60, 200);
    Servo_Anila.moveWhatServo(1, 0, 500);
    Servo_Anila.moveWhatServo(2, 40, 200);
    digitalWrite(WAYANG_HAND_10, LOW);
}

void Anila::downBack()
{
    digitalWrite(WAYANG_HAND_10, HIGH);
    Servo_Anila.moveWhatServo(1, 160, 500);
    Servo_Anila.moveWhatServo(2, 115, 200);
    digitalWrite(WAYANG_HAND_10, LOW);
}

void Anila::onHipBack()
{
    digitalWrite(WAYANG_HAND_10, HIGH);
    Servo_Anila.moveWhatServo(2, 110, 200);
    Servo_Anila.moveWhatServo(1, 100, 500);
    Servo_Anila.moveWhatServo(2, 75, 200);
    digitalWrite(WAYANG_HAND_10, LOW);
}

void Anila::mathentengA()
{
    Servo_Anila.resetArray();
    downBack();
    downFront();
    onHipBack();
}

void Anila::mathentengC()
{
    Servo_Anila.resetArray();
    downBack();
    downFront();
    digitalWrite(WAYANG_HAND_10, HIGH);
    Servo_Anila.moveWhatServo(2, 110, 200);
    Servo_Anila.moveWhatServo(1, 50, 500);
    Servo_Anila.moveWhatServo(2, 70, 200);
    Servo_Anila.moveWhatServo(4, 120, 200);
    digitalWrite(WAYANG_HAND_10, LOW);
}

void Anila::pointToSelf()
{
    digitalWrite(WAYANG_HAND_10, HIGH);
    Servo_Anila.moveWhatServo(4, 65, 200);
    Servo_Anila.moveWhatServo(3, 150, 500);
    Servo_Anila.moveWhatServo(4, 80, 200);
    digitalWrite(WAYANG_HAND_10, LOW);
}

void Anila::middleFrontBack()
{
    digitalWrite(WAYANG_HAND_10, HIGH);
    Servo_Anila.moveWhatServo(2, 110, 200);
    Servo_Anila.moveWhatServo(1, 100, 500);
    Servo_Anila.moveWhatServo(2, 95, 200);
    digitalWrite(WAYANG_HAND_10, LOW);
}

void Anila::lowPointToBack()
{
    digitalWrite(WAYANG_HAND_10, HIGH);
    Servo_Anila.moveWhatServo(2, 50, 200);
    Servo_Anila.moveWhatServo(1, 120, 500);
    // Servo_Anila.moveWhatServo(1, 45, 2000);
    // Servo_Anila.moveWhatServo(2, 40, 500);
    digitalWrite(WAYANG_HAND_10, LOW);
}

void Anila::middleBack()
{
    digitalWrite(WAYANG_HAND_10, HIGH);
    Servo_Anila.moveWhatServo(2, 70, 200);
    // Servo_Anila.moveWhatServo(1, 90, 500);
    // Servo_Anila.moveWhatServo(2, 70, 200);
    Servo_Anila.moveWhatServo(1, 0, 500);
    Servo_Anila.moveWhatServo(2, 60, 200);
    // Servo_Anila.moveWhatServo(2, 40, 500);
    digitalWrite(WAYANG_HAND_10, LOW);
}

void Anila::directControl(int num, int angle, int duration)
{
    digitalWrite(WAYANG_HAND_10, HIGH);
    Servo_Anila.moveWhatServo(num, angle, duration);
    digitalWrite(WAYANG_HAND_10, LOW);
}