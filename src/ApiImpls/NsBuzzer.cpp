#include "Api/Globals.hpp"
#include "CarApi/NsBuzzer.hpp"
#include "Api/DebuggingMacros.hpp"

static bool s_shouldBeep;
static unsigned long s_interval;
static unsigned long s_nextCheckTimestampMillis;

namespace NsBuzzer {

	void buzzerSetup() {
		pinMode(PIN_BUZZER, OUTPUT);
	}

	void buzzerRoutine() {
		ifu(!s_shouldBeep)
			return;

		if (millis() > s_nextCheckTimestampMillis) {
			if (digitalRead(PIN_BUZZER) == HIGH) {
				DEBUG_PRINTLN("Buzzer now `LOW`.");
				digitalWrite(PIN_BUZZER, LOW);
			} else {
				DEBUG_PRINTLN("Buzzer now `HIGH`.");
				digitalWrite(PIN_BUZZER, HIGH);
			}

			s_nextCheckTimestampMillis = millis() + s_interval;
		}
	}

	void buzzerStart(const unsigned long p_beepInterval) {
		s_interval = p_beepInterval;
		s_nextCheckTimestampMillis = millis() + s_interval;
		s_shouldBeep = true;
		// DEBUG_PRINTLN("BUZZER STARTED!");
		digitalWrite(PIN_BUZZER, HIGH);
	}

	void buzzerStop() {
		s_shouldBeep = false;
		// DEBUG_PRINTLN("Buzzer stopped.");
		digitalWrite(PIN_BUZZER, LOW);
	}

	bool buzzerIsBeeping() {
		return s_shouldBeep;
	}

	unsigned long buzzerGetBeepInterval() {
		return s_interval;
	}

}


