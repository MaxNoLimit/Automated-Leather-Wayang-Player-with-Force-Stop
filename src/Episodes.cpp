// #include <Arduino_FreeRTOS.h>
#include "Episodes.hpp"
#include "sound_system.hpp"
#include "characters/hanoman.hpp"
#include "characters/rama_wijaya.hpp"
#include "characters/sita.hpp"
#include "characters/rahwana.hpp"
#include "characters/laksmana.hpp"
#include "mainheader.hpp"
#include "characters/subali.hpp"
#include "characters/sugriwa.hpp"
#include "characters/wibhisana.hpp"
#include "characters/anggada.hpp"
#include "characters/anila.hpp"
#include "mainfunctions.hpp"
#include "state_management.hpp"

Hanoman hanoman;
RamaWijaya rama_wijaya;
Sita sita;
Rahwana rahwana;
Laksmana laksmana;
Subali subali;
Sugriwa sugriwa;
Wibhisana wibhisana;
Anggada anggada;
Anila anila;

TaskHandle_t episodeTaskHandler[6];

static void RamaFirstAttackTask(void *pvParameters)
{
    while (1)
    {
        rama_wijaya.pointToFront();
        rama_wijaya.downFront();
        rama_wijaya.middleFront();
        rama_wijaya.pointToFront();
        vTaskResume(episodeTaskHandler[4]);
        vTaskDelete(NULL);
    }
}

static void RahwanaFirstDefendTask(void *pvParameters)
{
    while (1)
    {
        rahwana.pointToFront();
        vTaskDelay(300 / portTICK_PERIOD_MS);
        rahwana.downFront();
        rahwana.middleFront();
        rahwana.pointToSelf();
        vTaskDelay(100 / portTICK_PERIOD_MS);
        vTaskDelete(NULL);
    }
}

static void WibhisanaFirstAttackTask(void *pvParameters)
{
    while (1)
    {
        wibhisana.pointToFront();
        wibhisana.downFront();
        wibhisana.middleFront();
        wibhisana.pointToFront();
        wibhisana.downFront();
        wibhisana.pointToFront();
        vTaskResume(episodeTaskHandler[4]);
        vTaskDelete(NULL);
    }
}

static void RahwanaSecondDefendTask(void *pvParameters)
{
    while (1)
    {
        rahwana.pointToFront();
        rahwana.downFront();
        rahwana.middleFront();
        rahwana.pointToFront();
        rahwana.downFront();
        rahwana.lower_pointToFront();
        vTaskDelay(200 / portTICK_PERIOD_MS);
        vTaskDelete(NULL);
    }
}

static void anggadaCheeringTask(void *pvParameters)
{
    while (1)
    {
        anila.pointToFront();
        delay(2000);
        anila.downFront();
        vTaskResume(episodeTaskHandler[3]);
        vTaskDelete(NULL);
    }
}

static void anilaCheeringTask(void *pvParameters)
{
    while (1)
    {
        anggada.pointToFront();
        delay(2000);
        anggada.downFront();
        vTaskDelete(NULL);
    }
}

static void sugriwaTaskFight1(void *pvParameters)
{
    while (1)
    {
        Serial.print(F("Running sugriwaTaskFight1: "));
        Serial.println(uxTaskGetStackHighWaterMark(NULL));
        sugriwa.pointToFront();       // takes 900 ms
        sugriwa.lower_pointToFront(); // takes 700 ms
        sugriwa.downFront();          // takes 700 ms
        sugriwa.lower_pointToFront(); // takes 700 ms
        // vTaskDelay(200 / portTICK_PERIOD_MS);

        // deleting sugriwaTaskFight1 task
        // Serial.println("sugriwaTaskFight1 stack: " + String(uxTaskGetStackHighWaterMark(NULL)));
        vTaskDelete(NULL);
    }
}

static void subaliTaskFight1(void *pvParameters)
{
    // vTaskSuspend(mainLoopTaskHandler);
    while (1)
    {
        Serial.print(F("Running subaliTaskFight1: "));
        Serial.println(uxTaskGetStackHighWaterMark(NULL));
        subali.pointToFront();       // takes 900 ms
        subali.lower_pointToFront(); // takes 700 ms
        subali.downFront();          // takes 700 ms
        subali.pointToFront();       // takes 900 ms
        // deleting subaliTaskFight1 task
        // Serial.println("subaliTaskFight1 stack: " + String(uxTaskGetStackHighWaterMark(NULL)));
        vTaskResume(episodeTaskHandler[1]);
        vTaskDelete(NULL);
    }
}

static void subaliTaskFight2(void *pvParameters)
{
    while (1)
    {
        Serial.print(F("Running subaliTaskFight2: "));
        Serial.println(uxTaskGetStackHighWaterMark(NULL));
        subali.pointToFront();       // takes 900 ms
        subali.lower_pointToFront(); // takes 700 ms
        subali.downFront();          // takes 700 ms
        subali.lower_pointToFront(); // takes 900 ms
        // deleting subaliTaskFight2 task
        // Serial.println("subaliTaskFight2 stack: " + String(uxTaskGetStackHighWaterMark(NULL)));
        vTaskDelete(NULL);
    }
}

static void ramaTaskFight1(void *pvParameters)
{
    while (1)
    {
        Serial.print(F("Running ramaTaskFight1 : "));
        Serial.println(uxTaskGetStackHighWaterMark(NULL));
        rama_wijaya.pointToFront();       // takes 900 ms
        rama_wijaya.lower_pointToFront(); // takes 700 ms
        rama_wijaya.downFront();          // takes 700 ms
        rama_wijaya.pointToFront();       // takes 700 ms
        // deleting ramaTaskFight1 task
        // Serial.println("ramaTaskFight1 stack: " + String(uxTaskGetStackHighWaterMark(NULL)));
        vTaskResume(episodeTaskHandler[1]);
        vTaskDelete(NULL);
    }
}

void Episodes::Episode_1()
{
    // Calibrating all wayang first
    CalibratingFunction::wayangHand();

    setAllMOSFETtoLOW();

    SoundSystem::playMusicWayang();
    sita.walk_to_a_certain_distance_before_calibrating_value(160);
    laksmana.walk_to_a_certain_distance_before_calibrating_value(160);
    // 001 (Sita1Sita-laksmana dialogue 1)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SITA1SITA_LAKS_DIALOGUE_1);
    // delay(3000); // audio test only 3s

    delay(1312);
    // movement 1, 2
    sita.pointToFront(); // takes 700 ms

    delay(4796 - 1312 - 700); // result = 2784 ms
    // movement 3
    sita.lower_pointToFront(); // takes 700 ms

    delay(7339 - 4796 - 700); // result = 1843 ms
    // movement 4, 5
    for (int i = 0; i < 4; i++)
    {
        sita.directControl(1, 70, 400);
        sita.directControl(1, 100, 400);
    } // takes 800 ms each loop

    delay(10673 - 7339 - 800 * 4);

    // movement 6, 7
    sita.pointToFront();        // takes 700 ms
    delay(12320 - 10673 - 700); // result = 1547 ms

    sita.defaultHandPosition(); // takes 1400 ms

    // 002 (01 S-L1 laksmana1F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::S_L1_LAKS1F);
    // delay(3000);

    /*You are the wife of the hero from Raghu lineage;*/
    delay(787);              // 787
    laksmana.pointToFront(); // 1487
    delay(3875 - 1487);      // 3875 (2388)

    /*you are the beloved of my brother,*/
    laksmana.lower_pointToFront(); // 4575 (700)
    laksmana.pointToFront();       // 5275 (700)
    laksmana.lower_pointToFront(); // 5975 (700)
    delay(6589 - 5975);            // 6589 (614)

    /*also you are the daughter of king Janaka.*/
    laksmana.pointToFront(); // 7289 (700)
    delay(9898 - 7289);      // 9898 (2609)

    /*Why do you worry and cry so at hearing such a call?*/
    laksmana.middleFront(); // 10798 (900)
    delay(13684 - 10798);   // 13684 (2886)

    /*Do you know that it is he who calls?*/
    laksmana.lower_pointToFront(); // 14384 (700)
    delay(16604 - 14384);          // 16604 (2220)

    /*Do you know who that is? */
    laksmana.middleFront(); // 17504 (900)
    delay(18923 - 17504);   // 18923 (1419)

    /*You may ask,*/
    laksmana.pointToFront(); // 19623 (700)
    delay(20269 - 19623);    // 20269 (646)

    /*who is powerful enough in this world to fight prince Rama in battle?*/
    laksmana.downBack();   // 20969 (700)
    laksmana.middleBack(); // 21669 (700)
    delay(25323 - 21669);  // 25323 (2954)

    /*He is the most powerful person,*/
    laksmana.lower_pointToFront(); // 26023 (700)
    delay(27655 - 26023);          // 27655 (1632)

    /*the most skilled in handling all weapons.*/
    laksmana.pointToBack(); // 29055 (1400)
    delay(30722 - 29055);   // 30722 (1667)

    /*How could you have fears that he would be killed,*/
    laksmana.downBack();     // 31422 (700)
    laksmana.pointToFront(); // 32122 (700)
    delay(34010 - 32122);    // 34010 (1888)

    /*butted by a deer?*/
    laksmana.onHipBack(); // 35210 (1200)
    delay(36072 - 35210); // 36072 (862)

    /*That call was not his,*/
    // laksmana.middleFront();              // 36972 (900)
    laksmana.directControl(4, 110, 400); // 1800
    laksmana.directControl(3, 180, 1000);
    laksmana.directControl(4, 120, 400);

    laksmana.directControl(4, 115, 400); // 37372 (400)
    laksmana.directControl(4, 120, 400); // 37772 (400)
    // laksmana.directControl(4, 115, 400); // 38172 (400)
    // laksmana.directControl(4, 120, 400); // 38572 (400)
    delay(38746 - 38572 - 100); // 38746 (174-100)

    /*it was the call of an evil demon, */
    laksmana.pointToFront(); // 39446 (700)
    delay(41447 - 39446);    // 41447 (2001)

    /*it was a trick with the purpose of deceiving us.*/
    laksmana.lower_pointToFront(); // 42147 (700)
    delay(44700 - 42147 - 700);    // 44000 (1853)
    laksmana.downFront();          // 44700 (700)

    /*I say, it was the cry of the deer*/
    laksmana.pointToSelf(); // 45400 (700)
    delay(48296 - 45400);   // 48296 (2896)
    laksmana.downFront();   // 48996 (700)

    /*which was hit by an arrow,*/
    laksmana.lower_pointToFront(); // 49696 (700)
    delay(50930 - 49696);          // 50930 (1234)

    /*sounding like the voice of Rama. */
    laksmana.middleFront(); // 51830 (900)
    delay(53233 - 51830);   // 53233 (1403)

    /*return to default position*/
    laksmana.downFront();
    laksmana.downBack();
    laksmana.onHipBack();

    // 003 (Sita2Sita-laksmana dialogue 1)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SITA2SITA_LAKS_DIALOGUE_1);
    // delay(3000);

    // (1114) My brother Laksmana. (2184)

    delay(1114);
    sita.pointToFront(); // takes 700 ms

    // (2562) What does this mean? (3546)

    delay(2562 - 1114 - 700);
    sita.lower_pointToFront(); // takes 700 ms

    // (4189) This is the first time that you do not obey my orders. (7113)

    delay(4198 - 2562 - 700);
    sita.middleFront(); // takes 900 ms

    // (8038) In the past you were very faithful to your brother, (10513)

    delay(8038 - 4189 - 900);
    for (int i = 0; i < 3; i++)
    {
        sita.directControl(1, 45, 400);
        sita.directControl(1, 0, 400);
    } // takes 800 ms each loop

    // (11095) but now he is in trouble, (12326)

    delay(11095 - 8038 - 800 * 3);
    sita.downFront();          // takes 700 ms
    sita.lower_pointToFront(); // takes 700 ms

    // (12747) shame on you, (13502)

    delay(12747 - 11095 - 700 - 700);
    sita.pointToFront(); // takes 700 ms

    // (14078) you do not want to help. (15167)

    delay(14078 - 12747 - 700);
    sita.lower_pointToFront(); // takes 700 ms

    // (15990) You think about Rama like this. (17638)

    delay(15990 - 14078 - 700);
    sita.downFront();   // takes 700 ms
    sita.middleFront(); // takes 900 ms

    // (18440)  ‘Let him be killed by the deer. (19962)

    // (20309) It will be very lucky! (21771)

    // ***MAY NOT SMOOTH MOVEMENT***

    delay(18440 - 15990 - 700 - 900);
    for (int i = 0; i < 4; i++)
    {
        sita.directControl(1, 45, 400);
        sita.directControl(1, 0, 400);
    } // takes 800 ms each loop

    // (22215) I will take his place and marry Sita. (24250)

    delay(22215 - 18440 - 800 * 4);
    sita.pointToSelf(); // takes 1400 ms

    // (24956) Who will be her protector, (26144)

    delay(24956 - 22215 - 1400);
    sita.downFront();          // takes 700 ms
    sita.lower_pointToFront(); // takes 700 ms

    // (26422) no one else except me.’ (28075)

    delay(26422 - 24956 - 700 - 700);
    sita.pointToSelf(); // takes 1400 ms

    // (28594) you said this to yourself, didn't you? (30247)

    delay(28594 - 26422 - 1400);
    sita.downFront();   // takes 700 ms
    sita.middleFront(); // takes 900 ms

    // (31045) Debased and foolish Laksmana, (32697)

    delay(31045 - 28594 - 700 - 900);
    sita.downFront();    // takes 700 ms
    sita.pointToFront(); // takes 700 ms

    // (33087) do you think I am wicked, (34225)

    // (34832) capable of such evil, (36212)

    // (36447) such lewdness? (37319)

    delay(33087 - 31045 - 700 - 700);
    // sita.oscillate(37913 - 33087); // takes 4826 ms ~~ 4200 ms
    for (int i = 0; i < 6; i++)
    {
        sita.directControl(1, 55, 400);
        sita.directControl(1, 10, 400);
    } // takes 800 ms each loop

    // (37913) I do not have any intention of marrying again, (40389)

    delay(37913 - 33087 - 800 * 6);
    sita.downFront(); // takes 700 ms

    // (40840) just this once. (41901)

    delay(40840 - 37913 - 700);
    sita.lower_pointToFront(); // takes 700 ms

    // (42759) I will only serve Rama, nobody else. (45432)

    delay(42759 - 40840 - 700);
    sita.pointToSelf(); // takes 1400 ms

    // (46341) If my lord and master died, (48024)

    // (48476) if Rama is killed in battle (50462)

    delay(46341 - 42759 - 1400);
    // sita.oscillate(50722 - 46341); // takes 4381 ms ~~ 4200 ms
    sita.downBack(); // takes 700 ms
    // sita.middleFrontBack(); // takes 700 ms
    // for (int i = 0; i < 3; i++)
    // {
    //     sita.directControl(3, 90, 400);
    //     sita.directControl(3, 120, 400);
    // } // takes 800 ms each loop

    // (50722) butted by the deer, (51570)

    delay(50722 - 46341 - 700);
    sita.downFront(); // takes 700 ms

    // (51781) I will sever my neck (52913)

    // (53241) and burn myself. (54287)

    // (54961) I will follow my husband; (56378)

    delay(51781 - 50722 - 700);
    sita.pointToSelf(); // takes 1400 ms

    // (56657) I will not take refuge with you. (58501)

    delay(56657 - 51781 - 1400);
    sita.downFront();    // takes 700 ms
    sita.pointToFront(); // take 700 ms

    delay(58501 - 56657 - 700 - 700);

    // 004 (02 S-L1 laksmana2F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::S_L1_LAKS2F);
    // delay(3000);

    delay(1188);
    /*You suspect me of being wicked,*/
    laksmana.pointToFront();             // 1888 (700)
    laksmana.directControl(3, 170, 400); // 2288 (400)
    laksmana.directControl(3, 180, 400); // 2688 (400)
    laksmana.directControl(3, 170, 400); // 3088 (400)
    laksmana.directControl(3, 180, 400); // 3488 (400)
    delay(3670 - 3488);                  // 3670 (182)

    /*having the intention to betray my older brother. */
    laksmana.lower_pointToFront(); // 4370 (700)
    delay(1000);                   // 5370 (1000)
    laksmana.downFront();          // 6070 (700)
    delay(6787 - 6070);            // 6787 (717)

    /*My mind is pure, truthful, and not wicked.*/
    laksmana.pointToSelf(); // 7487 (700)
    delay(10564 - 7487);    // 10564 (3077)

    /* Let all the deities bear witness to the purity of my heart.*/
    laksmana.directControl(3, 0, 1200);   // 11764 (1200)
    laksmana.directControl(4, 110, 400);  // 12244 (480) -> 400
    laksmana.directControl(3, 180, 1200); // 13444 (1200)
    laksmana.directControl(4, 140, 400);  // 13924 (480) -> 400
    delay(16175 - 13924 + 160);           // 16175 (2251)

    /*Let me fall into hell,*/
    laksmana.directControl(3, 120, 1000); // 17175 (1000)
    laksmana.directControl(4, 140, 400);  // 17575 (400)
    delay(18385 - 17575);                 // 18385 (810)

    /*let me be overcome by misfortunes, */
    laksmana.directControl(3, 0, 1000);  // 19385 (1000)
    laksmana.directControl(4, 110, 400); // 19785 (400)
    delay(21214 - 19785);                // 21214 (1429)

    /*if I am treacherous.*/
    laksmana.pointToSelf(); // 21914 (700)
    delay(24277 - 21914);   // 24277 (2363)

    /*O, daughter of Janaka, */
    laksmana.directControl(3, 0, 500);   // 25277 (1000)
    laksmana.directControl(4, 110, 400); // 25677 (400)
    laksmana.directControl(3, 180, 500); // 26677 (1000)
    laksmana.directControl(4, 120, 400); // 27077 (400)
    delay(26796 - 26077);                // 26796 (719)

    /*you have uttered bad words, */
    laksmana.pointToFront(); // 27496 (700)
    delay(29186 - 26796);    // 29186 (2390)

    /*as if you meant it when you accused me of wanting you to be my wife.*/
    laksmana.lower_pointToFront();       // 29886 (700)
    laksmana.directControl(3, 130, 400); // 30286 (400)
    laksmana.directControl(3, 120, 400); // 30686 (400)
    laksmana.directControl(3, 130, 400); // 31086 (400)
    laksmana.directControl(3, 120, 400); // 31486 (400)
    laksmana.directControl(3, 130, 400); // 31886 (400)
    laksmana.directControl(3, 120, 400); // 32286 (400)
    laksmana.directControl(3, 130, 400); // 32686 (400)
    laksmana.directControl(3, 120, 400); // 33086 (400)
    delay(33867 - 33086);                // 33867 (781)

    /*Because of your bad words, */
    laksmana.pointToFront(); // 34567 (700)
    delay(36000 - 33867);    // 36000 (2133)

    /*may you find great sorrow. */
    laksmana.lower_pointToFront();       // 36700 (700)
    laksmana.directControl(3, 130, 400); // 37100 (400)
    laksmana.directControl(3, 120, 400); // 37500 (400)
    laksmana.directControl(3, 130, 400); // 37900 (400)
    laksmana.directControl(3, 120, 400); // 38300 (400)
    laksmana.directControl(3, 130, 400); // 38700 (400)
    delay(63);                           // 38763 (63)

    /*You will be captured by the enemy,*/
    laksmana.middleFront(); // 39663 (900)
    delay(41139 - 39663);   // 41139 (1476)

    /*after my leave!*/
    laksmana.downFront(); // 41839 (700)

    /*return to default position*/
    laksmana.defaultHandPosition();
    sita.defaultHandPosition();

    SoundSystem::playMusicWayang();
    laksmana.defaultStandPosition();
    sita.defaultStandPosition();

    delay(1000);
    sita.walk_to_a_certain_distance_before_calibrating_value(160);
    rahwana.walk_to_a_certain_distance_before_calibrating_value(200);

    // 005 (005SitaRahwanadialogueRahwana1)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SITA_RAHWANA_DIALOGUE_RAHWANA_1);
    // delay(3000);
    /*Who are you, o beautiful one,*/
    rahwana.pointToFront(); // 900
    delay(2660 - 900);

    /*who enters the forest to pick flowers. */
    rahwana.downFront(); // 700
    delay(5682 - 2660 - 700 - 500);

    /*How unparalleled is your beauty,*/
    rahwana.middleFront(); // 1200
    delay(7910 - 5682 - (1200 - 500));

    /*most perfect.*/
    rahwana.pointToFront(); // 700
    delay(9579 - 7910 - 700);

    /*Even an extremely poor ascetic who has overcome his sensual impulses,*/
    rahwana.pointToFront();     // 700
    for (int i = 0; i < 3; i++) // 800*3
    {
        rahwana.directControl(3, 160, 400);
        rahwana.directControl(3, 180, 400);
    }
    rahwana.directControl(3, 160, 400); // 400
    delay(13390 - 9579 - 700 - (800 * 3) - 400);

    /* would be crazy about you and fall heels over ears */
    rahwana.downFront();   // 700
    delay(400);            // 400
    rahwana.middleFront(); // 1200
    delay(16906 - 13390 - 700 - 400 - 1200);

    /*in love with you */
    rahwana.pointToFront(); // 700
    rahwana.downFront();    // 700
    // delay(19101-16906-700-700);

    /*My name is Rawana, */ //(18306)
    rahwana.pointToSelf();  // 1100
    delay(20828 - 18306 - 1100);

    /*I am the king ruling over the country of Lenka, */
    rahwana.directControl(3, 0, 740);   // 740
    rahwana.directControl(4, 120, 600); // 600
    rahwana.directControl(3, 180, 740); // 740
    rahwana.directControl(4, 140, 300); // 300
    delay(24113 - 20828 - 740 - 600 - 740 - 300);

    /*my palace is on the beach and there are */
    rahwana.lower_pointToFront(); // 700
    delay(26298 - 24113 - 700);

    /*plenty of brilliant jewels*/
    rahwana.pointToFront(); // 700
    delay(28573 - 26298 - 700);

    /*and precious stones decorating it,*/
    rahwana.lower_pointToFront(); // 700
    delay(30925 - 28573 - 700);

    /*making it as glorious as the moon. */
    rahwana.middleFront();              // 1200
    rahwana.directControl(3, 160, 400); // 400
    rahwana.directControl(3, 180, 400); // 400
    rahwana.directControl(3, 160, 400); // 400
    rahwana.directControl(3, 180, 400); // 400
    delay(34625 - 30925 - 1200 - (400 * 4));

    /*you may rule over it,*/
    rahwana.pointToFront(); // 700
    delay(36311 - 34625 - 700 - 700);
    rahwana.downFront(); // 700

    /*and share a luxurious life with me. */
    rahwana.pointToSelf(); // 1100
    delay(39143 - 36311 - 1100 - 700);
    rahwana.downFront(); // 700

    /*Have no doubt,*/
    rahwana.lower_pointToFront(); // 700
    delay(40529 - 39143 - 700);

    /*everything you wish for is there.*/
    rahwana.pointToFront(); // 700
    delay(42971 - 40529 - 700 - 700);

    /*what do you think?*/
    rahwana.middleFront(); // 1200
    delay(44024 - 42971 - (1200 - 700));

    /*O beautiful one? */
    rahwana.pointToFront(); // 700

    // rahwana.Rahwana_1();

    // 006 (006SitaRahwanadialogueSita1)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SITA_RAHWANA_DIALOGUE_SITA_1);
    // delay(3000);

    // (74)I am sorry, I cannot accept for I am already betrothed to Rama, (4700)

    delay(74);
    sita.pointToSelf(); // takes 1400 ms

    // (5162)son of king Dasaratha (6668)

    delay(5162 - 74 - 1400);
    sita.downFront();    // takes 700 ms
    sita.pointToFront(); // takes 700 ms

    // (7272)and it is the duty of a wife to be loyal to her husband and no other. (12304)

    delay(7272 - 5162 - 700 - 700);
    sita.downFront(); // takes 700 ms
    delay(12304 - 7272 - 700);

    // 007 (007SitaRahwanadialogueRahwana2)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SITA_RAHWANA_DIALOGUE_RAHWANA_2);
    // delay(3000);

    /*I know that Rama,*/
    delay(464);
    rahwana.pointToFront(); // 700
    delay(3158 - 464 - 700);

    /*he is worthless. */
    rahwana.lower_pointToFront(); // 700
    delay(5451 - 3158 - 700);

    /*Why do you want to stay with him in this extreme destitution.*/
    rahwana.pointToFront();     // 700
    for (int i = 0; i < 5; i++) // 800*5
    {
        rahwana.directControl(3, 160, 400); // 400
        rahwana.directControl(3, 180, 400); // 400
    }

    delay(11047 - 5451 - 700 - (800 * 5) - 500);

    /*He is debased */
    rahwana.middleFront(); // 1200
    delay(12527 - 11047 - (1200 - 500));

    /*and inferior to all his clever brothers.*/
    rahwana.lower_pointToFront(); // 700
    for (int i = 0; i < 3; i++)   // 800*3
    {
        rahwana.directControl(3, 100, 400); // 400
        rahwana.directControl(3, 120, 400); // 400
    }
    rahwana.directControl(3, 100, 400); // 400
    delay(17084 - 12527 - 700 - (800 * 3) - 400);

    /*He is the eldest, */
    rahwana.lower_pointToFront(); // 700
    delay(18878 - 17084 - 700);

    /*fit to be king*/
    rahwana.pointToFront(); // 700
    delay(20968 - 18878 - 700);

    /*yet he is banished into the forests. */
    rahwana.downFront(); // 700
    delay(24973 - 20968 - 700 - 700);

    /*I*/
    rahwana.pointToSelf(); // 1100
    delay(25687 - 24973 - (1100 - 700));

    /*am victorious over deities,*/
    rahwana.directControl(3, 0, 740);   // 740
    rahwana.directControl(4, 120, 600); // 600
    rahwana.directControl(3, 180, 740); // 740
    rahwana.directControl(4, 140, 300); // 300
    delay(28938 - 25687 - 740 - 600 - 740 - 300);

    /*men and animals.*/
    rahwana.lower_pointToFront(); // 700
    delay(31492 - 28938 - 700);

    /*God Waisrawana is defeated and has submitted.*/
    rahwana.pointToFront();     // 700
    for (int i = 0; i < 3; i++) // 800*3
    {
        rahwana.directControl(3, 160, 400); // 400
        rahwana.directControl(3, 180, 400); // 400
    }
    delay(35933 - 31492 - 700 - (800 * 3) - 700);

    /*God Yama has begged for his life */
    rahwana.middleFront();      // 1200
    for (int i = 0; i < 2; i++) // 800*2
    {
        rahwana.directControl(3, 115, 400); // 400
        rahwana.directControl(3, 135, 400); // 400
    }
    delay(39230 - 35933 - (1200 - 700) - (800 * 2));

    /*out of fear of death.*/
    rahwana.lower_pointToFront(); // 700
    delay(42104 - 39230 - 700);

    /*the king of the gods,*/
    rahwana.pointToFront(); // 700
    delay(44275 - 42104 - 700 - 700);

    /*God Indra,*/
    rahwana.middleFront(); // 1200
    delay(45732 - 44275 - (1200 - 700));

    /*has paid tribute.*/
    rahwana.downFront(); // 700
    delay(48286 - 45732 - 700 - 700);

    /*All of them respect me. */
    rahwana.pointToSelf(); // 1100
    delay(50051 - 48286 - (1100 - 700));

    /*I say it is perfectly fitting*/
    rahwana.downFront();   // 700
    rahwana.middleFront(); // 1200
    delay(54195 - 50051 - 700 - 1200);

    /*that we love each other*/
    rahwana.pointToFront(); // 700
    delay(55734 - 54195 - 700);

    /*I am young and powerful, */
    rahwana.downFront();   // 700
    rahwana.pointToSelf(); // 1100
    delay(58706 - 55734 - 700 - 1100);

    /*you are a beautiful lady*/
    rahwana.downFront();   // 700
    rahwana.middleFront(); // 1200
    delay(61701 - 58706 - 700 - 1200);

    /*in the prime of womanhood. */
    rahwana.pointToFront(); // 700
    delay(64917 - 61701 - 700);

    /*Rama is worthless my dear, */
    rahwana.lower_pointToFront(); // 700
    delay(67663 - 64917 - 700);

    /*leave him!*/
    rahwana.downFront(); // 700
    delay(71024 - 67663 - 700);

    /*grr*/
    rahwana.lower_pointToFront(); // 700
    delay(72435 - 71024 - 700 - 700);

    /*If you won’t give me an answer*/
    rahwana.middleFront(); // 1200
    delay(75093 - 72435 - (1200 - 700));

    /*then i shall show you my might! */
    rahwana.pointToFront(); // 700
    delay(76693 - 75093 - 700);
    rahwana.downFront(); // 700
    delay(2000);

    /*insert kidnapping sequence below*/
    SoundSystem::playMusicWayang();
    rahwana.pointToFront();
    rahwana.walk_to_a_certain_distance_before_calibrating_value(340);
    delay(1000);

    sita.defaultStandPosition();
    rahwana.defaultHandPosition();
    rahwana.defaultStandPosition();

    // 008 (03 L-R1 laksmana1F)
    rama_wijaya.walk_to_a_certain_distance_before_calibrating_value(160);
    laksmana.walk_to_a_certain_distance_before_calibrating_value(160);

    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::L_R1_LAKS1F);
    // delay(3000);
    delay(329);
    /*Brother,*/
    laksmana.middleFront(); // 1029 (700)
    delay(1431 - 1029);     // 1431 (402)

    /*an injured bird told me that it saw Sita got kidnapped by a notorious demon called Rawana */
    laksmana.pointToFront();             // 2131 (700)
    laksmana.directControl(3, 170, 400); // 2531 (400)
    laksmana.directControl(3, 180, 400); // 2931 (400)
    laksmana.directControl(3, 170, 400); // 3331 (400)
    laksmana.directControl(3, 180, 400); // 3731 (400)
    laksmana.lower_pointToFront();       // 4431 (700)
    for (int i = 0; i < 3; i++)          // 6831 (800*3)
    {
        laksmana.directControl(3, 130, 400);
        laksmana.directControl(3, 120, 400);
    }
    laksmana.downFront(); // 7531 (700)
    delay(8188 - 7531);   // 8188 (657)

    /*and that they are in Lenka across the ocean. */
    laksmana.pointToBack(); // 9588 (1400)
    delay(11394 - 9588);    // 11394 (1806)

    /*It advised me that we should seek Sugriwa through the Resyamuka mountain*/
    laksmana.pointToSelf();     // 12094 (700)
    for (int i = 0; i < 3; i++) // 15294 (800*4)
    {
        laksmana.directControl(1, 10, 400);
        laksmana.directControl(1, 0, 400);
    }
    delay(16292 - 15294 - 700); // 15592 (998)

    /*for he may be able to help us with his monkey troops. */
    laksmana.downFront();       // 16292 (700)
    laksmana.middleFront();     // 17192 (900)
    for (int i = 0; i < 3; i++) // 19592 (800*3)
    {
        laksmana.directControl(3, 170, 400);
        laksmana.directControl(3, 180, 400);
    }
    delay(19775 - 19592); // 19775 (183)

    /*return to default position*/
    laksmana.downFront();
    laksmana.downBack();
    laksmana.onHipBack();

    // 009 (Rama1laksmana-Rama Diaglogue(in place of narrator for context))
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::RAMA1LAKS_RAMA_DIALOGUE_IN_PLACE_NARATOR);
    // delay(3000);

    // (1139) Yes, let us head to Resyamuka and introduce ourselves. (5074)
    delay(1139);
    rama_wijaya.pointToFront(); // takes 1200 ms
    rama_wijaya.downFront();    // takes 700 ms
    rama_wijaya.pointToSelf();  // takes 900 ms

    rama_wijaya.downFront();                     // takes 700 ms
    delay(5074 - 1139 - 1200 - 700 - 900 - 700); // result = 438

    SoundSystem::playMusicWayang();
    rama_wijaya.defaultStandPosition();
    laksmana.defaultStandPosition();

    delay(1000);
    rama_wijaya.walk_to_a_certain_distance_before_calibrating_value(160);
    hanoman.walk_to_a_certain_distance_before_calibrating_value(160);

    // 010 (04 H-R1 Hanuman1F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::H_R1_HANUMAN1F);
    // delay(3000);

    // (429) O excellent ones. (2307) [Front Middle-Front]

    delay(429);
    hanoman.middleFront(); // takes 1200 ms

    // (2634) You are marvelous, (4267) [Front Point to front]

    delay(2634 - 429 - 1200);
    hanoman.downFront();    // takes 700 ms
    hanoman.pointToFront(); // takes 900 ms

    // (4523) you dare, (5540) [Front Low point to front]

    delay(4523 - 2634 - 700 - 900);
    hanoman.lower_pointToFront(); // takes 700 ms

    // (5654) and are able to come here. (7701) [Front point to front]

    delay(5654 - 4523 - 700);
    hanoman.pointToFront(); // takes 900 ms

    // (8317) The mountain of Resyamuka is impassible, (11393) [Back point to back, Front Down]

    delay(8317 - 5654 - 900);
    hanoman.downBack();    // takes 700 ms
    hanoman.pointToBack(); // takes 1400 ms
    hanoman.downFront();   // takes 700 ms

    // (11909) even God Maheswara is reluctant to come here. (15287) [Back hip, Front point to front]

    delay(11909 - 8317 - 700 - 1400 - 700);
    hanoman.downBack();     // takes 700 ms
    hanoman.onHipBack();    // takes 900 ms
    hanoman.pointToFront(); // takes 900 ms

    // (16118) What is your purpose (17263) [Front Middle-Front]

    delay(16118 - 11909 - 700 - 900 - 900);
    hanoman.middleFront(); // takes 1200 ms

    // (17435) both of you? (18222) [Front Point to front, Oscillate]

    delay(17435 - 16118 - 1200);
    hanoman.pointToFront(); // takes 900 ms
    for (int i = 0; i < 2; i++)
    {
        hanoman.directControl(3, 170, 100);
        hanoman.directControl(3, 180, 100);
    } // takes 200 ms per one loop

    // (18867) There are many things that are highly dangerous here. (22205) [Front Middle-Front, oscillate]

    delay(18867 - 17435 - 900 - 200 * 2);
    hanoman.middleFront(); // takes 1200 ms
    for (int i = 0; i < 3; i++)
    {
        hanoman.directControl(3, 125, 400);
        hanoman.directControl(3, 135, 400);
    } // takes 800 ms per one loop

    // (22702) In the caves there are demons and imps, (25657) [Front Down, Back low point to back]

    delay(22702 - 18867 - 1200 - 800 * 3);
    hanoman.downFront();      // takes 700 ms
    hanoman.lowPointToBack(); // takes 700 ms

    // (26238) and the path you come through (28084) [Back hip, Front point to front]

    delay(26238 - 22702 - 700 - 700);
    hanoman.onHipBack();    // takes 900 ms
    hanoman.pointToFront(); // takes 900 ms

    // (28299) is thick with undergrowth and difficult to pass. (31694) [Front Middle-Front]

    delay(28299 - 26238 - 900 - 900);
    hanoman.downFront();   // takes 700 ms
    hanoman.middleFront(); // takes 1200 ms

    // (32293) Nobody but you have come here. (34495) [Front point to front]

    delay(32293 - 28299);
    hanoman.downFront();    // takes 700 ms
    hanoman.pointToFront(); // takes 900 ms

    delay(34495 - 32293 - 700 - 900);
    hanoman.downFront(); // takes 700 ms

    // 011 (Rama1Hanuman-Rama dialogue_E)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::RAMA1HANUMAN_RAMA_DIALOGUE_E);
    // delay(3000);

    // (1182) O, holy man, (2568)

    delay(1182);
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (3137) my purpose is like this. (4616)

    delay(3137 - 1182 - 1200);
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.middleFront(); // takes 1200 ms

    // (5124) Come near and listen. (6268)

    delay(5124 - 3137 - 700 - 1200);
    rama_wijaya.downFront();          // takes 700 ms
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (6801) I will tell you also about the reason of my travel. (9659)

    delay(6801 - 5124 - 700 - 700);
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.pointToSelf(); // takes 900 ms

    // (10458) The wealthy king Dasaratha, (12011)

    delay(10458 - 6801 - 700 - 900);
    rama_wijaya.downFront();    // takes 700 ms
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (12555) well known throughout the world, (13997)

    delay(12555 - 10458 - 700 - 1200);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (14498) possessing all kinds of luxury, (16448)

    delay(14498 - 12555 - 700);
    rama_wijaya.downFront(); // takes 700 ms

    // (16881) has many sons. (17951)

    delay(16881 - 14498 - 700);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (18780) All my brothers (19721)

    delay(18780 - 16881 - 700);
    rama_wijaya.middleFront(); // takes 900 ms

    // (19907) are excellent and powerful. (21398)

    delay(19907 - 18780 - 900);
    rama_wijaya.downFront();          // takes 700 ms
    delay(1000);                      // takes 1000 ms
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (22406) I am the exception, (23923)

    // (24387) the unfortunate. (25346)

    delay(22406 - 19907 - 700 - 1000 - 700);
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.pointToSelf(); // takes 900 ms

    // (26076) His orders to go to the impassible forests, (28984)

    delay(26076 - 22406 - 700 - 900);
    rama_wijaya.downFront();    // takes 700 ms
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (29529) is the reason that we both are here. (31682)

    delay(29529 - 26076 - 700 - 1200);
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.pointToSelf(); // takes 900 ms

    // (32573) I have been to the hermitage of the sage Sutiksna. (35630)

    delay(32573 - 29529 - 700 - 900);
    rama_wijaya.downFront();    // takes 700 ms
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (36472) There I stayed a while to care for the hermitage. (39844)

    delay(36472 - 32573 - 700 - 1200);
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.middleFront(); // takes 1200 ms

    // (40679) My wife Sita went with me formerly. (43080)

    delay(40679 - 36472 - 700 - 1200);
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.pointToSelf(); // takes 900 ms

    // (43823) Then the wicked Rawana abducted her (46131)

    delay(43823 - 40679 - 700 - 900);
    rama_wijaya.downFront();          // takes 700 ms
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (46558) and fled away so quickly. (48371)

    delay(46558 - 43823 - 700 - 700);
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.middleFront(); // takes 1200 ms

    // (49361) I have come here to look for Sita. (51471)

    delay(49361 - 46558 - 700 - 1200);
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.pointToSelf(); // takes 900 ms

    // (52133) That is the reason why I go everywhere through the forests. (55252)

    delay(52133 - 49361 - 700 - 900);
    rama_wijaya.downFront();    // takes 700 ms
    rama_wijaya.pointToFront(); // takes 1200 ms

    delay(55252 - 52133 - 700 - 1200);
    rama_wijaya.downFront(); // takes 700 ms

    // 012 (05 H-R1 Hanuman2F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::H_R1_HANUMAN2F);
    // delay(3000);
    delay(630);

    /*O, Raghawa,*/
    hanoman.middleFront(); // 1830 (1200)
    hanoman.downFront();   // 2530 (700)

    /* I have been ordered to come here- */
    hanoman.pointToSelf(); // 3430 (900)
    delay(4094 - 3430);    // 4094 (664)

    /*The king of the monkeys Sugriwa gave me orders to look for you.*/
    hanoman.middleBack();     // 5494 (1400)
    delay(8162 - 5494 - 700); // 7462 (1968)

    /*The situation is like this.*/
    hanoman.downFront();          // 8162 (700)
    hanoman.lower_pointToFront(); // 8862 (700)
    hanoman.downBack();           // 9562 (700)
    delay(10514 - 9562 - 700);    // 9814 (252)

    /*There is a great monkey, unequalled in power called Bali.*/
    hanoman.downFront();   // 10514 (700)
    hanoman.middleFront(); // 11714 (1200)
    hanoman.onHipBack();   // 12614 (900)
    delay(15273 - 12614);  // 15273 (2659)

    /*Even God Aditya is inferior to him in power.*/
    hanoman.pointToFront();     // 16173 (900)
    for (int i = 0; i < 3; i++) // 18573 (2400)
    {
        hanoman.directControl(3, 170, 400);
        hanoman.directControl(3, 180, 400);
    }
    delay(19453 - 18573); // 19453 (880)

    /*He was savagely outrageous towards my master*/
    hanoman.downFront();   // 20153 (700)
    hanoman.pointToBack(); // 21553 (1400)
    delay(22688 - 21553);  // 22688 (1135)

    /*and insulted him.*/
    hanoman.lowPointToBack(); // 23388 (700)
    delay(24763 - 23388);     // 24763 (1375)

    /*Out of fear the monkey-king Bali,*/
    hanoman.downBack();    // 25463 (700)
    hanoman.middleFront(); // 26663 (1200)
    delay(27691 - 26663);  // 27691 (1028)

    /*my master went to the region of Malaya. */
    hanoman.downFront();   // 28391 (700)
    hanoman.pointToBack(); // 29791 (1400)
    delay(31040 - 29791);  // 31040 (1249)

    /*He ordered me to look for you, */
    hanoman.pointToSelf(); // 31940 (900)
    delay(33058 - 31940);  // 33058 (1118)

    /*as he intends to be friends with you,*/
    hanoman.middleBack(); // 34458 (1400)
    delay(35707 - 34458); // 35707 (1249)

    /*to stay and serve at your feet, */
    hanoman.pointToBack();      // 37107 (1400)
    delay(38619 - 37107 - 800); // 37819 (802)

    /*o, lord. */
    hanoman.directControl(3, 170, 400); // 38219 (400)
    hanoman.directControl(4, 95, 400);  // 38619 (400)
    delay(40258 - 38619);               // 40258 (1639)

    /*I suggest that you may grant him a favor*/
    hanoman.directControl(4, 80, 400);  // 40658 (400)
    hanoman.directControl(3, 150, 400); // 41058 (400)
    delay(42949 - 41058);               // 42949 (1891)

    /*and make him your ally,*/
    hanoman.downFront();          // 43649 (700)
    hanoman.lower_pointToFront(); // 44349 (700)
    delay(45225 - 44349);         // 45225 (876)

    /*because he is powerful,*/
    hanoman.directControl(3, 120, 400); // 45625 (400)
    delay(46965 - 45625);               // 46965 (1340)

    /*noble,*/
    hanoman.directControl(3, 100, 400); // 47365 (400)
    delay(47716 - 47365);               // 47716 (351)

    /*and goodhearted.*/
    hanoman.lower_pointToFront(); // 48416 (700)
    delay(49691 - 48416);         // 49691 (1275)

    /*Let him follow you and love you and carry out all your orders*/
    hanoman.pointToFront();     // 50591 (900)
    for (int i = 0; i < 4; i++) // 53791 (3200)
    {
        hanoman.directControl(3, 135, 400);
        hanoman.directControl(3, 180, 400);
    }
    delay(54515 - 53791); // 54515 (724)

    /*Let him take part as commander in the battlefield*/
    hanoman.lower_pointToFront(); // 55215 (700)
    for (int i = 0; i < 3; i++)   // 57615 (2400)
    {
        hanoman.directControl(3, 135, 400);
        hanoman.directControl(3, 90, 400);
    }
    delay(350); // 57965 (350)

    /*to kill Dasamukha.*/
    hanoman.directControl(1, 45, 400);
    hanoman.directControl(1, 0, 400);
    hanoman.directControl(1, 45, 400);
    hanoman.directControl(1, 0, 240);

    /*return to default position*/
    hanoman.downFront();
    hanoman.downBack();
    hanoman.onHipBack();

    SoundSystem::playMusicWayang();
    rama_wijaya.defaultStandPosition();
    hanoman.defaultStandPosition();

    // setAllMOSFETtoHIGH();

    SoundSystem::playDialogFromACertainFolder(SoundSystem::INDICATOR_SOUND, SoundSystem::INDICATOR_SOUND_NUMBER::INDICATOR_FINISHED_SHOWING);
    delay(2000);
}

void Episodes::Episode_2()
{
    CalibratingFunction::wayangHand();

    setAllMOSFETtoLOW();

    SoundSystem::playMusicWayang();

    delay(1000);
    sugriwa.walk_to_a_certain_distance_before_calibrating_value(250);
    rama_wijaya.walk_to_a_certain_distance_before_calibrating_value(135);

    // 013 (06 S-R1 Sugriwa1F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::S_R1_SUGRIWA1F);
    // delay(3000);

    /*O, Raghawa!*/
    sugriwa.middleFront(); // 1200
    delay(1861 - 1200);

    /*The monkey king Bali is extremely powerful. */
    sugriwa.pointToFront(); // 900
    delay(5146 - 1861 - 900);

    /*There is no match for him in this threefold world.*/
    sugriwa.middleFront();             // 1200
    sugriwa.directControl(2, 80, 400); // 400
    sugriwa.directControl(2, 60, 400); // 400
    sugriwa.directControl(2, 80, 400); // 400
    sugriwa.directControl(2, 60, 400); // 400
    delay(9927 - 5146 - 1200 - 1600);

    /*It is not out of disdain that I talk to you like this, my lord,*/
    sugriwa.lower_pointToFront();       // 700
    sugriwa.directControl(1, 110, 400); // 400
    sugriwa.directControl(1, 90, 400);  // 400
    delay(12117 - 9927 - 700 - 800);
    sugriwa.downFront(); // 700
    delay(14600 - 12117 - 700);

    /*but it is because of out friendship*/
    sugriwa.pointToFront(); // 900
    delay(16806 - 14600 - 900 - 700);
    sugriwa.downFront(); // 700

    /* that I wish to explain the matter.*/
    sugriwa.pointToSelf(); // 900
    delay(19982 - 16806 - 900 - 500);

    /*Although Bali is famed for his power, */
    sugriwa.pointToBack(); // 1400
    sugriwa.downFront();   // 700
    delay(23332 - 19982 - 1400 - 700 + 500);

    /*he will certainly be killed by your irresistible arrows.*/
    sugriwa.pointToFront(); // 900
    sugriwa.downBack();     // 700
    sugriwa.onHipBack();    // 900
    delay(27727 - 23332 - 900 - 700 - 900);

    /*Well!*/
    sugriwa.downFront(); // 700
    delay(28800 - 27727 - 700);

    /*This is the story of how he obtained that extraordinary power in the world.*/
    sugriwa.middleFront(); // 1200
    delay(34590 - 28800 - 1200);

    /*It was a boon from a compassionate monk. */
    sugriwa.pointToBack(); // 1400
    delay(37961 - 34590 - 1400 - 500);

    /*He became more and more powerful */
    sugriwa.middleFront(); // 1400
    sugriwa.downBack();    // 700
    sugriwa.onHipBack();   // 900
    delay(40852 - 37961 - 1400 - 700 - 900 + 500);

    /*and finally irresistible.*/
    sugriwa.lower_pointToFront(); // 700
    delay(43472 - 40852 - 700);

    /*He is equal to the Sun,*/
    sugriwa.pointToFront(); // 900
    delay(45762 - 43472 - 900);

    /*whilst his opponents are Darkness. */
    sugriwa.lower_pointToFront();       // 700
    sugriwa.directControl(1, 110, 400); // 400
    sugriwa.directControl(1, 90, 400);  // 400
    sugriwa.directControl(1, 110, 400); // 400
    sugriwa.directControl(1, 90, 400);  // 400
    delay(49326 - 45762 - 700 - 1600 - 700);
    sugriwa.downFront(); // 700

    /*I am sad and afraid to see his power. */
    sugriwa.pointToSelf(); // 900
    delay(53635 - 49326 - 900);

    /*Formerly I had no idea that he could ever be killed.*/
    sugriwa.downBack();   // 700
    sugriwa.middleBack(); // 1400
    delay(58244 - 53635 - 700 - 1400 - 700);
    sugriwa.downFront();

    /*But now you, my lord, have come.*/
    sugriwa.middleFront(); // 1200
    sugriwa.downBack();    // 700
    sugriwa.onHipBack();   // 900
    delay(61669 - 58244 - 1200 - 700 - 900);

    /*You are unsurpassingly powerful,*/
    sugriwa.pointToFront();            // 900
    sugriwa.directControl(1, 20, 400); // 400
    sugriwa.directControl(1, 0, 400);  // 400
    sugriwa.directControl(1, 20, 400); // 400
    sugriwa.directControl(1, 0, 400);  // 400
    delay(64601 - 61669 - 900 - 1600);

    /*and I think,*/
    sugriwa.lower_pointToFront(); // 700
    delay(65888 - 64601 - 700);

    /*he will be killed by you. */
    sugriwa.pointToFront();            // 900
    sugriwa.directControl(1, 20, 400); // 400
    sugriwa.directControl(1, 0, 400);  // 400
    delay(68221 - 65888 - 900 - 800);

    /*I think we should go immediately to Kiskindha, */
    sugriwa.downFront();   // 700
    sugriwa.pointToSelf(); // 900
    delay(72351 - 68221 - 700 - 900 - (700));

    /* I will challenge him */
    sugriwa.pointToBack(); // 1400
    delay(73660 - 72351 - 700 - (600));
    sugriwa.downBack();

    /*and you will shoot him whilst we duel.*/
    sugriwa.downFront();    // 700
    sugriwa.pointToFront(); // 900
    delay(75908 - 73660 - 700 - 900 - (100));

    // /*return to default position*/
    sugriwa.defaultHandPosition();

    SoundSystem::playMusicWayang();
    sugriwa.defaultStandPosition();
    rama_wijaya.defaultStandPosition();

    delay(1000);
    sugriwa.walk_to_a_certain_distance_before_calibrating_value(235);
    // rama just hides
    // rama_wijaya.walk_to_a_certain_distance_before_calibrating_value(135);

    // 014 (07 Duel1 Sugriwa1F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::DUEL1_SUGRIWA1F);
    // delay(3000);

    // (315) BALI!! (1274) [Front point to front]
    delay(315);
    sugriwa.pointToFront(); // takes 900 ms

    // (1439) I challenge you to a duel, (3364) [Front low point to front]

    // (3779) come out here and fight me. (5454) [Back point to back, Front point to front]
    delay(1439 - 315 - 900);
    for (int i = 0; i < 6; i++)
    {
        sugriwa.directControl(1, 45, 400);
        sugriwa.directControl(1, 0, 400);
    } // takes 800 ms each loop

    // (5819) *roar* (7021) [Horizontal oscillation]
    delay(7021 - 1439 - 800 * 6);
    sugriwa.downFront(); // takes 700 ms

    SoundSystem::playMusicWayang();
    subali.walk_to_a_certain_distance_before_calibrating_value(160);

    // 015 (Subali round 1 rage)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SUBALI_ROUND_1_RAGE);
    // delay(3000);
    Serial.print(F("Current stack size: "));
    Serial.println(uxTaskGetStackHighWaterMark(NULL));
    // (717) you DARE challenge me? (2349) [Front point to front]
    delay(717);
    subali.pointToFront(); // takes 900 ms

    // (2887) *roars in response* (3989) [Horizontal oscillation]
    delay(2887 - 717 - 900);
    for (int i = 0; i < 1; i++)
    {
        subali.directControl(3, 135, 400);
        subali.directControl(3, 180, 400);
    } // takes 800 ms each loop

    delay(3989 - 2887 - 800 * 1);
    subali.downFront(); // takes 700 ms

    SoundSystem::playMusicWayang();
    subali.walk_to_a_certain_distance_before_calibrating_value(170);

    Serial.print(F("Current stack size: "));
    Serial.println(uxTaskGetStackHighWaterMark(NULL));

    xTaskCreate(sugriwaTaskFight1, "sugriwaTaskFight1", fighting_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(subaliTaskFight1, "subaliTaskFight1", fighting_STACK_SIZE, NULL, 1, NULL);

    // vTaskStartScheduler();

    vTaskSuspend(episodeTaskHandler[1]);
    // sugriwa.pointToFront();       // takes 900 ms
    // subali.pointToFront();        // takes 900 ms
    // sugriwa.lower_pointToFront(); // takes 700 ms
    // subali.lower_pointToFront();  // takes 700 ms
    // sugriwa.downFront();          // takes 700 ms
    // subali.downFront();           // takes 700 ms
    // sugriwa.lower_pointToFront(); // takes 700 ms
    // subali.pointToFront();        // takes 900 ms

    // Sugriwa fight Subali 1st loss

    // delay(5000);

    sugriwa.walk_to_a_certain_distance_before_calibrating_value(170);
    subali.downFront(); // takes 700 ms
    subali.walk_to_a_certain_distance_before_calibrating_value(225);

    // 016 (08 Duel1 Sugriwa2F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::DUEL1_SUGRIWA2F);
    // delay(3000);

    // (594) I yield! (1353) [Front point to front, Back Middle-Front, Horizontal move back]
    delay(594);

    // (1653) I yield! (2412) [Horizontal move back]
    delay(1653 - 594 - 900);
    sugriwa.lower_pointToFront(); // takes 700 ms

    delay(2412 - 1653 - 700);
    sugriwa.downFront(); // takes 700 ms

    SoundSystem::playMusicWayang();
    sugriwa.defaultStandPosition();
    rama_wijaya.defaultStandPosition();
    subali.defaultStandPosition();

    delay(1000);
    sugriwa.walk_to_a_certain_distance_before_calibrating_value(250);
    rama_wijaya.walk_to_a_certain_distance_before_calibrating_value(135);

    // 017 (09 DuAft1 Sugriwa1F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::DUAFT1_SUGRIWA1F);
    // delay(3000);

    // (315) O, my lord, (1453) [Front low point to front]
    delay(315);
    sugriwa.lower_pointToFront(); // takes 700 ms

    // (1818) why did you not keep your promise, (3836) [Front Middle-Front]
    delay(1818 - 315 - 700);
    sugriwa.downFront();   // takes 700 ms
    sugriwa.middleFront(); // takes 1200 ms

    // (4323) you lied. (5024) [Front point to front]
    delay(4323 - 1818 - 700 - 1200);
    sugriwa.downFront();    // takes 700 ms
    sugriwa.pointToFront(); // takes 900 ms

    // (6005) Why did you just watch our fight without doing anything? (8968) [Front Middle-Front]
    delay(6005 - 4323 - 700 - 900);
    sugriwa.downFront();   // takes 700 ms
    sugriwa.middleFront(); // takes 1200 ms

    delay(8968 - 6005 - 700 - 1200);
    sugriwa.downFront(); // takes 700 ms

    // 018 (Rama1Sugriwa-Rama-Subali dialogue)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::RAMA1SUGRIWA_RAMA_SUBALI_DIALOGUE);
    // delay(3000);

    // (1231) This is the reason, why I stood idle, (3242)

    delay(1231);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (3917) as if I do not care. (5229)

    delay(3917 - 1231 - 700);
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.middleFront(); // takes 1200 ms

    // (5928) When you were fighting with Bali (7333)

    delay(5928 - 3917 - 700 - 1200);
    rama_wijaya.downFront();          // takes 700 ms
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (7580) I saw you and Bali look alike. (9597)

    delay(7580 - 5928 - 700 - 700);
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.middleFront(); // takes 1200 ms

    // (10501) I could not distinguish you from him, (12264)

    delay(10501 - 7580 - 700 - 1200);
    rama_wijaya.downFront();    // takes 700 ms
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (12747) and this became more and more confused. (15628)

    delay(12747 - 10501 - 700 - 1200);
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.onHipBack();   // takes 900 ms
    rama_wijaya.middleFront(); // takes 1200 ms

    // (16683) That is the reason I appeared to forget my promise to my friend. (19857)

    delay(16683 - 12747 - 700 - 900 - 1200);
    rama_wijaya.downFront();    // takes 700 ms
    rama_wijaya.downBack();     // takes 700 ms
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (20686) Now, do this! (21825)

    delay(20686 - 16683 - 700 - 700 - 1200);
    rama_wijaya.downFront(); // takes 700 ms

    // (22549) Wear leaves around your body as an identification. (25556)

    delay(22549 - 20686 - 700);
    rama_wijaya.middleFront(); // takes 1200 ms
    for (int i = 0; i < 3; i++)
    {
        rama_wijaya.directControl(1, 30, 400);
        rama_wijaya.directControl(1, 0, 400);
    } // takes 800 ms each loop

    // (26460) After you have them on, (27790)

    delay(26460 - 22549 - 1200 - 800 * 3);
    rama_wijaya.downFront();          // takes 700 ms
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (28136) fight again, (28811)

    delay(28136 - 26460 - 700 - 700);
    rama_wijaya.directControl(1, 0, 400); // takes 400 ms

    // (29195) do not be afraid. (30104)

    delay(29195 - 28136 - 400);
    rama_wijaya.directControl(1, 90, 400); // takes 400 ms

    // (30792) For sure Bali will be killed (32301)

    delay(30792 - 29195 - 400);
    rama_wijaya.directControl(1, 0, 400); // takes 400 ms

    // (32548) and you will not be hit. (33693)

    delay(32548 - 30792 - 400);
    rama_wijaya.directControl(1, 90, 400); // takes 400 ms

    delay(33693 - 32548 - 400);
    rama_wijaya.downFront(); // takes 700 ms
    rama_wijaya.onHipBack(); // takes 900 ms

    SoundSystem::playMusicWayang();
    rama_wijaya.defaultHandPosition();

    rama_wijaya.defaultStandPosition();
    sugriwa.defaultStandPosition();
    delay(500);

    sugriwa.walk_to_a_certain_distance_before_calibrating_value(235);
    // rama hides
    // rama_wijaya.walk_to_a_certain_distance_before_calibrating_value(135);

    // 019 (10 Duel2 Sugriwa1F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::DUEL2_SUGRIWA1F);
    // delay(3000);

    // (565) BALI!! (1281)
    delay(565);
    sugriwa.pointToFront(); // takes 900 ms

    // (1510) This is not (2312)
    delay(1510 - 565 - 900);
    sugriwa.lower_pointToFront(); // takes 700 ms

    // (2519) over, (3214)
    delay(2519 - 1510 - 700);
    sugriwa.pointToFront(); // takes 900 ms

    // (3528) come out here and fight me. (5275)

    // (5690) *roar* (7365)
    delay(3528 - 2519 - 900);
    for (int i = 0; i < 4; i++)
    {
        sugriwa.directControl(1, 45, 400);
        sugriwa.directControl(1, 0, 400);
    } // takes 800 ms each loop

    delay(7365 - 3528 - 800 * 4);
    sugriwa.downFront(); // takes 700 ms

    // 020 (Subali round 2 rage)
    SoundSystem::playMusicWayang();
    subali.walk_to_a_certain_distance_before_calibrating_value(160);

    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SUBALI_ROUND_2_RAGE);
    // delay(3000);

    // (1046) You dare challenge me again (2827)
    delay(1046);
    subali.pointToFront(); // takes 900 ms

    // (3267) even though you already lost once? (5176)
    delay(3267 - 1046 - 900);
    subali.lower_pointToFront(); // takes 700 ms

    // (5659) How pathetic (6440)
    delay(5659 - 3267 - 700);
    subali.pointToFront(); // takes 900 ms

    // (6974) *roar* (7858)
    delay(6974 - 5659 - 900);
    for (int i = 0; i < 1; i++)
    {
        subali.directControl(3, 135, 400);
        subali.directControl(3, 180, 400);
    } // takes 800 ms each loop

    delay(7858 - 6974 - 800 * 1);
    subali.downFront(); // takes 700 ms

    SoundSystem::playMusicWayang();
    subali.walk_to_a_certain_distance_before_calibrating_value(170);

    xTaskCreate(sugriwaTaskFight1, "sugriwaTaskFight1", fighting_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(subaliTaskFight1, "subaliTaskFight1", fighting_STACK_SIZE, NULL, 1, NULL);

    vTaskSuspend(episodeTaskHandler[1]);

    // sugriwa.pointToFront();       // takes 900 ms
    // subali.pointToFront();        // takes 900 ms
    // sugriwa.lower_pointToFront(); // takes 700 ms
    // subali.lower_pointToFront();  // takes 700 ms
    // sugriwa.downFront();          // takes 700 ms
    // subali.downFront();           // takes 700 ms
    // sugriwa.lower_pointToFront(); // takes 700 ms
    // subali.pointToFront();        // takes 900 ms

    // Sugriwa fight Subali 1st loss
    // xTaskCreate(sugriwaTaskFight1, "sugriwaTaskFight1", 128, NULL, 1, NULL);
    // xTaskCreate(subaliTaskFight1, "subaliTaskFight1", 128, NULL, 1, NULL);
    // delay(5000);

    sugriwa.defaultStandPosition();
    subali.downFront(); // takes 700 ms
    subali.walk_to_a_certain_distance_before_calibrating_value(225);
    rama_wijaya.walk_to_a_certain_distance_before_calibrating_value(225);

    xTaskCreate(subaliTaskFight2, "subaliTaskFight2", fighting_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(ramaTaskFight1, "ramaTaskFight1", fighting_STACK_SIZE, NULL, 1, NULL);

    vTaskSuspend(episodeTaskHandler[1]);
    // rama_wijaya.pointToFront();       // takes 900 ms
    // subali.pointToFront();            // takes 900 ms
    // rama_wijaya.lower_pointToFront(); // takes 700 ms
    // subali.lower_pointToFront();      // takes 700 ms
    // rama_wijaya.downFront();          // takes 700 ms
    // subali.downFront();               // takes 700 ms
    // rama_wijaya.pointToFront();       // takes 900 ms
    // subali.lower_pointToFront();      // takes 700 ms
    subali.walk_to_a_certain_distance_before_calibrating_value(170);
    subali.downFront(); // takes 700 ms
    rama_wijaya.downFront();

    // 021 (Subali bacotin rama_E)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SUBALI_BACOTIN_RAMA_E);
    // delay(3000);

    // (897) Ah Rama, (1806)
    delay(897);
    subali.pointToFront(); // takes 900 ms

    // (2460) wicked, debased and silly. (4237)
    delay(2460 - 897 - 900);
    subali.lower_pointToFront(); // takes 700 ms

    // (4757) You look peaceful, but you are very mean. (6741)
    delay(4757 - 2460 - 700);
    subali.pointToFront(); // takes 900 ms

    // (7350) May all kinds of sins befall you, (9391)
    delay(7350 - 4757 - 900);
    subali.downFront();   // takes 700 ms
    subali.middleFront(); // takes 1200 ms

    // (9968) because you shot at one who only fights with his brother (13119)
    delay(9968 - 7350 - 700 - 1200);
    subali.pointToFront(); // takes 900 ms

    // (13517) and does nothing to you. (14597)
    delay(13517 - 9968 - 900);
    subali.downFront(); // takes 700 ms

    // (15272) O, you are wicked beyond limits. (17006)
    delay(15272 - 13517 - 700);
    subali.lower_pointToFront(); // takes 700 ms

    // (17710) You do not uphold the good name of your father. (19619)
    delay(17710 - 15272 - 700);
    subali.pointToFront(); // takes 900 ms

    // (20589) You know I have not done anything wrong. (22348)
    delay(20589 - 17710 - 900 - 700);
    subali.downFront();   // takes 700 ms
    subali.pointToSelf(); // takes 900 ms

    // (22972) You are extremely depraved, (24108)
    delay(22972 - 20589 - 900 - 700);
    subali.downFront();          // takes 700 ms
    subali.lower_pointToFront(); // takes 700 ms

    // (24599) your mind is corrupt. (25466)
    delay(24599 - 22972 - 700);
    subali.pointToFront(); // takes 900 ms

    // (26316) If you follow the ascetics, (27533)
    delay(26316 - 24599 - 900);
    subali.lower_pointToFront(); // takes 700 ms

    // (27776) then the main dharmma is to be a teacher (29933)
    delay(27776 - 26316 - 700);
    subali.pointToFront(); // takes 900 ms

    // (30339) for the people inferior to him, (31757)
    delay(30339 - 27776 - 900);
    subali.downFront(); // takes 700 ms

    // (32111) to be a cure for discord, (33298)
    delay(32111 - 30339 - 700);
    subali.middleFront(); // takes 1200 ms

    // (33828) a mediator for brothers in disagreement. (35929)
    delay(33828 - 32111 - 1200);
    subali.lower_pointToFront(); // takes 700 ms

    // (36386) He should best be a cure for me who has done wrong. (39440)
    delay(36386 - 33828 - 700);
    subali.pointToFront(); // takes 900 ms

    // (40302) Besides, (40823)
    delay(40302 - 36386 - 900 - 100);
    subali.lower_pointToFront(); // takes 700 ms

    // (40998) you take the wrong side. (42092)
    delay(40998 - 40302 - 600);
    subali.pointToFront(); // takes 900 ms

    // (42613) That is foolish. (43501)
    delay(42613 - 40998 - 900);
    subali.downFront(); // takes 700 ms

    // (44347) You think you have the judicious insight, (46367)
    delay(44347 - 42613 - 700);
    subali.middleFront(); // takes 1200 ms

    // (47105) but (47212)

    // (47584) in fact you are foolish. (48908)
    delay(47105 - 44347 - 1200);
    subali.pointToFront(); // takes 900 ms

    // (48510) You think it is good for you, (51188)
    delay(48510 - 47105 - 900);
    subali.downFront(); // takes 700 ms

    // (51654) now (51931)

    // (52281) that I am dead. (53311)
    delay(51654 - 48510 - 700);
    subali.pointToSelf(); // takes 900 ms

    // (54118) You are wrong, (54946)
    delay(54118 - 51654 - 900 - 200);
    subali.downFront();          // takes 700 ms
    subali.lower_pointToFront(); // takes 700 ms

    // (55395) because your act (56082)
    delay(55395 - 54118 - 700 - 500);
    subali.pointToFront(); // takes 900 ms

    // (56638) is an act of murder. (57923)
    delay(56638 - 55395 - 900);
    subali.lower_pointToFront(); // takes 700 ms

    // (58602) And you were known formerly to be of good conduct, (60618)
    delay(58602 - 56638 - 700);
    subali.pointToFront(); // takes 900 ms

    // (61455) to be a protector of the world (62783)
    delay(61455 - 58602 - 900);
    subali.middleBack(); // 1400

    // (63560) and to care for the people. (64876)
    delay(63560 - 61455 - 1400 - 700);
    subali.downFront();   // 700
    subali.pointToBack(); // 1400

    // (65427) Your merits and cancelled out, (66926)
    delay(65427 - 63560 - 1400);
    subali.downBack();           // 700
    subali.lower_pointToFront(); // 700

    // (67558) because of killing a monkey. (68591)
    delay(67558 - 65427 - 700 - 700);
    subali.pointToFront(); // 900

    // (69334) Are you not ashamed in front of your younger brother? (71461)
    delay(69334 - 67558 - 900);
    subali.downFront();      // 700
    subali.lowPointToBack(); // 700

    // (72614) Even though I am in fact fighting with my brother, (74899)
    delay(72614 - 69334 - 700 - 700);
    subali.pointToSelf(); // 900

    // (75082) in the future we might come together again, (77064)
    delay(75082 - 72614 - 900);
    subali.downBack();   // 700
    subali.middleBack(); // 1400

    // (77649) you love Sugriwa, a monkey of improper and debased nature. (80792)
    delay(77649 - 75082 - 700 - 1400);
    subali.downBack();     // 700
    subali.downFront();    // 700
    subali.pointToFront(); // 900
    delay(500);

    subali.downFront(); // 700

    // 022 (Rama2Sugriwa-Rama-Subali dialogue_E)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::RAMA2SUGRIWA_RAMA_SUBALI_DIALOGUE_E);
    // delay(3000);

    // (1085) Hey, monkey, (1828)

    delay(1085);
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (2533) you regard yourself as smart. (4230)

    delay(2533 - 1085 - 1200);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (4954) I do not sin by killing you. (6440)

    delay(4954 - 2533 - 700);
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.middleFront(); // takes 1200 ms

    // (7213) The nature of a ksatriya is my guidance. (9852)

    delay(7213 - 4954 - 700 - 1200);
    for (int i = 0; i < 4; i++)
    {
        rama_wijaya.directControl(1, 10, 400);
        rama_wijaya.directControl(1, 0, 400);
    } // takes 800 ms each loop

    // (10476) It is not murder to kill any animal. (12641)

    delay(10476 - 7213 - 800 * 4);
    rama_wijaya.downFront();    // takes 700 ms
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (13504) All the ksatriyas in the past I take as an example, (16826)

    delay(13504 - 10476 - 700 - 1200);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (17429) they did not sin. (18360)

    delay(17429 - 13504 - 700);
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (19273) Furthermore, (19918)

    // (20205) in fact (20649)

    delay(19273 - 17429 - 1200);
    rama_wijaya.middleFront(); // takes 1200 ms

    // (21161) animals may be killed in any way, (23279)

    delay(21161 - 19273 - 1200);
    rama_wijaya.directControl(1, 30, 400); // takes 400 ms

    // (23856) they can be trapped (24655)

    delay(23856 - 21161 - 400);
    rama_wijaya.directControl(1, 0, 400); // takes 400 ms

    // (24958) with pitfalls, (25722)

    delay(24958 - 23856 - 400);
    rama_wijaya.directControl(1, 30, 400); // takes 400 ms

    // (25996) snares (26465)

    delay(25996 - 24958 - 400);
    rama_wijaya.directControl(1, 0, 400); // takes 400 ms

    // (26651) and mantraps. (27473)

    delay(26651 - 25996 - 400);
    rama_wijaya.directControl(1, 30, 400); // takes 400 ms

    // (28396) All the game in the vast forest whether it is good (31014)

    delay(28396 - 26651 - 400);
    rama_wijaya.downFront(); // takes 700 ms
    // rama_wijaya.middleFrontBack(); // takes 1200 ms

    // (31411) or bad may be killed. (32727)

    delay(31411 - 28396 - 700);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (33649) But if you say you are not an animal but a human being, (36732)

    delay(33649 - 31411 - 700);
    rama_wijaya.downBack();  // takes 700 ms
    rama_wijaya.onHipBack(); // takes 900 ms

    // (36941) then follow my conduct (37983)

    // (38380) as a human being. (39311)

    delay(36941 - 33649 - 700 - 900);
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.pointToSelf(); // takes 900 ms

    // (39931) Even then I would not have sinned in any way, (42702)

    delay(39931 - 36941 - 700 - 900);
    rama_wijaya.downFront();    // takes 700 ms
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (43127) because I have killed (44174)

    // (44391) an adulterous man. (45589)

    delay(43127 - 39931 - 700 - 1200);
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.pointToSelf(); // takes 900 ms

    // (46589) I have heard about your conducts. (48187)

    delay(46589 - 43127 - 700 - 900);
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.middleFront(); // takes 1200 ms

    // (48650) You drove away Sugriwa and you stole his wife Tara. (51820)

    delay(48650 - 46589 - 700 - 1200);
    for (int i = 0; i < 4; i++)
    {
        rama_wijaya.directControl(1, 30, 400);
        rama_wijaya.directControl(1, 0, 400);
    } // takes 800 ms each loop

    // (52482) O, you will always be condemned by the world. (55499)

    delay(52482 - 48650 - 800 * 4);
    rama_wijaya.downFront();    // takes 700 ms
    rama_wijaya.pointToFront(); // takes 1200 ms

    delay(55499 - 52482 - 700 - 1200);
    delay(1000);
    rama_wijaya.downFront(); // takes 700 ms

    // 023 (Subali tobat_E)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SUBALI_TOBAT_E);
    // delay(3000);

    /*(944) O, Raghawa (1806) */
    delay(944);
    subali.pointToFront(); // 900

    /*(2237) how noble you are, (3231)  */
    delay(2237 - 944 - 900);
    subali.lower_pointToFront(); // 700

    /*(3696) that you kill any evildoer who commits evil in the world. (7019)  */
    delay(3696 - 2237 - 700);
    subali.pointToFront();             // 900
    subali.directControl(3, 160, 400); // 400
    subali.directControl(3, 180, 400); // 400
    subali.directControl(3, 160, 400); // 400
    subali.directControl(3, 180, 400); // 400

    /*(8037) But (8277)

    (8772) may your benevolence be without limit, (10861)  */
    delay(8037 - 3696 - 900 - 1600);
    subali.downFront();      // 700
    subali.lowPointToBack(); // 700

    /*(11784) may you save the life of my child. (13305) */
    delay(11784 - 8037 - 700 - 700);
    subali.pointToSelf(); // 900

    /*(14185) As for you my brother, (15197)  */
    delay(14185 - 11784 - 900);
    subali.downFront();          // 700
    subali.lower_pointToFront(); // 700

    /*(16024) come near! Sugriwa, (17258) */
    delay(16024 - 14185 - 700 - 700);
    subali.pointToFront(); // 900

    /*(17879) I ask leave to die. (19034)  */
    delay(17879 - 16024 - 900);
    subali.downFront(); // 700

    /*(19799) In the future incarnations, (21099)  */
    delay(19799 - 17879 - 700 - (700));
    subali.downBack();     // 700
    subali.pointToFront(); // 900

    /*(21567) by the grace of the gods, (22585)  */
    delay(21567 - 19799 - (700) - 900);
    subali.downFront();   // 700
    subali.pointToBack(); // 1400

    /*(23000) may we be brothers again. (24317) */
    delay(23000 - 21567 - 1400);
    subali.pointToSelf(); // 900

    /*(25242) Let us in the future be of the same abode, (27529)  */
    delay(25242 - 23000 - 900);
    subali.downFront();    // 700
    subali.pointToFront(); // 900

    /*(28206) whether it will be a mountain of a tree with ripe fruits and plenty of honey, (32653)  */
    delay(28206 - 25242 - 700 - 900);
    subali.downBack();           // 700
    subali.lower_pointToFront(); // 700

    /*(33192) never exhausted to be enjoyed forever. (35288) */
    delay(33192 - 28206 - 700 - 700);
    subali.pointToFront(); // 900

    /*(35997) My conduct was very wrong, (37168)  */
    delay(35997 - 33192 - 900 - (700));
    subali.downFront();   // 700
    subali.pointToSelf(); // 900

    /*(38504) but the reason was not evil. (39811)  */
    delay(38504 - 35997 - 900 - (700));
    subali.downFront();    // 700
    subali.pointToFront(); // 900

    /*(40635) It was the trick of the gods (41996) */
    delay(40635 - 38504 - 900);
    subali.middleBack(); // 1400

    /*(42203) that we, (42691)  */
    /*(42960) brothers are fighting each other. (44325)  */
    delay(42203 - 40635 - 1400);
    subali.downFront();   // 700
    subali.pointToSelf(); // 900

    /*(44960) Let it be so! (45709)  */
    delay(44960 - 42203 - 700 - 900 - (700));
    subali.downFront();          // 700
    subali.lower_pointToFront(); // 700

    /*(46286) Because it is God’s will. (47695) */
    delay(46286 - 44960 - 700);
    subali.pointToBack(); // 1400

    /*(48122) Besides (48641)

    (48826) the powerful god Acintya (50217)  */
    delay(48122 - 46286 - 1400);
    subali.lowPointToBack(); // 700

    /*(50488) does not permit us (51463)  */
    delay(50488 - 48122 - 700);
    subali.downFront(); // 700

    /*(51598) to live together in happiness. (52823)*/
    delay(51598 - 50488 - 700);
    subali.downBack();           // 700
    subali.lower_pointToFront(); // 700

    /*(53490) So I will go ahead (54707) */
    delay(53490 - 51598 - 700 - 700 - (100));
    subali.downFront();   // 700
    subali.pointToSelf(); // 900

    /*(55062) to find heavenly bliss, (56509)  */
    delay(55062 - 53490 - 700 - 900 + 100);
    subali.downFront();          // 700
    subali.lower_pointToFront(); // 700

    /*(56757) to follow the decree of the gods. (58567) */
    delay(56757 - 55062 - 700 - 700);
    subali.pointToFront(); // 900
    delay(58567 - 56757 - 900);
    delay(2000);

    /*lower arms*/
    subali.downFront();

    SoundSystem::playMusicWayang();
    rama_wijaya.defaultHandPosition();
    subali.defaultHandPosition();
    sugriwa.defaultHandPosition();

    rama_wijaya.defaultStandPosition();
    sugriwa.defaultStandPosition();
    subali.defaultStandPosition();

    delay(1000);
    sugriwa.walk_to_a_certain_distance_before_calibrating_value(270);
    rama_wijaya.walk_to_a_certain_distance_before_calibrating_value(150);

    // 024 (11 S-R2 Sugriwa1F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::S_R2_SUGRIWA1F);
    // delay(3000);

    /*Ah, my lord, */
    delay(358);
    sugriwa.pointToFront(); // 900
    delay(1746 - 358 - 900);

    /*how great and unlimited is your mercy towards us,*/
    sugriwa.lower_pointToFront();       // 700
    sugriwa.directControl(1, 110, 400); // 400
    sugriwa.directControl(1, 90, 400);  // 400
    sugriwa.directControl(1, 110, 400); // 400
    sugriwa.directControl(1, 90, 400);  // 400
    sugriwa.downFront();                // 700
    delay(5217 - 1746 - 700 - 1600 - 700);

    /*but we cannot return it right away. */
    sugriwa.pointToSelf(); // 900
    delay(7794 - 5217 - 900);

    /*Let it be delayed for a while,*/
    sugriwa.pointToBack(); // 1400
    delay(10242 - 7794 - 1400 - 700);
    sugriwa.downBack(); // 700

    /*because the rainy season has come,*/
    sugriwa.downFront();    // 700
    sugriwa.pointToFront(); // 900
    delay(12876 - 10242 - 700 - 900);

    /*and the monkeys are troubled by the cold. */
    sugriwa.lower_pointToFront(); // 700
    sugriwa.onHipBack();          // 900
    delay(15853 - 12876 - 700 - 900);

    /*with the dry season*/
    sugriwa.pointToFront();             // 900
    delay(17262 - 15853 - 900 - (500)); // slightly faster to avoid delay -
    sugriwa.downFront();                // 700

    /*we will search for Sita and destroy the enemy.*/
    sugriwa.pointToSelf(); // 900
    sugriwa.pointToBack(); // 1400
    delay(19925 - 17262 - 900 - 1400);
    delay(2000);

    /*return to default position*/
    sugriwa.mathentengA();

    // 025 (Rama1Sugriwa-Rama dialogue 2_E)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::RAMA1SUGRIWA_RAMA_DIALOGUE_2_E);
    // delay(3000);

    // (892) Very well, (1742)
    delay(892);
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (2387) I shall wait for you and your troops (4446)
    delay(2387 - 892 - 1200);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (4700) on the mountain of Malyawan. (6128)
    delay(4700 - 2387 - 700);
    rama_wijaya.pointToFront(); // takes 1200 ms

    delay(6128 - 4700 - 1200);
    rama_wijaya.downFront(); // takes 700 ms

    SoundSystem::playMusicWayang();
    rama_wijaya.defaultStandPosition();
    sugriwa.defaultStandPosition();

    delay(1000);
    rama_wijaya.walk_to_a_certain_distance_before_calibrating_value(200);

    // 026 (Rama Sadboi_E)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::RAMA_SADBOI_E);
    // delay(3000);

    // (1769) Ah, the breeze is blowing from north to the south, (4908)
    delay(1769);
    rama_wijaya.middleFront(); // takes 1200 ms
    for (int i = 0; i < 3; i++)
    {
        rama_wijaya.directControl(1, 45, 400);
        rama_wijaya.directControl(1, 0, 400);
    } // takes 800 ms each loop

    // (5399) taking along the fragrance (6925)
    delay(5399 - 1769 - 1200 - (800 * 3));
    rama_wijaya.downFront();          // takes 700 ms
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (7077) of the lovely kadamba flowers. (9089)
    delay(7077 - 5399 - 700 - 700);
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (9975) Even the passionless in the forests would truly be thrown into confusion. (14309)
    delay(9975 - 7077 - 1200);
    for (int i = 0; i < 6; i++)
    {
        rama_wijaya.directControl(1, 45, 400);
        rama_wijaya.directControl(1, 0, 400);
    } // takes 800 ms each loop

    // (15092) Sad is the heart of the pessimist (17360)
    delay(15092 - 9975 - (800 * 6));
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.middleFront(); // takes 1200 ms

    // (17731) who sees only darkness all around, (20081)

    // (20761) darkness (21287)

    // (21707) what in no way will lift. (23406)
    delay(17731 - 15092 - 700 - 1200);
    for (int i = 0; i < 8; i++)
    {
        rama_wijaya.directControl(1, 45, 400);
        rama_wijaya.directControl(1, 0, 400);
    } // takes 800 ms each loop

    // (24147) It is like the prison (25229)
    delay(24147 - 17731 - (800 * 8));
    rama_wijaya.downFront(); // takes 700 ms

    // (25538) of the god of love. (26637)
    delay(25538 - 24147 - 700);
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (27156) It is tenuous, (28020)
    delay(27156 - 25538 - 1200);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (28495) hard to grasp, (29288)
    delay(28495 - 27156 - 700);
    rama_wijaya.downFront(); // takes 700 ms

    // (29690) but it exists. (30676)
    delay(29690 - 28495 - 700);
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (31506) Besides (32107)
    delay(31506 - 29690 - 1200);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (32439) the lightning is tormenting my dazzled eyes. (35124)
    delay(32439 - 31506 - 700);
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (35769) I am sad (36396)

    // (36825) and startled by its flashes. (38573)
    delay(35769 - 32439 - 1200);
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.pointToSelf(); // takes 900 ms

    // (39506) Just one flash (40389)
    delay(39506 - 35769 - 700 - 900);
    rama_wijaya.downFront(); // takes 700 ms

    // (40570) and quickly it disappears. (42189)
    delay(40570 - 39506 - 700);
    rama_wijaya.middleFront(); // takes 1200 ms

    // (42867) O, it is highly irritating and agonizing. (46267)
    delay(42867 - 40570 - 1200);
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.pointToSelf(); // takes 900 ms

    // (47258) Janaki (47935)

    // (48339) how unhappy you must be. (49884)
    delay(47258 - 42867 - 700 - 900);
    rama_wijaya.downFront();    // takes 700 ms
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (50436) You were never separated from me for long. (52745)
    delay(50436 - 47258 - 700 - 1200);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (53217) Ah! (53537)

    // (53945) How cruel is Fate (55058)
    delay(53217 - 50436 - 700);
    rama_wijaya.downFront();    // takes 700 ms
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (55538) who allows you to be separated violently from me. (58352)
    delay(55538 - 53217 - 700 - 1200);
    for (int i = 0; i < 4; i++)
    {
        rama_wijaya.directControl(1, 45, 400);
        rama_wijaya.directControl(1, 0, 400);
    } // takes 800 ms each loop

    // (59252) My longing is terrible, (60621)

    // (61144) beyond description. (62319)
    delay(59252 - 55538 - (800 * 4));
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.pointToSelf(); // takes 900 ms

    // (62883) My eyes ache severely when I look into the sky (66010)
    delay(62883 - 59252 - 700 - 900);
    for (int i = 0; i < 4; i++)
    {
        rama_wijaya.directControl(1, 52, 400);
        rama_wijaya.directControl(1, 22, 400);
    } // takes 800 ms each loop

    // (66223) or to the woods. (67126)
    delay(66223 - 62883 - (800 * 4));
    rama_wijaya.downFront(); // takes 700 ms

    // (67651) All gives rise to memories. (69594)
    delay(67651 - 66223 - 700);
    rama_wijaya.middleFront(); // takes 1200 ms

    // (70409) I wish (71045)
    delay(70409 - 67651 - 1200);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (71288) that the night would be brief, (72636)
    delay(71288 - 70409 - 700);
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (72975) and it always daytime be. (74274)
    delay(72975 - 71288 - 1200);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (75254) Ah, (75645)
    delay(75254 - 72975 - 700);
    rama_wijaya.downFront(); // takes 700 ms

    // (76143) I am weak (76727)
    delay(76143 - 75254 - 700);
    rama_wijaya.pointToSelf(); // takes 900 ms

    // (77456) and in grief, (78216)
    delay(77456 - 76143 - 900);
    rama_wijaya.downFront(); // takes 700 ms

    // (78528) at night the memory of you is haunting me. (80847)
    delay(78528 - 77456 - 700);
    rama_wijaya.middleFront(); // takes 1200 ms

    // (82046) O, I wake up at night (83626)

    // (84029) seized by the agony of love, (85763)

    // (86311) kept awake I could not fall in slumber, (88826)
    delay(82046 - 78528 - 1200);
    for (int i = 0; i < 9; i++)
    {
        rama_wijaya.directControl(1, 45, 400);
        rama_wijaya.directControl(1, 0, 400);
    } // takes 800 ms each loop

    // (89380) I have lost my taste and feeling (91336)

    // (91647) because of my suffering,
    delay(89380 - 82046 - (800 * 9));
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.pointToSelf(); // takes 900 ms

    // (93430) Ah there is no cure for the pangs of yearning. (96438)
    delay(93430 - 89380 - 700 - 900);
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.middleFront(); // takes 1200 ms

    delay(96438 - 93430 - 700 - 1200);
    rama_wijaya.downFront(); // takes 700 ms

    SoundSystem::playMusicWayang();
    laksmana.walk_to_a_certain_distance_before_calibrating_value(200);

    // 027 (Rama telling laksmana to bacot sugriwa_E)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::RAMA_TELLING_LAKSMANA_BACOT_SUGRIWA_E);
    // delay(3000);

    // (1038) My brother, (1618)
    delay(1038);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (1993) look at the sky! (2992)
    delay(1993 - 1038 - 700);
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (3528) Beautiful swans are flying heading for a lake that they sound so happy. (7233)
    delay(3528 - 1993 - 1200);
    for (int i = 0; i < 5; i++)
    {
        rama_wijaya.directControl(1, 45, 400);
        rama_wijaya.directControl(1, 0, 400);
    } // takes 800 ms each loop

    // (7947) Clearly the dry season has come, (9874)
    delay(7947 - 3528 - (800 * 5));
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.middleFront(); // takes 1200 ms

    // (10448) the time agreed upon. (11703)
    delay(10448 - 7947 - 700 - 1200);
    rama_wijaya.directControl(1, 45, 400); // takes 400 ms
    rama_wijaya.directControl(1, 0, 400);  // takes 400 ms
    rama_wijaya.downFront();               // takes 700 ms

    // (12142) Ah! The king of the apes has lied, (14017)
    delay(12142 - 10448 - 400 - 400 - 700);
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (14577) he has not held to his promise. (16268)
    delay(14577 - 12142 - 1200);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (16826) He dares to make an offence, (18226)
    delay(16826 - 14577 - 700);
    rama_wijaya.directControl(1, 130, 400); // takes 400 ms
    rama_wijaya.directControl(1, 100, 400); // takes 400 ms
    rama_wijaya.directControl(1, 130, 400); // takes 400 ms
    rama_wijaya.directControl(1, 100, 400); // takes 400 ms

    // (18536) that ape is negligent. (19817)
    delay(18536 - 16826 - 400 - 400 - 400 - 400);
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (20383) He does not come, (21384)
    delay(20383 - 18536 - 1200);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (21663) his promise formerly is a gross deception. (23762)
    delay(21663 - 20383 - 700);
    rama_wijaya.downFront();   // takes 700 ms
    rama_wijaya.middleFront(); // takes 1200 ms

    // (24442) He has enjoyed luxury all the time, (26515)
    delay(24442 - 21663 - 700 - 1200);
    for (int i = 0; i < 2; i++)
    {
        rama_wijaya.directControl(1, 45, 500);
        rama_wijaya.directControl(1, 0, 500);
    } // takes 1000 ms each loop

    // (26837) without looking at the sky from time to time (29022)
    delay(26837 - 24442 - (1000 * 2));
    rama_wijaya.downFront();    // takes 700 ms
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (29324) to see whether it has cleared or not. (31262)
    delay(29324 - 26837 - 700 - 1200);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (31908) It is clear now, (32774)

    // (33000) with stars even. (34102)
    delay(31908 - 29324 - 700);
    rama_wijaya.downBack();     // takes 700 ms
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (34519) Ah! He is really blind not to see them. (36798)
    delay(34519 - 31908 - 700 - 1200);
    rama_wijaya.middleBack();   // takes 1200 ms
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (37542) He is preoccupied with the reunion with his wife and children. (40890)
    delay(37542 - 34519 - 1200 - 1200);
    for (int i = 0; i < 4; i++)
    {
        rama_wijaya.directControl(3, 135, 400);
        rama_wijaya.directControl(3, 180, 400);
    } // takes 800 ms each loop
    rama_wijaya.downBack(); // takes 700 ms

    // (41659) That makes him thoughtless. (42831)
    delay(41659 - 37542 - (800 * 4) - 700);
    rama_wijaya.pointToBack(); // takes 1400 ms

    // (43214) My younger brother, (44111)
    delay(43214 - 41659 - 1400);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (44402) go to him quickly. (45395)
    delay(44402 - 43214 - 700);
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (45801) Do not be afraid. (46659)
    delay(45801 - 44402 - 1200);
    rama_wijaya.downFront(); // takes 700 ms

    // (47167) Speak to that stupid ape with harsh words until it hurts, (50215)
    delay(47167 - 45801 - 700);
    rama_wijaya.middleBack(); // takes 1200 ms
    for (int i = 0; i < 2; i++)
    {
        rama_wijaya.directControl(3, 135, 400);
        rama_wijaya.directControl(3, 180, 400);
    } // takes 800 ms each loop

    // (50614) because he has done first by not respecting you, lying to you. (53883)
    delay(50614 - 47167 - (800 * 2) - 1200);
    for (int i = 0; i < 5; i++)
    {
        rama_wijaya.directControl(3, 135, 400);
        rama_wijaya.directControl(3, 180, 400);
    } // takes 800 ms each loop

    // (54729) He does not remember at all where all that luxury came from. (58059)
    delay(54729 - 50614 - (800 * 5));
    for (int i = 0; i < 3; i++)
    {
        rama_wijaya.directControl(3, 135, 400);
        rama_wijaya.directControl(3, 180, 400);
    } // takes 800 ms each loop
    rama_wijaya.downBack(); // takes 700 ms

    // (58406) Ah! He is stupid. (59612)
    delay(58406 - 54729 - (800 * 3) - 700);
    rama_wijaya.pointToBack(); // takes 1400 ms

    // (60029) Therefore go! (60924)
    delay(60029 - 58406 - 1400);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (61173) Tell him that he is sinful. (62555)
    delay(61173 - 60029 - 700);
    rama_wijaya.pointToFront(); // takes 1200 ms

    delay(62555 - 61173 - 1200);
    rama_wijaya.defaultHandPosition();

    SoundSystem::playMusicWayang();
    laksmana.defaultStandPosition();
    rama_wijaya.defaultStandPosition();

    delay(1000);
    sugriwa.walk_to_a_certain_distance_before_calibrating_value(270);
    rama_wijaya.walk_to_a_certain_distance_before_calibrating_value(150);

    // 028 (12 SApol Sugriwa1F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SApol_Sugriwa1F);
    // delay(3000);

    /*I am a negligent slave,*/
    delay(644);
    sugriwa.pointToSelf();    // 900
    sugriwa.lowPointToBack(); // 700
    delay(2891 - 644 - 900 - 700);

    /*indulging in luxury instead of coming to you.*/
    sugriwa.downBack();   // 700
    sugriwa.middleBack(); // 1400
    delay(6527 - 2891 - 700 - 1400 - 700);
    sugriwa.downFront(); // 700

    /*Please*/
    sugriwa.lower_pointToFront(); // 700
    delay(7257 - 6527 - 700);

    /*accept my humble apologies.*/
    sugriwa.downFront();   // 700
    sugriwa.pointToSelf(); // 900
    sugriwa.downBack();    // 700
    delay(9608 - 7257 - 700 - 900 - 700);

    /*it is very bad of me*/
    sugriwa.downFront();          // 700
    sugriwa.lower_pointToFront(); // 700
    delay(11902 - 9608 - 700 - 700);

    /*I was lost in the luxury you gave me, */
    sugriwa.downFront();   // 700
    sugriwa.pointToSelf(); // 900
    delay(14851 - 11902 - 700 - 900);

    /*until I became neglectful of the agreement to come*/
    sugriwa.middleBack(); // 1400
    delay(18351 - 14851 - 1400);

    /*when the dry season has come*/
    sugriwa.lowPointToBack(); // 700
    delay(20813 - 18351 - 700);

    /*because I am too pre-occupied.*/
    sugriwa.downBack();           // 700
    sugriwa.downFront();          // 700
    sugriwa.lower_pointToFront(); // 700
    delay(23797 - 20813 - 700 - 700 - 700);

    /*Now I will order the monkeys to depart.*/
    sugriwa.downFront();   // 700
    sugriwa.pointToSelf(); // 900
    delay(26860 - 23797 - 700 - 900 - 700);
    sugriwa.downFront(); // 700

    /*Do not worry.*/
    sugriwa.lower_pointToFront(); // 700
    delay(28399 - 26860 - 700);

    /*Order the monkeys to search*/
    sugriwa.pointToFront(); // 900
    delay(30253 - 28399 - 900);

    /*all the mountains and forests,*/
    sugriwa.lower_pointToFront(); // 700
    delay(33116 - 30253 - 700 - 700);
    sugriwa.downFront(); // 700

    /* how impassible the forests may be, */
    sugriwa.middleBack(); // 1400
    delay(35907 - 33116 - 1400);

    /*the search will be carried out.*/
    sugriwa.pointToBack(); // 1400
    delay(38705 - 35907 - 1400 - 700);
    sugriwa.downBack(); // 700

    /*Wherever Sita be staying,*/
    sugriwa.middleFront(); // 1200
    delay(40810 - 38705 - 1200);

    /*she will be found*/
    sugriwa.pointToFront(); // 900
    delay(41948 - 40810 - 900);
    delay(2000);
    sugriwa.downFront(); // 700

    // 029 (13 SApol Sugriwa2F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SApol_Sugriwa2F);
    // delay(3000);
    /* Hanuman, */
    sugriwa.pointToBack(); // 1400
    delay(1632 - 1400);

    SoundSystem::pauseMusicWayang();
    hanoman.walk_to_a_certain_distance_before_calibrating_value(135);
    SoundSystem::continuePlaying();

    /*gather all the monkey troops and have them march to Malyawan.*/
    sugriwa.downBack();   // 700
    sugriwa.middleBack(); // 1400
    delay(5239 - 1632 - 700 - 1400);
    delay(1000);

    /*return to default position*/
    sugriwa.mathentengA();

    // 030 (14 SApol Hanuman1F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SApol_Hanuman1F);
    // delay(3000);

    /*At once, my lord. */
    hanoman.pointToSelf();              // 900 (900)
    hanoman.directControl(3, 170, 400); // 1300 (400)
    hanoman.directControl(4, 95, 400);  // 1700 (400)
    delay(2000);

    /*return to default position*/
    hanoman.directControl(4, 80, 400);
    hanoman.directControl(3, 150, 400);
    hanoman.downFront();

    SoundSystem::playMusicWayang();
    hanoman.defaultStandPosition();

    // 031 (15 SApol Sugriwa3F)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::SApol_Sugriwa3F);
    // delay(3000);
    /*O, my lord, */
    delay(594);
    sugriwa.pointToFront(); // 900
    delay(2161 - 544 - 900 - 700);
    sugriwa.downFront();

    /*please accept my humble apologies because I have not been truthful */
    sugriwa.pointToSelf(); // 900
    sugriwa.pointToBack(); // 1400
    delay(7536 - 2161 - 900 - 1400 - (50));

    /*and have lied to you.*/
    sugriwa.downBack();     // 700
    sugriwa.downFront();    // 700
    sugriwa.pointToFront(); // 900
    delay(10006 - 7536 - 700 - 700 - 900);
    sugriwa.downFront(); // 700

    /*I forget about my promise to come,*/
    sugriwa.pointToSelf(); // 900
    sugriwa.pointToBack(); // 1400
    delay(13348 - 10006 - 900 - 1400 - (700));

    /* and kept away,*/
    sugriwa.lowPointToBack(); // 700
    delay(15030 - 13348 - 700 - 700);
    sugriwa.downBack(); // 700

    /* living in luxury, */
    sugriwa.middleBack(); // 1400
    delay(16891 - 15030 - 1400);

    /*as if I have attained it myself.*/
    sugriwa.downBack();    // 700
    sugriwa.downFront();   // 700
    sugriwa.middleFront(); // 1200
    delay(19904 - 16891 - 700 - 700 - 1200);

    /*I have not thought about your mercy towards me.*/
    sugriwa.downFront();   // 700
    sugriwa.pointToSelf(); // 900
    sugriwa.pointToBack(); // 1400
    delay(23747 - 19904 - 700 - 900 - 1400);

    /*I am stupid, */
    sugriwa.lowPointToBack(); // 700
    delay(25658 - 23747 - 700);

    /*I am too slothful.*/
    sugriwa.downBack(); // 700
    delay(27812 - 25658 - 700 - 700);
    sugriwa.downFront(); // 700

    /*I am really foolish not to remember friendship,*/
    sugriwa.lower_pointToFront(); // 700
    delay(31563 - 27812 - 700);

    /*and not to realize that I have been cared for,*/
    sugriwa.pointToFront(); // 900
    delay(35241 - 31563 - 700 - 900);

    /* the more so to return the favor.*/
    sugriwa.lower_pointToFront(); // 700
    delay(38483 - 35241 - 700 - 800);
    sugriwa.downFront(); // 700

    /*Therefore forgive me my lord,*/
    sugriwa.pointToSelf(); // 900
    sugriwa.pointToBack(); // 1400
    delay(40702 - 38483 - 900 - 1400 + (100));

    /*as I am stupid, */
    sugriwa.lowPointToBack(); // 700
    delay(42234 - 40702 - 700);

    /*debased and dumb.*/
    sugriwa.downBack(); // 700
    delay(44624 - 42234 - 700 - 700);
    sugriwa.downFront(); // 700

    /*It is because my lord has reminded me,*/
    sugriwa.pointToFront(); // 900
    delay(47501 - 44624 - 700 - 900);

    /*that you foolish slave has come now.*/
    sugriwa.lower_pointToFront(); // 700
    delay(50135 - 47501 - 700);
    delay(2000);

    /*lower hands (default position would be disrespectful)*/
    sugriwa.downFront();

    // 032 (Rama forgives sugriwa)
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_1, SoundSystem::EPISODE_1_DIALOG::RAMA_FORGIVES_SUGRIWA);
    // delay(3000);

    // (820) I forgive you, (1847)

    delay(820);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (1985) for bringing numerous troops to aid me (4166)

    delay(1985 - 820 - 700);
    rama_wijaya.pointToFront(); // takes 1200 ms

    // (4519) and they all seem very powerful and vigorous. (7174)

    delay(4519 - 1985 - 1200);
    rama_wijaya.directControl(1, 45, 500);
    rama_wijaya.directControl(1, 0, 500);
    rama_wijaya.directControl(1, 45, 500);
    rama_wijaya.directControl(1, 0, 500);
    rama_wijaya.lower_pointToFront(); // takes 700 ms

    // (7550) Surely Rawana will be destroyed. (9353)

    delay(7550 - 4519 - 700 - 500 * 4);
    rama_wijaya.pointToFront(); // takes 1200 ms

    delay(9353 - 7550 - 1200);
    rama_wijaya.downFront(); // takes 700 ms

    SoundSystem::playMusicWayang();
    rama_wijaya.defaultHandPosition();
    sugriwa.defaultHandPosition();

    rama_wijaya.defaultStandPosition();
    sugriwa.defaultStandPosition();

    // setAllMOSFETtoHIGH();
    SoundSystem::playDialogFromACertainFolder(SoundSystem::INDICATOR_SOUND, SoundSystem::INDICATOR_SOUND_NUMBER::INDICATOR_FINISHED_SHOWING);
    delay(2000);
}

void Episodes::Episode_3()
{
    CalibratingFunction::wayangHand();

    setAllMOSFETtoLOW();

    SoundSystem::playMusicWayang();

    delay(1000);
    rahwana.walk_to_a_certain_distance_before_calibrating_value(250); // going to the dialog position
    sita.walk_to_a_certain_distance_before_calibrating_value(150);    // going to the dialog position

    /*001_Sita-Rawana-Hanuman_Rawana1v here*/
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_3, SoundSystem::EPISODE_3_DIALOG::SITA_RAHWANA_HANUMAN_RAHWANA1);

    delay(821);
    // (821) Hey Maithili, (1930)
    rahwana.pointToFront(); // takes 900 ms
    delay(2516 - 821 - 900);

    // (2516) you are very cruel towards me. (4681)
    rahwana.middleFront(); // takes 1200 ms
    delay(5486 - 2516 - 1200);

    // (5486) Let me fall into hell if I lie. (7893)
    rahwana.downFront(); // takes 700 ms
    delay(8862 - 5486 - 700);

    // (8862) You are the only one, my dear, (11206)
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(11644 - 8862 - 700 - (700));
    rahwana.downFront(); // takes 700 ms

    // (11644) who always stays in my mind. (13410)
    rahwana.pointToSelf(); // takes 1100 ms
    delay(14481 - 11644 - 1100 - (700));
    rahwana.downFront(); // takes 700 ms

    // (14481) Janakatmaja, (15583)
    rahwana.middleFront(); // takes 1200 ms
    delay(16317 - 14481 - 1200);

    // (16317) you hurt me more and more. (18162)
    rahwana.directControl(3, 180, 500); // takes 500 ms
    rahwana.directControl(4, 140, 200); // takes 200 ms
    delay(18888 - 16317 - 500 - 200);

    // (18888) You should not be so cruel in all your deeds, my dear. (22342)
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(23382 - 18888 - 700 - (700));
    rahwana.downFront(); // takes 700 ms

    // (23382) Now my longing for you is profound. (25804)
    rahwana.pointToFront(); // takes 900 ms
    delay(26570 - 23382 - 900 - (700));
    rahwana.downFront(); // takes 700 ms

    // (26570) I prefer to die, (28024)
    rahwana.pointToSelf(); // takes 1100 ms
    delay(28485 - 26570 - 1100);

    // (28485) than be tortured like this, (30532)
    rahwana.downFront(); // takes 700 ms
    delay(31376 - 28485 - 700);

    // (31376) because you have no pity for me. (33478)
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(34478 - 31376 - 700);
    rahwana.downFront(); // takes 700 ms

    /*sita silence */
    delay(3000);

    /*002_Sita-Rawana-Hanuman_Rawana2v here*/
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_3, SoundSystem::EPISODE_3_DIALOG::SITA_RAHWANA_HANUMAN_RAHWANA2);

    delay(516);
    // (516) Janakatmaja! (1649)
    rahwana.pointToFront(); // takes 900 ms
    delay(2209 - 516 - 900);

    // (2209) What is the use of remaining silent? (4531)
    rahwana.lower_pointToFront(); // takes 700 ms
    for (int i = 0; i < 2; i++)
    {                                       // takes 800 ms *2
        rahwana.directControl(3, 150, 400); // takes 400 ms
        rahwana.directControl(3, 120, 400); // takes 400 ms
    }
    delay(5153 - 2209 - 700 - (800 * 2));

    // (5153) That is not the way to stop me from asking, (7721)
    rahwana.downFront(); // takes 700 ms
    delay(8282 - 5153 - 700);

    // (8282) because I do not think I am wrong, my dear. (11002)
    rahwana.pointToSelf(); // takes 1100 ms
    delay(11781 - 8282 - 1100);

    // (11781) I am only following the behavior of a raksasa, (14815)
    rahwana.downFront(); // takes 700 ms
    delay(15336 - 11781 - 700);

    // (15336) nothing else. (16295)
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(17411 - 15336 - 700);

    // (17411) I have reserved for you a jeweled pavilion. (20019)
    rahwana.middleFront(); // takes 1200 ms
    delay(20787 - 17411 - 1200);

    // (20787) Let us sleep there and have fun together, my dear. (23658)
    rahwana.directControl(3, 180, 500); // takes 500 ms
    rahwana.directControl(4, 140, 200); // takes 200 ms
    delay(24650 - 20787 - 500 - 200);

    // (24650) Is it not very cold to sleep on the ground? (27321)
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(28256 - 24650 - 700);

    // (28256) You are in my heart, (29478)
    rahwana.pointToFront(); // takes 900
    delay(29826 - 28256 - 900);

    // (29826) you alone, (30634)
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(31088 - 29826 - 700);

    // (31088) so that you will not be far wherever I go. (33634)
    rahwana.middleFront(); // takes 1200 ms
    delay(34323 - 31088 - 1200 - (700));
    rahwana.downFront(); // takes 700 ms

    // (34323) Or let me stay in your heart, (36095)
    rahwana.pointToSelf(); // takes 1100 ms
    delay(36235 - 34323 - 1100 - (700));
    rahwana.downFront(); // takes 700 ms

    // (36235) so that I will not be far from you, my beloved. (39247)
    rahwana.pointToFront(); // takes 900 ms
    delay(40424 - 36235 - 900);

    // (40424) Please, (41075)
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(41731 - 40424 - 700);

    // (41731) listen to my words my dear, (43609)
    rahwana.pointToFront(); // takes 900 ms
    delay(44285 - 41731 - 900);

    // (44249) they are true. (45291)
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(45880 - 44249 - 700);

    // (45880) No one else shall I serve (48241) and love. (48987)
    rahwana.middleFront(); // takes 1200 ms
    delay(48241 - 45880 - 1200);
    rahwana.directControl(3, 180, 500); // takes 500 ms
    rahwana.directControl(4, 140, 200); // takes 200 ms
    delay(49834 - 48241 - 500 - 200);

    // (49834) Besides, (50641)
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(51045 - 49834 - 700);

    // (51045) your life at my side will be a success. (54017)
    rahwana.pointToFront(); // takes 900 ms
    delay(54662 - 51045 - 900);

    // (54662) What is the use grieving over Raghuputra? (57727)
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(58333 - 54662 - 700);

    // (59097) If milk could be obtained from squeezing sand, (62529)
    rahwana.middleFront(); // takes 1200 ms
    delay(63219 - 59097 - 1200);

    // (63219) then you will find happiness with Raghawa. (65630)
    rahwana.directControl(3, 180, 500); // takes 500 ms
    rahwana.directControl(4, 140, 200); // takes 200 ms
    delay(66493 - 63219 - 500 - 200);

    // (66493) Therefore do not deprecate my words, my dear. (69432)
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(70205 - 66493 - 700 - (700));
    rahwana.downFront(); // takes 700 ms

    // (70205) Let me be your protector and lord. (72577)
    rahwana.pointToSelf(); // takes 1100 ms
    delay(73918 - 70205 - 1100 - (700));
    rahwana.downFront(); // takes 700 ms

    // (73918) If I am happy with your service, (75948)
    rahwana.middleFront(); // takes 1200 ms
    delay(76435 - 73918 - 1200);

    // (76435) I will make you the queen of the threefold world. (79749)
    rahwana.directControl(3, 180, 500); // takes 500 ms
    rahwana.directControl(4, 140, 200); // takes 200 ms
    delay(80574 - 76435 - 500 - 200);

    // (80574) What is the use of all this weeping? (83476)
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(83977 - 80574 - 700);

    // (83977) Stop it! (84785)
    rahwana.downFront(); // takes 700 ms
    delay(85615 - 83977 - 700);

    // (85615) I will be the cure, (86983)
    rahwana.pointToSelf(); // takes 1100 ms
    delay(87437 - 85615 - 1100 - (700));
    rahwana.downFront(); // takes 700 ms

    // (87437) I will heal your depressed heart. (89764)
    rahwana.middleFront(); // takes 1200 ms
    delay(90762 - 87437 - 1200);

    // (90762) You may reign over my demon-army. (93538)
    rahwana.directControl(3, 180, 500); // takes 500 ms
    rahwana.directControl(4, 140, 200); // takes 200 ms
    delay(94138 - 90762 - 500 - 200);

    // (94138) All what you wish, (95473)
    rahwana.downFront(); // takes 700 ms
    delay(95719 - 94138 - 700);

    // (95719) I will give to you. (96897)
    rahwana.pointToSelf(); // takes 1100 ms
    delay(97727 - 95719 - 1100 - (700));
    rahwana.downFront(); // takes 700 ms

    // (97727) If you want Indra to wait upon you, (100043)
    rahwana.pointToFront(); // takes 900 ms
    delay(100441 - 97727 - 900);

    // (100441) just say so. (101540)
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(102376 - 100441 - 700);

    // (102376) Do not worry, (103290)
    rahwana.middleFront(); // takes 1200 ms
    delay(103648 - 102376 - 1200);

    // (103648) if that is what you want. (105219)
    rahwana.directControl(3, 180, 500); // takes 500 ms
    rahwana.directControl(4, 140, 200); // takes 200 ms
    delay(105219 - 103648 - 500 - 200);

    delay(2000);
    rahwana.downFront(); // takes 700 ms

    /*003_Sita-Rahwana-Hanuman_Sita1 here*/
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_3, SoundSystem::EPISODE_3_DIALOG::SITA_RAHWANA_HANUMAN_SITA1);

    delay(118);
    // (118) Wicked ten headed and debased Rawana. (2377)
    sita.pointToFront(); // takes 700 ms
    delay(2377 - 118 - 700);

    // (2658) Deceitful mongrel, stupid and filthy imp. (5589)
    sita.lower_pointToFront(); // takes 700 ms
    delay(6183 - 2658 - 700);

    // (6183) If you dare to fight prince Raghuttama, why did you abduct me while he was absent? (10566)
    sita.pointToFront(); // takes 700 ms
    delay(11661 - 6183 - 700 - (700));
    sita.downFront(); // takes 700 ms

    // (11661) If you have courage and are brave in battle, (13833)
    sita.middleFront(); // takes 900 ms
    delay(14205 - 11661 - 900);

    // (14205) what was the reason that you did not look for him in the forest? (17332)
    sita.pointToFront(); // takes 700 ms
    delay(17786 - 14205 - 700);

    // (17786) Is he a hero, who only dares to attack when the enemy is not at home. (22549)
    sita.downFront();   // takes 700 ms
    sita.middleFront(); // takes 900 ms
    delay(23375 - 17786 - 700 - 900);

    // (23375) That man is a coward, (24874)
    sita.pointToFront(); // takes 700 ms
    delay(25196 - 23375 - 700);

    // (25196) and you are that kind of person, a devilish man. (27745)
    sita.lower_pointToFront(); // takes 700 ms
    delay(28345 - 25196 - 700);

    // (28435) That is the evidence that you are a coward in battle. (30975)
    sita.pointToFront(); // takes 700 ms
    delay(31665 - 28435 - 700);

    // (31665) You think only of stealing the wife of another man, nothing else. (35403)
    sita.downFront(); // takes 700 ms
    delay(35919 - 31665 - 700);

    // (35919) What have I learned about a real hero, (37894)
    sita.pointToSelf(); // takes 1400 ms
    delay(38203 - 35919 - 1400);

    // (38203) victorious over his enemies, (39860)
    sita.downFront(); // takes 700 ms
    delay(40454 - 38203 - 700);

    // (40454) is that he gives freedom to his captives. (42751)
    sita.middleFront(); // takes 900 ms
    delay(43383 - 40454 - 900);

    // (43383) What do you learn about prince Raghuttama? (45419)
    sita.pointToFront(); // takes 700 ms
    delay(45911 - 43383 - 700);

    // (45911) Truly he is the Bowman amongst the bowmen of the world. (49071)
    sita.lower_pointToFront(); // takes 700 ms
    delay(49674 - 45911 - 700);

    // (49674) He is the incarnation of Purusottama, a divine man. (52991)
    sita.downFront();   // takes 700 ms
    sita.middleFront(); // takes 900 ms
    delay(53581 - 49674 - 700 - 900);

    // (53581) You will surely be killed in battle by him. (56303)
    sita.pointToFront(); // takes 700 ms
    delay(57030 - 53851 - 700);

    // (57030) Even if you run away (58472)
    sita.lower_pointToFront(); // takes 700 ms
    delay(58678 - 57030 - 700);

    // (58678) and hide yourself in the ocean, (60384)
    sita.pointToFront(); // takes 700 ms
    delay(61107 - 58678 - 700);

    // (61107) or in a hole in the earth, (62305)
    sita.lower_pointToFront(); // takes 700 ms
    delay(63193 - 61107 - 700);

    // (63193) or on an impassible or inaccessible mountain, (66535)
    sita.downFront(); // takes 700 ms
    delay(66865 - 63193 - 700);

    // (66865) or you make yourself so small (68435)
    sita.pointToFront(); // takes 700 ms
    delay(68926 - 66865 - 700);

    // (68926) that you cannot be located with the sense-organs of the body, (72334)
    sita.lower_pointToFront(); // takes 700 ms
    delay(72838 - 68926 - 700);

    // (72838) yet there is no way to escape him in battle. (75155)
    sita.downFront();   // takes 700 ms
    sita.middleFront(); // takes 900 ms
    delay(75717 - 72838 - 700 - 900);

    // (75717) You are too debilitated to fight him in battle. (78055)
    sita.pointToFront(); // takes 700 ms
    delay(78468 - 75717 - 700);

    // (78468) Go (78794)

    // (79009) and make your obeisance (80409)
    sita.downFront();   // takes 700 ms
    sita.middleFront(); // takes 900 ms
    delay(80880 - 78468 - 700 - 900);

    // (80880) to that noble man, Raghawa. (82648)
    sita.pointToFront(); // takes 700 ms
    delay(83424 - 80880 - 700);

    // (83424) He is heroic and without equal in valor. (86390)
    sita.lower_pointToFront(); // takes 700 ms
    delay(87167 - 83424 - 700);

    // (87167) If you do not submit to him, clearly you will be slain. (90083)
    sita.pointToFront(); // takes 700 ms
    delay(90083 - 87167 - 700);
    delay(2000);
    sita.downFront(); // takes 700 ms

    /*004_Sita-Rawana-Hanuman_Rawana3v here*/
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_3, SoundSystem::EPISODE_3_DIALOG::SITA_RAHWANA_HANUMAN_RAHWANA3);
    delay(370);
    // (370) Janakatmaja, (1518)
    rahwana.middleFront(); // takes 1200 ms
    delay(2115 - 370 - 1200);

    // (2115) look carefully at what this is, (4942)
    rahwana.directControl(3, 180, 500); // takes 500 ms
    rahwana.directControl(4, 140, 200); // takes 200 ms
    delay(5867 - 2115 - 500 - 200);

    // (5867) which is like death in my perilous hand. (8820)
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(10157 - 5867 - 700);

    // (10157) If you do not obey the order of Rawana, (13341)
    rahwana.downFront(); // takes 700 ms
    delay(14340 - 10157 - 700);

    // (14340) for sure it will fall upon your neck (17843) savagely. (19018)
    rahwana.pointToFront(); // takes 900 ms
    delay(17843 - 14340 - 900);
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(19018 - 17843 - 700);
    rahwana.downFront(); // takes 700 ms

    // *Leaves from scene*
    SoundSystem::playMusicWayang();
    rahwana.defaultStandPosition();

    /*005_Sita-Rahwana-Hanuman_Sita2*/
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_3, SoundSystem::EPISODE_3_DIALOG::SITA_RAHWANA_HANUMAN_SITA2);

    delay(62);
    // (62) Ah, I am in deep sorrow (1743)
    sita.pointToSelf(); // takes 1400 ms
    delay(1917 - 62 - 1400);

    // (1917) and brimming with confusion. (3565)
    sita.downFront(); // takes 700 ms
    delay(4213 - 1917 - 700);

    // (4213) Everything I see or hear is hurting, (6836)
    sita.pointToFront(); // takes 700 ms
    delay(7567 - 4213 - 700);

    // (7567) even the sound of flutes and string instruments is torture. (11198)
    sita.lower_pointToFront(); // takes 700 ms
    delay(11937 - 7567 - 700);

    // (11937) The grief of separation is severe, (14093)
    sita.downFront(); // takes 700 ms
    delay(14329 - 11937 - 700);

    // (14329) incureable. (15209)
    sita.pointToFront(); // takes 700 ms
    delay(16076 - 14329 - 700);

    // (16076) When will this longing end? (17571)
    sita.downFront(); // takes 700 ms
    delay(17968 - 16076 - 700);

    // (17968) My heart is broken and strays aimlessly. (21099)
    sita.pointToSelf(); // takes 1400 ms
    delay(21756 - 17968 - 1400 - (700));
    sita.downFront(); // takes 700 ms

    // (21756) O wind, (22561)
    sita.pointToFront(); // takes 700 ms
    delay(22858 - 21756 - 700);

    // (22858) have pity and help. (24135)
    sita.lower_pointToFront(); // takes 700 ms
    delay(24672 - 22858 - 700);

    // (24672) Have compassion for me, (26091)
    sita.pointToFront(); // takes 700 ms
    delay(26580 - 24672 - 700);

    // (26580) separated from my beloved, (28071)
    sita.lower_pointToFront(); // takes 700 ms
    delay(28687 - 26580 - 700);

    // (28687) please tell prince Raghuttama in the hermitage, that I am here, (32140)
    sita.pointToFront(); // takes 700 ms
    delay(32528 - 28687 - 700);

    // (32528) kept captive by a demon. (34238)
    sita.downFront(); // takes 700 ms
    delay(34692 - 32528 - 700);

    // (34692) Convey to him my devotion and love, (37022)
    sita.pointToSelf(); // takes 1400 ms
    delay(37505 - 34692 - 1400);

    // (37505) and my incomparable misery of separation. (40149)
    sita.downFront();    // takes 700 ms
    sita.pointToFront(); // takes 700 ms
    delay(40851 - 37505 - 700 - 700);

    // (40851) I am almost dead through being separated from him. (43511)
    sita.lower_pointToFront(); // takes 700 ms
    delay(44036 - 40851 - 700);

    // (44036) Tell that to the prince who is so far away from me. (46853)
    sita.pointToFront(); // takes 700 ms
    delay(46853 - 44036 - 700);
    delay(2000);
    sita.downFront(); // takes 700 ms

    /*006_Sita-Rawana-Hanuman_Hanuman1*/
    SoundSystem::playMusicWayang();
    hanoman.walk_to_a_certain_distance_before_calibrating_value(200);
    // play audio here
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_3, SoundSystem::EPISODE_3_DIALOG::SITA_RAHWANA_HANUMAN_HANUMAN1);

    delay(1198);
    // (1198) Hail to thee, O princess! (3100)
    hanoman.pointToFront(); // takes 900 ms
    delay(3519 - 1198 - 900);

    // (3519) Do not have doubts about me. (5071)
    hanoman.lower_pointToFront(); // takes 700 ms
    delay(5461 - 3519 - 700 - (700));
    hanoman.downFront(); // takes 700 ms

    // (5461) I am the son of the Wind-god Pawanatmaja (8253)
    hanoman.pointToSelf(); // takes 900 ms
    delay(8642 - 5461 - 900 - (700));
    hanoman.downFront(); // takes 700 ms

    // (8642) ordered by the prince Rama (10183)
    hanoman.lower_pointToFront(); // takes 700 ms
    delay(10183 - 8642 - 700);

    // (10323) to become a messenger (11416)
    hanoman.middleFront(); // takes 1200 ms
    delay(11631 - 10183 - 1200);

    // (11631) to find out about you. (12870)
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(13830 - 11631 - 300 - 200);

    // (13830) Prince Rama is now staying at the mountain of Malyawan, (17046)
    hanoman.downFront(); // takes 700 ms
    delay(17465 - 13830 - 700);

    // (17465) north of the mountain Windhya (19151)
    hanoman.pointToFront(); // takes 900 ms
    delay(19430 - 17465 - 900);

    // (19430) and south of the mountain Resyamuka. (21454)
    hanoman.lower_pointToFront(); // takes 700 ms
    delay(22460 - 19430 - 700 - (700));
    hanoman.downFront(); // takes 700 ms

    // (22460) I came at night around seven o’clock and entered this garden. (25967)
    hanoman.pointToSelf(); // takes 900 ms
    delay(26700 - 22460 - 900 - (700));
    hanoman.downFront(); // takes 700 ms

    // (26700) When Dasamukha drew his sword, (28549)
    hanoman.lower_pointToFront(); // takes 700 ms
    delay(29154 - 26700 - 700);

    // (29154) I wanted to fight him in battle, (31126)
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(31923 - 29154 - 300 - 200 - (700));
    hanoman.downFront(); // takes 700 ms

    // (31923) but I reconsidered as to not compromise the order of prince Rama (35807) if I were to be unsuccessful. (38064)
    hanoman.pointToSelf(); // takes 900 ms
    delay(35807 - 31923 - 900);
    hanoman.downFront(); // takes 700 ms
    delay(39443 - 35807 - 700);

    // (39443) That was why I did not appear to fight him. (41757)
    hanoman.middleFront(); // takes 1200 ms
    delay(43130 - 39443 - 1200);

    // (43130) There is a friend of your husband, (44787)
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(45147 - 43130 - 300 - 200);

    // (45147) Sugriwa by name. (46468)
    hanoman.lower_pointToFront(); // takes 700 ms
    delay(47043 - 45147 - 700);

    // (47043) He is the king of the monkeys, (48698)
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(49178 - 47043 - 300 - 200);

    // (49178) and he ordered me to be the messenger. (51196)
    hanoman.lower_pointToFront(); // takes 700 ms
    delay(51783 - 49178 - 700 - (700));
    hanoman.downFront(); // takes 700 ms

    // (51783) I entered the palace in search of you, (54063)
    hanoman.pointToSelf(); // takes 900 ms
    delay(54540 - 51783 - 900 - (700));
    hanoman.downFront(); // takes 700 ms

    // (54540) to make my audience, (55889)
    hanoman.middleFront(); // takes 1200 ms
    delay(56273 - 54540 - 1200);

    // (56273) but you (56849) were not in the city. (58088)
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(56849 - 56273 - 300 - 200);
    hanoman.downFront(); // takes 700 ms
    delay(59204 - 56849 - 700);

    // (59204) King Raghusuta is very depressed (61443) thinking about you. (62653)
    hanoman.pointToFront(); // takes 900 ms
    delay(61443 - 59204 - 900);
    hanoman.lower_pointToFront(); // takes 700 ms
    delay(63258 - 61443 - 700);

    // (63258) Because of that he is very thin and ordered me (66125)
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    hanoman.downFront();   // takes 700 ms
    hanoman.pointToSelf(); // takes 900 ms
    delay(66485 - 63258 - 300 - 200 - 700 - 900);

    // (66485) to go as a messenger instead. (68166)
    hanoman.downFront(); // takes 700 ms
    delay(69475 - 66485 - 700);

    // (69475) He gave me his ring (70772) as a verification of my mission. (73290)
    hanoman.middleFront(); // takes 1200
    delay(73290 - 69475 - 1200);

    // pause audio here to show the ring closer
    // SoundSystem::pause();
    // // hanoman.walk_to_a_certain_distance_before_calibrating_value(160);
    // // delay(1000);
    // // hanoman.walk_to_a_certain_distance_before_calibrating_value(140);

    // // continue audio here
    // SoundSystem::continuePlaying();
    delay(74180 - 73290);

    // (74180) You should also know that your younger brother, (76570)
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(76936 - 74180 - 300 - 200);

    // (76936) Laksmana, (77691)
    hanoman.lower_pointToFront(); // takes 700 ms
    delay(78012 - 76936 - 700);

    // (78012) is exceedingly upset (79571)
    hanoman.middleFront(); // takes 1200 ms
    delay(80054 - 78012 - 1200);

    // (80054) and that he wants to come here as soon as possible (82694)
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(82985 - 80054 - 300 - 200);

    // (82985) to kill the wicked Rawana. (84997)
    hanoman.downFront();          // takes 700 ms
    hanoman.lower_pointToFront(); // takes 700 ms
    delay(85887 - 82985 - 700 - 700);

    // (85887) Do not be impatient (87021) and look after your life, (88597)
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(87021 - 85887 - 300 - 200);
    hanoman.lower_pointToFront(); // takes 700 ms
    delay(89260 - 87021 - 700 - (700));
    hanoman.downFront(); // takes 700 ms

    // (89260) as we have the monkey troops assembled (91272) and ready to attack the enemy. (93343)
    hanoman.pointToSelf(); // takes 900 ms
    delay(91272 - 89260 - 900);
    hanoman.downFront();          // takes 700 ms
    hanoman.lower_pointToFront(); // takes 700 ms
    delay(94349 - 91272 - 700 - 700);

    // (94349) With certainty, (95262)
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(95628 - 94349 - 300 - 200);

    // (95628) Rawana will be killed (96838) by king Rama (98292) in battle. (99187)
    hanoman.lower_pointToFront(); // takes 700 ms
    delay(96838 - 95628 - 700);
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(98292 - 96838 - 300 - 200);
    hanoman.downFront(); // takes 700 ms
    delay(100106 - 98292 - 700);

    // (100106) He must pay with his life (101775) for his sins of kidnapping my lady. (104620)
    hanoman.middleFront(); // takes 1200 ms
    delay(101775 - 100106 - 1200);
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(105463 - 101775 - 300 - 200);

    // (105463) Please, (106000)
    hanoman.lower_pointToFront(); // takes 700 ms
    delay(106480 - 105463 - 700);

    // (106480) give me your message to Raghusuta, (108260)
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(108673 - 106480 - 300 - 200);

    // (108673) while the guards are away. (109987)
    hanoman.downFront();
    delay(109987 - 108673 - 700);
    delay(2000);

    /*007_Sita-Rahwana-Hanuman_Sita3*/
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_3, SoundSystem::EPISODE_3_DIALOG::SITA_RAHWANA_HANUMAN_SITA3);

    delay(194);
    // (194) Hey Pawanatmaja, step forward! (2280)
    sita.pointToFront(); // takes 700 ms
    delay(2772 - 194 - 700);

    // (2772) I am happy that you were ordered to come here. (4870)
    sita.pointToSelf(); // takes 1400 ms
    delay(5514 - 2772 - 1400);

    // (5514) Please (5870)

    // (6336) give my crest jewel to Rama. (8026)
    sita.downFront();    // takes 700 ms
    sita.pointToFront(); // takes 700 ms
    delay(8331 - 5514 - 700 - 700);

    // (8331) Also, (8815)
    sita.lower_pointToFront(); // takes 700 ms
    delay(9302 - 8331 - 700);

    // (9302) take with you my letter as a proof of my sorrow (12305)
    sita.pointToSelf(); // takes 1400 ms
    delay(12714 - 9302 - 1400);

    // (12714) and longing. (13420)
    sita.downFront(); // takes 700 ms
    delay(13957 - 12714 - 700);

    // (13957) Give it to Rama and tell him this. (15878)
    sita.pointToFront(); // takes 700 ms
    delay(16737 - 13957 - 700);

    // (16737) He should eat, (17443)
    sita.lower_pointToFront(); // takes 700 ms
    delay(17724 - 16737 - 700);

    // (17724) sleep and not worry. (19145)
    sita.downFront();   // takes 700 ms
    sita.middleFront(); // takes 900 ms
    delay(19624 - 17724 - 700 - 900);

    // (19624) I am no longer grieving and miserable, (21917)
    sita.pointToSelf(); // takes 1400 ms
    delay(22429 - 19624 - 1400);

    // (22429) as I now know his plans. (24725)
    sita.downFront();    // takes 700 ms
    sita.pointToFront(); // takes 700 ms
    delay(24725 - 22429 - 700 - 700);
    delay(2000);
    sita.downFront(); // takes 700 ms

    /*008_Sita-Rawana-Hanuman_Hanuman2*/
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_3, SoundSystem::EPISODE_3_DIALOG::SITA_RAHWANA_HANUMAN_HANUMAN2);

    delay(508);
    // (508) But of course, (1412)
    hanoman.lower_pointToFront(); // takes 700 ms
    delay(1824 - 508 - 700);

    // (1824) In the meantime (2593) I shall get some battle scars as evidence of my deed (6051) by destroying this garden (7708) and the demons. (8937)
    hanoman.downFront();   // takes 700 ms
    hanoman.pointToSelf(); // takes 900 ms
    delay(6051 - 1824 - 700 - 900);
    hanoman.downFront(); // takes 700 ms
    delay(7708 - 6051 - 700);
    hanoman.pointToFront(); // takes 900 ms
    delay(8937 - 7708 - 900);
    delay(2000);
    hanoman.downFront(); // takes 700 ms
    hanoman.downBack();  // takes 700 ms

    // *Sita leaves from scene*
    SoundSystem::playMusicWayang();
    sita.defaultStandPosition();

    /*008p5_Sita-Rawana-Hanuman_Hanuman3*/
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_3, SoundSystem::EPISODE_3_DIALOG::SITA_RAHWANA_HANUMAN_HANUMAN3);

    delay(481);
    // (481) *roar* (1892) fight me ye demons!! (4209)
    hanoman.middleFront(); // takes 1200 ms
    delay(1892 - 481 - 1200);
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(4209 - 1892 - 300 - 200);

    SoundSystem::playMusicWayang();
    hanoman.mathenthengC();
    hanoman.defaultStandPosition();
    hanoman.defaultHandPosition();
    delay(1000);

    /*009_Hanuman-Rawana-Wibhisana_HanumanEnter*/ // Gak usah dimainin (konteksny beda karna hanuman 'obedient')
    hanoman.walk_to_a_certain_distance_before_calibrating_value(140);
    // (555) Agh! (933)
    rahwana.walk_to_a_certain_distance_before_calibrating_value(350);

    /*010_Hanuman-Rawana-Wibhisana_Rawana1v*/
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_3, SoundSystem::EPISODE_3_DIALOG::HANUMAN_RAHWANA_WIBHISANA_RAHWANA1);
    // Rawana distance is further than Hanoman (in front of Hanoman)

    delay(188);
    // (688) So, (1302)
    rahwana.middleFront(); // takes 1200 ms
    delay(2030 - 188 - 1200);

    // (2030) you are the one who smashed and destroyed all the trees in the garden. (6028)
    rahwana.lower_pointToFront(); // takes 700 ms
    for (int i = 0; i < 4; i++)
    {                                       // 800*4 = 3200
        rahwana.directControl(3, 150, 400); // takes 400 ms
        rahwana.directControl(3, 120, 400); // takes 400 ms
    }
    delay(7029 - 2030 - 700 - 3200 - (700));
    rahwana.directControl(3, 180, 500); // takes 500 ms
    rahwana.directControl(4, 140, 200); // takes 200 ms

    // (7209) *angry* You (7582) deceitful monkey of evil conduct! (10415)
    for (int i = 0; i < ((10415 - 7209) / 400); i++)
    {                                       // maximum loops
        rahwana.directControl(3, 150, 200); // takes 200 ms
        rahwana.directControl(3, 180, 200); // takes 200 ms
    }
    delay((10415 - 7209) % 400);

    // (10811) Guards, (11373) Kill him! (11986)
    rahwana.downFront(); // takes 700 - (10811-10415) ms
    rahwana.directControl(4, 60, 200);
    rahwana.directControl(3, 180, 500);
    delay(11986 - 10811 - (700 - (10811 - 10415)) - 200 - 500);
    delay(2000);
    rahwana.downFront(); // takes 700 ms

    SoundSystem::playMusicWayang();
    hanoman.defaultStandPosition();
    rahwana.walk_to_a_certain_distance_before_calibrating_value(200);
    wibhisana.walk_to_a_certain_distance_before_calibrating_value(250);

    /*011_Hanuman-Rawana-Wibhisana_Wibhisana1*/
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_3, SoundSystem::EPISODE_3_DIALOG::HANUMAN_RAHWANA_WIBHISANA_WIBHISANA1);

    // *enters* (hanuman moves to just barely in the frame, since the main focus is on Wibhisana and Rawana)
    // *adjust positions*

    delay(87);
    // (87) O king of the world, (1225)
    wibhisana.middleFront(); // takes 1200 ms
    delay(1557 - 87 - 1200);

    // (1557) Dasawadana! (2506)
    wibhisana.pointToFront(); // takes 900 ms
    delay(2739 - 1557 - 900);

    // (2739) Follow the teachings of the holy scriptures. (4869)
    wibhisana.lower_pointToFront(); // takes 700 ms
    delay(5336 - 2739 - 700);

    // (5336) A messenger may not be sentenced to death, (7861)
    wibhisana.pointToFront(); // takes 900 ms
    delay(8541 - 5336 - 900);

    // (8541) even if he is extremely wicked. (10537)
    wibhisana.lower_pointToFront(); // takes 700 ms
    delay(10537 - 8541 - 700);
    delay(2000);
    wibhisana.downFront(); // takes 700 ms
    wibhisana.defaultStandPosition();

    /*012_Hanuman-Rawana-Wibhisana_Rawana2v*/
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_3, SoundSystem::EPISODE_3_DIALOG::HANUMAN_RAHWANA_WIBHISANA_RAHWANA2);

    delay(1667);
    // (1667) *angrier* Why should he escape punishment? (3459)
    rahwana.middleFront(); // takes 1200 ms
    delay(3843 - 1667 - 1200);

    // (3843) Certainly, he should be brought to death, (5916)
    rahwana.directControl(3, 180, 500);
    rahwana.directControl(4, 140, 200);
    delay(6319 - 3843 - 500 - 200);

    // (6319) because he is too wicked. (7849)
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(8504 - 6319 - 700);

    // (8504) He has destroyed my plants, (10213) killed my subjects (11768) and insulted me in doing so. (13925)
    rahwana.directControl(3, 180, 500);
    rahwana.directControl(4, 140, 200);
    delay(10213 - 8504 - 500 - 200);
    rahwana.downFront(); // takes 700 ms
    delay(11768 - 10213 - 700);
    rahwana.pointToSelf(); // takes 1100 ms
    delay(13925 - 11768 - 1100);
    rahwana.downFront(); // takes 700 ms
    delay(14776 - 13925 - 700);

    // (14776) Therefore he must die, (16423)
    rahwana.pointToFront(); // takes 900 ms
    delay(16423 - 14776 - 900 - (700));
    rahwana.downFront(); // takes 700 ms

    // (16782) like anyone who insults me. (18685)
    rahwana.pointToSelf();      // takes 1100 ms
    for (int i = 0; i < 2; i++) // takes 400*2 = 800 ms
    {
        rahwana.directControl(4, 70, 200);
        rahwana.directControl(4, 80, 200);
    }
    delay(19594 - 16782 - 1100 - 800);

    // (19594) What do you want with that monkey. (21495)
    rahwana.downFront();          // takes 700 ms
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(21930 - 19594 - 700 - 700);

    // (21930) Why do you wish to keep him alive. (23811)
    rahwana.directControl(3, 180, 500);
    rahwana.directControl(4, 140, 200);
    delay(24253 - 21930 - 500 - 200);

    // (24253) He is only a sinful animal, (26518)
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(26294 - 24253 - 700);

    // (26294) who dares to make trouble here. (29417)
    rahwana.downFront(); // takes 700 ms
    rahwana.directControl(4, 60, 200);
    rahwana.directControl(3, 180, 500);
    delay(29417 - 26294 - 700 - 200 - 500);
    delay(2000);
    rahwana.downFront(); // takes 700 ms

    SoundSystem::playMusicWayang();
    hanoman.walk_to_a_certain_distance_before_calibrating_value(140);
    rahwana.walk_to_a_certain_distance_before_calibrating_value(350);

    /*013_Hanuman-Rawana-Wibhisana_Hanuman1*/
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_3, SoundSystem::EPISODE_3_DIALOG::HANUMAN_RAHWANA_WIBHISANA_HANUMAN1);

    delay(336);
    // (336) O king of the demons, (2112)
    hanoman.middleFront(); // takes 1200 ms
    delay(2426 - 336 - 1200);

    // (2426) useless is your anger. (4072)
    hanoman.pointToFront(); // takes 900 ms
    delay(4451 - 2426 - 900);

    // (4451) There is nothing true applicable to a monkey. (7049)
    hanoman.lower_pointToFront(); // takes 700 ms
    delay(7520 - 4451 - 700 - (700));
    hanoman.downFront(); // takes 700 ms

    // (7520) I am alone, (8387)
    hanoman.pointToSelf(); // takes 900 ms
    hanoman.downFront();   // takes 700 ms

    // (8706) I am a messenger, (9713)
    hanoman.lower_pointToFront(); // takes 700 ms
    delay(10027 - 7520 - 900 - 700 - 700);

    // (10027) in the grip of a snake. (11365)
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(11987 - 10027 - 300 - 200);

    // (11987) You should not kill a monkey. (13352)
    hanoman.downFront(); // takes 700 ms
    delay(14018 - 11987 - 700);

    // (14018) The nature of an excellent man, (15766) victorious in battle (17423) is averse to harm his good name. (19719)
    hanoman.pointToFront(); // takes 900 ms
    delay(15766 - 14018 - 900);
    hanoman.lower_pointToFront(); // takes 700 ms
    delay(17423 - 15766 - 700);
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(20369 - 17423 - 300 - 200);

    // (20369) He should not be angry with a lower class of creature. (23514)
    hanoman.downFront(); // takes 700 ms
    delay(24039 - 20369 - 700);

    // (24039) All the conduct of an animal (25702) does not concern him. (27293)
    hanoman.middleFront(); // takes 1200 ms
    delay(28068 - 24039 - 1200);

    // (28068) On the other hand, (28945) Raghawa is good. (30298)
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(28945 - 28068 - 300 - 200);
    hanoman.lower_pointToFront(); // takes 700 ms
    delay(31018 - 28945 - 700);

    // (31018) He is excellent as he protects the people all the time. (34521)
    hanoman.pointToFront(); // takes 900 ms
    delay(35058 - 31018 - 900);

    // (35058) He is not cruel to his enemies and does not hate them. (37932)
    hanoman.lower_pointToFront(); // takes 700 ms
    delay(38528 - 35058 - 700);

    // (38528) But you are wicked and very brutal. (40948)
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(41630 - 38528 - 300 - 200);

    // (41630) Raghawa and Sugriwa. (43287)
    hanoman.downFront(); // takes 700 ms
    delay(43894 - 41630 - 700);

    // (43894) You should make friends with them both. (45502)
    hanoman.pointToFront(); // takes 900 ms
    delay(46000 - 43894 - 900);

    // (46000) Clearly the world would be happy with that (48463) and your fortune would increase. (50569)
    hanoman.downBack(); // takes 700 ms
    delay(48463 - 46000 - 700);
    hanoman.pointToFront(); // 900
    delay(51143 - 48463 - 900);

    // (51143) Do not doubt. Be peaceful of mind! (53293)
    hanoman.downFront(); // takes 700 ms
    delay(54219 - 51143 - 700);

    // (54219) It is best that Raghawa be king, (56254)
    hanoman.pointToFront(); // takes 900 ms
    delay(56688 - 54219 - 900);

    // (56688) he is unequalled and victorious in the world. (59530)
    hanoman.lower_pointToFront(); // takes 700 ms
    delay(60072 - 56688 - 700);

    // (60072) His arrow, (60813) only one, (61902) is equal to Death, (63244)
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(60813 - 60072 - 300 - 200);
    hanoman.lower_pointToFront(); // takes 700 ms
    delay(61902 - 60813 - 700);
    hanoman.downFront(); // takes 700 ms
    delay(63780 - 61902 - 700);

    // (63780) bringing destruction to numerous opponents. (66569)
    hanoman.pointToFront(); // takes 900 ms
    delay(67392 - 63780 - 900);

    // (67392) Tataka, (68233) Bali, (68967) Yojanabahu, (70039) Dusana, (70868) Marica, (71674) and Wiradha (72714)
    hanoman.directControl(3, 160, 300);
    delay(68233 - 67392 - 300);
    hanoman.directControl(3, 140, 300);
    delay(68967 - 68233 - 300);
    hanoman.directControl(3, 120, 300);
    delay(70039 - 68967 - 300);
    hanoman.directControl(3, 100, 300);
    delay(70868 - 70039 - 300);
    hanoman.directControl(3, 80, 300);
    delay(71674 - 70868 - 300);
    hanoman.directControl(3, 60, 300);
    delay(73093 - 71674 - 300);

    // (73093) were killed by Raghuputra, (74598)
    hanoman.downFront(); // takes 700 ms
    delay(74792 - 73093 - 700);

    // (74792) though all of them were powerful. (76699)
    hanoman.middleFront(); // takes 1200 ms
    delay(77614 - 74792 - 1200);

    // (77614) This should not become the reason for your wrath. (79776)
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(80473 - 77614 - 300 - 200);

    // (80473) Even if many of your demon subjects were killed, (83131)
    hanoman.lower_pointToFront(); // takes 700 ms
    delay(83570 - 80473 - 700);

    // (83570) it is because your subjects were the evil ones who wanted to kill Rama. (87674)
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(88616 - 83570 - 300 - 200 - (700));
    hanoman.downFront();

    // (88616) It was very good of Raghuputra to kill the wicked demons. (92142)
    hanoman.middleFront(); // takes 1200 ms
    delay(92698 - 88616 - 1200);

    // (92698) He thus protected the lives of the exalted persons, (96255)
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(96727 - 92698 - 300 - 200);

    // (96727) and that is the aim of one who wants to establish the supreme dharmma. (101799)
    hanoman.lower_pointToFront(); // takes 700 ms
    delay(101799 - 96727 - 700);
    delay(2000);
    hanoman.downFront(); // takes 700 ms

    /*014_Hanuman-Rawana-Wibhisana_Rawana3v*/
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_3, SoundSystem::EPISODE_3_DIALOG::HANUMAN_RAHWANA_WIBHISANA_RAHWANA3);

    // *angrier*
    delay(142);
    // (442) Ah, (801)
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(1152 - 142 - 700);

    // (1152) debased and deceitful monkey. (3410)
    rahwana.directControl(3, 180, 500);
    rahwana.directControl(4, 140, 200);
    for (int i = 0; i < 3; i++) // takes 400*3 = 1200 ms
    {
        rahwana.directControl(3, 150, 200);
        rahwana.directControl(3, 180, 200);
    }
    delay(3883 - 1152 - 500 - 200 - 1200);

    // (3883) Foolish and stupid (5462) and not a real messenger. (7247)
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(5462 - 3883 - 700);
    rahwana.downFront(); // takes 700 ms
    delay(7804 - 5462 - 700);

    // (7804) A real messenger says nothing, (9917)
    rahwana.pointToFront(); // takes 900 ms
    delay(10428 - 7804 - 900);

    // (10428) does nothing. (11450)
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(12144 - 10428 - 700);

    // (12144) All that he does is just to be a messenger. (14639)
    rahwana.directControl(3, 180, 500);
    rahwana.directControl(4, 140, 200);
    for (int i = 0; i < 4; i++) // takes 400*4 = 1600 ms
    {
        rahwana.directControl(3, 150, 200);
        rahwana.directControl(3, 180, 200);
    }
    rahwana.downFront(); // takes 700 ms
    delay(15295 - 12144 - 500 - 200 - 1600 - 700);

    // (15295) You praised the power of Rama. (17113)
    rahwana.pointToFront(); // takes 900 ms
    delay(17606 - 15295 - 900);

    // (17606) Empty praises. (18758)
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(19193 - 17606 - 700);

    // (19193) You do not know what (20535) and who you are praising, (22175)
    rahwana.directControl(3, 180, 500);
    rahwana.directControl(4, 140, 200);
    delay(20535 - 19193 - 500 - 200);
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(23015 - 20535 - 700);

    // (23015) Rama is unequaled in sinfulness, (25631)
    rahwana.directControl(3, 180, 500);
    rahwana.directControl(4, 140, 200);
    delay(25974 - 23015 - 500 - 200);

    // (25974) because he has killed people (27820) that should not have been killed. (29537)
    rahwana.downFront(); // takes 700 ms
    delay(27820 - 25974 - 700);
    rahwana.pointToFront(); // takes 900 ms
    delay(30269 - 27820 - 900);

    // (30269) You knew Yojanabahu, didn’t you? (32153)
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(32611 - 30269 - 700);

    // (32611) He had an accident, (33816)
    rahwana.directControl(3, 180, 500);
    rahwana.directControl(4, 140, 200);
    delay(34091 - 32611 - 500 - 200);

    // (34091) he was a cripple (35311) and yet he was killed by Raghuputra. (37714)
    rahwana.downFront(); // takes 700 ms
    delay(35311 - 34091 - 700);
    rahwana.directControl(4, 60, 200);
    rahwana.directControl(3, 180, 500);
    delay(38263 - 35311 - 200 - 500 - (700 + 700));
    rahwana.downFront(); // takes 700 ms

    // (38263) Damn you! (39049) Cruel bastard! (40773)
    rahwana.middleFront(); // takes 1200 ms - 700 ms
    delay(39049 - 38263 - (1200 - 700));
    rahwana.directControl(3, 180, 500);
    rahwana.directControl(4, 140, 200);
    for (int i = 0; i < 2; i++) // takes 400 *2 = 800 ms
    {
        rahwana.directControl(3, 150, 200);
        rahwana.directControl(3, 180, 200);
    }
    delay(41689 - 39049 - 500 - 200 - 800);

    // (41689) Tataka should not have been killed. (43496)
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(44114 - 41689 - 700);

    // (44114) She is a woman, (45304) without a protector. (46739)
    rahwana.directControl(3, 180, 500);
    rahwana.directControl(4, 140, 200);
    delay(45304 - 44114 - 500 - 200);
    rahwana.middleFront(); // takes 1200 ms
    delay(47181 - 45304 - 1200);

    // (47181) She too was killed by Rama. (49233)
    rahwana.directControl(3, 180, 500);
    rahwana.directControl(4, 140, 200);
    delay(49759 - 47181 - 500 - 200);

    // (49759) Ah! (50568) Devilish, (51613) heartless and shameful. (53390)
    rahwana.downFront(); // takes 700 ms
    delay(50568 - 49759 - 700);
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(51613 - 50568 - 700);
    rahwana.directControl(3, 180, 500);
    rahwana.directControl(4, 140, 200);
    delay(54374 - 51613 - 500 - 200);

    // (54374) That is not the goal of the people with pride. (56884)
    rahwana.downFront(); // takes 700 ms
    delay(57403 - 54374 - 700);

    // (57403) It is accomplishment and merit, (59646)
    rahwana.middleFront(); // takes 1200 ms
    delay(60103 - 57403 - 1200);

    // (60103) that are strived for, (61576)
    rahwana.directControl(3, 180, 500);
    rahwana.directControl(4, 140, 200);
    delay(61987 - 60103 - 500 - 200 - (700));
    rahwana.downFront(); // takes 700 ms

    // (61987) nothing else. (63076)
    rahwana.directControl(4, 60, 200);
    rahwana.directControl(3, 180, 500);
    delay(64810 - 61987 - 200 - 500);

    // (64810) Rama and Sugriwa should be befriended. (67121)
    rahwana.downFront();   // takes 700 ms
    rahwana.middleFront(); // takes 1200 ms
    delay(67747 - 64810 - 700 - 1200);

    // (67747) That is your foolish and stupid advice. (70485)
    rahwana.directControl(3, 180, 500);
    rahwana.directControl(4, 140, 200);
    for (int i = 0; i < 5; i++) // takes 400 *5 = 2000 ms
    {
        rahwana.directControl(3, 150, 200);
        rahwana.directControl(3, 180, 200);
    }
    delay(71202 - 67747 - 500 - 200 - 2000);

    // (71202) Is it proper that a demon be friends with a human being (75299) and a monkey. (76239)
    rahwana.middleFront(); // takes 1200 ms
    delay(75299 - 71202 - 1200);
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(77130 - 75299 - 700);

    // (77130) Their nature (78175) and their conduct (79319) are incompatible. (80936)
    rahwana.directControl(3, 180, 500);
    rahwana.directControl(4, 140, 200);
    delay(78175 - 77130 - 500 - 200);
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(79319 - 78175 - 700);
    rahwana.downFront(); // takes 700 ms
    delay(82157 - 79319 - 700);

    // (82157) The hero Wiradha was killed by him. (84270)
    rahwana.pointToFront(); // takes 900 ms
    delay(84811 - 82157 - 900);

    // (84811) He should not have been killed because he was alone. (87474)
    rahwana.downFront(); // takes 700 ms
    delay(88046 - 84811 - 700);

    // (88046) Raghawa is extremely deceitful and shameless, (91913)
    rahwana.pointToFront();     // takes 900 ms
    for (int i = 0; i < 7; i++) // takes 400 *7 = 2800 ms
    {
        rahwana.directControl(3, 150, 200);
        rahwana.directControl(3, 180, 200);
    }
    delay(92623 - 88046 - 900 - 2800);

    // (92623) as was his accomplice, Laksmana. (94926)
    rahwana.downFront(); // takes 700 ms
    rahwana.directControl(4, 60, 200);
    rahwana.directControl(3, 180, 500);
    delay(95865 - 92623 - 700 - 200 - 500);

    // (95865) Also the debased Marica, (97642) you should not praise his slayer. (99648)
    rahwana.downFront();          // takes 700 ms
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(97642 - 95865 - 700 - 700);
    rahwana.directControl(3, 180, 500);
    rahwana.directControl(4, 140, 200);
    delay(100075 - 97642 - 500 - 200);

    // (100075) It was obvious that he was afraid of enemies, (103647)
    rahwana.downFront(); // takes 700 ms
    delay(104210 - 100075 - 700);

    // (104210) like a deer when it sees a tiger, (106163)
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(106793 - 104210 - 700);

    // (106793) but he did his deed anyways out of (109626) respect for me. (110870)
    rahwana.directControl(3, 180, 500);
    rahwana.directControl(4, 140, 200);
    for (int i = 0; i < 3; i++) // takes 400 *3 = 1200 ms
    {
        rahwana.directControl(3, 150, 200);
        rahwana.directControl(3, 180, 200);
    }
    delay(109626 - 106793 - 500 - 200 - 1200 - (700 + 200));
    rahwana.downFront();   // takes 700 ms
    rahwana.pointToSelf(); // takes 1100 ms - 200 ms
    delay(111930 - 109626 - (1100 - 200));

    // (111930) You said that Bali the monkey was powerful. (114630)
    rahwana.downFront();          // takes 700 ms
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(115195 - 111930 - 700 - 700);

    // (115195) How is it that he was pierced with an arrow? (118040)
    rahwana.directControl(3, 180, 500);
    rahwana.directControl(4, 140, 200);
    delay(118704 - 115195 - 500 - 200);

    // (118704) If he was truly mighty (120550) that arrow would have been broken. (123265)
    rahwana.downFront(); // takes 700 ms
    delay(120550 - 118704 - 700);
    rahwana.middleFront(); // takes 1200 ms
    delay(123983 - 120550 - 1200);

    // (123983) That is why Bali (125272) was in fact powerless. (127293)
    rahwana.directControl(3, 180, 500);
    rahwana.directControl(4, 140, 200);
    delay(125272 - 123983 - 500 - 200);
    rahwana.downFront(); // takes 700 ms
    delay(128155 - 125272 - 700);

    // (128155) On the other hand (129345) Rama was sinful and (131168) evil in killing the mighty Bali (133953) because he shot him (135341) while he was fighting with his brother. (137561)
    rahwana.pointToFront(); // takes 900 ms
    delay(129345 - 128155 - 900);
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(131168 - 129345 - 700);
    rahwana.directControl(3, 180, 500);
    rahwana.directControl(4, 140, 200);
    delay(133953 - 131168 - 500 - 200);
    rahwana.downFront(); // takes 700 ms
    delay(135341 - 133953 - 700);
    rahwana.pointToFront(); // takes 900 ms
    delay(137958 - 135341 - 900);

    // (137958) Hah!
    rahwana.directControl(3, 130, 500);
    delay(138926 - 137958 - 500);

    // (138926) Hah!
    rahwana.directControl(3, 80, 500);
    delay(140238 - 138926 - 500);

    // (140238) Hah!
    rahwana.downFront(); // takes 700 ms
    delay(141352 - 140238 - 700);

    // (141352) O! How debased is Rama! (144190)
    rahwana.middleFront(); // takes 1200 ms
    delay(144190 - 141352 - 1200);
    delay(2000);
    rahwana.downFront(); // takes 700 ms

    /*015_Hanuman-Rawana-Wibhisana_Hanuman2*/
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_3, SoundSystem::EPISODE_3_DIALOG::HANUMAN_RAHWANA_WIBHISANA_HANUMAN2);

    delay(579);
    // (579) Why do you blame me for ransacking the trees in the pleasure garden. (4081)
    hanoman.pointToSelf(); // takes 900 ms
    delay(4579 - 579 - 900 - (700));
    hanoman.downFront(); // takes 700 ms

    // (4579) A messenger should look for a trick. (6107)
    hanoman.middleFront(); // takes 1200 ms
    delay(6523 - 4579 - 1200);

    // (6523) He should plan a strategy. (7918)
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(8623 - 6523 - 300 - 200 - (700));
    hanoman.downFront(); // takes 700 ms

    // (8623) I am appointed to be a messenger, (10604) to search for the whereabouts of Sita. (12601)
    hanoman.pointToSelf(); // takes 900 ms
    delay(10604 - 8623 - 900);
    hanoman.downFront(); // takes 700 ms
    delay(13254 - 10604 - 700);

    // (13254) On this matter I did not want to guess. (15487)
    hanoman.pointToSelf(); // takes 900 ms
    delay(15910 - 13254 - 900 - (700));
    hanoman.downFront(); // takes 700 ms

    // (15910) I wanted to know the matter exactly. (17899)
    hanoman.lower_pointToFront(); // takes 700 ms
    delay(18589 - 15910 - 700 - (700));
    hanoman.downFront(); // takes 700 ms

    // (18589) That was my purpose in destroying the trees in the pleasure garden. (22226)
    hanoman.pointToSelf(); // takes 900 ms
    delay(22701 - 18589 - 900 - (700));
    hanoman.downFront(); // takes 700 ms

    // (22701) Do not be angry, (23769) do not be furious. (25179)
    hanoman.lower_pointToFront(); // takes 700 ms
    delay(23769 - 22701 - 700);
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(25572 - 23769 - 300 - 200 - (700));
    hanoman.downFront(); // takes 700 ms

    // (25572) What is the use of being angry? (27027)
    hanoman.middleFront(); // takes 1200 ms
    delay(27658 - 25572 - 1200);

    // (27658) You have said before, (28815)
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(29313 - 27658 - 300 - 200);

    // (29313) only ‘merit’ should be the purpose of battle. (31650)
    hanoman.lower_pointToFront(); // takes 700 ms
    delay(32095 - 29313 - 700);

    // (32095) If so, my actions in killing all the demons were not wrong. (35717)
    hanoman.downFront();   // takes 700 ms
    hanoman.pointToSelf(); // takes 900 ms
    delay(36489 - 32095 - 700 - 900 - (700));
    hanoman.downFront();

    // (36489) You also make a rule, (37727) that you also follow prakreti, (39450)
    hanoman.lower_pointToFront(); // takes 700 ms
    delay(37727 - 36489 - 700);
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(40303 - 37727 - 300 - 200);

    // (40303) but it is the debased nature of a raksasa that you take as guidance. (43835)
    hanoman.downFront(); // takes 700 ms
    delay(44563 - 40303 - 700);

    // (44563) You are a fool who gives instruction in dharmma. (47197)
    hanoman.pointToFront(); // takes 900 ms
    delay(47850 - 44563 - 900);

    // (47850) Clearly (48525)
    hanoman.downFront(); // takes 700 ms
    delay(48822 - 47850 - 700);

    // (48822) it is not the guidance towards truth that you teach. (51664)
    hanoman.middleFront(); // takes 1200 ms
    delay(52191 - 48822 - 1200);

    // (52191) You are the opposite of one who is learned in scriptures, (56013)
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(56444 - 52191 - 300 - 200);

    // (56444) but in fact you are an ignoramus (58737) who pretends to know everything. (60493)
    hanoman.lower_pointToFront(); // takes 700 ms
    delay(58737 - 56444 - 700);
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(61200 - 58737 - 300 - 200);

    // (61200) Ah, you are debased and very wicked. (63790)
    hanoman.lower_pointToFront(); // takes 700 ms
    delay(64325 - 61200 - 700);

    // (64325) You are misguided in your life, (66261)
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(66788 - 64325 - 300 - 200);

    // (66788) regularly committing sins and evil while basically your nature was meant to be good. (72318)
    hanoman.downFront(); // takes 700 ms
    delay(73133 - 66788 - 700);

    // (73133) I advise you to be friends with Rama, (75211)
    hanoman.pointToSelf(); // takes 900 ms
    delay(75597 - 73133 - 900 - (700));
    hanoman.downFront(); // takes 700 ms

    // (75597) but you do not want to, (76896) ah how stupid. (78492)
    hanoman.pointToFront(); // takes 900 ms
    delay(76896 - 75597 - 900);
    hanoman.downFront(); // takes 700 ms
    delay(79011 - 76896 - 700);

    // (79011) Really you are a man of sin. (80926)
    hanoman.pointToFront(); // takes 900 ms
    delay(81556 - 79011 - 900);

    // (81556) Also concerning that Marica, (83337)
    hanoman.lower_pointToFront(); // takes 700 ms
    delay(83782 - 81556 - 700);

    // (83782) why should it be wrong that he was killed by one arrow. (86387)
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(86810 - 83782 - 300 - 200);

    // (86810) The more so, he was a magic deer, (89029)
    hanoman.downFront(); // takes 700 ms
    delay(89370 - 86810 - 700);

    // (89370) running and leaping away in all directions. (92279)
    hanoman.middleFront();      // takes 1200 ms
    for (int i = 0; i < 2; i++) // takes 600 *2 = 1200 ms
    {
        hanoman.directControl(3, 105, 300);
        hanoman.directControl(3, 135, 300);
    }
    delay(92962 - 89370 - 1200 - 1200);

    // (92962) Yet only once did Raghusuta shot at his stomach. (95871)
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(96672 - 92962 - 300 - 200);

    // (96672) Who is the ksatriya (98000) other than he, (98965) who has the power and ability to shoot a magic deer. (102424)
    hanoman.lower_pointToFront(); // takes 700 ms
    delay(98000 - 96672 - 700);
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(98965 - 98000 - 300 - 200);
    hanoman.downFront();   // takes 700 ms
    hanoman.middleFront(); // takes 1200 ms
    delay(103396 - 98965 - 700 - 1200);

    // (103396) You abused Bali. (104769)
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(105385 - 103396 - 300 - 200);

    // (105385) Do you not remember that he was mighty. (107299)
    hanoman.downFront(); // takes 700 ms
    delay(107752 - 105385 - 700);

    // (107752) There was once someone who was almost killed, (110216)
    hanoman.pointToFront(); // takes 900 ms
    delay(110794 - 107752 - 900);

    // (110794) flattened (111529) by Bali. (112286)
    hanoman.lower_pointToFront(); // takes 700 ms
    delay(111529 - 110794 - 700);
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(113251 - 111529 - 300 - 200);

    // (113251) O, Dasamukha, (114468)
    hanoman.lower_pointToFront(); // takes 700 ms
    delay(114868 - 113251 - 700);

    // (114868) therefore be peaceful of mind. (116421)
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(116850 - 114868 - 300 - 200);

    // (116850) Do not quarrel with god Rama, (118705)
    hanoman.downFront(); // takes 700 ms
    hanoman.directControl(4, 60, 200);
    hanoman.directControl(3, 150, 500);
    delay(119106 - 116850 - 700 - 200 - 500);

    // (119106) in order that you will find unlimited glory. (121874)
    hanoman.downFront();    // takes 700 ms
    hanoman.pointToFront(); // takes 900 ms
    delay(122512 - 119106 - 700 - 900);

    // (122512) But if you fight him, (123840)
    hanoman.lower_pointToFront(); // takes 700 ms
    delay(124152 - 122512 - 700);

    // (124152) Lenka will be destroyed. (126022)
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(126794 - 124152 - 300 - 200 - (700));
    hanoman.downFront(); // takes 700 ms

    // (126794) So, serve Raghusuta, (128308)
    hanoman.middleFront(); // takes 1200 ms
    delay(128909 - 126794 - 1200);

    // (128909) let him be the king. (130200)
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(130675 - 128909 - 300 - 200);

    // (130675) Regard Janakasuta as a godess, (132820)
    hanoman.lower_pointToFront(); // takes 700 ms
    delay(133191 - 130675 - 700);

    // (133191) the subject of your worship, (134526)
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(135016 - 133191 - 300 - 200 - (700));
    hanoman.downFront(); // takes 700 ms

    // (135016) and return her to king Rama. (136805)
    hanoman.directControl(4, 60, 200);
    hanoman.directControl(3, 150, 500);
    delay(137421 - 135016 - 200 - 500);

    // (137421) Bring along gold, jewels and most of all, (140159) your homage. (141205)
    hanoman.downFront();   // takes 700 ms
    hanoman.middleFront(); // takes 1200 ms
    delay(140159 - 137421 - 700 - 1200);
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(141205 - 140159 - 300 - 200);
    delay(2000);
    hanoman.downFront(); // takes 700 ms

    /*016_Hanuman-Rawana-Wibhisana_Rawana4v*/
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_3, SoundSystem::EPISODE_3_DIALOG::HANUMAN_RAHWANA_WIBHISANA_RAHWANA4);

    delay(262);
    // (662) Hell! (1159)
    rahwana.pointToFront(); // takes 900 ms
    delay(1433 - 262 - 900);

    // (1433) What kind of monkey are you, (2870)
    rahwana.downFront(); // takes 700 ms
    delay(3278 - 1433 - 700);

    // (3278) you dare to talk so insolently. (5277)
    rahwana.pointToFront();     // takes 900 ms
    for (int i = 0; i < 3; i++) // takes 400 *3 = 1200 ms
    {
        rahwana.directControl(3, 150, 200);
        rahwana.directControl(3, 180, 200);
    }
    delay(5665 - 3278 - 900 - 1200);

    // (5665) Your words are rubbish, (7338) and yet you seem to believe them. (8970)
    rahwana.lower_pointToFront(); // takes 700 ms
    delay(7338 - 5665 - 700);
    rahwana.directControl(3, 180, 500);
    rahwana.directControl(4, 140, 200);
    delay(9660 - 7338 - 500 - 200);

    // (9660) Tie his tail very firmly and burn him. (12451)
    rahwana.downFront(); // takes 700 ms
    rahwana.directControl(4, 60, 200);
    rahwana.directControl(3, 180, 500);
    delay(12876 - 9660 - 700 - 200 - 500);

    // (12876) Torture him slowly! (14481)
    rahwana.downFront();    // takes 700 ms
    rahwana.pointToFront(); // takes 900 ms
    delay(14481 - 12876 - 700 - 900);
    delay(2000);
    rahwana.downFront(); // takes 700 ms

    /*017_Hanuman-Rawana-Wibhisana_HanumanRoar*/
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_3, SoundSystem::EPISODE_3_DIALOG::HANUMAN_RAHWANA_WIBHISANA_HANUMANROAR);

    // g ad delay, main lgsg
    // (318) *roar* (1665)
    hanoman.mathenthengC();
    SoundSystem::playMusicWayang();

    // *Hanuman escapes*
    hanoman.defaultStandPosition();

    /*018_Hanuman-Rawana-Wibhisana_Rawana5v*/
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_3, SoundSystem::EPISODE_3_DIALOG::HANUMAN_RAHWANA_WIBHISANA_RAHWANA5);

    // no delay, just move servo immediately
    // (560) What?! (946)
    rahwana.directControl(3, 30, 300);
    rahwana.directControl(4, 110, 200);
    rahwana.directControl(3, 135, 500);
    delay(1302 - 300 - 200 - 500);

    // (1302) Guards, (1991) don’t let him escape! (3071)
    rahwana.directControl(3, 180, 500);
    rahwana.directControl(4, 140, 200);
    rahwana.downFront(); // takes 700 ms
    delay(3071 - 1302 - 500 - 200 - 700);
    delay(2000);

    // *Rawana leaves the scene*
    SoundSystem::playMusicWayang();
    rahwana.defaultStandPosition();

    // setAllMOSFETtoHIGH();
    SoundSystem::playDialogFromACertainFolder(SoundSystem::INDICATOR_SOUND, SoundSystem::INDICATOR_SOUND_NUMBER::INDICATOR_FINISHED_SHOWING);
    delay(2000);
}

void Episodes::Episode_4()
{
    CalibratingFunction::wayangHand();

    setAllMOSFETtoLOW();

    SoundSystem::playMusicWayang();

    delay(1000);

    hanoman.walk_to_a_certain_distance_before_calibrating_value(200);
    sita.walk_to_a_certain_distance_before_calibrating_value(150);

    /*019_Hanuman_pays_respect_Hanuman1*/
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_4, SoundSystem::EPISODE_4_DIALOG::HANUMAN_PAYS_RESPECT_HANUMAN1);

    delay(182);
    // (182) O, my lady, (1170)
    hanoman.pointToFront(); // 900ms
    delay(1778 - 182 - 900);

    // (1778) I am Maruti, (2712)
    hanoman.downFront(); // 700
    delay(2986 - 1778 - 700);

    // (2986) I am really the messenger of Ramabhadra. (5302)
    hanoman.pointToSelf(); // 900
    delay(5751 - 2986 - 900 - (700));
    hanoman.downFront(); // 700

    // (5751) Do not doubt that I am the messenger of Raghutanaya, (8729)
    hanoman.middleFront(); // 1200
    delay(9291 - 5751 - 1200 - (700));
    hanoman.downFront(); // 700

    // (9291) as you can see by many evidence. (11213)
    hanoman.directControl(4, 70, 200);
    hanoman.directControl(3, 150, 500);
    delay(11881 - 9291 - 200 - 500);

    // (11881) Well, (12367)
    hanoman.downFront(); // 700
    delay(12687 - 11881 - 700);

    // (12687) I must ask your leave to return to convey your message to the great king Ramabhirama. (17594)
    hanoman.middleFront(); // 1200
    delay(17594 - 12687 - 1200);

    sita.middleFront();
    sita.downFront();

    delay(1000);

    SoundSystem::playMusicWayang();

    hanoman.downFront();
    hanoman.defaultStandPosition();
    sita.defaultStandPosition();

    /*20 preparing next scene*/
    anggada.walk_to_a_certain_distance_before_calibrating_value(150);
    anila.walk_to_a_certain_distance_before_calibrating_value(150);
    // delay(1000);
    // hanoman.walk_to_a_certain_distance_before_calibrating_value(300);

    /*Nila:  021 */
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_4, SoundSystem::EPISODE_4_DIALOG::HANUMAN_RETURNS_TO_RAMA_NILA1);

    delay(1114);
    // (1114) Brothers, look at Hanuman! (2752)
    anila.pointToFront(); // 900
    delay(3304 - 1114 - 900);

    // (3304) Clearly he is successful! (4755)
    anila.lower_pointToFront(); // 700
    delay(4755 - 3304 - 700);

    /*Angada: 022 */
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_4, SoundSystem::EPISODE_4_DIALOG::HANUMAN_RETURNS_TO_RAMA_ANGGADA1);

    delay(1032);
    // (1032) Ah! Only a hero is capable of enduring the pain as he did it on purpose (5842)
    anggada.middleFront(); // 1200
    delay(6124 - 1032 - 1200);

    // (6124) to decorate his body. (7527)
    anggada.directControl(1, 5, 500);
    anggada.directControl(2, 35, 200);
    delay(7527 - 6124 - 500 - 200 - (700));
    anggada.downFront();

    /*Nila: 023 */
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_4, SoundSystem::EPISODE_4_DIALOG::HANUMAN_RETURNS_TO_RAMA_NILA2);

    delay(610);
    // (610) Pawanatmaja is like the sun. (2631)
    anila.directControl(3, 175, 500); // 500 ms
    anila.directControl(4, 140, 200); // 200 ms
    delay(2631 - 610 - 500 - 200 - (700));
    anila.downFront();

    /*Angada: 024 */
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_4, SoundSystem::EPISODE_4_DIALOG::HANUMAN_RETURNS_TO_RAMA_ANGGADA2);

    delay(826);
    // (826) He is like light, and the severe lovesickness of Lord Rama is the intense darkness that is destroyed by him. (7018)
    anggada.pointToFront();       // 900
    anggada.lower_pointToFront(); // 700
    for (int i = 0; i < 6; i++)   // 600*3
    {
        anggada.directControl(1, 5, 300);
        anggada.directControl(1, 90, 300);
    }
    anggada.downFront();

    delay(7018 - 826 - 900 - 700 - (600 * 6) - 700);
    delay(2000);

    /* Using RTOS for Anggada and Anila cheering simultaneously */
    // cheering (lakukan ini bersamaan kalo bisa)

    /*
        anila.pointToFront(); //aksi 1
        anggada.pointToFront(); //aksi 1
        delay(2000);
        anila.downFront(); //aksi 2
        anggada.downFront(); //aksi 2
    */
    xTaskCreate(anggadaCheeringTask, "AnggadaCheeringTask", fighting_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(anilaCheeringTask, "AnilaCheeringTask", fighting_STACK_SIZE, NULL, 1, NULL);

    // suspend general episode 3 task, running anila and anggada cheering task
    vTaskSuspend(episodeTaskHandler[3]);

    SoundSystem::playMusicWayang();

    // balek ke commandlist biasa
    anila.defaultStandPosition();
    anggada.defaultStandPosition();

    // siapin next scene
    hanoman.walk_to_a_certain_distance_before_calibrating_value(150);
    rama_wijaya.walk_to_a_certain_distance_before_calibrating_value(150);

    /*Hanuman: 027 */
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_4, SoundSystem::EPISODE_4_DIALOG::HANUMAN_RETURNS_TO_RAMA_HANUMAN1);

    delay(379);
    // (379) Here is the crest jewel and her letter my Lord (3063)
    hanoman.middleFront(); // 1200
    delay(3063 - 379 - 1200);
    delay(1000);
    hanoman.downFront();

    /*rama baca surat*/
    rama_wijaya.middleFront();
    delay(3000);

    /*Rama: 028*/
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_4, SoundSystem::EPISODE_4_DIALOG::HANUMAN_RETURNS_TO_RAMA_RAMA1);

    delay(140);
    // (140) *sobbing* (883)
    rama_wijaya.downFront();
    delay(1378 - 140 - 700);

    // (1378) O, Maruti, (2477)
    rama_wijaya.pointToFront();
    delay(2842 - 1378 - 1200);

    // (2842) look! (3625) Help me! (4627) My brother Laksmana, (6112) come here, (6942)
    rama_wijaya.lower_pointToFront();
    delay(3625 - 2842 - 700);
    rama_wijaya.directControl(1, 0, 500);
    rama_wijaya.directControl(2, 10, 200);
    delay(4627 - 3625 - 500 - 200);
    rama_wijaya.lower_pointToFront();
    delay(6112 - 4627 - 700);
    rama_wijaya.downFront();
    delay(6942 - 6112 - 700);

    delay(7487 - 6942 - (500)); // minjem 500
    // (7487) look! (8279) Look at the writing, (9311)
    rama_wijaya.pointToFront();
    delay(8279 - 7487 - (1200 - 500));
    rama_wijaya.lower_pointToFront();
    delay(9848 - 8279 - 700);

    // (9848) it disappears, (10920)
    rama_wijaya.downFront();
    delay(11412 - 9848 - 700);

    // (11412) most is not legible. (12798)
    rama_wijaya.middleFront();
    delay(13213 - 11412 - 1200);

    // (13213) Ah! I cannot know what was further in the letter, (15800)
    rama_wijaya.lower_pointToFront();
    delay(16134 - 13213 - 700 - (700));
    rama_wijaya.downFront();

    // (16134) because I am so sad. (17529)
    rama_wijaya.pointToSelf();
    delay(18718 - 16134 - 900);

    // (18718) O, where is the rest of the letter? (19904)
    rama_wijaya.downFront();
    delay(20531 - 18718 - 700);

    // (20531) O, how sad. (22284)
    rama_wijaya.middleFront();
    delay(22284 - 20531 - 1200);
    rama_wijaya.downFront();

    /* Hanuman: 029 */
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_4, SoundSystem::EPISODE_4_DIALOG::HANUMAN_RETURNS_TO_RAMA_HANUMAN2);

    // langsung jalan no delay
    //  (350) Well my lord, (1400)
    hanoman.lower_pointToFront();
    delay(1815 - 700 - (700) - (300)); // minjem 700 buat downfront dan 300 buat slight delay ke pts
    hanoman.downFront();
    delay(300); // experimental delay buat nunggu stop goyang baru pts

    // (1815) I beg your mercy. (2836)
    hanoman.pointToSelf();
    delay(3305 - 1815 - 900);

    // (3305) Do not be so distressed. (4811)
    hanoman.downFront();
    delay(5482 - 3305 - 700);

    // (5482) Take it easy, (6235)
    hanoman.lower_pointToFront();
    delay(6639 - 5482 - 700);

    // (6639) because she has already asked for my lord to come. (9498)
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(10299 - 6639 - 300 - 200);

    // (10299) What my lord should do (11842) is to depart as soon as possible. (13616)
    hanoman.lower_pointToFront();
    delay(11842 - 10299 - 700);
    hanoman.downFront();
    hanoman.middleFront();
    delay(14411 - 11842 - 700 - 1200);

    // (14411) What my lord should do, (15662)
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(16030 - 14411 - 300 - 200);

    // (16030) since it is now clear (17341) that the queen is without a doubt alive, (19459)
    hanoman.downFront();
    delay(17341 - 16030 - 700);
    hanoman.middleFront();
    delay(19809 - 17341 - 1200);

    // (19809) is to depart and to attack the whole country of Lenka. (23019)
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(23885 - 19809 - 300 - 200);

    // (23885) My lord Raghuputra, (25107)
    hanoman.lower_pointToFront();
    delay(25582 - 23885 - 700);

    // (25582) Rawana has mistreated (27018) and endangered the world for a long time. (27018)
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(30138 - 25582 - 300 - 200);

    // (30138) He drove away Waisrawana (31728)
    hanoman.downFront();
    delay(32102 - 30138 - 700);

    // (32102) and robbed him of his gold he kept, (33965)
    hanoman.pointToFront();
    delay(34517 - 32102 - 900);

    // (34517) hundreds and hundreds of thousands were stolen. (36955)
    hanoman.downFront();
    delay(37447 - 34517 - 700);

    // (37447) Nothing was left. (38579)
    hanoman.middleFront();
    delay(39470 - 37447 - 1200);

    // (39470) Furthermore princess Janakatmaja is in grief, (42146)
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(42911 - 39470 - 300 - 200);

    // (42911) my lady is despondent from separation. (45296)
    hanoman.lower_pointToFront();
    delay(45919 - 42911 - 700);

    // (45919) She thinks only of my lord, (47456)
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(47889 - 45919 - 300 - 200);

    // (47889) and weeps day and night. (49348)
    hanoman.downFront();
    delay(50120 - 47889 - 700);

    // (50120) Though painful, (50938)
    // (51318) her loyalty, (52362) that she always keeps in mind, (54237) remains pure. (55536)
    hanoman.middleFront();
    delay(52362 - 50120 - 1200);
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(54237 - 52362 - 300 - 200);
    hanoman.lower_pointToFront();
    delay(55536 - 54237 - 700);
    hanoman.downFront();

    /* Rama: 030 */
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_4, SoundSystem::EPISODE_4_DIALOG::HANUMAN_RETURNS_TO_RAMA_RAMA2);

    delay(874 - (500)); // minjem 500
    // (874) You are right. (1352)
    rama_wijaya.middleFront();
    delay(1811 - 874 - (1200 - 500));

    // (1811) Laksmana! (2418)
    rama_wijaya.directControl(1, 0, 500);
    rama_wijaya.directControl(2, 10, 200);
    delay(2796 - 1811 - 500 - 200);

    // (2796) Issue the order to depart! (4178)
    rama_wijaya.lower_pointToFront();
    delay(4586 - 2796 - 700);

    // (4586) We are crossing the great ocean! (6161)
    rama_wijaya.directControl(1, 0, 500);
    rama_wijaya.directControl(2, 10, 200);
    delay(6161 - 4586 - 500 - 200);
    delay(2000);

    SoundSystem::playMusicWayang();

    hanoman.defaultStandPosition();
    rama_wijaya.defaultHandPosition();
    rama_wijaya.defaultStandPosition();
    delay(1000);

    rahwana.walk_to_a_certain_distance_before_calibrating_value(150);
    wibhisana.walk_to_a_certain_distance_before_calibrating_value(150);

    /*Wibhisana-Rawana*/
    /*Wibhisana: 031*/
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_4, SoundSystem::EPISODE_4_DIALOG::WIBHISANA_RAHWANA_WIBHISANA1);

    delay(598);
    // (598) O, Dasasya. (1716)
    wibhisana.pointToFront();
    delay(1930 - 598 - 900);

    // (1930) Without doubt death will come. (3752)
    wibhisana.lower_pointToFront();
    delay(4279 - 1930 - 700);

    // (4279) There are recently been amazing bad omens. (6772)
    wibhisana.downFront();
    wibhisana.middleFront();
    delay(7341 - 4279 - 700 - 1200);

    // (7341) Dust was filling the sky and covering the whole city. (10393)
    wibhisana.directControl(1, 5, 500);
    wibhisana.directControl(2, 35, 200);
    delay(11121 - 7341 - 500 - 200);

    // (11121) There was no reason, (12232) but still suddenly it came. (13780)
    wibhisana.lower_pointToFront();
    delay(12232 - 11121 - 700);
    wibhisana.directControl(1, 5, 500);
    wibhisana.directControl(2, 35, 200);
    delay(14637 - 12232 - 500 - 200);

    // (14637) Do not be stubborn, (15827)
    wibhisana.downFront();
    delay(16205 - 14637 - 700);

    // (16205) listen to good advice. (17453)
    wibhisana.pointToFront();
    delay(17931 - 16205 - 900);

    // (17931) Pay attention to those giving you good counsel. (20266)
    wibhisana.lower_pointToFront();
    delay(20716 - 17931 - 700);

    // (20716) Your attendants are very thoughtless, (22481)
    wibhisana.downFront();
    delay(23023 - 20716 - 700);

    // (23023) they only spoil the king. (24446)
    wibhisana.middleFront();
    delay(25143 - 23023 - 1200);

    // (25143) There is no remedy, (26264)
    wibhisana.directControl(1, 5, 500);
    wibhisana.directControl(2, 35, 200);
    delay(26584 - 25143 - 500 - 200);

    // (26584) other than appeasement offerings, (28293)
    wibhisana.lower_pointToFront();
    delay(28729 - 26584 - 700);

    // (28729) other than submission to Raghutanaya. (31025)
    wibhisana.directControl(1, 5, 500);
    wibhisana.directControl(2, 35, 200);
    delay(31668 - 28729 - 500 - 200);

    // (31668) Bring back Maithili, (32829)
    wibhisana.downFront();
    delay(33275 - 31668 - 700);

    // (33275) she is equal to one thousand appeasement offerings. (36098)
    wibhisana.middleFront();
    delay(36643 - 33275 - 1200);

    // (36643) Please, (37477) grant me your approval, (38813)
    wibhisana.downFront();
    wibhisana.pointToSelf();
    delay(39224 - 36643 - 700 - 900);

    // (39224) submit yourself to Raghutanaya. (41088)
    wibhisana.downFront();
    wibhisana.pointToFront();
    delay(41088 - 39224 - 700 - 900);
    delay(2000);
    wibhisana.downFront();

    /*Rawana: 032*/
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_4, SoundSystem::EPISODE_4_DIALOG::WIBHISANA_RAHWANA_RAHWANA1);

    delay(609);
    // (609) Hey Wibhisana, (1674)
    rahwana.pointToFront();
    delay(2053 - 900);

    // (2053) get out! Beat it! (3252)
    rahwana.directControl(3, 150, 200);
    rahwana.directControl(3, 180, 200);
    rahwana.directControl(3, 150, 200);
    rahwana.directControl(3, 180, 200);
    rahwana.downFront();
    delay(3849 - 2053 - 800 - 700);

    // (3849) Your words are bad and ill-motivated. (6542)
    rahwana.middleFront();      // 1200
    for (int i = 0; i < 3; i++) // 1200
    {
        rahwana.directControl(3, 105, 200);
        rahwana.directControl(3, 135, 200);
    }
    delay(7100 - 3849 - 1200 - 1200);

    // (7100) Raghawa will win. (8313)
    rahwana.directControl(3, 180, 500);
    rahwana.directControl(4, 140, 200);
    delay(8563 - 7100 - 700);

    // (8563) Rawana will lose. (9698)
    rahwana.lower_pointToFront();
    delay(9968 - 8563 - 700);

    // (9968) Ah! (10727) That is absurd, (11847)
    rahwana.directControl(3, 180, 500);
    rahwana.directControl(4, 140, 200);
    delay(10727 - 9968 - 500 - 200);

    // (12245) even if Rama were able to double his might. (14945)
    rahwana.downFront();
    delay(15856 - 12245 - 700);

    // (15856) You think you can give advice, (17562)
    rahwana.lower_pointToFront();
    delay(17819 - 15856 - 700);

    // (17819) but now I know that your mind is debased, (20814) treacherous, and extremely deceitful. (23727)
    rahwana.directControl(3, 180, 500);
    rahwana.directControl(4, 140, 200);
    delay(20814 - 17819 - 500 - 300);
    rahwana.downFront();
    rahwana.directControl(4, 65, 200);
    delay(200); // biar sendi g awikwok
    rahwana.directControl(3, 179, 500);
    delay(24509 - 20814 - 700 - 200 - 200 - 500 - (700));
    rahwana.downFront();

    // (24509) Just now that which was hidden in the past (27478) has been revealed. (28665)
    rahwana.pointToFront();
    delay(27478 - 24509 - 900);
    rahwana.lower_pointToFront();
    delay(29460 - 27478 - 700);

    // (29460) In the past (30333) I thought you abstained from battles (32853)
    rahwana.downFront();
    delay(30333 - 29460 - 700);
    rahwana.middleFront();
    delay(33174 - 30333 - 1200);

    // (33174) as I thought you were a conscientious objector (35830)
    rahwana.directControl(3, 180, 500);
    rahwana.directControl(4, 140, 200);
    delay(36157 - 33174 - 500 - 200);

    // (36157) based on religious principles. (38119)
    rahwana.lower_pointToFront();
    delay(38883 - 36157 - 700);

    // (38883) Now it proves that you are a damned (41493) debased traitor. (42763)
    rahwana.directControl(3, 180, 500);
    rahwana.directControl(4, 140, 200);
    for (int i = 0; i < 4; i++) // 1600
    {
        rahwana.directControl(3, 150, 200);
        rahwana.directControl(3, 180, 200);
    }
    delay(41493 - 38883 - 500 - 200 - 1600);
    rahwana.downFront();
    delay(43603 - 41493 - 700);

    // (43603) When the city was burnt to the ground (45900) you were delighted to see the flaming fire. (48408)
    rahwana.middleFront();
    delay(45900 - 43603 - 1200);
    rahwana.directControl(3, 180, 500);
    rahwana.directControl(4, 140, 200);
    delay(48927 - 45900 - 500 - 200);

    // (48927) You were the reason that the ape could escape. (51852)
    for (int i = 0; i < 4; i++) // 1600
    {
        rahwana.directControl(3, 150, 200);
        rahwana.directControl(3, 180, 200);
    }
    delay(52590 - 48927 - 1600);

    // (52590) That is the proof that you are a debased, (54803) wicked and filthy traitor. (56496)
    rahwana.downFront();
    delay(54803 - 52590 - 700);
    rahwana.pointToFront();
    delay(56496 - 54803 - 900 - (700));
    rahwana.downFront();
    delay(2000);

    // *walk forward*
    rahwana.walk_to_a_certain_distance_before_calibrating_value(280); // ini harus ditentuin posisiny

    /*32 Rawana_punches_wibhisana */
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_4, SoundSystem::EPISODE_4_DIALOG::WIBHISANA_RAHWANA_RAHWANA2);

    delay(800 - (300)); // minjem 300
    // (800) Bastard! (ini harus dicut sih karena takut desync[done])
    rahwana.directControl(3, 50, 200);
    rahwana.directControl(4, 140, 200);
    rahwana.directControl(3, 30, 200);
    rahwana.directControl(4, 100, 200);

    // (2003) Euagh!
    // *punch*
    rahwana.pointToFront();
    wibhisana.walk_to_a_certain_distance_before_calibrating_value(130); // perlu disetting
    rahwana.downFront();

    delay(1000);

    rahwana.walk_to_a_certain_distance_before_calibrating_value(150);

    delay(1000);

    wibhisana.walk_to_a_certain_distance_before_calibrating_value(150);

    /*Wibhisana: 033 */
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_4, SoundSystem::EPISODE_4_DIALOG::WIBHISANA_RAHWANA_WIBHISANA2);

    delay(803 - (200)); // minjem 200
    // (803) O king, (1524)
    wibhisana.middleFront();
    delay(1861 - 803 - (1200 - 200));

    // (1861) banish your anger, (2959)
    wibhisana.directControl(1, 5, 500);
    wibhisana.directControl(2, 35, 200);
    delay(3306 - 1861 - 500 - 200);

    // (3306) clear your fury from your mind, (5451) and keep it pure. (6427)
    wibhisana.lower_pointToFront();
    delay(5451 - 3306 - 700);
    wibhisana.directControl(1, 5, 500);
    wibhisana.directControl(2, 35, 200);
    delay(6923 - 5451 - 500 - 200);

    // (6923) May the king be well and prosperous. (9244)
    wibhisana.lower_pointToFront();
    delay(9636 - 6923 - 700);

    // (9636) Follow the counsel of other people. (11525)
    wibhisana.downFront();
    delay(11979 - 9636 - 700);

    // (11979) It is worthless to listen to my advice, (14391) as it is not as good as all those others. (17246)
    wibhisana.pointToSelf();
    delay(14391 - 11979 - 900);
    wibhisana.downFront();
    wibhisana.middleFront();
    delay(17751 - 14391 - 700 - 1200);

    // (17751) Do as you wish, (19442) stick to your decision firmly and do not change your mind. (22682)
    wibhisana.directControl(1, 5, 500);
    wibhisana.directControl(2, 35, 200);
    delay(19442 - 17751 - 500 - 200);
    wibhisana.lower_pointToFront();
    delay(23221 - 19442 - 700 - (700) - (200)); // minjem
    wibhisana.downFront();
    delay(200);

    // (23221) People like me are not to blame (25304) when one does not listen to them. (27271)
    wibhisana.pointToSelf();
    delay(25304 - 23221 - 900);

    // (27671) It is like the case of a philanthropist (30019) who wants to help a patient by giving him medicine. (32834)
    wibhisana.downFront();
    delay(30019 - 27671 - 700);
    wibhisana.pointToFront();
    delay(33047 - 30019 - 900);

    // (33407) The doctor is not to blame when the bitter but beneficent medicine is not taken. (37913)
    wibhisana.lower_pointToFront();
    delay(38628 - 33047 - 700);

    // (38628) Likewise in my case, (40004) when I give you counsel, I will not be condemned. (42668)
    wibhisana.downFront();
    delay(40004 - 38628 - 700);
    wibhisana.pointToSelf();
    delay(43412 - 40004 - 900 - (700));
    wibhisana.downFront();

    // (43412) Let the king say who is correct (45370) and who is wrong. (46221)
    wibhisana.pointToFront();
    delay(45370 - 43412 - 900);
    wibhisana.lower_pointToFront();
    delay(46595 - 45370 - 700);

    // (46595) If a servant gives advice to his master, (49353) is it the servant who should be punished if the advice does not suit the king? (53598)
    wibhisana.downFront();
    delay(49353 - 46595 - 700);
    wibhisana.middleFront();
    delay(54046 - 46595 - 1200);

    // (54046) If the king is inconsiderate and very quick to aim his punches at his faithful attendants? (59579)
    wibhisana.directControl(1, 5, 500);
    wibhisana.directControl(2, 35, 200);
    delay(60215 - 54046 - 500 - 200);

    // (60215) Ask all your ministers, (61991) because they are all experienced people. (64096)
    wibhisana.downFront();
    delay(61991 - 60215 - 700);
    wibhisana.pointToFront();
    delay(64596 - 61991 - 900 - (700) - (200)); // minjem
    wibhisana.downFront();
    delay(200);

    // (64596) I shall take my leave now. (66457)
    wibhisana.pointToSelf();
    delay(66457 - 64596 - 900);
    delay(1000);

    SoundSystem::playMusicWayang();

    wibhisana.downFront();
    wibhisana.defaultStandPosition();
    delay(1000);
    rahwana.defaultStandPosition();
    delay(1000);

    hanoman.walk_to_a_certain_distance_before_calibrating_value(150);
    delay(1000);
    wibhisana.walk_to_a_certain_distance_before_calibrating_value(150);

    /*Wibhisana_Defects*/
    /*Hanuman: 034*/
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_4, SoundSystem::EPISODE_4_DIALOG::WIBHISANA_DEFECTS_HANUMAN1);

    delay(343);
    // (343) Ah, (914)
    hanoman.lower_pointToFront();
    delay(1298 - 343 - 700);

    // (1298) you were the one who tried to persuade Rawana from killing me (4231)
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(4491 - 1298 - 300 - 200);

    // (4491) despite being a messenger. (5758)
    hanoman.downFront();
    delay(6500 - 4491 - 700);

    // (6500) My name is Hanuman. (7545)
    hanoman.pointToSelf();
    delay(8109 - 6500 - 700 - (700));
    hanoman.downFront();

    // (8109) Please, (8556)
    // (8850) may I ask for your purpose in coming here? (11081)
    hanoman.lower_pointToFront();
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(11081 - 8109 - 700 - 300 - 200);
    delay(2000);
    hanoman.downFront();

    /*Wibhisana: 035*/
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_4, SoundSystem::EPISODE_4_DIALOG::WIBHISANA_DEFECTS_WIBHISANA1);

    // langsung jalan
    //  (1061) Of course, (1803) my name is Wibhisana, (3324) and I have come here to render my devotion to Raghusuta. (7228)
    wibhisana.lower_pointToFront();
    wibhisana.downFront();
    delay(1803 - 700 - 700);
    wibhisana.pointToSelf();
    delay(3324 - 1803 - 900);
    wibhisana.downFront();
    wibhisana.pointToFront();
    delay(7705 - 3324 - 700 - 900);

    // (7705) I would like to have an audience with your lord. (10399)
    wibhisana.lower_pointToFront();
    delay(10399 - 7705 - 700);
    delay(2000);
    wibhisana.downFront();

    /*Hanuman: 036*/
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_4, SoundSystem::EPISODE_4_DIALOG::WIBHISANA_DEFECTS_HANUMAN2);

    // langsung jalan
    //  (537) Very well! (1291)
    hanoman.lower_pointToFront();
    hanoman.downFront();
    delay(1853 - 700 - 700);

    // (1853) I shall inform my brothers (3584) to relay your message as a reward for showing mercy to me in the past. (7316)
    hanoman.pointToSelf();
    delay(3584 - 1853 - 900);
    hanoman.downFront();
    hanoman.pointToFront();
    delay(8012 - 3584 - 700 - 900);

    // (8012) Anila, (8568)
    hanoman.lower_pointToFront();
    delay(9105 - 8012 - 700);

    // (9105) please grant this honorable man his wish (11601) and relay the message to lord Rama. (14242)
    hanoman.directControl(3, 180, 300);
    hanoman.directControl(4, 140, 200);
    delay(11601 - 9105 - 300 - 200);
    hanoman.downFront();
    delay(14242 - 11601 - 700);

    SoundSystem::playMusicWayang();

    wibhisana.defaultStandPosition();
    anila.walk_to_a_certain_distance_before_calibrating_value(340); // cari value pasti

    /*Nila: 037*/
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_4, SoundSystem::EPISODE_4_DIALOG::WIBHISANA_DEFECTS_NILA1);

    delay(861);
    // (861) Yes brother. (1507)
    anila.pointToSelf();
    delay(2000);
    anila.downFront();

    SoundSystem::playMusicWayang();

    anila.defaultStandPosition();
    hanoman.defaultStandPosition();
    delay(1000);

    anila.walk_to_a_certain_distance_before_calibrating_value(150);
    rama_wijaya.walk_to_a_certain_distance_before_calibrating_value(150);
    /*Rama_informed*/
    /*Nila: 038*/
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_4, SoundSystem::EPISODE_4_DIALOG::RAMA_INFORMED_NILA1);

    delay(933);
    // (933) The most outstanding Wibhisana has come to render his service without reservation at the feet (7007) of my lord. (7644)
    anila.pointToFront();
    delay(1000);
    anila.lower_pointToFront();
    delay(7007 - 933 - 900 - 1000 - 700);
    anila.pointToSelf();
    delay(8104 - 7007 - 900);

    // (8104) It is certainly better to accept him (10320) as he is noble and virtuous, (12215)
    anila.downFront();
    anila.middleFront();
    delay(10320 - 8104 - 700 - 1200);
    anila.directControl(3, 175, 500); // 500 ms
    anila.directControl(4, 140, 200); // 200 ms
    delay(12858 - 10320 - 700);

    // (12858) conversant (13942) in scriptures (15124) and formulas (16221) and may become a good ally. (18198)
    anila.lower_pointToFront();
    delay(13942 - 12858 - 700);
    anila.downFront();
    delay(15124 - 13942 - 700);
    anila.lower_pointToFront();
    delay(16221 - 15124 - 700);
    anila.directControl(3, 175, 500); // 500 ms
    anila.directControl(4, 140, 200); // 200 ms
    delay(18198 - 16221 - 500 - 200);
    delay(2000);
    anila.downFront();

    /*Rama: 039*/
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_4, SoundSystem::EPISODE_4_DIALOG::RAMA_INFORMED_RAMA1);

    delay(589);
    // (589) I agree with your sentiment, (2633) please lead him to our camp. (4885)
    rama_wijaya.pointToSelf();
    delay(2663 - 589 - 900 - (700)); // minjem
    rama_wijaya.downFront();
    rama_wijaya.pointToFront();
    delay(4885 - 2663 - 700 - (1200 - 700));
    delay(2000);
    rama_wijaya.downFront();

    SoundSystem::playMusicWayang();

    anila.defaultStandPosition();
    sugriwa.walk_to_a_certain_distance_before_calibrating_value(270);

    /*Before final ultimatum*/
    /*Sugriwa: 040*/
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_4, SoundSystem::EPISODE_4_DIALOG::BEFORE_FINAL_ULTIMATUM_SUGRIWA1);

    // langsung jalan
    //  (459) My lord, (992)
    sugriwa.pointToSelf();
    delay(1499 - 900);

    // (1499) most of our monkey troops are overcrowding our camps, (4733)
    sugriwa.downFront();
    sugriwa.middleFront();
    delay(5129 - 1499 - 700 - 1200 - (700) - (200));
    sugriwa.downFront();
    delay(200);

    // (5129) I think it is best if we confront the enemy as soon as possible, (8769)
    sugriwa.pointToSelf();
    delay(9334 - 5129 - 900);

    // (9334) to avoid running out of food. (10690)
    sugriwa.downFront();
    sugriwa.lower_pointToFront();
    delay(2000);
    sugriwa.downFront();

    SoundSystem::playMusicWayang();

    sugriwa.defaultStandPosition();
    laksmana.walk_to_a_certain_distance_before_calibrating_value(150); // cari value

    /*Laksmana: 041*/
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_4, SoundSystem::EPISODE_4_DIALOG::BEFORE_FINAL_ULTIMATUM_LAKSMANA1);

    // langsung jalan
    //  (318) What about it brother? (1380)
    laksmana.pointToFront();
    delay(2031 - 900 - (700) - (200));
    laksmana.downFront();
    delay(200);

    // (2031) I agree with his opinion, (3264)
    laksmana.pointToSelf();
    delay(3920 - 2031 - 700);

    // (3920) we should attack the enemy quickly (5703)
    laksmana.downFront();
    laksmana.middleFront();
    delay(6332 - 3920 - 700 - 900);

    // (6332) and save Sita from captivity. (8094)
    laksmana.pointToFront();
    delay(8830 - 6332 - 700);

    // (8830) Sita must have been longing to see you again brother, (11420)
    laksmana.lower_pointToFront();
    delay(12078 - 8830 - 700);

    // (12078) so let us not make her wait (13479) and advance with utmost haste! (15332)
    laksmana.pointToFront();
    delay(13479 - 12078 - 700);
    laksmana.downFront();
    delay(200);
    laksmana.pointToSelf();
    delay(15332 - 13479 - 700 - 200 - 900);
    delay(2000);
    laksmana.downFront();

    /*Rama: 042*/
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_4, SoundSystem::EPISODE_4_DIALOG::BEFORE_FINAL_ULTIMATUM_RAMA1);

    // langsung jalan
    //  (819) Alright, (1158)
    rama_wijaya.middleFront();
    delay(1513 - 1200);

    // (1513) let us attack the enemy tomorrow. (3377)
    rama_wijaya.directControl(1, 0, 500);
    rama_wijaya.directControl(2, 10, 200);
    delay(3920 - 1513 - 500 - 200);

    // (3920) Have the monkeys forage for the day so that they can have a feast for the night (8697)
    rama_wijaya.lower_pointToFront();
    delay(9191 - 3920 - 700 - (700));
    rama_wijaya.downFront();

    // (9191) and once they are rested from the march, (11798)
    rama_wijaya.middleFront();
    delay(12206 - 9191 - 1200);

    // (12206) we shall attack. (13058)
    rama_wijaya.directControl(1, 0, 500);
    rama_wijaya.directControl(2, 10, 200);
    delay(13667 - 12206 - 500 - 200);

    // (13667) But first, (14662) Angada will be sent to the enemy as a messenger (17272)
    rama_wijaya.downFront();
    delay(14662 - 13667 - 700);
    rama_wijaya.pointToFront();
    delay(17646 - 14662 - 1200 - (700));
    rama_wijaya.downFront();

    // (17646) as I believe there is still a chance (20284) that he will see reason. (21570)
    rama_wijaya.pointToSelf();
    delay(20284 - 17646 - 900);
    rama_wijaya.downFront();
    rama_wijaya.lower_pointToFront();
    delay(2000);
    rama_wijaya.downFront();

    SoundSystem::playMusicWayang();

    laksmana.defaultStandPosition();
    rama_wijaya.defaultStandPosition();

    SoundSystem::playDialogFromACertainFolder(SoundSystem::INDICATOR_SOUND, SoundSystem::INDICATOR_SOUND_NUMBER::INDICATOR_FINISHED_SHOWING);
    delay(2000);
}

void Episodes::Episode_5()
{
    CalibratingFunction::wayangHand();

    SoundSystem::playMusicWayang();

    anggada.walk_to_a_certain_distance_before_calibrating_value(150);
    rahwana.walk_to_a_certain_distance_before_calibrating_value(150);

    /*Ultimatum */
    /* Angada: 043*/
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_5, SoundSystem::EPISODE_5_DIALOG::ULTIMATUM_ANGGADA1);

    delay(1003);
    // (1003) Hey king Dasanana. (2666) Listen to my words. (3651)
    anggada.pointToFront();
    delay(2666 - 1003 - 900);
    anggada.directControl(1, 55, 400);
    anggada.directControl(1, 5, 400);
    delay(4174 - 2666 - 400 - 400 - (700));
    anggada.downFront();

    // (4174) I am the well-known Angada, (5871) the son of Bali. (6883)
    delay(300);
    anggada.pointToSelf();
    delay(7388 - 4174 - 300 - 900);

    // (7388) My lord Rama, the son of Raghu, (9762) king of the Universe, (11066) ordered me to come to you. (12514)
    anggada.downFront();
    delay(9762 - 7388 - 700);
    anggada.middleFront();
    delay(11066 - 9762 - 1200);
    anggada.directControl(1, 5, 500);
    anggada.directControl(2, 35, 200);
    delay(13011 - 11066 - 500 - 200 - (1000));
    anggada.downFront();
    delay(300);

    // (13011) That is why I am here, (14571) to urge you to surrender to Lord Rama with all your subjects. (18428)
    anggada.pointToSelf();
    delay(14571 - 13011 - 900);
    anggada.downFront();
    anggada.pointToFront();
    delay(19139 - 14571 - 700 - 900);

    // (19139) Beg for your life, so that you can enjoy your luxurious life forever. (23099)
    anggada.lower_pointToFront();
    for (int i = 0; i < 5; i++) // 3000
    {
        anggada.directControl(1, 60, 300);
        anggada.directControl(1, 90, 300);
    }
    delay(23609 - 19139 - 700 - 3000);

    // (23690) All valuables in the palace must be brought along and handed over, (27890) let ornaments, jewels, precious stones, and other luxuries accompany the return of princess Sita. (34053)
    anggada.downFront();
    delay(300);
    anggada.directControl(2, 120, 200);
    anggada.directControl(1, 20, 500);
    delay(27890 - 23690 - 700 - 300 - 700);
    anggada.downFront();
    anggada.middleFront();
    for (int i = 0; i < 4; i++)
    {
        anggada.directControl(1, 75, 500);
        anggada.directControl(1, 45, 500);
    }
    delay(34773 - 27890 - 700 - 1200 - 4000);

    // (34773) If you refuse to surrender (36452) and to return princess Maithili, (38312) Lord Ramabhadra will be annoyed and might destroy you. (41681)
    anggada.directControl(1, 5, 500);
    anggada.directControl(2, 35, 200);
    delay(36452 - 34773 - 500 - 200);
    anggada.lower_pointToFront();
    delay(38312 - 36452 - 700);

    // (42126) Clearly all of you will be smashed to dust completely, (45161)
    anggada.downFront();
    delay(300);
    anggada.directControl(2, 120, 200);
    anggada.directControl(1, 20, 500);
    delay(45589 - 42126 - 700 - 300 - 200 - 500);

    // (45589) because his Lordship is exceedingly powerful and irresistible in the world. (50140)
    anggada.downFront();
    anggada.lower_pointToFront();
    delay(50646 - 45589 - 700 - 700);

    // (50646) Anyway (51409) what is the use of being haughty and boastful all the time? (54314)
    anggada.directControl(1, 5, 500);
    anggada.directControl(2, 35, 200);
    delay(51409 - 50646 - 500 - 200);
    anggada.downFront();
    delay(54726 - 51409 - 700);

    // (54726) It is true that a man can live for a long time, but vitality does not remain for long. (60374) Likewise is the union with one’s beloved, (63237) it is very changeable. (64617)
    anggada.middleFront();
    for (int i = 0; i < 4; i++)
    {
        anggada.directControl(1, 75, 500);
        anggada.directControl(1, 45, 500);
    }
    delay(60374 - 54726 - 1200 - 4000);
    anggada.lower_pointToFront();
    delay(63237 - 60374 - 700);
    anggada.directControl(1, 5, 500);
    anggada.directControl(2, 35, 200);
    delay(65174 - 63237 - 500 - 200);

    // (65174) Ah, you are cruel, (66802) evil is in your head, Rawana! (68971) You are a very stupid and foolish adulterer with a dumb mind. (73916) The arrow of Lord Rama is very sharp (76436) and extremely venomous. (77885)
    anggada.downFront();
    delay(66802 - 65174 - 700);
    anggada.pointToFront();
    delay(68971 - 66802 - 900);
    anggada.middleFront();
    for (int i = 0; i < 3; i++)
    {
        anggada.directControl(1, 75, 500);
        anggada.directControl(1, 45, 500);
    }
    delay(73916 - 68971 - 1200 - 3000);
    anggada.directControl(1, 5, 500);
    anggada.directControl(2, 35, 200);
    delay(76436 - 73916 - 500 - 2000);
    anggada.lower_pointToFront();
    delay(78399 - 76436 - 700);

    // (78399) You do not think about that, how stupid! (81176)
    anggada.downFront();
    anggada.pointToFront();
    anggada.downFront();
    delay(81176 - 78399 - 700 - 900 - 700);
    delay(1000);

    /*Rawana: 044*/
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_5, SoundSystem::EPISODE_5_DIALOG::ULTIMATUM_RAHWANA1);

    // langsung jalan
    //  (701) Ah. (1169)
    rahwana.middleFront();
    delay(1708 - 1200);

    // (1708) How shameful and sinful is this ape. (4081)
    rahwana.directControl(3, 180, 500);
    rahwana.directControl(4, 140, 200);
    delay(4809 - 1708 - 500 - 200);

    // (4809) Alright, (5339)
    rahwana.downFront();
    delay(5843 - 4809 - 700);

    // (5843) he is courageous and mighty, (7632)
    rahwana.middleFront();
    delay(8315 - 5843 - 1200);

    // (8315) because he is the son of Bali, (10005)
    rahwana.lower_pointToFront();
    delay(10571 - 8315 - 700);

    // (10571) but he is talking utter rubbish (12951)
    for (int i = 0; i < 5; i++)
    {
        rahwana.directControl(3, 150, 200);
        rahwana.directControl(3, 120, 200);
    }
    delay(13925 - 10571 - 2000);

    // (13295) and has no shame before people who know (16656) that he is debased. (18369)
    rahwana.downFront();
    rahwana.directControl(4, 65, 200);
    rahwana.directControl(3, 179, 500);
    delay(16656 - 13295 - 700 - 200 - 500);
    rahwana.downFront();
    rahwana.pointToFront();
    delay(19263 - 16656 - 700 - 900);

    // (19263) He talks about the power of dignity, (21573)
    rahwana.lower_pointToFront();
    delay(22113 - 19263 - 700);

    // (22113) while he himself (23497) is the destroyer of the greatest dignity. (26553)
    rahwana.directControl(3, 180, 500);
    rahwana.directControl(4, 140, 200);
    delay(23497 - 22113 - 500 - 200);
    rahwana.downFront();
    rahwana.directControl(4, 65, 200);
    rahwana.directControl(3, 179, 500);
    delay(27416 - 23497 - 700 - 200 - 500 - (700));
    rahwana.downFront();

    // (27416) You are dumb and arrogant (29528) and uncontrolled. (30652)
    rahwana.pointToFront();
    delay(29528 - 27416 - 900);
    rahwana.lower_pointToFront();
    delay(31416 - 29528 - 700);

    // (31416) You have a debased mind, (33259)
    rahwana.directControl(3, 180, 500);
    rahwana.directControl(4, 140, 200);
    for (int i = 0; i < 3; i++)
    {
        rahwana.directControl(3, 150, 200);
        rahwana.directControl(3, 180, 200);
    }
    delay(33762 - 31416 - 500 - 200 - 1200);

    // (33762) because you serve the despised enemy. (36423)
    rahwana.middleFront();
    delay(37079 - 33762 - 1200);

    // (37079) It does not penetrate into your skull (39569)
    rahwana.directControl(3, 180, 500);
    rahwana.directControl(4, 140, 200);
    delay(39911 - 37079 - 500 - 200);

    // (39911) about the death of your father. (41681)
    rahwana.downFront();
    delay(42338 - 39911 - 700);

    // (42338) You ape, (43194)
    rahwana.lower_pointToFront();
    delay(43668 - 42338 - 700);

    // (43668) betrayer of teachers (45259)
    rahwana.directControl(3, 180, 500);
    rahwana.directControl(4, 140, 200);
    delay(45556 - 43668 - 500 - 200);

    // (45556) will go to hell. (46818)
    rahwana.downFront();
    delay(47605 - 45556 - 700 - (500));

    // (47605) You are bad (48594) through and through (49807) and now you ask me to follow suit. (51731)
    rahwana.middleFront();
    delay(48594 - 47605 - (1200 - 500));
    rahwana.directControl(3, 180, 500);
    rahwana.directControl(4, 140, 200);
    delay(49807 - 48594 - 500 - 200);
    rahwana.downFront();
    delay(52684 - 49807 - 700);

    // (52684) You think I am so dumb (54275)
    rahwana.pointToFront();
    delay(54616 - 52684 - 900 - (700));
    rahwana.downFront();

    // (54616) that you can talk me into doing it. (56504)
    delay(300);
    rahwana.pointToSelf();
    delay(57223 - 54616 - 300 - 1100);

    // (57223) Even if God tells me to return Sita to Raghusuta, (60935)
    rahwana.downFront();
    rahwana.pointToFront();
    delay(61349 - 57223 - 700 - 900);

    // (61349) I will refuse, (62527)
    rahwana.lower_pointToFront();
    delay(62922 - 61349 - 700);

    // (62922) least of all you. (64286)
    rahwana.downFront();
    delay(65052 - 62922 - 700);

    // (65052) Go home, quickly. (66097)
    rahwana.lower_pointToFront();
    delay(66473 - 65052 - 700);

    // (66473) Tell your master (67614) that I refuse (69097) and urge him to attack me. (71057)
    rahwana.directControl(3, 180, 500);
    rahwana.directControl(4, 140, 200);
    delay(67614 - 66473 - 500 - 200);
    rahwana.lower_pointToFront();
    delay(69097 - 67614 - 700);
    rahwana.directControl(3, 180, 500);
    rahwana.directControl(4, 140, 200);
    delay(71623 - 69097 - 500 - 200);

    // (71623) Let him start. (72567)
    rahwana.lower_pointToFront();
    delay(74467 - 71623 - 700);

    // (74467) Even if a thousand Ramas come to the attack, (75974)
    rahwana.downFront();
    delay(76378 - 74467 - 700 - (500));

    // (76378) I will not be afraid, (77897)
    rahwana.pointToSelf();
    delay(78392 - 76378 - (1100 - 500));

    // (78392) let alone him alone (79974) with the monkeys. (81080)
    rahwana.downFront();
    delay(79974 - 78392 - 700);
    rahwana.middleFront();
    delay(81511 - 79974 - 1200);

    // (81511) Even hunters can take care of you. (84283)
    rahwana.directControl(3, 180, 500);
    rahwana.directControl(4, 140, 200);
    delay(84283 - 81511 - 500 - 200);

    SoundSystem::playMusicWayang();
    rahwana.downFront();
    anggada.defaultStandPosition();
    rahwana.defaultStandPosition();

    anggada.walk_to_a_certain_distance_before_calibrating_value(150);
    rama_wijaya.walk_to_a_certain_distance_before_calibrating_value(330);

    /*Night before battle*/
    /*Angada: 045*/
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_5, SoundSystem::EPISODE_5_DIALOG::NIGHT_BEFORE_BATTLE_ANGGADA1);

    // langsung jalan
    //  (1002) My lord, (1574)
    anggada.pointToSelf();
    delay(2040 - 900);

    // (2040) it seems that Rawana will not see reason, (4779) he has insulted me (6064) as well as my lord. (7687)
    anggada.downFront();
    delay(4779 - 2040 - 700);
    anggada.lower_pointToFront();
    delay(6064 - 4779 - 700);
    anggada.directControl(1, 5, 500);
    anggada.directControl(2, 35, 200);
    delay(7687 - 6064 - 500 - 200);
    delay(2000);
    anggada.downFront();

    /*Rama: 046*/
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_5, SoundSystem::EPISODE_5_DIALOG::NIGHT_BEFORE_BATTLE_RAMA1);

    delay(1260 - (500));
    // (1260) I see, (1986)
    rama_wijaya.middleFront();
    delay(2331 - 1260 - (1200 - 500));

    // (2331) order the monkeys to eat up their fill and prepare for tomorrow’s battle. (6540)
    rama_wijaya.directControl(1, 0, 500);
    rama_wijaya.directControl(2, 10, 200);
    delay(6540 - 2331 - 500 - 200 - (700));
    rama_wijaya.downFront();
    delay(2000);

    /*Angada: 047*/
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_5, SoundSystem::EPISODE_5_DIALOG::NIGHT_BEFORE_BATTLE_ANGGADA2);

    delay(1113);
    // (1113) As you wish, my lord. (2891)
    anggada.pointToSelf();
    delay(2891 - 1113 - 900);
    anggada.downFront();

    SoundSystem::playMusicWayang();
    anggada.defaultStandPosition();
    rama_wijaya.defaultStandPosition();

    /* Last Battle */

    // *Rama, Laksmana, Wibhisana step forward*

    // *Rawana step forward*

    // *Rawana gets wombo comboed*

    /*
        Rama fight first, pushing Rahwana back a little bit
        Laskmana flank, pushing Rahwana front a little bit
        Wibhisana fight like rama, pushing Rahwana back a little bit
        Rama one tap finishing Rahwana, ded
     */

    /* Rama fight first, pushing Rahwana back a little bit */
    rama_wijaya.walk_to_a_certain_distance_before_calibrating_value(200);
    rahwana.walk_to_a_certain_distance_before_calibrating_value(200);

    xTaskCreate(RamaFirstAttackTask, "RamaFirstAttackTask", fighting_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(RahwanaFirstDefendTask, "RahwanaFirstDefendTask", fighting_STACK_SIZE, NULL, 1, NULL);

    vTaskSuspend(episodeTaskHandler[4]);

    rahwana.walk_to_a_certain_distance_before_calibrating_value(150);
    rahwana.downFront();
    rama_wijaya.downFront();
    rama_wijaya.defaultStandPosition();
    rahwana.walk_to_a_certain_distance_before_calibrating_value(270);

    /* Laskmana flank, pushing Rahwana front a little bit */
    laksmana.walk_to_a_certain_distance_before_calibrating_value(200);
    laksmana.pointToFront();

    rahwana.walk_to_a_certain_distance_before_calibrating_value(290);
    laksmana.downFront();
    laksmana.defaultStandPosition();

    /* Wibhisana fight like rama, pushing Rahwana back a little bit */
    rahwana.walk_to_a_certain_distance_before_calibrating_value(210);
    wibhisana.walk_to_a_certain_distance_before_calibrating_value(240);

    xTaskCreate(WibhisanaFirstAttackTask, "WibhisanaFirstAttackTask", fighting_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(RahwanaSecondDefendTask, "RahwanaFirstDefendTask", fighting_STACK_SIZE, NULL, 1, NULL);

    vTaskSuspend(episodeTaskHandler[4]);

    rahwana.walk_to_a_certain_distance_before_calibrating_value(200);
    rahwana.downFront();
    wibhisana.downFront();
    wibhisana.defaultStandPosition();

    /* Rama one tap finishing Rahwana, ded */
    rahwana.walk_to_a_certain_distance_before_calibrating_value(180);
    rama_wijaya.walk_to_a_certain_distance_before_calibrating_value(270);

    rama_wijaya.pointToFront();
    rahwana.walk_to_a_certain_distance_before_calibrating_value(150);
    rama_wijaya.downFront();

    /* Rawana: 048*/
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_5, SoundSystem::EPISODE_5_DIALOG::AFTER_BATTLE_RAHWANA1);

    // langsung jalan
    //  (487) *eugh..* (1187)
    rahwana.pointToSelf();
    delay(2000);

    SoundSystem::playMusicWayang();
    rahwana.defaultStandPosition();
    rahwana.downFront();
    rama_wijaya.walk_to_a_certain_distance_before_calibrating_value(150);
    wibhisana.walk_to_a_certain_distance_before_calibrating_value(300);

    /*Wibhisana: 049 */
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_5, SoundSystem::EPISODE_5_DIALOG::AFTER_BATTLE_WIBHISANA1);

    delay(1749);
    // (355) *sobbing*
    // (1749) My brother, O, Dasanana. (3694) Look at me (4470) and forgive me. (5484)
    wibhisana.pointToFront();
    delay(3694 - 1749 - 900);
    wibhisana.lower_pointToFront();
    delay(4470 - 3694 - 700);
    wibhisana.downFront();
    delay(5748 - 4470 - 700);

    // (5748) Let me not suffer, because I left you, (7704)
    wibhisana.pointToSelf();
    delay(7978 - 5748 - 900);

    // (7978) since I went to an unselfish person, (10330) and my purpose was the weal of others. (13056)
    wibhisana.directControl(1, 130, 1000); // df 2x lambat
    wibhisana.directControl(2, 70, 400);
    delay(10330 - 7978 - 1400);
    wibhisana.directControl(1, 90, 1000); // lptf 2x lambat
    wibhisana.directControl(2, 80, 400);
    delay(13518 - 10330 - 1400);

    // (13518) I chose to be the servant of a great and noble person, (17025) who cared for the whole world. (18804)
    wibhisana.pointToSelf();
    delay(17025 - 13518 - 900);
    wibhisana.directControl(1, 130, 1000); // df 2x lambat
    wibhisana.directControl(2, 70, 400);
    delay(19600 - 17025 - 1400);

    // (19600) What makes me cry is only that you die because of misguidance. (23259)
    wibhisana.directControl(2, 75, 400); // ptf 2x lambat
    wibhisana.directControl(1, 5, 1000);
    wibhisana.directControl(2, 35, 400);
    delay(23609 - 19600 - 400 - 1000 - 400);

    // (23609) You did not follow my good advice in the council formerly, (26777) because of disinclination. (28211)
    wibhisana.directControl(1, 90, 1000); // lptf 2x lambat
    wibhisana.directControl(2, 80, 400);
    delay(26777 - 23609 - 1000 - 400);
    wibhisana.directControl(1, 130, 1000); // df 2x lambat
    wibhisana.directControl(2, 70, 400);
    delay(28627 - 26777 - 1000 - 400);

    // (28627) Now you can see the result of the words of Prahasta, (31774)
    wibhisana.directControl(2, 75, 400); // ptf 2x lambat
    wibhisana.directControl(1, 5, 1000);
    wibhisana.directControl(2, 35, 400);
    delay(32166 - 28627 - 1800);

    // (32166) your death (33011) has come. (33852)
    wibhisana.directControl(1, 130, 1000); // df 2x lambat
    wibhisana.directControl(2, 70, 400);
    delay(35043 - 32166 - 1000 - 400);

    // (35043) From the beginning (36118) this result has been clearly seen. (38196)
    wibhisana.lower_pointToFront();
    delay(36118 - 35043 - 700);
    wibhisana.downFront();
    delay(39276 - 36118 - 700);

    // (39276) My devotion to religion is confirmed now, since I see the fruit of your misguided deeds. (44927) See what you obtain because you were so obstinate, (47740) your death.(48815)
    wibhisana.pointToSelf();
    delay(44927 - 39276 - 900);
    wibhisana.directControl(1, 130, 1000); // df 2x lambat
    wibhisana.directControl(2, 70, 400);
    delay(47740 - 44927 - 1000 - 400);
    wibhisana.pointToFront();
    delay(50264 - 47740 - 900);

    // (50264) You had taken wrong counsel; (52053) you disappointed me in the council. (53873)
    wibhisana.lower_pointToFront();
    delay(52053 - 50264 - 700);
    wibhisana.downFront();
    delay(54263 - 52053 - 700);

    // (54263) Even though my advice was a good one (56438) you did not take it. (57598)
    wibhisana.pointToSelf();
    delay(56438 - 54263 - 900);
    wibhisana.downFront();
    delay(58039 - 56438 - 700);

    // (58039) I had the development of your wellbeing at heart, (60654)
    wibhisana.middleFront();
    delay(61024 - 58039 - 1200);

    // (61024) when I gave you that good advice, (63437) but you were out of your mind, because of your eagerness (66397) to fight. (66914)
    wibhisana.directControl(1, 5, 500);
    wibhisana.directControl(2, 35, 200);
    delay(63437 - 61024 - 500 - 200);
    wibhisana.lower_pointToFront();
    delay(66397 - 63437 - 700);
    wibhisana.downFront();
    delay(67370 - 66397 - 700);

    // (67370) Because of your lack of love (68947) and your great anger, (70204)
    wibhisana.pointToFront();
    delay(68947 - 67370 - 900);
    wibhisana.downFront();
    delay(70563 - 68947 - 700);

    // (70563) my mind was very much perturbed (72342) and tortured, (73305) as you did not obey the guidance of a wise man. (75875)
    wibhisana.pointToSelf();
    delay(72342 - 70563 - 900);
    wibhisana.downFront();
    delay(73305 - 72342 - 700);
    wibhisana.pointToFront();
    delay(76752 - 73305 - 900);

    // (76752) Indeed, I was correct to think that you were wrong (79910) in disobeying wise people, (81790) because one who had insulted his elders (84309) and was cruel (85277) and malicious, (86286)
    wibhisana.directControl(1, 130, 1000); // df 2x lambat
    wibhisana.directControl(2, 70, 400);
    delay(79910 - 76752 - 1000 - 400);
    wibhisana.directControl(1, 90, 1000); // lptf 2x lambat
    wibhisana.directControl(2, 80, 400);
    delay(81790 - 79910 - 1000 - 400);
    wibhisana.directControl(1, 5, 1000);
    wibhisana.directControl(2, 35, 400);
    delay(84309 - 81790 - 1000 - 400);
    wibhisana.lower_pointToFront();
    delay(85277 - 84309 - 700);
    wibhisana.downFront();
    delay(86595 - 85277 - 700);

    // (86595) his well-being (87796) and good life disappeared whilst his sorrow and death were near. (91157)
    wibhisana.middleFront();
    wibhisana.directControl(1, 5, 1000);
    wibhisana.directControl(2, 35, 400);
    delay(91552 - 86595 - 1200 - 1000 - 400);

    // (91552) Ah! My brother. (92931) This is the result when you have reached the ultimate of (95972) ingloriousness. (97051)
    wibhisana.lower_pointToFront();
    wibhisana.downFront();
    delay(95972 - 91552 - 700 - 700);
    wibhisana.lower_pointToFront();
    delay(97051 - 95972 - 700);
    wibhisana.downFront();

    /* Rama: 050*/
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_5, SoundSystem::EPISODE_5_DIALOG::AFTER_BATTLE_RAMA1);

    delay(1961 - (300));
    // (1961) Wibhisana, (2520)
    rama_wijaya.pointToFront();
    delay(2899 - 1961 - (1200 - 300));

    // (2899) it is enough. (3345)
    rama_wijaya.lower_pointToFront();
    delay(3859 - 2899 - 700);

    // (3859) Do not be so sad, (5243) because Dasasya has died with honor. (7565)
    rama_wijaya.directControl(1, 0, 500);
    rama_wijaya.directControl(2, 10, 200);
    delay(5243 - 3859 - 500 - 200);
    rama_wijaya.lower_pointToFront();
    delay(8295 - 5243 - 700);

    // (8295) He was known to have performed asceticism and was a renowned universal monarch. (13173)
    rama_wijaya.downFront();
    delay(200);
    rama_wijaya.middleFront();
    delay(13638 - 8295 - 700 - 200 - 1200);

    // (13638) He died in fierce combat. (15135)
    rama_wijaya.downFront();
    delay(15693 - 13638 - 700);

    // (15693) Whoever dies in battle (17461) goes to heaven. (18457)
    rama_wijaya.lower_pointToFront();
    delay(17461 - 15693 - 700);
    rama_wijaya.directControl(1, 0, 500);
    rama_wijaya.directControl(2, 10, 200);
    delay(18813 - 17461 - 500 - 200);

    // (18813) You should not grieve over him, (20613) because he died in great glory in the battlefield. (23276)
    rama_wijaya.lower_pointToFront();
    delay(20613 - 18813 - 700);
    rama_wijaya.directControl(1, 0, 500);
    rama_wijaya.directControl(2, 10, 200);
    delay(23867 - 20613 - 500 - 200);

    // (23867) On the other hand you must succeed him as king, (26784)
    rama_wijaya.downFront();
    rama_wijaya.middleFront();
    delay(27135 - 23867 - 700 - 1200);

    // (27135) because your excellent virtues are truly faultless. (29831)
    rama_wijaya.directControl(1, 0, 500);
    rama_wijaya.directControl(2, 10, 200);
    delay(30318 - 27135 - 500 - 200);

    // (30318) Rebuild (31058) and beautify the whole country of Lenka. (33321)
    for (int i = 0; i < 5; i++)
    {
        rama_wijaya.directControl(1, 30, 300);
        rama_wijaya.directControl(1, 0, 300);
    }
    delay(33654 - 30318 - 3000);

    // (33654) You will be the ruler over the demons. (36134)
    rama_wijaya.lower_pointToFront();
    delay(36504 - 33654 - 700);

    // (36504) Make the evil-minded demons realize their wrongdoings by good examples (41188) and devotion to religion. (42910)
    rama_wijaya.directControl(1, 0, 500);
    rama_wijaya.directControl(2, 10, 200);
    for (int i = 0; i < 5; i++)
    {
        rama_wijaya.directControl(1, 30, 300);
        rama_wijaya.directControl(1, 0, 300);
    }
    delay(41188 - 36504 - 500 - 200 - 3000);
    rama_wijaya.lower_pointToFront();
    delay(42910 - 41188 - 700);

    SoundSystem::playMusicWayang();
    rama_wijaya.defaultStandPosition();
    wibhisana.defaultStandPosition();

    rama_wijaya.walk_to_a_certain_distance_before_calibrating_value(150);
    sita.walk_to_a_certain_distance_before_calibrating_value(330);

    /* Reunion*/
    /* Rama: 051*/
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_5, SoundSystem::EPISODE_5_DIALOG::REUNION_RAMA1);

    // langsung jalan
    //  (621) Sita! (1388)
    rama_wijaya.pointToFront();
    delay(1796 - 1200);

    // (1796) How long have I waited to be with you once more, (5059) I’m glad (6106) you’re safe. (6903)
    rama_wijaya.downFront();
    delay(5059 - 1796 - 700);
    rama_wijaya.pointToSelf();
    delay(6903 - 5059 - 900);

    /* Sita: 052 */
    SoundSystem::playDialogFromACertainFolder(SoundSystem::EPISODE_NUMBER::EPISODE_5, SoundSystem::EPISODE_5_DIALOG::REUNION_SITA1);

    delay(420);
    // (420) Oh I have longed to be in your presence again Rama. (3576)
    sita.lower_pointToFront();
    delay(3954 - 700 - (700));
    sita.downFront();

    // (3954) Please, take me home to Ayodhya. (6058)
    delay(300);
    sita.pointToSelf();
    delay(6058 - 3954 - 300 - 1400);
    delay(2000);

    SoundSystem::playMusicWayang();

    rama_wijaya.downFront();
    sita.downFront();
    rama_wijaya.defaultStandPosition();
    sita.defaultStandPosition();

    SoundSystem::playDialogFromACertainFolder(SoundSystem::INDICATOR_SOUND, SoundSystem::INDICATOR_SOUND_NUMBER::INDICATOR_FINISHED_SHOWING);
    delay(2000);

    // *end*
}

void Episodes::Episode_Extra()
{
    /* put the scene debug code below */
}

void Episodes::Episode_1_task(void *pvParameters)
{
    currentEpisode = 1;
    Serial.print(F("Current Episode: "));
    Serial.println(currentEpisode);
    while (1)
    {
        Episode_1();
        vTaskResume(mainLoopTaskHandler);
        // isEpisodeTaskCreated = false;
        backToEpisodeSelection();
        vTaskDelete(NULL);
    }
}

void Episodes::Episode_2_task(void *pvParameters)
{
    currentEpisode = 2;
    Serial.print(F("Current Episode: "));
    Serial.println(currentEpisode);
    while (1)
    {
        Episode_2();
        vTaskResume(mainLoopTaskHandler);
        // isEpisodeTaskCreated = false;
        backToEpisodeSelection();
        vTaskDelete(NULL);
    }
}

void Episodes::Episode_3_task(void *pvParameters)
{
    currentEpisode = 3;
    Serial.print(F("Current Episode: "));
    Serial.println(currentEpisode);
    while (1)
    {
        Episode_3();
        vTaskResume(mainLoopTaskHandler);
        // isEpisodeTaskCreated = false;
        backToEpisodeSelection();
        vTaskDelete(NULL);
    }
}

void Episodes::Episode_4_task(void *pvParameters)
{
    currentEpisode = 4;
    Serial.print(F("Current Episode: "));
    Serial.println(currentEpisode);
    while (1)
    {
        Episode_4();
        vTaskResume(mainLoopTaskHandler);
        // isEpisodeTaskCreated = false;
        backToEpisodeSelection();
        vTaskDelete(NULL);
    }
}

void Episodes::Episode_5_task(void *pvParameters)
{
    currentEpisode = 5;
    Serial.print(F("Current Episode: "));
    Serial.println(currentEpisode);
    while (1)
    {
        Episode_5();
        vTaskResume(mainLoopTaskHandler);
        // isEpisodeTaskCreated = false;
        backToEpisodeSelection();
        vTaskDelete(NULL);
    }
}

void Episodes::Extra_Debug_task(void *pvParameters)
{
    currentEpisode = 6;
    Serial.println(F("Currently in debugging a scene!"));
    while (1)
    {
        Episode_Extra();
        vTaskResume(mainLoopTaskHandler);
        backToEpisodeSelection();
        vTaskDelete(NULL);
    }
}