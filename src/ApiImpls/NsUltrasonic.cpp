#include "Arduino.h"
#include "CarApi/NsServo.hpp"
#include "CarApi/NsBuzzer.hpp"
#include "CarApi/NsUltrasonic.hpp"
#include "Api/DebuggingMacros.hpp"
#include "RoutineDecls/CRoutineStoppedForever.hpp"
#include "RoutineDecls/CRoutineObstacleHandling.hpp"

namespace NsUltrasonic {

	volatile int g_countingSemaphoreZeroReads = 0;

	int read() {
		// Lower `TRIG` for `4` microseconds as an error check:
		digitalWrite(PIN_ULTRASONIC_TRIG, LOW);
		delayMicroseconds(4); // ...We'll also wait this out.

		// From the HC-SR04 datasheet:
		// Set `TRIG` for `10` microseconds:
		digitalWrite(PIN_ULTRASONIC_TRIG, HIGH);
		delayMicroseconds(10);

		// Set it low again for next use! ...things go wrong, okay!?
		digitalWrite(PIN_ULTRASONIC_TRIG, LOW);

		// Giving the ultrasonic sensor a duration gets us a reading:
		const unsigned long pulseDur = pulseIn(PIN_ULTRASONIC_ECHO, HIGH, 10000); // Pulse duration.
		const unsigned long distCm = pulseDur / 29 / 2; // Time-to-centimeters conversion.

		// ifl(pulseDur == 0) {
		//
		// 	ifu(NsUltrasonic::g_countingSemaphoreZeroReads < 0) {
		// 		CRoutineStoppedForever::reason = "Ultrasonic sensor wiring broke!";
		// 		NsBuzzer::buzzerStartAsyncBeeps(BUZZER_INTERVAL_ULTRASONIC_BROKE);
		// 		NsRoutines::removeRoutine<CRoutineObstacleHandling>();
		// 		NsRoutines::addRoutine<CRoutineStoppedForever>();
		// 		ERROR_PRINTLN("Ultrasonic sensor wiring broke!");
		// 		return 0;
		// 	}
		//
		// 	ERROR_PRINT("Semaphore 'zero-reads' hit! Value: ");
		// 	ERROR_WRITE(NsUltrasonic::g_countingSemaphoreZeroReads);
		//
		// 	--NsUltrasonic::g_countingSemaphoreZeroReads;
		// }

		return distCm;
	}

	int lookLeft() {
		NsServo::servo.write(180);
		delay(800);
		return NsUltrasonic::read();
	}

	int lookRight() {
		NsServo::servo.write(20);
		delay(800);
		return NsUltrasonic::read();
	}

}
