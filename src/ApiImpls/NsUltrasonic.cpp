#include "Arduino.h"

#include "Api/Globals.hpp"
#include "Api/DebuggingMacros.hpp"

#include "CarApi/NsServo.hpp"
#include "CarApi/NsBuzzer.hpp"
#include "CarApi/NsUltrasonic.hpp"

#include "RoutineDecls/CRoutineStoppedForever.hpp"
#include "RoutineDecls/CRoutineObstacleHandling.hpp"

namespace NsUltrasonic {

	int read() {
		int static s_semaphoreCountingZeroReads = ULTRASONIC_MAX_ZERO_READS;

		while (s_semaphoreCountingZeroReads > 0) {

			unsigned long static s_msLastRead = millis();

			// unsigned long msToWait = (s_msLastRead + 75) - millis();
			// DEBUG_PRINT("Waiting `");
			// DEBUG_APPEND(msToWait);
			// DEBUG_APPENDLN("ms` to reach a target gap of `75ms`."); Serial.flush();

			// unsigned long msTarget = msToWait + millis();
			unsigned long msTarget = 75 + s_msLastRead;
			while (millis() < msTarget) {

			}

			s_msLastRead = millis();
			// DEBUG_PRINTLN("Delay complete.");

			// Calls to `millis()` also disable interrupts, so we'll do it here!:
			noInterrupts(); // Don't play around with and expand my delays!
			// From the HC-SR04 datasheet:
			// Set `TRIG` for at least `10` microseconds:
			digitalWrite(PIN_ULTRASONIC_TRIG, HIGH);
			delayMicroseconds(10);
			digitalWrite(PIN_ULTRASONIC_TRIG, LOW); // Set it low again for next use! ...things go wrong, okay!?

			// We'll still keep `TRIG` high so the sensor doesn't skimp out.
			// Giving the ultrasonic sensor a duration gets us a reading:
			unsigned long const usSensorPulse = pulseIn(PIN_ULTRASONIC_ECHO, HIGH); // Pulse duration.
			interrupts();

			// If the sensor successfully replies back, that's a win! Reading obtained!:
			ifl(usSensorPulse != 0) {

				s_semaphoreCountingZeroReads = ULTRASONIC_MAX_ZERO_READS;
				return usSensorPulse / 29 / 2; // Time-to-centimeters conversion.
				// For inches, divide by `148`.
				// These calculations assume that the speed of sound is `340ms`.mode=

			}

			// TODO: Get these logs back!
			ERROR_PRINTLN("ZEEEEEEEROOOO!");
			--s_semaphoreCountingZeroReads;

			ifu(s_semaphoreCountingZeroReads <= 0) {

				CRoutineStoppedForever::reason = EcRoutineStoppedForeverCallReason::SENSOR;
				NsBuzzer::buzzerStartAsyncBeeps(BUZZER_INTERVAL_ULTRASONIC_BROKE);
				NsRoutines::removeRoutine<CRoutineObstacleHandling>();
				NsRoutines::addRoutine<CRoutineStoppedForever>();

				return 0;

			} else {

				// TODO: Get these logs back, too!
				ERROR_PRINT("Semaphore 'zero-reads' hit! Value: ");
				ERROR_APPENDLN(s_semaphoreCountingZeroReads);

			}

		}

		return 0;
	}

}
