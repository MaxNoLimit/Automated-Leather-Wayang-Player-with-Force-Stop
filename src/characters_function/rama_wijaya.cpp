#include "characters/rama_wijaya.hpp"
#include "a4988_nema.hpp"

WayangHandServo Servo_RamaWijaya(whatSideServo::RIGHT);
HorizontalController HC_rama_wijaya;

void RamaWijaya::defaultHandPosition()
{
    digitalWrite(WAYANG_HAND_1, HIGH);
    Servo_RamaWijaya.defaultPosition();
    digitalWrite(WAYANG_HAND_1, LOW);
}

void RamaWijaya::walk_to_scene()
{
    HC_rama_wijaya.step_for_n_dir(1, 1100, "cw");
}

void RamaWijaya::leave_from_scene()
{
    HC_rama_wijaya.step_for_n_dir(1, 1100, "ccw");
}

void RamaWijaya::hand_movement_test_1()
{
    digitalWrite(WAYANG_HAND_1, HIGH);
    Servo_RamaWijaya.moveWhatServo(1, 0);
    Servo_RamaWijaya.moveWhatServo(2, 0);
    Servo_RamaWijaya.moveWhatServo(3, 0);
    Servo_RamaWijaya.moveWhatServo(4, 0);
    delay(1000);
    Servo_RamaWijaya.moveWhatServo(1, 180);
    Servo_RamaWijaya.moveWhatServo(2, 180);
    Servo_RamaWijaya.moveWhatServo(3, 180);
    Servo_RamaWijaya.moveWhatServo(4, 180);
    delay(1000);
    digitalWrite(WAYANG_HAND_1, LOW);
}

void RamaWijaya::hand_movement_test_2()
{
}

void RamaWijaya::hand_movement_test_3()
{
}

void RamaWijaya::hand_movement_test_4()
{
}

void RamaWijaya::talking(int delay_in_sec)
{
    // digitalWrite(WAYANG_HAND_1, HIGH);
    // for (int i = 0; i < (delay_in_sec * 1000000 / 4998272) - 1; i++)
    // {
    //     rama_wijaya_stepper.rightHandSpin("ccw", 90);
    //     rama_wijaya_stepper.rightHandSpin("cw", 90);
    //     delay(2000);
    // }
    // rama_wijaya_stepper.stopAllStepper();
    // digitalWrite(WAYANG_HAND_1, LOW);
}
