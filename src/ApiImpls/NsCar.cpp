#define ENABLE_DEBUG_LOGS

#include "../include/Api/DebuggingMacros.hpp"

#include "AFMotor.h"
#include "../include/CarApi/NsCar.hpp"
#include "../include/CarApi/NsUltrasonic.hpp"

namespace NsCar {

	AF_DCMotor dcMotors[4] = {
		AF_DCMotor(1),
		AF_DCMotor(2),
		AF_DCMotor(3),
		AF_DCMotor(4),
	};

	void stop() {
		DEBUG_PRINTLN("Stop"); // "Car is stopping.");
		NsCar::dcMotors[1].run(RELEASE);
		NsCar::dcMotors[2].run(RELEASE);
		NsCar::dcMotors[3].run(RELEASE);
		NsCar::dcMotors[4].run(RELEASE);
	}

	void moveLeft() {
		DEBUG_PRINTLN("Left"); // "Car is going left.");
		NsCar::dcMotors[1].run(FORWARD);
		NsCar::dcMotors[2].run(FORWARD);
		NsCar::dcMotors[3].run(BACKWARD);
		NsCar::dcMotors[4].run(BACKWARD);
	}

	void moveRight() {
		DEBUG_PRINTLN("Right"); // "Car is going right.");
		NsCar::dcMotors[1].run(BACKWARD);
		NsCar::dcMotors[2].run(BACKWARD);
		NsCar::dcMotors[3].run(FORWARD);
		NsCar::dcMotors[4].run(FORWARD);
	}

	void moveForward() {
		DEBUG_PRINTLN("For"); // "Car is going forwards.");
		NsCar::dcMotors[1].run(FORWARD);
		NsCar::dcMotors[2].run(FORWARD);
		NsCar::dcMotors[3].run(FORWARD);
		NsCar::dcMotors[4].run(FORWARD);
	}

	void moveBackward() {
		DEBUG_PRINTLN("Back"); // "Car is going backwards.");
		NsCar::dcMotors[1].run(BACKWARD);
		NsCar::dcMotors[2].run(BACKWARD);
		NsCar::dcMotors[3].run(BACKWARD);
		NsCar::dcMotors[4].run(BACKWARD);
	}

}
