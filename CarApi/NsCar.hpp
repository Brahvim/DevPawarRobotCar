#pragma once

#include "NsUltrasonic.hpp"

#include <AFMotor.h>

namespace NsCar {

	extern const AF_DCMotor dcMotors[4];

	void stop();
	void moveLeft();
	void moveRight();
	void moveForward();
	void moveBackward();

}
