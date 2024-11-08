#include <AFMotor.h>
#include <ArduinoSTL.h>

#include "CarApi/NsCar.hpp"
#include "CarApi/NsBuzzer.hpp"
#include "CarApi/NsUltrasonic.hpp"

#include "Api/DebuggingMacros.hpp"

namespace NsCar {

	AF_DCMotor motors[4] = {

		/*

		L293D motor numbers:
		```
		2 1
		3 4
		```

		As array indices:
		```
		1 0
		2 3
		```

		*/

			AF_DCMotor(1),
			AF_DCMotor(2),
			AF_DCMotor(3),
			AF_DCMotor(4),

	};
	bool g_wasForwards = false;

	void stop() {
		// DEBUG_PRINTLN("Stop"); // "Car is stopping.");
		NsCar::motors[0].run(RELEASE);
		NsCar::motors[1].run(RELEASE);
		NsCar::motors[2].run(RELEASE);
		NsCar::motors[3].run(RELEASE);
	}

	void moveLeftAsync() {
		// DEBUG_PRINTLN("Right"); // "Car is going right.");
		NsCar::motors[0].run(FORWARD);
		NsCar::motors[1].run(RELEASE);
		NsCar::motors[2].run(RELEASE);
		NsCar::motors[3].run(FORWARD);
	}

	void moveRightAsync() {
		// DEBUG_PRINTLN("Left"); // "Car is going left.");
		NsCar::motors[0].run(RELEASE);
		NsCar::motors[1].run(FORWARD);
		NsCar::motors[2].run(FORWARD);
		NsCar::motors[3].run(RELEASE);
	}

	void moveForwardAsync() {
		g_wasForwards = true;

		// DEBUG_PRINTLN("For"); // "Car is going forwards.");
		NsCar::motors[0].run(FORWARD);
		NsCar::motors[1].run(FORWARD);
		NsCar::motors[2].run(FORWARD);
		NsCar::motors[3].run(FORWARD);
	}

	void moveBackwardAsync() {
		g_wasForwards = false;

		// DEBUG_PRINTLN("Back"); // "Car is going backwards.");
		NsCar::motors[0].run(BACKWARD);
		NsCar::motors[1].run(BACKWARD);
		NsCar::motors[2].run(BACKWARD);
		NsCar::motors[3].run(BACKWARD);
	}

	void moveLeftOnSpotAsync() {
		// DEBUG_PRINTLN("Right"); // "Car is going right.");
		NsCar::motors[0].run(RELEASE); // Anti-CW.
		NsCar::motors[1].run(RELEASE); // Anti-CW.
		NsCar::motors[2].run(FORWARD);
		NsCar::motors[3].run(FORWARD);
	}

	void moveRightOnSpotAsync() {
		// DEBUG_PRINTLN("Left"); // "Car is going left.");
		NsCar::motors[0].run(FORWARD);
		NsCar::motors[1].run(FORWARD);
		NsCar::motors[2].run(BACKWARD); // Anti-CW.
		NsCar::motors[3].run(BACKWARD); // Anti-CW.
	}

	void stop(const unsigned long p_ms) {
		// DEBUG_PRINTLN("Stop"); // "Car is stopping.");
		NsCar::stop();
		delay(p_ms);
	}

	void moveLeft(const unsigned long p_ms) {
		NsCar::moveLeftAsync();
		delay(p_ms);
		NsCar::stop();
	}

	void moveRight(const unsigned long p_ms) {
		NsCar::moveRightAsync();
		delay(p_ms);
		NsCar::stop();
	}

	void moveForward(const unsigned long p_ms) {
		// DEBUG_PRINTLN("For"); // "Car is going forwards.");
		NsCar::moveForwardAsync();
		delay(p_ms);
		NsCar::stop();
	}

	void moveBackward(const unsigned long p_ms) {
		NsBuzzer::buzzerStartAsyncBeeps(BUZZER_INTERVAL_BACK_MUSIC);
		NsCar::moveBackwardAsync();
		delay(p_ms);
		NsCar::stop();
		NsBuzzer::buzzerStopAsyncBeeps();
	}

	void moveLeftOnSpot(const unsigned long p_ms) {
		NsCar::moveLeftOnSpotAsync();
		delay(p_ms);
		NsCar::stop();
	}

	void moveRightOnSpot(const unsigned long p_ms) {
		NsCar::moveRightOnSpotAsync();
		delay(p_ms);
		NsCar::stop();
	}

}
