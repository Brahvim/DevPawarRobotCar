#include <Arduino.h>

#include "Ifs.h"
#include "Car.h"
#include "Main.h"
#include "Buzzer.h"
#include "Routines.h"
#include "LoggingProjectWide.h"

static void impl();

static bool s_shouldBeep;
static unsigned long s_interval;
static routine_t s_implCall = g_routineNullImpl;
static unsigned long s_nextCheckTimestampMillis;

static void impl() {
	ifu(millis() > s_nextCheckTimestampMillis) {

		ifu(digitalRead(CAR_PIN_ANALOG_BUZZER) == HIGH) {

			logvs("Buzzer now `LOW`.");
			digitalWrite(CAR_PIN_ANALOG_BUZZER, LOW);

		} else {

			logvs("Buzzer now `HIGH`.");
			digitalWrite(CAR_PIN_ANALOG_BUZZER, HIGH);

		}

		s_nextCheckTimestampMillis = millis() + s_interval;

	}
}

void routineBuzzerRun() {
	s_implCall();
}

void routineBuzzerEnable() {
	s_implCall = impl;
}

void routineBuzzerDisable() {
	s_implCall = g_routineNullImpl;
}

bool routineBuzzerIsRunning() {
	return s_implCall == impl;
}

#pragma region Buzzer API Implementation.

void buzzerStopAsyncBeeps() {
	s_shouldBeep = false;
	// logds("Buzzer stopped.");
	digitalWrite(CAR_PIN_ANALOG_BUZZER, LOW);
}

void buzzerPlayStartupBeeps() {
	for (char i = 0; i < 3; ++i) {
		buzzerDoSyncBeep(80);
		delay(20);
	}

	buzzerDoSyncBeep(120);
}

bool buzzerIsDoingAsyncBeeps() {
	return s_shouldBeep;
}

unsigned long buzzerGetAsyncBeepsInterval() {
	return s_interval;
}

void buzzerDoSyncBeep(const unsigned long p_duration) {
	digitalWrite(CAR_PIN_ANALOG_BUZZER, HIGH);
	delay(p_duration);
	digitalWrite(CAR_PIN_ANALOG_BUZZER, LOW);
}

void buzzerStartAsyncBeeps(const unsigned long p_beepInterval) {
	// logds("BUZZER STARTED!");

	s_nextCheckTimestampMillis = millis() + s_interval;
	s_interval = p_beepInterval;
	s_shouldBeep = true;
	digitalWrite(CAR_PIN_ANALOG_BUZZER, HIGH);
}
#pragma endregion
