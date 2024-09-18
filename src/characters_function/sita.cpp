#include "characters/sita.hpp"
#include "a4988_nema.hpp"
#include "distanceSensorVL53L0X.hpp"

WayangHandServo Servo_Sita(whatSideServo::LEFT);
HorizontalController HC_sita;

void Sita::defaultStandPosition()
{
    walk_to_a_certain_distance_before_calibrating_value(41);
}

void Sita::defaultHandPosition()
{
    digitalWrite(WAYANG_HAND_1, HIGH);
    // Servo_Sita.moveWhatServo(1, 120, 2000);
    // Servo_Sita.moveWhatServo(3, 60, 2000);
    Servo_Sita.defaultPosition();
    // Servo_Sita.moveWhatServo(2, 60, 2000);
    // Servo_Sita.moveWhatServo(4, 60, 2000);
    Servo_Sita.resetArray();
    digitalWrite(WAYANG_HAND_1, LOW);
}

void Sita::walk_to_scene(int distanceValue)
{
    HC_sita.step_for_n_dir(1, distanceValue, "ccw");
}

void Sita::leave_from_scene(int distanceValue)
{
    HC_sita.step_for_n_dir(1, distanceValue, "cw");
}

void Sita::hand_movement_test_1()
{
    digitalWrite(WAYANG_HAND_1, HIGH);
    Servo_Sita.moveWhatServo(1, 0, 2000);
    Servo_Sita.moveWhatServo(2, 85, 2000);

    // Servo_Sita.moveWhatServo(1, 0);
    // delay(10);
    // Servo_Sita.moveWhatServo(2, 0);
    // delay(10);
    // Servo_Sita.moveWhatServo(3, 180);
    // delay(10);
    // Servo_Sita.moveWhatServo(4, 180);
    // delay(1000);
    // Servo_Sita.moveWhatServo(1, 180);
    // delay(10);
    // Servo_Sita.moveWhatServo(2, 180);
    // delay(10);
    // Servo_Sita.moveWhatServo(3, 0);
    // delay(10);
    // Servo_Sita.moveWhatServo(4, 0);
    // delay(1000);
    digitalWrite(WAYANG_HAND_1, LOW);
}

void Sita::hand_movement_test_2()
{
    digitalWrite(WAYANG_HAND_1, HIGH);
    Servo_Sita.moveWhatServo(1, 30, 2000);
    Servo_Sita.moveWhatServo(2, 65, 2000);
    digitalWrite(WAYANG_HAND_1, LOW);
}

void Sita::hand_movement_test_3()
{
    digitalWrite(WAYANG_HAND_1, HIGH);
    Servo_Sita.moveWhatServo(4, 65, 2000);
    Servo_Sita.moveWhatServo(3, 100, 2000);
    Servo_Sita.moveWhatServo(1, 180, 2000);
    Servo_Sita.moveWhatServo(2, 120, 2000);
    digitalWrite(WAYANG_HAND_1, LOW);
}

void Sita::hand_movement_test_4()
{
    digitalWrite(WAYANG_HAND_1, HIGH);
    Servo_Sita.moveWhatServo(1, 90, 2000);
    Servo_Sita.moveWhatServo(2, 65, 2000);
    Servo_Sita.moveWhatServo(1, 65, 2000);
    Servo_Sita.moveWhatServo(2, 90, 2000);
    digitalWrite(WAYANG_HAND_1, LOW);
}

void Sita::left_raise_hand()
{
    digitalWrite(WAYANG_HAND_1, HIGH);
    Servo_Sita.moveWhatServo(1, 180, 500);
    Servo_Sita.moveWhatServo(2, 65, 500);
    digitalWrite(WAYANG_HAND_1, LOW);
}

void Sita::left_raise_half_hand()
{
    digitalWrite(WAYANG_HAND_1, HIGH);
    Servo_Sita.moveWhatServo(1, 110, 500);
    Servo_Sita.moveWhatServo(2, 65, 500);
    digitalWrite(WAYANG_HAND_1, LOW);
}

void Sita::left_lower_hand()
{
    digitalWrite(WAYANG_HAND_1, HIGH);
    Servo_Sita.moveWhatServo(2, 75, 2000);
    Servo_Sita.moveWhatServo(1, 0, 2000);
    digitalWrite(WAYANG_HAND_1, LOW);
}

void Sita::left_lower_half_hand()
{
    digitalWrite(WAYANG_HAND_1, HIGH);
    Servo_Sita.moveWhatServo(2, 75, 750);
    Servo_Sita.moveWhatServo(1, 70, 750);
    digitalWrite(WAYANG_HAND_1, LOW);
}

void Sita::right_raise_hand()
{
    digitalWrite(WAYANG_HAND_1, HIGH);
    Servo_Sita.moveWhatServo(3, 0, 2000);
    Servo_Sita.moveWhatServo(4, 65, 2000);
    digitalWrite(WAYANG_HAND_1, LOW);
}

void Sita::right_raise_half_hand()
{
    digitalWrite(WAYANG_HAND_1, HIGH);
    Servo_Sita.moveWhatServo(3, 45, 2000);
    Servo_Sita.moveWhatServo(4, 65, 2000);
    digitalWrite(WAYANG_HAND_1, LOW);
}

void Sita::right_lower_hand()
{
    digitalWrite(WAYANG_HAND_1, HIGH);
    Servo_Sita.moveWhatServo(4, 90, 2000);
    Servo_Sita.moveWhatServo(3, 180, 2000);
    digitalWrite(WAYANG_HAND_1, LOW);
}

void Sita::right_lower_half_hand()
{
    digitalWrite(WAYANG_HAND_1, HIGH);
    Servo_Sita.moveWhatServo(4, 90, 2000);
    Servo_Sita.moveWhatServo(3, 135, 2000);
    digitalWrite(WAYANG_HAND_1, LOW);
}


void Sita::walk_to_a_certain_distance(int desiredDistance)
{
    if (!getSensorStatus(1))
    {
        beginSensor1();
    }
    // desiredDistance = desiredDistance + (float)desiredDistance * 0.093;
    // Serial.println("\ndesiredDistance: ");
    // Serial.print(desiredDistance);
    // Serial.println("mm \n");
    int readValue = getDistanceSensor1();
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
        int finalReadValue = getDistanceSensor1();
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
        int finalReadValue = getDistanceSensor1();
        Serial.print(finalReadValue);
        Serial.println("mm \n");
        if (finalReadValue < desiredDistance)
        {
            walk_to_a_certain_distance(desiredDistance);
        }
    }
    else
    {
    }
}

void Sita::walk_to_a_certain_distance_before_calibrating_value(int desiredDistance)
{
    int desiredDistanceAfterCalibratingValue = desiredDistance + (float)desiredDistance * 0.1;
    Serial.println("\ndesiredDistance: ");
    Serial.print(desiredDistanceAfterCalibratingValue);
    Serial.println("mm \n");
    walk_to_a_certain_distance(desiredDistanceAfterCalibratingValue);
}

void Sita::oscillate(int desiredDurationForOscillating)
{
    digitalWrite(WAYANG_HAND_1, HIGH);
    int loopCount = desiredDurationForOscillating / 1000;
    bool upDown = true;

    for (int i = 0; i < loopCount; i++)
    {
        if (upDown)
        {
            left_raise_hand(); // takes 1000 ms
        }
        else if (!upDown)
        {
            left_raise_half_hand(); // takes 1000 ms
        }
        upDown = !upDown;
    }
    digitalWrite(WAYANG_HAND_1, LOW);
}

void Sita::pointToFront()
{
    // digitalWrite(WAYANG_HAND_3, HIGH);
    // Servo_Sita.moveWhatServo(1, 0, 2000);
    // Servo_Sita.moveWhatServo(2, 60, 2000);
    // digitalWrite(WAYANG_HAND_3, LOW);

    digitalWrite(WAYANG_HAND_1, HIGH);
    Servo_Sita.defaultPosition();
    Servo_Sita.moveWhatServo(1, 0, 800);
    Servo_Sita.moveWhatServo(2, 50, 800);

    digitalWrite(WAYANG_HAND_1, LOW);
}

void Sita::lower_pointToFront()
{
}

void Sita::middleFront()
{
}

void Sita::downFront()
{
}

void Sita::pointToBack()
{
}

void Sita::downBack()
{
}

void Sita::onHipBack()
{
    // digitalWrite(WAYANG_HAND_3, HIGH);
    // Servo_Sita.moveWhatServo(4, 70, 2000);
    // Servo_Sita.moveWhatServo(3, 80, 2000);
    // Servo_Sita.moveWhatServo(4, 50, 2000);
    // digitalWrite(WAYANG_HAND_3, LOW);

    digitalWrite(WAYANG_HAND_1, HIGH);
    Servo_Sita.defaultPosition();
    Servo_Sita.moveWhatServo(4, 60 + 10, 2000);
    Servo_Sita.moveWhatServo(3, 90, 2000);
    Servo_Sita.moveWhatServo(4, 90, 2000);
    // Servo_RamaWijaya.moveWhatServo(4, 70, 2500);
    // Servo_RamaWijaya.moveWhatServo(3, 80, 2500);
    // Servo_RamaWijaya.moveWhatServo(4, 50, 2500);
    // Servo_RamaWijaya.moveWhatServo(3, 100, 2500);
    // Servo_RamaWijaya.moveWhatServo(4, 90, 2500);
    digitalWrite(WAYANG_HAND_1, LOW);
}

void Sita::pointToSelf()
{
    // digitalWrite(WAYANG_HAND_1, HIGH);
    // Servo_Sita.moveWhatServo(2, 135, 2000);
    // Servo_Sita.moveWhatServo(1, 30, 2000);
    // Servo_Sita.moveWhatServo(2, 85, 2000);
    // digitalWrite(WAYANG_HAND_1, LOW);

    digitalWrite(WAYANG_HAND_1, HIGH);
    Servo_Sita.defaultPosition();
    Servo_Sita.moveWhatServo(2, 120, 2000);
    Servo_Sita.moveWhatServo(1, 0, 2000);
    digitalWrite(WAYANG_HAND_1, LOW);
}

void Sita::middleFrontBack()
{
}

void Sita::lowPointToBack()
{
}

void Sita::middleBack()
{
}