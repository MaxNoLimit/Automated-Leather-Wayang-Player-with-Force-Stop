#ifndef EPISODES_H
#define EPISODES_H

#include <Arduino.h>
#include <mainheader.hpp>
#define fighting_STACK_SIZE 256 + 256 // already maximum and optimal, cannot exceed anymore

namespace Episodes
{
    void Episode_1();
    void Episode_2();
    void Episode_3();
    void Episode_4();
    void Episode_5();
    void Episode_Extra();

    void Episode_1_task(void *pvParameters);
    void Episode_2_task(void *pvParameters);
    void Episode_3_task(void *pvParameters);
    void Episode_4_task(void *pvParameters);
    void Episode_5_task(void *pvParameters);
    void Extra_Debug_task(void *pvParameters);
};

#endif // EPISODES_H