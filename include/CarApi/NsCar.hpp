#pragma once

#define LEAST_DISTANCE_FOR_OBSTACLES_CM 20

#include <AFMotor.h>

namespace NsCar {

	extern bool g_wasForwards;
	extern AF_DCMotor motors[4];

	void stop();
	void moveLeftAsync();
	void moveRightAsync();
	void moveForwardAsync();
	void moveBackwardAsync();
	void moveLeftOnSpotAsync();
	void moveRightOnSpotAsync();

	void stop(unsigned long const durationMs);
	void moveLeft(unsigned long const durationMs);
	void moveRight(unsigned long const durationMs);
	void moveForward(unsigned long const durationMs);
	void moveBackward(unsigned long const durationMs);
	void moveLeftOnSpot(unsigned long const durationMs);
	void moveRightOnSpot(unsigned long const durationMs);

}
