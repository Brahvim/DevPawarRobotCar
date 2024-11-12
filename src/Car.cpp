#include "Car.h"
#include "Ifs.h"
#include "Main.h"
#include "Buzzer.h"
#include "LoggingProjectWide.h"

Servo g_carServo;
AF_DCMotor g_carMotors[4] = {

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

void carCbckMode() {
	ifu(routineControlsListenerIsRunning()) {
		routineObstacleHandlingDisable();
		routineControlsListenerEnable();
	} else {
		routineObstacleHandlingEnable();
		routineControlsListenerDisable();
	}
}

#pragma region Movement (Async).
void carMoveStop() {
	// DEBUG_PRINTLN("Stop"); // "Car is stopping.");
	g_carMotors[0].run(RELEASE);
	g_carMotors[1].run(RELEASE);
	g_carMotors[2].run(RELEASE);
	g_carMotors[3].run(RELEASE);
}

void carMoveLeft() {
	// DEBUG_PRINTLN("Right"); // "Car is going right.");
	g_carMotors[0].run(FORWARD);
	g_carMotors[1].run(RELEASE);
	g_carMotors[2].run(RELEASE);
	g_carMotors[3].run(FORWARD);
}

void carMoveRight() {
	// DEBUG_PRINTLN("Left"); // "Car is going left.");
	g_carMotors[0].run(RELEASE);
	g_carMotors[1].run(FORWARD);
	g_carMotors[2].run(FORWARD);
	g_carMotors[3].run(RELEASE);
}

void carMoveForwards() {
	// DEBUG_PRINTLN("For"); // "Car is going forwards.");
	g_carMotors[0].run(FORWARD);
	g_carMotors[1].run(FORWARD);
	g_carMotors[2].run(FORWARD);
	g_carMotors[3].run(FORWARD);
}

void carMoveBackwards() {
	// DEBUG_PRINTLN("Back"); // "Car is going backwards.");
	g_carMotors[0].run(BACKWARD);
	g_carMotors[1].run(BACKWARD);
	g_carMotors[2].run(BACKWARD);
	g_carMotors[3].run(BACKWARD);
}

void carMoveLeftOnSpot() {
	// DEBUG_PRINTLN("Right"); // "Car is going right.");
	g_carMotors[0].run(RELEASE); // Anti-CW.
	g_carMotors[1].run(RELEASE); // Anti-CW.
	g_carMotors[2].run(FORWARD);
	g_carMotors[3].run(FORWARD);
}

void carMoveRightOnSpot() {
	// DEBUG_PRINTLN("Left"); // "Car is going left.");
	g_carMotors[0].run(FORWARD);
	g_carMotors[1].run(FORWARD);
	g_carMotors[2].run(BACKWARD); // Anti-CW.
	g_carMotors[3].run(BACKWARD); // Anti-CW.
}
#pragma endregion

unsigned long carSensorUltrasonicRead() {
	int static s_semaphoreCountingZeroReads = CAR_ULTRASONIC_MAX_ZERO_READS;

	while (s_semaphoreCountingZeroReads > 0) {

		unsigned long static s_msLastRead = millis();

		// unsigned long msToWait = (s_msLastRead + 75) - millis();
		// logd("Waiting `%ldms` to reach a target gap of `75ms`.", msToWait);
		// Serial.flush();

		// unsigned long msTarget = msToWait + millis();
		unsigned long msTarget = 75 + s_msLastRead;
		while (millis() < msTarget) {

		}

		s_msLastRead = millis();
		// logds("Delay complete.");

		// Calls to `millis()` also disable interrupts, so we'll do it here!:
		noInterrupts(); // Don't play around with and expand my delays!
		// From the HC-SR04 datasheet:
		// Set `TRIG` for at least `10` microseconds:
		digitalWrite(CAR_PIN_ANALOG_ULTRASONIC_TRIGGER, HIGH);
		delayMicroseconds(10);
		digitalWrite(CAR_PIN_ANALOG_ULTRASONIC_TRIGGER, LOW); // Set it low again for next use! ...things go wrong, okay!?

		// We'll still keep `TRIG` high so the sensor doesn't skimp out.
		// Giving the ultrasonic sensor a duration gets us a reading:
		unsigned long const usSensorPulse = pulseIn(CAR_PIN_ANALOG_ULTRASONIC_ECHO, HIGH); // Pulse duration.
		interrupts();

		// If the sensor successfully replies back, that's a win! Reading obtained!:
		ifl(usSensorPulse != 0) {

			s_semaphoreCountingZeroReads = CAR_ULTRASONIC_MAX_ZERO_READS;
			return usSensorPulse / 29 / 2; // Time-to-centimeters conversion.
			// For inches, divide by `148`.
			// These calculations assume that the speed of sound is `340ms`.mode=

		}

		// TODO: Get these logs back!
		loges("ZEEEEEEEROOOO!");
		--s_semaphoreCountingZeroReads;

		ifu(s_semaphoreCountingZeroReads <= 0) {

			routineStoppedEnable(CAR_STOP_REASON_SENSOR_TRIGGER_DISCONNECTED);
			buzzerStartAsyncBeeps(CAR_BUZZER_INTERVAL_ULTRASONIC_BROKE);
			routineObstacleHandlingDisable();

			return 0;

		} else {

			// TODO: Get these logs back, too!
			loge("Semaphore 'zero-reads' hit! Value: `%d`.", s_semaphoreCountingZeroReads);

		}

	}

	return 0;
}

#pragma region Movement (Synced).
void carMoveStop(const unsigned long p_ms) {
	// DEBUG_PRINTLN("Stop"); // "Car is stopping.");
	carMoveStop();
	delay(p_ms);
}

void carMoveLeft(const unsigned long p_ms) {
	carMoveLeft();
	delay(p_ms);
	carMoveStop();
}

void carMoveRight(const unsigned long p_ms) {
	carMoveRight();
	delay(p_ms);
	carMoveStop();
}

void carMoveForwards(const unsigned long p_ms) {
	// DEBUG_PRINTLN("For"); // "Car is going forwards.");
	carMoveForwards();
	delay(p_ms);
	carMoveStop();
}

void carMoveBackwards(const unsigned long p_ms) {
	buzzerStartAsyncBeeps(CAR_BUZZER_INTERVAL_BACK_MUSIC);
	carMoveBackwards();
	delay(p_ms);
	carMoveStop();
	buzzerStopAsyncBeeps();
}

void carMoveLeftOnSpot(const unsigned long p_ms) {
	carMoveLeftOnSpot();
	delay(p_ms);
	carMoveStop();
}

void carMoveRightOnSpot(const unsigned long p_ms) {
	carMoveRightOnSpot();
	delay(p_ms);
	carMoveStop();
}
#pragma endregion
