#pragma once

#define LEAST_DISTANCE_FOR_OBSTACLES 20

#include <AFMotor.h>

namespace NsCar {

	extern const AF_DCMotor arrayOfDcMotors[4];
	extern AF_DCMotor dcMotor1, dcMotor2, dcMotor3, dcMotor4;

	void stop();
	void moveRight();
	void moveLeft();
	void moveForward();
	void moveBackward();

	void stop(const unsigned long forHowLongInMs);
	void moveRight(const unsigned long forHowLongInMs);
	void moveLeft(const unsigned long forHowLongInMs);
	void moveForward(const unsigned long forHowLongInMs);
	void moveBackward(const unsigned long forHowLongInMs);

}
