#include "Api/Globals.hpp"
#include "CarApi/NsBuzzer.hpp"
#include "Api/DebuggingMacros.hpp"
#include "RoutineDecls/CRoutineBuzzer.hpp"

static bool s_shouldBeep;
static unsigned long s_interval;
static unsigned long s_nextCheckTimestampMillis;

MAKE_TYPE_INFO(CRoutineBuzzer);

namespace NsBuzzer {

	void buzzerStopAsyncBeeps() {
		s_shouldBeep = false;
		// DEBUG_PRINTLN("Buzzer stopped.");
		digitalWrite(PIN_BUZZER, LOW);
	}

	bool buzzerIsDoingAsyncBeeps() {
		return s_shouldBeep;
	}

	unsigned long buzzerGetAsyncBeepsInterval() {
		return s_interval;
	}

	void buzzerDoSyncBeep(const unsigned long p_duration) {
		digitalWrite(PIN_BUZZER, HIGH);
		delay(p_duration);
		digitalWrite(PIN_BUZZER, LOW);
	}

	void buzzerStartAsyncBeeps(const unsigned long p_beepInterval) {
		// DEBUG_PRINTLN("BUZZER STARTED!");

		s_nextCheckTimestampMillis = millis() + s_interval;
		s_interval = p_beepInterval;
		s_shouldBeep = true;
		digitalWrite(PIN_BUZZER, HIGH);
	}

}

void playStartupBeepPattern() {
	for (char i = 0; i < 3; ++i) {
		NsBuzzer::buzzerDoSyncBeep(80);
		delay(20);
	}

	NsBuzzer::buzzerDoSyncBeep(120);
}

#pragma region // `CRoutineBuzzer` implementation.
void CRoutineBuzzer::setup() {
	DEBUG_PRINTLN("Buzzer-routine started, beeping to notify.");
	playStartupBeepPattern();
}

void CRoutineBuzzer::loop() {
	ifu(!s_shouldBeep) // DoD-Book discouraged :/
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
#pragma endregion
