#include <Arduino.h>

#include "Api/Globals.hpp"
#include "Api/DebuggingMacros.hpp"

#include "CarApi/NsServo.hpp"
#include "CarApi/NsBuzzer.hpp"
#include "CarApi/NsUltrasonic.hpp"


#include "RoutineDecls/CRoutineStoppedForever.hpp"
#include "RoutineDecls/CRoutineObstacleHandling.hpp"

namespace NsUltrasonic {

	volatile int g_countingSemaphoreZeroReads = ULTRASONIC_MAX_ZERO_READS;

	int read() {
again:
		noInterrupts();
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
		unsigned long const pulseDur = pulseIn(PIN_ULTRASONIC_ECHO, HIGH, 10000); // Pulse duration.
		unsigned long const distCm = pulseDur / 29 / 2; // Time-to-centimeters conversion.

		ifl(pulseDur == 0) {

			ERROR_PRINTLN("ZEEEEEEEROOOO!");

			--NsUltrasonic::g_countingSemaphoreZeroReads;

			ifu(NsUltrasonic::g_countingSemaphoreZeroReads < 1) {
				CRoutineStoppedForever::reason = EcRoutineStoppedForeverCallReason::SENSOR;
				NsBuzzer::buzzerStartAsyncBeeps(BUZZER_INTERVAL_ULTRASONIC_BROKE);
				NsRoutines::removeRoutine<CRoutineObstacleHandling>();
				NsRoutines::addRoutine<CRoutineStoppedForever>();
				return 0;
			} else {
				ERROR_PRINT("Semaphore 'zero-reads' hit! Value: ");
				ERROR_WRITELN(NsUltrasonic::g_countingSemaphoreZeroReads);
				goto again;
			}

		}
		interrupts();
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
