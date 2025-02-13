#include "a4988_nema.hpp"
#include "mainfunctions.hpp"
#include "distanceSensorVL53L0X.hpp"

/*
Function untuk membuat suatu nema wayang bergerak sebanyak step_value dan arah tertentu
*/
void HorizontalController::step_for_n_dir(int nema_num, int step_value, String dir)
{
    if (isEpisodeTaskCreated)
    {
        vTaskSuspend(mainLoopTaskHandler);
    }
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
                delay(PERIOD_NEMA);
            }
            digitalWrite(EN_NEMA_1, HIGH);
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
                delay(PERIOD_NEMA);
            }
            digitalWrite(EN_NEMA_2, HIGH);
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
                delay(PERIOD_NEMA);
            }
            digitalWrite(EN_NEMA_3, HIGH);
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
                delay(PERIOD_NEMA);
            }
            digitalWrite(EN_NEMA_4, HIGH);
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
                delay(PERIOD_NEMA);
            }
            digitalWrite(EN_NEMA_5, HIGH);
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
                delay(PERIOD_NEMA);
            }
            digitalWrite(EN_NEMA_6, HIGH);
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
                delay(PERIOD_NEMA);
            }
            digitalWrite(EN_NEMA_7, HIGH);
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
                delay(PERIOD_NEMA);
            }
            digitalWrite(EN_NEMA_8, HIGH);
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
                delay(PERIOD_NEMA);
            }
            digitalWrite(EN_NEMA_9, HIGH);
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
                delay(PERIOD_NEMA);
            }
            digitalWrite(EN_NEMA_10, HIGH);
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
                delay(PERIOD_NEMA);
            }
            digitalWrite(EN_NEMA_1, HIGH);
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
                delay(PERIOD_NEMA);
            }
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
                delay(PERIOD_NEMA);
            }
            digitalWrite(EN_NEMA_3, HIGH);
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
                delay(PERIOD_NEMA);
            }
            digitalWrite(EN_NEMA_4, HIGH);
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
                delay(PERIOD_NEMA);
            }
            digitalWrite(EN_NEMA_5, HIGH);
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
                delay(PERIOD_NEMA);
            }
            digitalWrite(EN_NEMA_6, HIGH);
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
                delay(PERIOD_NEMA);
            }
            digitalWrite(EN_NEMA_7, HIGH);
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
                delay(PERIOD_NEMA);
            }
            digitalWrite(EN_NEMA_8, HIGH);
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
                delay(PERIOD_NEMA);
            }
            digitalWrite(EN_NEMA_9, HIGH);
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
                delay(PERIOD_NEMA);
            }
            digitalWrite(EN_NEMA_10, HIGH);
            break;
        }
        }
    }
    if (isEpisodeTaskCreated)
    {
        vTaskResume(mainLoopTaskHandler);
    }
}

