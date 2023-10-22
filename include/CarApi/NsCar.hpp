#pragma once

#include <AFMotor.h>

namespace NsCar {

	extern AF_DCMotor dcMotors[4];

	void stop();
	void moveLeft();
	void moveRight();
	void moveForward();
	void moveBackward();

}
