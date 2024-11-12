#pragma once

#include <Servo.h>
#include <AFMotor.h>

#include "CarConfig.h"

enum CarStopReason {

	CAR_STOP_REASON_UNKNOWN,
	CAR_STOP_REASON_NO_PATH,
	CAR_STOP_REASON_SENSOR_TRIGGER_DISCONNECTED,

};

extern Servo g_carServo;
extern AF_DCMotor g_carMotors[4];

void carModeSwitch();
void carModeSetController();
void carModeSetObstacleAvoidance();

unsigned long carSensorUltrasonicRead();

void carMoveLeftOnSpot();
void carMoveRightOnSpot();

void carMoveStop(); void carMoveStop(unsigned long const durationMs);

void carMoveLeft(); void carMoveLeft(unsigned long const durationMs);
void carMoveRight(); void carMoveRight(unsigned long const durationMs);

void carMoveForwards(); void carMoveForwards(unsigned long const durationMs);
void carMoveBackwards(); void carMoveBackwards(unsigned long const durationMs);
