#ifndef MAINHEADER_H
#define MAINHEADER_H

// LCD 20x4 & ROTARY ENCODER
#define SCL_PIN 21
#define SDA_PIN 20
#define OUTPUT_A 3
#define OUTPUT_B 12   
#define BUTTON_ROTARY 2

// Servo SG90
#define LEFT_SERVO_1 22
#define LEFT_SERVO_2 24
#define LEFT_SERVO_3 26
#define LEFT_SERVO_4 28

#define RIGHT_SERVO_1 23
#define RIGHT_SERVO_2 25
#define RIGHT_SERVO_3 27
#define RIGHT_SERVO_4 29

// NEMA-17 & A4988
#define NEMA_STEP 9
#define NEMA_DIR 8

#define EN_NEMA_1 30
#define EN_NEMA_2 32
#define EN_NEMA_3 34
#define EN_NEMA_4 36
#define EN_NEMA_5 38
#define EN_NEMA_6 40
#define EN_NEMA_7 42
#define EN_NEMA_8 44
#define EN_NEMA_9 46
#define EN_NEMA_10 48

// DF MINI PLAYER
#define RXD2_PIN 17
#define TXD2_PIN 16

// WAYANG HAND SWITCH (IRLML2502 MOSFET)
#define WAYANG_HAND_1 31
#define WAYANG_HAND_2 33
#define WAYANG_HAND_3 35
#define WAYANG_HAND_4 37
#define WAYANG_HAND_5 39
#define WAYANG_HAND_6 41
#define WAYANG_HAND_7 43
#define WAYANG_HAND_8 45
#define WAYANG_HAND_9 47
#define WAYANG_HAND_10 49

// VL53L0X XSHUTS
#define XSHUT_1 54
#define XSHUT_2 55
#define XSHUT_3 56
#define XSHUT_4 57
#define XSHUT_5 58
#define XSHUT_6 59
#define XSHUT_7 60
// #define XSHUT_8 61
// #define XSHUT_9 62
// #define XSHUT_10 63



#include <Arduino.h>
#include <Wire.h>


#endif //MAINHEADER_H