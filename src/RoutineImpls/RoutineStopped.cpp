#include "Main.h"
#include "LoggingProjectWide.h"

static void impl() {

	logds("Stop routine running!");

};

routine_t const g_routineStoppedImpl = impl;
routine_t g_routineStoppedCall = impl;
