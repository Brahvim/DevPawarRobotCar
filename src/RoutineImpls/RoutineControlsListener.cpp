#include "Main.h"
#include "LoggingProjectWide.h"

static void impl();
static routine_t s_implCall = g_routineNullImpl;

static void impl() {

	logds("Controls-listening routine running!");

};

void routineControlsListenerRun() {
	s_implCall();
}

void routineControlsListenerEnable() {
	s_implCall = impl;
}

void routineControlsListenerDisable() {
	s_implCall = g_routineNullImpl;
}

bool routineControlsListenerIsRunning() {
	return s_implCall == impl;
}
