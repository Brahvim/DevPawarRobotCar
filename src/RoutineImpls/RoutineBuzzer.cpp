#include "Main.h"
#include "LoggingProjectWide.h"

static void impl() {

	logds("Buzzer routine running!");

};

routine_t const g_routineBuzzerImpl = impl;
routine_t g_routineBuzzerCall = impl;
