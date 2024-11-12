#include "Main.h"
#include "LoggingProjectWide.h"

static void impl();
static char const *s_toLog;
static routine_t s_implCall = g_routineNullImpl;

static void impl() {

	// logesnf(s_toLog);

};

void routineStoppedRun() {
	s_implCall();
}

void routineStoppedEnable(enum CarStopReason const p_reason) {
	s_implCall = impl;

	switch (p_reason) {

		case CAR_STOP_REASON_SENSOR_TRIGGER_DISCONNECTED:
		{ s_toLog = "Check sensor `TRIG` maybe...?"; }
		break;

		case CAR_STOP_REASON_UNKNOWN:
		default:
		{ s_toLog = "No idea why, but some code somewhere got the car to stop."; }
		break;

		case CAR_STOP_REASON_NO_PATH:
		{ s_toLog = "No path ahead..."; }
		break;

	}
}

void routineStoppedDisable() {
	s_implCall = g_routineNullImpl;
}

bool routineStoppedIsRunning() {
	return s_implCall == impl;
}
