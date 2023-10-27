#include <AFMotor.h>
#include <ArduinoSTL.h>

#include "../include/Api/DebuggingMacros.hpp"
#include "../include/CarApi/NsCar.hpp"
#include "../include/CarApi/NsUltrasonic.hpp"

namespace NsCar {

	AF_DCMotor dcMotor1(1), dcMotor2(2), dcMotor3(3), dcMotor4(4);
	const AF_DCMotor arrayOfDcMotors[4] = {
		NsCar::dcMotor1,
		NsCar::dcMotor2,
		NsCar::dcMotor3,
		NsCar::dcMotor4,
	};

	/*

	Group A: 1 and 3.
	Group B: 2 and 4.

	Diag-right-up: 1 and 4 go CW.
	Right: 1 and 4 are already CW.

	*/

	void stop(const unsigned long p_forMs) {
		DEBUG_PRINTLN("Stop"); // "Car is stopping.");
		NsCar::dcMotor1.run(RELEASE);
		NsCar::dcMotor2.run(RELEASE);
		NsCar::dcMotor3.run(RELEASE);
		NsCar::dcMotor4.run(RELEASE);
		delay(p_forMs);
	}

	void moveRight(const unsigned long p_forMs) {
		DEBUG_PRINTLN("Left"); // "Car is going left.");
		NsCar::dcMotor1.run(FORWARD);
		NsCar::dcMotor2.run(FORWARD);
		NsCar::dcMotor3.run(BACKWARD); // Anti-CW.
		NsCar::dcMotor4.run(BACKWARD); // Anti-CW.
		delay(p_forMs);
	}

	void moveLeft(const unsigned long p_forMs) {
		DEBUG_PRINTLN("Right"); // "Car is going right.");
		NsCar::dcMotor1.run(BACKWARD); // Anti-CW.
		NsCar::dcMotor2.run(BACKWARD); // Anti-CW.
		NsCar::dcMotor3.run(FORWARD);
		NsCar::dcMotor4.run(FORWARD);
		delay(p_forMs);
	}

	void moveForward(const unsigned long p_forMs) {
		DEBUG_PRINTLN("For"); // "Car is going forwards.");
		NsCar::dcMotor1.run(FORWARD);
		NsCar::dcMotor2.run(FORWARD);
		NsCar::dcMotor3.run(FORWARD);
		NsCar::dcMotor4.run(FORWARD);
		delay(p_forMs);
	}

	void moveBackward(const unsigned long p_forMs) {
		DEBUG_PRINTLN("Back"); // "Car is going backwards.");
		NsCar::dcMotor1.run(BACKWARD);
		NsCar::dcMotor2.run(BACKWARD);
		NsCar::dcMotor3.run(BACKWARD);
		NsCar::dcMotor4.run(BACKWARD);
		delay(p_forMs);
	}

	void stop() {
		DEBUG_PRINTLN("Stop"); // "Car is stopping.");
		NsCar::dcMotor1.run(RELEASE);
		NsCar::dcMotor2.run(RELEASE);
		NsCar::dcMotor3.run(RELEASE);
		NsCar::dcMotor4.run(RELEASE);
	}

	void moveRight() {
		DEBUG_PRINTLN("Left"); // "Car is going left.");
		NsCar::dcMotor1.run(FORWARD);
		NsCar::dcMotor2.run(FORWARD);
		NsCar::dcMotor3.run(BACKWARD); // Anti-CW.
		NsCar::dcMotor4.run(BACKWARD); // Anti-CW.
	}

	void moveLeft() {
		DEBUG_PRINTLN("Right"); // "Car is going right.");
		NsCar::dcMotor1.run(BACKWARD); // Anti-CW.
		NsCar::dcMotor2.run(BACKWARD); // Anti-CW.
		NsCar::dcMotor3.run(FORWARD);
		NsCar::dcMotor4.run(FORWARD);
	}

	void moveForward() {
		DEBUG_PRINTLN("For"); // "Car is going forwards.");
		NsCar::dcMotor1.run(FORWARD);
		NsCar::dcMotor2.run(FORWARD);
		NsCar::dcMotor3.run(FORWARD);
		NsCar::dcMotor4.run(FORWARD);
	}

	void moveBackward() {
		DEBUG_PRINTLN("Back"); // "Car is going backwards.");
		NsCar::dcMotor1.run(BACKWARD);
		NsCar::dcMotor2.run(BACKWARD);
		NsCar::dcMotor3.run(BACKWARD);
		NsCar::dcMotor4.run(BACKWARD);
	}

}
