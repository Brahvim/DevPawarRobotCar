#pragma once

#include <Servo.h>
#include <AFMotor.h>

#include "CarConfig.h"

#define PIN_DIGITAL_SERVO               10

#define PIN_ANALOG_BUZZER               A2
#define PIN_ANALOG_ULTRASONIC_ECHO      A1
#define PIN_ANALOG_ULTRASONIC_TRIGGER   A0

enum CarStopReason {

	CAR_STOP_REASON_UNKNOWN,
	CAR_STOP_REASON_NO_PATH,
	CAR_STOP_REASON_SENSOR_TRIGGER_DISCONNECTED,

};

extern Servo g_carServo;
extern AF_DCMotor g_carMotors[4];
extern CarStopReason g_carStopReason;

void carModeCbck();
unsigned long carUltrasonicSensorRead();
