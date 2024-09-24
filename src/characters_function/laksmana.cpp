#include "characters/laksmana.hpp"
#include "a4988_nema.hpp"
#include "distanceSensorVL53L0X.hpp"

WayangHandServo Servo_Laskmana(whatSideServo::RIGHT);
HorizontalController HC_laksmana;

void Laksmana::defaultHandPosition()
{
    digitalWrite(WAYANG_HAND_5, HIGH);
    Servo_Laskmana.defaultPosition();
    Servo_Laskmana.moveWhatServo(4, 100, 200);
    // Servo_Laskmana.moveWhatServo(1, 45, 500);
    downBack();
    onHipBack();
    digitalWrite(WAYANG_HAND_5, LOW);
}

void Laksmana::defaultStandPosition()
{
    walk_to_a_certain_distance_before_calibrating_value(0);
}

void Laksmana::leave_from_scene(int distanceValue)
{
    HC_laksmana.step_for_n_dir(5, distanceValue, "ccw");
}

void Laksmana::walk_to_a_certain_distance(int desiredDistance)
{
    if (!getSensorStatus(5))
    {
        beginSensor5();
    }

    int readValue = getDistanceSensor5();
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
        int finalReadValue = getDistanceSensor5();
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
        int finalReadValue = getDistanceSensor5();
        Serial.print(finalReadValue);
        Serial.println("mm \n");
        if (finalReadValue < desiredDistance * 0.9)
        {
            walk_to_a_certain_distance(desiredDistance);
        }
    }
}

void Laksmana::walk_to_a_certain_distance_before_calibrating_value(int desiredDistance)
{
    int desiredDistanceAfterCalibratingValue = desiredDistance + (float)desiredDistance * 0.155 + 47;
    Serial.println("\ndesiredDistance: ");
    Serial.print(desiredDistanceAfterCalibratingValue);
    Serial.println("mm \n");
    walk_to_a_certain_distance(desiredDistanceAfterCalibratingValue);
}

void Laksmana::walk_to_scene(int distanceValue)
{
    HC_laksmana.step_for_n_dir(5, distanceValue, "cw");
}

void Laksmana::pointToFront()
{
    digitalWrite(WAYANG_HAND_5, HIGH);
    Servo_Laskmana.moveWhatServo(3, 180, 500);
    Servo_Laskmana.moveWhatServo(4, 140, 200);
    digitalWrite(WAYANG_HAND_5, LOW);
}

void Laksmana::lower_pointToFront()
{

    digitalWrite(WAYANG_HAND_5, HIGH);
    Servo_Laskmana.moveWhatServo(3, 120, 500);
    Servo_Laskmana.moveWhatServo(4, 140, 200);
    digitalWrite(WAYANG_HAND_5, LOW);
}

void Laksmana::middleFront()
{
    digitalWrite(WAYANG_HAND_5, HIGH);
    Servo_Laskmana.moveWhatServo(4, 110, 200);
    Servo_Laskmana.moveWhatServo(3, 180, 500);
    Servo_Laskmana.moveWhatServo(4, 120, 200);
    digitalWrite(WAYANG_HAND_5, LOW);
}

void Laksmana::downFront()
{
    digitalWrite(WAYANG_HAND_5, HIGH);
    Servo_Laskmana.moveWhatServo(3, 0, 500);
    Servo_Laskmana.moveWhatServo(4, 110, 200);
    digitalWrite(WAYANG_HAND_5, LOW);
}

void Laksmana::pointToBack()
{
    digitalWrite(WAYANG_HAND_5, HIGH);
    Servo_Laskmana.moveWhatServo(1, 90, 500);
    Servo_Laskmana.moveWhatServo(2, 60, 200);
    Servo_Laskmana.moveWhatServo(1, 0, 500);
    Servo_Laskmana.moveWhatServo(2, 40, 200);
    digitalWrite(WAYANG_HAND_5, LOW);
}

void Laksmana::downBack()
{
    digitalWrite(WAYANG_HAND_5, HIGH);
    Servo_Laskmana.moveWhatServo(1, 160, 500);
    Servo_Laskmana.moveWhatServo(2, 100, 200);

    digitalWrite(WAYANG_HAND_5, LOW);
}

void Laksmana::onHipBack()
{
    digitalWrite(WAYANG_HAND_5, HIGH);
    Servo_Laskmana.moveWhatServo(1, 180, 500);
    Servo_Laskmana.moveWhatServo(2, 90, 200);
    Servo_Laskmana.moveWhatServo(1, 45, 500);
    digitalWrite(WAYANG_HAND_5, LOW);
}

void Laksmana::pointToSelf()
{
    digitalWrite(WAYANG_HAND_5, HIGH);
    Servo_Laskmana.moveWhatServo(4, 80, 200);
    Servo_Laskmana.moveWhatServo(3, 180, 500);
    digitalWrite(WAYANG_HAND_5, LOW);
}

void Laksmana::middleFrontBack()
{
    digitalWrite(WAYANG_HAND_5, HIGH);
    Servo_Laskmana.moveWhatServo(1, 90, 500);
    Servo_Laskmana.moveWhatServo(2, 100, 200);
    digitalWrite(WAYANG_HAND_5, LOW);
}

void Laksmana::lowPointToBack()
{
    digitalWrite(WAYANG_HAND_5, HIGH);
    Servo_Laskmana.moveWhatServo(1, 90, 500);
    Servo_Laskmana.moveWhatServo(2, 60, 200);
    Servo_Laskmana.moveWhatServo(1, 45, 500);
    Servo_Laskmana.moveWhatServo(2, 40, 200);
    digitalWrite(WAYANG_HAND_5, LOW);
}

void Laksmana::middleBack()
{
    digitalWrite(WAYANG_HAND_5, HIGH);
    Servo_Laskmana.moveWhatServo(1, 90, 500);
    Servo_Laskmana.moveWhatServo(2, 50, 200);
    Servo_Laskmana.moveWhatServo(1, 45, 500);
    Servo_Laskmana.moveWhatServo(2, 70, 200);
    digitalWrite(WAYANG_HAND_5, LOW);
}

void Laksmana::directControl(int num, int angle, int duration)
{
    digitalWrite(WAYANG_HAND_5, HIGH);
    Servo_Laskmana.moveWhatServo(num, angle, duration);
    digitalWrite(WAYANG_HAND_5, LOW);
}