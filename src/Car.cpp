#include "Car.h"
#include "Ifs.h"
#include "Main.h"
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
enum CarStopReason g_carStopReason = CAR_STOP_REASON_UNKNOWN;

unsigned long carUltrasonicSensorRead() {
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
		digitalWrite(PIN_ANALOG_ULTRASONIC_TRIGGER, HIGH);
		delayMicroseconds(10);
		digitalWrite(PIN_ANALOG_ULTRASONIC_TRIGGER, LOW); // Set it low again for next use! ...things go wrong, okay!?

		// We'll still keep `TRIG` high so the sensor doesn't skimp out.
		// Giving the ultrasonic sensor a duration gets us a reading:
		unsigned long const usSensorPulse = pulseIn(PIN_ANALOG_ULTRASONIC_ECHO, HIGH); // Pulse duration.
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

			// CRoutineStoppedForever::reason = EcRoutineStoppedForeverCallReason::SENSOR;
			// NsBuzzer::buzzerStartAsyncBeeps(BUZZER_INTERVAL_ULTRASONIC_BROKE);
			// NsRoutines::removeRoutine<CRoutineObstacleHandling>();
			// NsRoutines::addRoutine<CRoutineStoppedForever>();

			g_carStopReason = CAR_STOP_REASON_SENSOR_TRIGGER_DISCONNECTED;
			g_routineObstacleHandlingCall = g_routineNullImpl;
			g_routineStoppedCall = g_routineStoppedImpl;

			return 0;

		} else {

			// TODO: Get these logs back, too!
			loge("Semaphore 'zero-reads' hit! Value: ", s_semaphoreCountingZeroReads);

		}

	}

	return 0;
}

void carModeCbck() {
	ifu(g_routineControlsListenerCall == g_routineNullImpl) {
		g_routineObstacleHandlingCall = g_routineNullImpl;
		g_routineControlsListenerCall = g_routineControlsListenerImpl;
	} else {
		g_routineObstacleHandlingCall = g_routineObstacleHandlingImpl;
		g_routineControlsListenerCall = g_routineNullImpl;
	}
}
