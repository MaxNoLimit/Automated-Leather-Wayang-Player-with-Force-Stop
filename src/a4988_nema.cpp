#include "a4988_nema.hpp"
#include "mainfunctions.hpp"
#include "distanceSensorVL53L0X.hpp"

// const int nema_pins[10] = {
//     EN_NEMA_1,
//     EN_NEMA_2,
//     EN_NEMA_3,
//     EN_NEMA_4,
//     EN_NEMA_5,
//     EN_NEMA_6,
//     EN_NEMA_7,
//     EN_NEMA_8,
//     EN_NEMA_9,
//     EN_NEMA_10,
// };

// int selected_nema = 0;
// String desiredDir = "cw";
// int desiredDistance = 0;
// bool state_1 = true;
// TaskHandle_t spinNEMAHandler;

/*
Function untuk membuat suatu nema wayang bergerak sebanyak step_value dan arah tertentu
*/
void HorizontalController::step_for_n_dir(int nema_num, int step_value, String dir)
{
    // String temp_dir = (String)tolower(dir);
    vTaskSuspend(mainLoopTaskHandler);
    if (dir == "ccw")
    {
        switch (nema_num)
        {
        case 1:
        {
            Serial.println(F("NEMA 1 CCW"));
            digitalWrite(EN_NEMA_1, LOW);
            digitalWrite(NEMA_DIR, HIGH);

            bool state = true;
            for (int i = 0; i < step_value; i++)
            {
                digitalWrite(NEMA_STEP, state);
                state = !state;
                delayMicroseconds(PERIOD_NEMA);
            }
            digitalWrite(EN_NEMA_1, HIGH);
            // NEMAs.en_num_gpio_a(NEMAs.DISABLE_ALL_EN);
            break;
        }

        case 2:
        {
            Serial.println(F("NEMA 2 CCW"));
            digitalWrite(EN_NEMA_2, LOW);
            digitalWrite(NEMA_DIR, HIGH);

            bool state = true;
            for (int i = 0; i < step_value; i++)
            {
                digitalWrite(NEMA_STEP, state);
                state = !state;
                delayMicroseconds(PERIOD_NEMA);
            }
            digitalWrite(EN_NEMA_2, HIGH);
            // NEMAs.en_num_gpio_a(NEMAs.DISABLE_ALL_EN);
            break;
        }

        case 3:
        {
            Serial.println(F("NEMA 3 CCW"));
            digitalWrite(EN_NEMA_3, LOW);
            digitalWrite(NEMA_DIR, HIGH);

            bool state = true;
            for (int i = 0; i < step_value; i++)
            {
                digitalWrite(NEMA_STEP, state);
                state = !state;
                delayMicroseconds(PERIOD_NEMA);
            }
            digitalWrite(EN_NEMA_3, HIGH);
            // NEMAs.en_num_gpio_a(NEMAs.DISABLE_ALL_EN);
            break;
        }
        case 4:
        {
            Serial.println(F("NEMA 4 CCW"));
            digitalWrite(EN_NEMA_4, LOW);
            digitalWrite(NEMA_DIR, HIGH);

            bool state = true;
            for (int i = 0; i < step_value; i++)
            {
                digitalWrite(NEMA_STEP, state);
                state = !state;
                delayMicroseconds(PERIOD_NEMA);
            }
            digitalWrite(EN_NEMA_4, HIGH);
            // NEMAs.en_num_gpio_a(NEMAs.DISABLE_ALL_EN);
            break;
        }
        case 5:
        {
            Serial.println(F("NEMA 5 CCW"));
            digitalWrite(EN_NEMA_5, LOW);
            digitalWrite(NEMA_DIR, HIGH);

            bool state = true;
            for (int i = 0; i < step_value; i++)
            {
                digitalWrite(NEMA_STEP, state);
                state = !state;
                delayMicroseconds(PERIOD_NEMA);
            }
            digitalWrite(EN_NEMA_5, HIGH);
            // NEMAs.en_num_gpio_a(NEMAs.DISABLE_ALL_EN);
            break;
        }
        case 6:
        {
            Serial.println(F("NEMA 6 CCW"));
            digitalWrite(EN_NEMA_6, LOW);
            digitalWrite(NEMA_DIR, HIGH);

            bool state = true;
            for (int i = 0; i < step_value; i++)
            {
                digitalWrite(NEMA_STEP, state);
                state = !state;
                delayMicroseconds(PERIOD_NEMA);
            }
            digitalWrite(EN_NEMA_6, HIGH);
            // NEMAs.en_num_gpio_a(NEMAs.DISABLE_ALL_EN);
            break;
        }
        case 7:
        {
            Serial.println(F("NEMA 7 CCW"));
            digitalWrite(EN_NEMA_7, LOW);
            digitalWrite(NEMA_DIR, HIGH);

            bool state = true;
            for (int i = 0; i < step_value; i++)
            {
                digitalWrite(NEMA_STEP, state);
                state = !state;
                delayMicroseconds(PERIOD_NEMA);
            }
            digitalWrite(EN_NEMA_7, HIGH);
            // NEMAs.en_num_gpio_a(NEMAs.DISABLE_ALL_EN);
            break;
        }
        case 8:
        {
            Serial.println(F("NEMA 8 CCW"));
            digitalWrite(EN_NEMA_8, LOW);
            digitalWrite(NEMA_DIR, HIGH);

            bool state = true;
            for (int i = 0; i < step_value; i++)
            {
                digitalWrite(NEMA_STEP, state);
                state = !state;
                delayMicroseconds(PERIOD_NEMA);
            }
            digitalWrite(EN_NEMA_8, HIGH);
            // NEMAs.en_num_gpio_a(NEMAs.DISABLE_ALL_EN);
            break;
        }
        case 9:
        {
            Serial.println(F("NEMA 9 CCW"));
            digitalWrite(EN_NEMA_9, LOW);
            digitalWrite(NEMA_DIR, HIGH);

            bool state = true;
            for (int i = 0; i < step_value; i++)
            {
                digitalWrite(NEMA_STEP, state);
                state = !state;
                delayMicroseconds(PERIOD_NEMA);
            }
            digitalWrite(EN_NEMA_9, HIGH);
            // NEMAs.en_num_gpio_a(NEMAs.DISABLE_ALL_EN);
            break;
        }
        case 10:
        {
            Serial.println(F("NEMA 10 CCW"));
            digitalWrite(EN_NEMA_10, LOW);
            digitalWrite(NEMA_DIR, HIGH);

            bool state = true;
            for (int i = 0; i < step_value; i++)
            {
                digitalWrite(NEMA_STEP, state);
                state = !state;
                delayMicroseconds(PERIOD_NEMA);
            }
            digitalWrite(EN_NEMA_10, HIGH);
            // NEMAs.en_num_gpio_a(NEMAs.DISABLE_ALL_EN);
            break;
        }
        }
    }
    else if (dir == "cw")
    {
        Serial.println(F("dir command recognize"));
        switch (nema_num)
        {
        case 1:
        {
            Serial.println(F("NEMA 1 CW"));
            digitalWrite(EN_NEMA_1, LOW);
            digitalWrite(NEMA_DIR, LOW);

            bool state = true;
            for (int i = 0; i < step_value; i++)
            {
                digitalWrite(NEMA_STEP, state);
                state = !state;
                delayMicroseconds(PERIOD_NEMA);
            }
            digitalWrite(EN_NEMA_1, HIGH);
            // NEMAs.en_num_gpio_a(NEMAs.DISABLE_ALL_EN);
            break;
        }

        case 2:
        {
            Serial.println(F("NEMA 2 CW"));
            digitalWrite(EN_NEMA_2, LOW);
            digitalWrite(NEMA_DIR, LOW);

            bool state = true;
            for (int i = 0; i < step_value; i++)
            {
                digitalWrite(NEMA_STEP, state);
                state = !state;
                delayMicroseconds(PERIOD_NEMA);
            }
            // digitalWrite(EN_2_NEMA, HIGH);
            // NEMAs.en_num_gpio_a(NEMAs.DISABLE_ALL_EN);
            digitalWrite(EN_NEMA_2, HIGH);
            break;
        }
        case 3:
        {
            Serial.println(F("NEMA 3 CW"));
            digitalWrite(EN_NEMA_3, LOW);
            digitalWrite(NEMA_DIR, LOW);

            bool state = true;
            for (int i = 0; i < step_value; i++)
            {
                digitalWrite(NEMA_STEP, state);
                state = !state;
                delayMicroseconds(PERIOD_NEMA);
            }
            digitalWrite(EN_NEMA_3, HIGH);
            // NEMAs.en_num_gpio_a(NEMAs.DISABLE_ALL_EN);
            break;
        }
        case 4:
        {
            Serial.println(F("NEMA 4 CW"));
            digitalWrite(EN_NEMA_4, LOW);
            digitalWrite(NEMA_DIR, LOW);

            bool state = true;
            for (int i = 0; i < step_value; i++)
            {
                digitalWrite(NEMA_STEP, state);
                state = !state;
                delayMicroseconds(PERIOD_NEMA);
            }
            digitalWrite(EN_NEMA_4, HIGH);
            // NEMAs.en_num_gpio_a(NEMAs.DISABLE_ALL_EN);
            break;
        }
        case 5:
        {
            Serial.println(F("NEMA 5 CW"));
            digitalWrite(EN_NEMA_5, LOW);
            digitalWrite(NEMA_DIR, LOW);

            bool state = true;
            for (int i = 0; i < step_value; i++)
            {
                digitalWrite(NEMA_STEP, state);
                state = !state;
                delayMicroseconds(PERIOD_NEMA);
            }
            digitalWrite(EN_NEMA_5, HIGH);
            // NEMAs.en_num_gpio_a(NEMAs.DISABLE_ALL_EN);
            break;
        }
        case 6:
        {
            Serial.println(F("NEMA 6 CW"));
            digitalWrite(EN_NEMA_6, LOW);
            digitalWrite(NEMA_DIR, LOW);

            bool state = true;
            for (int i = 0; i < step_value; i++)
            {
                digitalWrite(NEMA_STEP, state);
                state = !state;
                delayMicroseconds(PERIOD_NEMA);
            }
            digitalWrite(EN_NEMA_6, HIGH);
            // NEMAs.en_num_gpio_a(NEMAs.DISABLE_ALL_EN);
            break;
        }
        case 7:
        {
            Serial.println(F("NEMA 7 CW"));
            digitalWrite(EN_NEMA_7, LOW);
            digitalWrite(NEMA_DIR, LOW);

            bool state = true;
            for (int i = 0; i < step_value; i++)
            {
                digitalWrite(NEMA_STEP, state);
                state = !state;
                delayMicroseconds(PERIOD_NEMA);
            }
            digitalWrite(EN_NEMA_7, HIGH);
            // NEMAs.en_num_gpio_a(NEMAs.DISABLE_ALL_EN);
            break;
        }
        case 8:
        {
            Serial.println(F("NEMA 8 CW"));
            digitalWrite(EN_NEMA_8, LOW);
            digitalWrite(NEMA_DIR, LOW);

            bool state = true;
            for (int i = 0; i < step_value; i++)
            {
                digitalWrite(NEMA_STEP, state);
                state = !state;
                delayMicroseconds(PERIOD_NEMA);
            }
            digitalWrite(EN_NEMA_8, HIGH);
            // NEMAs.en_num_gpio_a(NEMAs.DISABLE_ALL_EN);
            break;
        }
        case 9:
        {
            Serial.println(F("NEMA 9 CW"));
            digitalWrite(EN_NEMA_9, LOW);
            digitalWrite(NEMA_DIR, LOW);

            bool state = true;
            for (int i = 0; i < step_value; i++)
            {
                digitalWrite(NEMA_STEP, state);
                state = !state;
                delayMicroseconds(PERIOD_NEMA);
            }
            digitalWrite(EN_NEMA_9, HIGH);
            // NEMAs.en_num_gpio_a(NEMAs.DISABLE_ALL_EN);
            break;
        }
        case 10:
        {
            Serial.println(F("NEMA 10 CW"));
            digitalWrite(EN_NEMA_10, LOW);
            digitalWrite(NEMA_DIR, LOW);

            bool state = true;
            for (int i = 0; i < step_value; i++)
            {
                digitalWrite(NEMA_STEP, state);
                state = !state;
                delayMicroseconds(PERIOD_NEMA);
            }
            digitalWrite(EN_NEMA_10, HIGH);
            // NEMAs.en_num_gpio_a(NEMAs.DISABLE_ALL_EN);
            break;
        }
        }
    }
    vTaskResume(mainLoopTaskHandler);
}

// void spinNEMA(void *pvParameters)
// {
//     if (getDistanceSensorNum(selected_nema) - desiredDistance > 0)
//     {
//         digitalWrite(nema_pins[selected_nema - 1], LOW);
//         digitalWrite(NEMA_DIR, HIGH);
//     }
//     else
//     {
//         digitalWrite(nema_pins[selected_nema - 1], LOW);
//         digitalWrite(NEMA_DIR, LOW);
//     }
//     while (1)
//     {
//         digitalWrite(NEMA_STEP, state_1);
//         state_1 = !state_1;
//         vTaskDelay(2 / portTICK_PERIOD_MS);
//     }
// }

// void distanceKeeper(void *pvParameters)
// {
//     while (1)
//     {
//         if (getDistanceSensorNum(selected_nema) == desiredDistance)
//         {
//             digitalWrite(nema_pins[selected_nema - 1], HIGH);
//             vTaskDelete(spinNEMAHandler);
//             if (isEpisodeTaskCreated)
//             {
//                 vTaskResume(episodeTaskHandler[currentEpisode - 1]);
//             }
//             free(pvParameters);

//             vTaskDelete(NULL);
//         }
//     }
// }

// /*
// Function untuk closed loop horizontal movement with thread
// */
// void HorizontalController::step_for_what_distance(int nema_num, int distance)
// {
//     selected_nema = nema_num;
//     desiredDistance = distance;
//     xTaskCreate(
//         distanceKeeper,   /* Task function. */
//         "DistanceKeeper", /* name of task. */
//         128,              /* Stack size of task */
//         NULL,             /* parameter of the task */
//         1,                /* priority of the task */
//         NULL);            /* Task handle to keep track of created task */

//     xTaskCreate(
//         spinNEMA,          /* Task function. */
//         "SpinNEMA",        /* name of task. */
//         128,               /* Stack size of task */
//         NULL,              /* parameter of the task */
//         1,                 /* priority of the task */
//         &spinNEMAHandler); /* Task handle to keep track of created task */
//     if (isEpisodeTaskCreated)
//     {
//         vTaskSuspend(episodeTaskHandler[currentEpisode - 1]);
//     }
// }