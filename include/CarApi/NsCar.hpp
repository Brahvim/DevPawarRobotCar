#pragma once

#include <AFMotor.h>

namespace NsCar {

	extern AF_DCMotor dcMotor1, dcMotor2, dcMotor3, dcMotor4;

	void stop();
	void moveLeft();
	void moveRight();
	void moveForward();
	void moveBackward();

}
