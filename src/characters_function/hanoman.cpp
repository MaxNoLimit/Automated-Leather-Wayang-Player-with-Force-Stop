#include "characters/hanoman.hpp"
#include "a4988_nema.hpp"

WayangStepper hanoman_stepper;
HorizontalController HC_hanuman;

void Hanoman::begin(int rpm)
{
    hanoman_stepper.begin(rpm);
}

void Hanoman::walk_to_scene()
{
    HC_hanuman.step_for_n_dir(2, 1100, "ccw");
}

void Hanoman::leave_from_scene()
{
    HC_hanuman.step_for_n_dir(2, 1100, "cw");
}

void Hanoman::hand_movement_test_1()
{
    // hanoman_stepper.step_0_3(100, "a");        // 100
    // hanoman_stepper.step_reverse_4_7(50, "a"); // -50
    // hanoman_stepper.step_4_7(50, "a");         // 0
    // hanoman_stepper.step_reverse_4_7(50, "a"); // -50
    // hanoman_stepper.step_4_7(50, "a");         // 0
    // hanoman_stepper.step_reverse_4_7(50, "a"); // -50
    // hanoman_stepper.stop_stepping();
}

// void Hanoman::hand_movement_test_2(){
//     hanoman_stepper.step_4_7(50);
//     hanoman_stepper.step_reverse_0_3(100);
// }

void Hanoman::hand_movement_test_2()
{
    // hanoman_stepper.step_reverse_0_3(200, "a"); // -100
    // hanoman_stepper.step_4_7(100, "a");         // 50
    // hanoman_stepper.stop_stepping();
}

void Hanoman::hand_movement_test_3()
{
    // hanoman_stepper.step_0_3(250, "a");         // 150
    // hanoman_stepper.step_reverse_4_7(120, "a"); // -70
    // hanoman_stepper.stop_stepping();
}

void Hanoman::hand_movement_test_4()
{
    // hanoman_stepper.step_reverse_0_3(250, "a"); // -100
    // hanoman_stepper.step_4_7(120, "a");         // 50
    // hanoman_stepper.stop_stepping();
}

void Hanoman::hand_movement_test_5()
{
    // hanoman_stepper.step_0_3(100, "a");        // 0
    // hanoman_stepper.step_reverse_4_7(50, "a"); // 0
    // hanoman_stepper.stop_stepping();
}

void Hanoman::talking(int delay_in_sec)
{
    digitalWrite(WAYANG_HAND_2, HIGH);
    for (int i = 0; i < (delay_in_sec * 1000000 / 4998272) - 2; i++)
    {
        hanoman_stepper.leftHandSpin("cw", 90); // 1499136 us
        hanoman_stepper.leftHandSpin("ccw", 90); // 1499136 us

        delay(2000);
    }
    hanoman_stepper.stopAllStepper();
    digitalWrite(WAYANG_HAND_2, LOW);
}