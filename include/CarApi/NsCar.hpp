#pragma once

#define LEAST_DISTANCE_FOR_OBSTACLES_CM 20

#include <AFMotor.h>

namespace NsCar {

	extern AF_DCMotor motors[4];

	void stop();
	void moveLeftAsync();
	void moveRightAsync();
	void moveForwardAsync();
	void moveBackwardAsync();

	void stop(const unsigned long forHowLongInMs);
	void moveForward(const unsigned long forHowLongInMs);
	void moveBackward(const unsigned long forHowLongInMs);
	void moveLeftOnSpot(const unsigned long forHowLongInMs);
	void moveRightOnSpot(const unsigned long forHowLongInMs);

}
