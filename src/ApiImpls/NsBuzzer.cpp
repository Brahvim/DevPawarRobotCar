#include "Api/Globals.hpp"
#include "CarApi/NsBuzzer.hpp"
#include "Api/DebuggingMacros.hpp"
#include "RoutineDecls/BuzzerRoutine.hpp"

static bool s_shouldBeep;
static unsigned long s_interval;
static unsigned long s_nextCheckTimestampMillis;

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

	void buzzerDoSyncBeep(const unsigned long p_beepInterval) {
		digitalWrite(PIN_BUZZER, HIGH);
		delay(p_beepInterval);
		digitalWrite(PIN_BUZZER, LOW);
	}

	void buzzerStartAsyncBeeps(const unsigned long p_beepInterval) {
		s_interval = p_beepInterval;
		s_nextCheckTimestampMillis = millis() + s_interval;
		s_shouldBeep = true;
		// DEBUG_PRINTLN("BUZZER STARTED!");
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

#pragma region // `BuzzerRoutine` implementation.
void BuzzerRoutine::setup() {
	pinMode(PIN_BUZZER, OUTPUT);

	DEBUG_PRINTLN("Buzzer-routine started, beeping to notify.");
	playStartupBeepPattern();
}

void BuzzerRoutine::loop() {
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
