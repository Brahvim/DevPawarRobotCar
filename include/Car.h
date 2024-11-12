#pragma once

#include <Servo.h>
#include <AFMotor.h>

#define PIN_DIGITAL_SERVO               10

#define PIN_ANALOG_ULTRASONIC_TRIGGER   A0
#define PIN_ANALOG_ULTRASONIC_ECHO      A1
#define PIN_ANALOG_BUZZER               A2

extern AF_DCMotor g_carMotors[4];
extern Servo g_carServo;
