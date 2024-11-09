#include <Arduino.h>

#include "Api/Globals.hpp"
#include "Api/DebuggingMacros.hpp"

#include "CarApi/NsServo.hpp"
#include "CarApi/NsBuzzer.hpp"
#include "CarApi/NsUltrasonic.hpp"

#include "RoutineDecls/CRoutineStoppedForever.hpp"
#include "RoutineDecls/CRoutineObstacleHandling.hpp"


namespace NsUltrasonic {

	int static volatile s_semaphoreCountingZeroReads = ULTRASONIC_MAX_ZERO_READS;

	int readNoInterrupts();

	int read() {
		noInterrupts();
		delay(4);
		int volatile const toRet = readNoInterrupts();
		interrupts();

		return toRet;
	}

	int readNoInterrupts() {
		while (s_semaphoreCountingZeroReads > 0) {

			// Lower `TRIG` for `4` microseconds as an error check:
			digitalWrite(PIN_ULTRASONIC_TRIG, LOW);
			delayMicroseconds(4); // ...We'll also wait this out.

			// From the HC-SR04 datasheet:
			// Set `TRIG` for `10` microseconds:
			digitalWrite(PIN_ULTRASONIC_TRIG, HIGH);
			delayMicroseconds(10);

			// Giving the ultrasonic sensor a duration gets us a reading:
			unsigned long const durationPulse = pulseIn(PIN_ULTRASONIC_ECHO, HIGH, 10000); // Pulse duration.
			unsigned long const cmDist = durationPulse / 29 / 2; // Time-to-centimeters conversion.

			// Set it low again for next use! ...things go wrong, okay!?
			digitalWrite(PIN_ULTRASONIC_TRIG, LOW);

			ifl(durationPulse != 0) {

				s_semaphoreCountingZeroReads = ULTRASONIC_MAX_ZERO_READS;
				return cmDist;

			}

			ERROR_PRINTLN("ZEEEEEEEROOOO!");
			--NsUltrasonic::s_semaphoreCountingZeroReads;

			ifu(NsUltrasonic::s_semaphoreCountingZeroReads <= 0) {

				CRoutineStoppedForever::reason = EcRoutineStoppedForeverCallReason::SENSOR;
				NsBuzzer::buzzerStartAsyncBeeps(BUZZER_INTERVAL_ULTRASONIC_BROKE);
				NsRoutines::removeRoutine<CRoutineObstacleHandling>();
				NsRoutines::addRoutine<CRoutineStoppedForever>();

				return 0;

			} else {

				ERROR_PRINT("Semaphore 'zero-reads' hit! Value: ");
				ERROR_WRITELN(NsUltrasonic::s_semaphoreCountingZeroReads);

			}

		}

		return 0;
	}

}
