#include "characters/anggada.hpp"
#include "a4988_nema.hpp"
#include "distanceSensorVL53L0X.hpp"

WayangHandServo Servo_Anggada(whatSideServo::LEFT);
HorizontalController HC_anggada;

void Anggada::defaultHandPosition()
{
    // digitalWrite(WAYANG_HAND_9, HIGH);
    // // Servo_Anggada.moveWhatServo(4, 100, 500);
    // // Servo_Anggada.moveWhatServo(2, 140, 500);
    // // Servo_Anggada.defaultPosition();
    // // Servo_Anggada.moveWhatServo(4, 110, 200);
    // downFront();
    // downBack();
    // onHipBack();
    // directControl(2, 70, 200);
    // Servo_Anggada.resetArray();

    // digitalWrite(WAYANG_HAND_9, LOW);
    mathentengA();
}

void Anggada::defaultStandPosition()
{
    walk_to_a_certain_distance_before_calibrating_value(0);
}

void Anggada::leave_from_scene(int distanceValue)
{
    HC_anggada.step_for_n_dir(9, distanceValue, "cw");
}

void Anggada::walk_to_scene(int distanceValue)
{
    HC_anggada.step_for_n_dir(9, distanceValue, "ccw");
}

void Anggada::walk_to_a_certain_distance(int desiredDistance)
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

void Anggada::walk_to_a_certain_distance_before_calibrating_value(int desiredDistance)
{
    int desiredDistanceAfterCalibratingValue = desiredDistance + (float)desiredDistance * 0.155 + 63;
    Serial.println("\ndesiredDistance: ");
    Serial.print(desiredDistanceAfterCalibratingValue);
    Serial.println("mm \n");
    walk_to_a_certain_distance(desiredDistanceAfterCalibratingValue);
}

void Anggada::pointToFront()
{
    digitalWrite(WAYANG_HAND_9, HIGH);
    // Servo_Anggada.moveWhatServo(1, 150, 200);
    Servo_Anggada.moveWhatServo(2, 75, 200);
    Servo_Anggada.moveWhatServo(1, 0, 500);
    Servo_Anggada.moveWhatServo(2, 35, 200);
    digitalWrite(WAYANG_HAND_9, LOW);
}

void Anggada::lower_pointToFront()
{
    digitalWrite(WAYANG_HAND_9, HIGH);
    Servo_Anggada.moveWhatServo(1, 90, 500);
    Servo_Anggada.moveWhatServo(2, 40, 200);
    digitalWrite(WAYANG_HAND_9, LOW);
}

void Anggada::middleFront()
{
    digitalWrite(WAYANG_HAND_9, HIGH);
    Servo_Anggada.moveWhatServo(1, 135, 500);
    Servo_Anggada.moveWhatServo(2, 80, 200);
    Servo_Anggada.moveWhatServo(1, 45, 500);
    digitalWrite(WAYANG_HAND_9, LOW);
}

void Anggada::downFront()
{
    digitalWrite(WAYANG_HAND_9, HIGH);
    Servo_Anggada.moveWhatServo(1, 150, 500);
    Servo_Anggada.moveWhatServo(2, 70, 200);
    digitalWrite(WAYANG_HAND_9, LOW);
}

void Anggada::pointToBack()
{
    digitalWrite(WAYANG_HAND_9, HIGH);
    Servo_Anggada.moveWhatServo(3, 90, 500);
    Servo_Anggada.moveWhatServo(4, 120, 200);
    Servo_Anggada.moveWhatServo(3, 180, 500);
    Servo_Anggada.moveWhatServo(4, 140, 200);
    digitalWrite(WAYANG_HAND_9, LOW);
}

void Anggada::downBack()
{
    digitalWrite(WAYANG_HAND_9, HIGH);
    Servo_Anggada.moveWhatServo(3, 60, 500);
    Servo_Anggada.moveWhatServo(4, 80, 200);
    digitalWrite(WAYANG_HAND_9, LOW);
}

void Anggada::onHipBack()
{
    digitalWrite(WAYANG_HAND_9, HIGH);
    // Servo_Anggada.moveWhatServo(4, 80, 200);
    Servo_Anggada.moveWhatServo(3, 160, 500);
    Servo_Anggada.moveWhatServo(4, 95, 200);
    digitalWrite(WAYANG_HAND_9, LOW);
}

void Anggada::mathentengA()
{
    Servo_Anggada.resetArray();
    downBack();
    onHipBack();
    downFront();
}

void Anggada::mathentengC()
{
    Servo_Anggada.resetArray();
    downBack();
    downFront();
    digitalWrite(WAYANG_HAND_9, HIGH);
    // Servo_Anggada.moveWhatServo(4, 105, 200);
    Servo_Anggada.moveWhatServo(3, 180, 500);
    Servo_Anggada.moveWhatServo(4, 110, 200);
    Servo_Anggada.moveWhatServo(2, 60, 200);
    digitalWrite(WAYANG_HAND_9, LOW);
}

void Anggada::pointToSelf()
{
    digitalWrite(WAYANG_HAND_9, HIGH);
    // Servo_Anggada.moveWhatServo(1, 135, 500);
    Servo_Anggada.moveWhatServo(2, 120, 200);
    Servo_Anggada.moveWhatServo(1, 20, 500);
    Servo_Anggada.moveWhatServo(2, 100, 200);
    digitalWrite(WAYANG_HAND_9, LOW);
}

void Anggada::middleFrontBack()
{
    digitalWrite(WAYANG_HAND_9, HIGH);
    Servo_Anggada.moveWhatServo(3, 90, 500);
    Servo_Anggada.moveWhatServo(4, 60, 200);
    digitalWrite(WAYANG_HAND_9, LOW);
}

void Anggada::lowPointToBack()
{
    digitalWrite(WAYANG_HAND_9, HIGH);
    Servo_Anggada.moveWhatServo(3, 135, 500);
    Servo_Anggada.moveWhatServo(4, 125, 200);
    // Servo_Anggada.moveWhatServo(1, 45, 2000);
    // Servo_Anggada.moveWhatServo(2, 40, 500);
    digitalWrite(WAYANG_HAND_9, LOW);
}

void Anggada::middleBack()
{
    digitalWrite(WAYANG_HAND_9, HIGH);
    Servo_Anggada.moveWhatServo(3, 90, 500);
    Servo_Anggada.moveWhatServo(4, 110, 200);
    Servo_Anggada.moveWhatServo(3, 180, 500);
    Servo_Anggada.moveWhatServo(4, 115, 200);
    // Servo_Anggada.moveWhatServo(2, 40, 500);
    digitalWrite(WAYANG_HAND_9, LOW);
}

void Anggada::directControl(int num, int angle, int duration)
{
    digitalWrite(WAYANG_HAND_9, HIGH);
    Servo_Anggada.moveWhatServo(num, angle, duration);
    digitalWrite(WAYANG_HAND_9, LOW);
}