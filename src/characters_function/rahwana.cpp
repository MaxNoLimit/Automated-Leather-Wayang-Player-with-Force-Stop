#include "characters/rahwana.hpp"
#include "a4988_nema.hpp"
#include "distanceSensorVL53L0X.hpp"

WayangHandServo Servo_Rahwana(whatSideServo::RIGHT);
HorizontalController HC_rahwana;

void Rahwana::defaultStandPosition()
{
    walk_to_a_certain_distance_before_calibrating_value(67);
}

void Rahwana::walk_to_a_certain_distance(int desiredDistance)
{
    if (!getSensorStatus(2))
    {
        beginSensor2();
    }

    int readValue = getDistanceSensor2();
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
        int finalReadValue = getDistanceSensor2();
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
        int finalReadValue = getDistanceSensor2();
        Serial.print(finalReadValue);
        Serial.println("mm \n");
        if (finalReadValue < desiredDistance)
        {
            walk_to_a_certain_distance(desiredDistance);
        }
    }
}

void Rahwana::Rahwana_1()
{
    digitalWrite(WAYANG_HAND_2, HIGH);
    Servo_Rahwana.moveWhatServo(4, 90 + 20, 300 * 5);
    Servo_Rahwana.moveWhatServo(3, 180, 700 * 5);
    Servo_Rahwana.moveWhatServo(4, 90 + 35, 300 * 5); // 1.3s
    delay(1350);                                      // 2.65s

    for (int i = 0; i < 13; i++)
    {
        Servo_Rahwana.moveWhatServo(4, 90 + 15, 200 * 5);
        Servo_Rahwana.moveWhatServo(4, 90 + 25, 200 * 5);
    } // 7.85s

    Servo_Rahwana.moveWhatServo(4, 90 + 35, 300 * 5); // 8.15s
    delay(1240);                                      // 9.39s

    for (int i = 0; i < 10; i++)
    {
        Servo_Rahwana.moveWhatServo(4, 90 + 10, 200 * 5);
        Servo_Rahwana.moveWhatServo(3, 180 - 10, 200 * 5);
        Servo_Rahwana.moveWhatServo(4, 90 + 25, 200 * 5);
        Servo_Rahwana.moveWhatServo(3, 180, 200 * 5);
    } // 17.39s

    RahwanaSelfTalk(4, 3, 10, 14000, 400); // 31.39s
    delay(2000);

    Servo_Rahwana.moveWhatServo(3, 0, 700 * 5);
    Servo_Rahwana.moveWhatServo(4, 90 + 35, 300 * 5);
    Servo_Rahwana.moveWhatServo(3, 180, 700 * 5);
    Servo_Rahwana.moveWhatServo(4, 90 + 25, 300 * 5); // 35.39s
    delay(900);                                       // 36.29s

    for (int i = 0; i < 16; i++)
    {
        Servo_Rahwana.moveWhatServo(4, 90 + 15, 200 * 5);
        Servo_Rahwana.moveWhatServo(4, 90 + 25, 200 * 5);
    } // 42.69s

    Servo_Rahwana.moveWhatServo(4, 90 + 35, 300 * 5); // 42.99s
    delay(2000);
    Servo_Rahwana.moveWhatServo(3, 0, 700 * 5);
    Servo_Rahwana.moveWhatServo(4, 90, 300 * 5);
    delay(9500);

    // interlude
    digitalWrite(WAYANG_HAND_2, LOW);
}

void Rahwana::defaultHandPosition()
{
    digitalWrite(WAYANG_HAND_2, HIGH);
    Servo_Rahwana.moveWhatServo(3, 60, 2000);
    Servo_Rahwana.defaultPosition();
    Servo_Rahwana.resetArray();
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

void Rahwana::hand_movement_test_1()
{
    digitalWrite(WAYANG_HAND_2, HIGH);
    // Servo_Rahwana.moveWhatServo(1, 0);
    // delay(10);
    // Servo_Rahwana.moveWhatServo(2, 0);
    // delay(10);
    // Servo_Rahwana.moveWhatServo(3, 0);
    // delay(10);
    // Servo_Rahwana.moveWhatServo(4, 0);
    // delay(1000);
    // Servo_Rahwana.moveWhatServo(1, 180);
    // delay(10);
    // Servo_Rahwana.moveWhatServo(2, 180);
    // delay(10);
    // Servo_Rahwana.moveWhatServo(3, 180);
    // delay(10);
    // Servo_Rahwana.moveWhatServo(4, 180);
    // delay(1000);
    digitalWrite(WAYANG_HAND_2, LOW);
}

void Rahwana::RahwanaSelfTalk(int frontpin, int backpin, int oscdeg, int timeMillis, int periodMillis)
{
    int remainingMillis = timeMillis - 1100;
    Servo_Rahwana.moveWhatServo(frontpin, 60, 300 * 5);
    Servo_Rahwana.moveWhatServo(backpin, 180, 800 * 5);
    int loops = remainingMillis / periodMillis;
    int remainderMillis = remainingMillis % periodMillis;

    if (remainderMillis != 0)
    {
        Servo_Rahwana.moveWhatServo(frontpin, 90 - oscdeg, remainderMillis);
        for (int i = 0; i < loops; i++)
        {
            Servo_Rahwana.moveWhatServo(frontpin, 90, periodMillis / 2 * 5);
            Servo_Rahwana.moveWhatServo(frontpin, 90 - oscdeg, periodMillis / 2 * 5);
        }
    }
    else
    {
        for (int i = 0; i < loops; i++)
        {
            Servo_Rahwana.moveWhatServo(frontpin, 90 - oscdeg, periodMillis / 2 * 5);
            Servo_Rahwana.moveWhatServo(frontpin, 90, periodMillis / 2 * 5);
        }
    }
}

void Rahwana::hand_movement_1()
{
    digitalWrite(WAYANG_HAND_2, HIGH);
    Servo_Rahwana.moveWhatServo(4, 90 + 20, 2000);
    Servo_Rahwana.moveWhatServo(3, 180, 2000);
    Servo_Rahwana.moveWhatServo(4, 90 + 35, 2000);
    digitalWrite(WAYANG_HAND_2, LOW);
}

void Rahwana::hand_movement_2()
{
    digitalWrite(WAYANG_HAND_2, HIGH);
    Servo_Rahwana.moveWhatServo(3, 140, 2000);
    digitalWrite(WAYANG_HAND_2, LOW);
}

void Rahwana::hand_movement_3()
{
    digitalWrite(WAYANG_HAND_2, HIGH);
    Servo_Rahwana.moveWhatServo(4, 90 + 15, 2000);
    digitalWrite(WAYANG_HAND_2, LOW);
}

void Rahwana::hand_movement_4()
{
    digitalWrite(WAYANG_HAND_2, HIGH);
    Servo_Rahwana.moveWhatServo(4, 90 + 35, 2000);
    digitalWrite(WAYANG_HAND_2, LOW);
}

void Rahwana::hand_movement_5()
{
    digitalWrite(WAYANG_HAND_2, HIGH);
    Servo_Rahwana.moveWhatServo(3, 0, 2000);
    Servo_Rahwana.moveWhatServo(4, 90, 2000);
    digitalWrite(WAYANG_HAND_2, LOW);
}

void Rahwana::hand_movement_6()
{
    digitalWrite(WAYANG_HAND_2, HIGH);
    Servo_Rahwana.moveWhatServo(4, 60, 2000);
    Servo_Rahwana.moveWhatServo(3, 180, 2000);
    digitalWrite(WAYANG_HAND_2, LOW);
}

void Rahwana::hand_movement_7()
{
    digitalWrite(WAYANG_HAND_2, HIGH);
    Servo_Rahwana.moveWhatServo(3, 0, 2000);
    Servo_Rahwana.moveWhatServo(4, 90 + 35, 2000);
    Servo_Rahwana.moveWhatServo(3, 180, 2000);
    Servo_Rahwana.moveWhatServo(4, 90 + 25, 2000);
    digitalWrite(WAYANG_HAND_2, LOW);
}

void Rahwana::hand_movement_8()
{
    digitalWrite(WAYANG_HAND_2, HIGH);
    Servo_Rahwana.moveWhatServo(3, 180, 2000);
    digitalWrite(WAYANG_HAND_2, LOW);
}

void Rahwana::hand_movement_9()
{
    digitalWrite(WAYANG_HAND_2, HIGH);
    Servo_Rahwana.moveWhatServo(3, 0, 2000);
    Servo_Rahwana.moveWhatServo(4, 90, 2000);
    digitalWrite(WAYANG_HAND_2, LOW);
}

void Rahwana::hand_movement_10()
{
    digitalWrite(WAYANG_HAND_2, HIGH);
    Servo_Rahwana.moveWhatServo(4, 60, 2000);
    Servo_Rahwana.moveWhatServo(3, 180, 2000);
    digitalWrite(WAYANG_HAND_2, LOW);
}

void Rahwana::hand_movement_11()
{
    digitalWrite(WAYANG_HAND_2, HIGH);
    Servo_Rahwana.moveWhatServo(3, 0, 2000);
    Servo_Rahwana.moveWhatServo(4, 90 + 35, 2000);
    Servo_Rahwana.moveWhatServo(3, 180, 2000);
    Servo_Rahwana.moveWhatServo(4, 90 + 25, 2000);
    digitalWrite(WAYANG_HAND_2, LOW);
}

void Rahwana::hand_movement_12()
{
    digitalWrite(WAYANG_HAND_2, HIGH);
    Servo_Rahwana.moveWhatServo(3, 140, 2000);
    digitalWrite(WAYANG_HAND_2, LOW);
}

void Rahwana::hand_movement_13()
{
    digitalWrite(WAYANG_HAND_2, HIGH);
    Servo_Rahwana.moveWhatServo(3, 140, 2000);
    Servo_Rahwana.moveWhatServo(4, 90 + 35, 2000);
    digitalWrite(WAYANG_HAND_2, LOW);
}

void Rahwana::hand_movement_14()
{
    digitalWrite(WAYANG_HAND_2, HIGH);
    Servo_Rahwana.moveWhatServo(3, 0, 2000);
    Servo_Rahwana.moveWhatServo(4, 90, 2000);
    Servo_Rahwana.moveWhatServo(4, 60, 2000);
    Servo_Rahwana.moveWhatServo(3, 180, 2000);
    digitalWrite(WAYANG_HAND_2, LOW);
}

void Rahwana::hand_movement_15()
{
    digitalWrite(WAYANG_HAND_2, HIGH);
    Servo_Rahwana.moveWhatServo(4, 50, 2000);
    Servo_Rahwana.moveWhatServo(3, 160, 2000);
    digitalWrite(WAYANG_HAND_2, LOW);
}

void Rahwana::hand_movement_16()
{
    digitalWrite(WAYANG_HAND_2, HIGH);
    Servo_Rahwana.moveWhatServo(3, 0, 2000);
    digitalWrite(WAYANG_HAND_2, LOW);
}

void Rahwana::hand_movement_17()
{
    digitalWrite(WAYANG_HAND_2, HIGH);
    Servo_Rahwana.moveWhatServo(4, 60, 2000);
    digitalWrite(WAYANG_HAND_2, LOW);
}

void Rahwana::hand_movement_18()
{
    digitalWrite(WAYANG_HAND_2, HIGH);
    Servo_Rahwana.moveWhatServo(3, 150, 2000);
    digitalWrite(WAYANG_HAND_2, LOW);
}

void Rahwana::walk_to_a_certain_distance_before_calibrating_value(int desiredDistance)
{
    int desiredDistanceAfterCalibratingValue = desiredDistance + (float)desiredDistance * 0.155;
    Serial.println("\ndesiredDistance: ");
    Serial.print(desiredDistanceAfterCalibratingValue);
    Serial.println("mm \n");
    walk_to_a_certain_distance(desiredDistanceAfterCalibratingValue);
}

void Rahwana::rahwana_120_bpm_deathstream()
{
    digitalWrite(WAYANG_HAND_2, HIGH);
    delay(152);

    for (int i = 0; i < 60; i++)
    {
        Servo_Rahwana.moveWhatServo(4, 90 - 15, 500 * 5);
        Servo_Rahwana.moveWhatServo(4, 90 + 15, 500 * 5);
    };
    digitalWrite(WAYANG_HAND_2, LOW);
}

void Rahwana::pointToFront()
{
    digitalWrite(WAYANG_HAND_2, HIGH);
    Servo_Rahwana.defaultPosition();
    Servo_Rahwana.moveWhatServo(4, 120, 2000);
    Servo_Rahwana.moveWhatServo(3, 180, 3000);
    Servo_Rahwana.moveWhatServo(4, 130, 2000);
    digitalWrite(WAYANG_HAND_2, LOW);
}

void Rahwana::lower_pointToFront()
{
}

void Rahwana::middleFront()
{
}

void Rahwana::downFront()
{
}

void Rahwana::pointToBack()
{
}

void Rahwana::downBack()
{
}

void Rahwana::onHipBack()
{
}

void Rahwana::pointToSelf()
{
    digitalWrite(WAYANG_HAND_2, HIGH);
    Servo_Rahwana.defaultPosition();
    Servo_Rahwana.moveWhatServo(4, 60, 2000);
    Servo_Rahwana.moveWhatServo(3, 150, 3000);
    Servo_Rahwana.moveWhatServo(4, 80, 2000);
    digitalWrite(WAYANG_HAND_2, LOW);
}

void Rahwana::middleFrontBack()
{
}

void Rahwana::lowPointToBack()
{
}

void Rahwana::middleBack()
{
}