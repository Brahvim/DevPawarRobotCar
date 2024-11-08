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

	void stop(const unsigned long durationMs);
	void moveLeft(const unsigned long durationMs);
	void moveRight(const unsigned long durationMs);
	void moveForward(const unsigned long durationMs);
	void moveBackward(const unsigned long durationMs);
	void moveLeftOnSpot(const unsigned long durationMs);
	void moveRightOnSpot(const unsigned long durationMs);

}
