#include "characters/sita.hpp"
#include "a4988_nema.hpp"
#include "distanceSensorVL53L0X.hpp"

WayangHandServo Servo_Sita(whatSideServo::LEFT);
HorizontalController HC_sita;

void Sita::defaultStandPosition()
{
    walk_to_a_certain_distance_before_calibrating_value(0);
}

// takes 1400 ms
void Sita::defaultHandPosition()
{
    // digitalWrite(WAYANG_HAND_1, HIGH);
    // // Servo_Sita.moveWhatServo(1, 120, 2000);
    // // Servo_Sita.moveWhatServo(3, 60, 2000);
    // Servo_Sita.defaultPosition();
    // // Servo_Sita.moveWhatServo(2, 60, 2000);
    // downBack();
    // onHipBack();
    // Servo_Sita.resetArray();
    // digitalWrite(WAYANG_HAND_1, LOW);
    anjujur();
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

    // desiredDistance = desiredDistance + (float)desiredDistance * 0.093;
    // Serial.println("\ndesiredDistance: ");
    // Serial.print(desiredDistance);
    // Serial.println("mm \n");
    int readValue = getDistanceSensorNum(1);
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
        int finalReadValue = getDistanceSensorNum(1);;
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
        Serial.println("readValue 2: ");
        int finalReadValue = getDistanceSensorNum(1);;
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

void Sita::walk_to_a_certain_distance_before_calibrating_value(int desiredDistance)
{
    int desiredDistanceAfterCalibratingValue = desiredDistance + 36;
    Serial.println("\ndesiredDistance: ");
    Serial.print(desiredDistanceAfterCalibratingValue);
    Serial.println("mm \n");
    walk_to_a_certain_distance(desiredDistanceAfterCalibratingValue);
}

void Sita::oscillate(int desiredDurationForOscillating)
{
    digitalWrite(WAYANG_HAND_1, HIGH);
    int loopCount = desiredDurationForOscillating / 700;
    bool upDown = true;

    for (int i = 0; i < loopCount; i++)
    {
        if (upDown)
        {
            pointToFront(); // takes 700 ms
        }
        else if (!upDown)
        {
            lower_pointToFront(); // takes 700 ms
        }
        upDown = !upDown;
    }
    digitalWrite(WAYANG_HAND_1, LOW);
}

// takes 700 ms
void Sita::pointToFront()
{
    // digitalWrite(WAYANG_HAND_3, HIGH);
    // Servo_Sita.moveWhatServo(1, 0, 2000);
    // Servo_Sita.moveWhatServo(2, 60, 2000);
    // digitalWrite(WAYANG_HAND_3, LOW);

    digitalWrite(WAYANG_HAND_1, HIGH);
    // Servo_Sita.defaultPosition();
    // Servo_Sita.resetArray();
    Servo_Sita.moveWhatServo(1, 10, 500);
    Servo_Sita.moveWhatServo(2, 20, 200);

    digitalWrite(WAYANG_HAND_1, LOW);
}

// takes 700 ms
void Sita::lower_pointToFront()
{
    digitalWrite(WAYANG_HAND_1, HIGH);
    // Servo_Sita.defaultPosition();
    Servo_Sita.moveWhatServo(1, 100, 500);
    Servo_Sita.moveWhatServo(2, 40, 200);

    digitalWrite(WAYANG_HAND_1, LOW);
}

// takes 900 ms
void Sita::middleFront()
{
    digitalWrite(WAYANG_HAND_1, HIGH);
    // Servo_Sita.moveWhatServo(2, 70, 200);
    // Servo_Sita.moveWhatServo(1, 0, 500);
    // Servo_Sita.moveWhatServo(2, 60, 200);

    Servo_Sita.moveWhatServo(1, 100, 350);
    Servo_Sita.moveWhatServo(2, 60, 200);
    Servo_Sita.moveWhatServo(1, 0, 350);
    digitalWrite(WAYANG_HAND_1, LOW);
}

// takes 700 ms
void Sita::downFront()
{
    digitalWrite(WAYANG_HAND_1, HIGH);
    Servo_Sita.moveWhatServo(1, 170, 500);
    Servo_Sita.moveWhatServo(2, 70, 200);
    digitalWrite(WAYANG_HAND_1, LOW);
}

// takes 1400 ms
void Sita::pointToBack()
{
    digitalWrite(WAYANG_HAND_1, HIGH);
    Servo_Sita.moveWhatServo(3, 90, 500);
    Servo_Sita.moveWhatServo(4, 120, 200);
    Servo_Sita.moveWhatServo(3, 180, 500);
    Servo_Sita.moveWhatServo(4, 140, 200);
    digitalWrite(WAYANG_HAND_1, LOW);
}

// takes 700 ms
void Sita::downBack()
{
    digitalWrite(WAYANG_HAND_1, HIGH);
    Servo_Sita.moveWhatServo(3, 10, 500);
    Servo_Sita.moveWhatServo(4, 100, 200);
    digitalWrite(WAYANG_HAND_1, LOW);
}

// takes 900 ms
void Sita::onHipBack()
{
    // digitalWrite(WAYANG_HAND_3, HIGH);
    // Servo_Sita.moveWhatServo(4, 70, 2000);
    // Servo_Sita.moveWhatServo(3, 80, 2000);
    // Servo_Sita.moveWhatServo(4, 50, 2000);
    // digitalWrite(WAYANG_HAND_3, LOW);

    digitalWrite(WAYANG_HAND_1, HIGH);
    Servo_Sita.defaultPosition();
    Servo_Sita.moveWhatServo(4, 60 + 10, 200);
    Servo_Sita.moveWhatServo(3, 90, 500);
    Servo_Sita.moveWhatServo(4, 80, 200);
    // Servo_RamaWijaya.moveWhatServo(4, 70, 2500);
    // Servo_RamaWijaya.moveWhatServo(3, 80, 2500);
    // Servo_RamaWijaya.moveWhatServo(4, 50, 2500);
    // Servo_RamaWijaya.moveWhatServo(3, 100, 2500);
    // Servo_RamaWijaya.moveWhatServo(4, 90, 2500);
    digitalWrite(WAYANG_HAND_1, LOW);
}

// takes 1400 ms
void Sita::pointToSelf()
{
    // digitalWrite(WAYANG_HAND_1, HIGH);
    // Servo_Sita.moveWhatServo(2, 135, 2000);
    // Servo_Sita.moveWhatServo(1, 30, 2000);
    // Servo_Sita.moveWhatServo(2, 85, 2000);
    // digitalWrite(WAYANG_HAND_1, LOW);

    downFront(); // takes 700 ms
    digitalWrite(WAYANG_HAND_1, HIGH);
    Servo_Sita.moveWhatServo(2, 105, 200);
    Servo_Sita.moveWhatServo(1, 45, 500);
    // Servo_Sita.moveWhatServo(2, 80, 200);
    digitalWrite(WAYANG_HAND_1, LOW);
}

// takes 700 ms
void Sita::middleFrontBack()
{
    digitalWrite(WAYANG_HAND_1, HIGH);
    Servo_Sita.moveWhatServo(4, 60, 200);
    Servo_Sita.moveWhatServo(3, 120, 500);
    digitalWrite(WAYANG_HAND_1, LOW);
}

// takes 1200 ms
void Sita::lowPointToBack()
{
    digitalWrite(WAYANG_HAND_1, HIGH);
    Servo_Sita.moveWhatServo(3, 90, 500);
    Servo_Sita.moveWhatServo(4, 130, 200);
    Servo_Sita.moveWhatServo(3, 100, 500);
    // Servo_Sita.moveWhatServo(4, 140, 200);
    digitalWrite(WAYANG_HAND_1, LOW);
}

// takes 700 ms
void Sita::middleBack()
{
    digitalWrite(WAYANG_HAND_1, HIGH);
    Servo_Sita.moveWhatServo(4, 110, 200);
    Servo_Sita.moveWhatServo(3, 120, 500);
    // Servo_Sita.moveWhatServo(4, 120, 200);
    digitalWrite(WAYANG_HAND_1, LOW);
}

// takes the duration value
void Sita::directControl(int num, int angle, int duration)
{
    digitalWrite(WAYANG_HAND_2, HIGH);
    Servo_Sita.moveWhatServo(num, angle, duration);
    digitalWrite(WAYANG_HAND_2, LOW);
}

// takes 1400 ms
void Sita::anjujur()
{
    Servo_Sita.resetArray();
    downBack();
    downFront();
}