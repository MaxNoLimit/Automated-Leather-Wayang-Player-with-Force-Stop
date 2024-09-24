#include "a4988_nema.hpp"
#include "mainfunctions.hpp"


/*
Function untuk membuat suatu nema wayang bergerak sebanyak step_value dan arah tertentu
*/
void HorizontalController::step_for_n_dir(int nema_num, int step_value, String dir)
{
    // String temp_dir = (String)tolower(dir);
    if (dir == "ccw")
    {
        switch (nema_num)
        {
        case 1:
        {
            Serial.println("NEMA 1 CCW");
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
            Serial.println("NEMA 2 CCW");
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
            Serial.println("NEMA 3 CCW");
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
            Serial.println("NEMA 4 CCW");
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
            Serial.println("NEMA 5 CCW");
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
        }
    }
    else if (dir == "cw")
    {
        Serial.println("dir command recognize");
        switch (nema_num)
        {
        case 1:
        {
            Serial.println("NEMA 1 CW");
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
            Serial.println("NEMA 2 CW");
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
            Serial.println("NEMA 3 CW");
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
            Serial.println("NEMA 4 CW");
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
            Serial.println("NEMA 5 CW");
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
        }
    }
}
