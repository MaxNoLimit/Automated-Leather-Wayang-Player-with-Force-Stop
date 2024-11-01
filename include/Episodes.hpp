#ifndef EPISODES_H
#define EPISODES_H

#include <Arduino.h>
#define fighting_STACK_SIZE 512

namespace Episodes
{
    void Mei2nd_Episode();
    void July29_Episode();
    void Testing_Hanuman();
    void Testing_Rama();
    void randomTesting();

    void manual_begin();
    void testing_hanuman_horizontal_movement();
    void testing_rama_wijaya_horizontal_movement();
    void testing_sita_horizontal_movement();
    void testing_rahwana_horizontal_movement();

    void Episode_1();
    void Episode_2();
    void Episode_3();
    void Episode_4();
    void Episode_5();

    void Episode_1_task(void *pvParameters);
    void Episode_2_task(void *pvParameters);
    void Episode_3_task(void *pvParameters);
    void Episode_4_task(void *pvParameters);
    void Episode_5_task(void *pvParameters);

    // static void sugriwaTaskFight1(void *pvParameters);
    // // void sugriwaTaskFight2(void *pvParameters);

    // static void subaliTaskFight1(void *pvParameters);
    // static void subaliTaskFight2(void *pvParamaters);

    // static void ramaTaskFight1(void *pvParameters);

};

#endif // EPISODES_H