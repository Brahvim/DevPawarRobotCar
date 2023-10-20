#pragma once

#include <AFMotor.h>

namespace NsCar {

	AF_DCMotor dcMotors[4] = {
		(void*)0,
		(void*)0,
		(void*)0,
		(void*)0,
	};

	void stop();
	void moveLeft();
	void moveRight();
	void moveForward();
	void moveBackward();

}
