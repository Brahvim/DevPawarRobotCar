#include <AFMotor.h>
#include <ArduinoSTL.h>

#include "CarApi/NsCar.hpp"
#include "CarApi/NsBuzzer.hpp"
#include "CarApi/NsUltrasonic.hpp"

#include "Api/DebuggingMacros.hpp"

namespace NsCar {

	AF_DCMotor motors[4] = {
		AF_DCMotor(1),
		AF_DCMotor(2),
		AF_DCMotor(3),
		AF_DCMotor(4),
	};

	/*

	Group A: 1 and 3.
	Group B: 2 and 4.

	Diag-right-up: 1 and 4 go CW.
	Right: 1 and 4 are already CW.

	*/

	void stop() {
		// DEBUG_PRINTLN("Stop"); // "Car is stopping.");
		NsCar::motors[1].run(RELEASE);
		NsCar::motors[2].run(RELEASE);
		NsCar::motors[3].run(RELEASE);
		NsCar::motors[4].run(RELEASE);
	}

	void moveLeftAsync() {
		// DEBUG_PRINTLN("Right"); // "Car is going right.");
		NsCar::motors[1].run(BACKWARD); // Anti-CW.
		NsCar::motors[2].run(BACKWARD); // Anti-CW.
		NsCar::motors[3].run(FORWARD);
		NsCar::motors[4].run(FORWARD);
	}

	void moveRightAsync() {
		// DEBUG_PRINTLN("Left"); // "Car is going left.");
		NsCar::motors[1].run(FORWARD);
		NsCar::motors[2].run(FORWARD);
		NsCar::motors[3].run(BACKWARD); // Anti-CW.
		NsCar::motors[4].run(BACKWARD); // Anti-CW.
	}

	void moveForwardAsync() {
		// DEBUG_PRINTLN("For"); // "Car is going forwards.");
		NsCar::motors[1].run(FORWARD);
		NsCar::motors[2].run(FORWARD);
		NsCar::motors[3].run(FORWARD);
		NsCar::motors[4].run(FORWARD);
	}

	void moveBackwardAsync() {
		// DEBUG_PRINTLN("Back"); // "Car is going backwards.");
		NsCar::motors[1].run(BACKWARD);
		NsCar::motors[2].run(BACKWARD);
		NsCar::motors[3].run(BACKWARD);
		NsCar::motors[4].run(BACKWARD);
	}

	void stop(const unsigned long p_forMs) {
		// DEBUG_PRINTLN("Stop"); // "Car is stopping.");
		NsCar::motors[1].run(RELEASE);
		NsCar::motors[2].run(RELEASE);
		NsCar::motors[3].run(RELEASE);
		NsCar::motors[4].run(RELEASE);
		delay(p_forMs);
	}

	void moveForward(const unsigned long p_forMs) {
		// DEBUG_PRINTLN("For"); // "Car is going forwards.");
		NsCar::motors[1].run(FORWARD);
		NsCar::motors[2].run(FORWARD);
		NsCar::motors[3].run(FORWARD);
		NsCar::motors[4].run(FORWARD);
		delay(p_forMs);
	}

	void moveBackward(const unsigned long p_forMs) {
		NsBuzzer::buzzerStart(BUZZER_INTERVAL_BACK_MUSIC);

		// DEBUG_PRINTLN("Back"); // "Car is going backwards.");
		NsCar::motors[1].run(BACKWARD);
		NsCar::motors[2].run(BACKWARD);
		NsCar::motors[3].run(BACKWARD);
		NsCar::motors[4].run(BACKWARD);
		delay(p_forMs);

		NsBuzzer::buzzerStop();
	}

	void moveLeftOnSpot(const unsigned long p_forMs) {
		// DEBUG_PRINTLN("Right"); // "Car is going right.");
		NsCar::motors[1].run(BACKWARD); // Anti-CW.
		NsCar::motors[2].run(BACKWARD); // Anti-CW.
		NsCar::motors[3].run(FORWARD);
		NsCar::motors[4].run(FORWARD);
		delay(p_forMs);
	}

	void moveRightOnSpot(const unsigned long p_forMs) {
		// DEBUG_PRINTLN("Left"); // "Car is going left.");
		NsCar::motors[1].run(FORWARD);
		NsCar::motors[2].run(FORWARD);
		NsCar::motors[3].run(BACKWARD); // Anti-CW.
		NsCar::motors[4].run(BACKWARD); // Anti-CW.
		delay(p_forMs);
	}

}
