#include "NsCar.hpp"

namespace NsCar {
	const AF_DCMotor dcMotors[4] = {
		AF_DCMotor(1),
		AF_DCMotor(2),
		AF_DCMotor(3),
		AF_DCMotor(4),
	};

	void stop() {
		NsCar::dcMotors[1].run(RELEASE);
		NsCar::dcMotors[2].run(RELEASE);
		NsCar::dcMotors[3].run(RELEASE);
		NsCar::dcMotors[4].run(RELEASE);
	}

	void moveLeft() {
		NsCar::dcMotors[1].run(FORWARD);
		NsCar::dcMotors[2].run(FORWARD);
		NsCar::dcMotors[3].run(BACKWARD);
		NsCar::dcMotors[4].run(BACKWARD);
	}

	void moveRight() {
		NsCar::dcMotors[1].run(BACKWARD);
		NsCar::dcMotors[2].run(BACKWARD);
		NsCar::dcMotors[3].run(FORWARD);
		NsCar::dcMotors[4].run(FORWARD);
	}

	void moveForward() {
		NsCar::dcMotors[1].run(FORWARD);
		NsCar::dcMotors[2].run(FORWARD);
		NsCar::dcMotors[3].run(FORWARD);
		NsCar::dcMotors[4].run(FORWARD);
	}

	void moveBackward() {
		NsCar::dcMotors[1].run(BACKWARD);
		NsCar::dcMotors[2].run(BACKWARD);
		NsCar::dcMotors[3].run(BACKWARD);
		NsCar::dcMotors[4].run(BACKWARD);
	}

}
