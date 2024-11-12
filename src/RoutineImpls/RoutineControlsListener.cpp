#include "Main.h"
#include "LoggingProjectWide.h"

static void impl() {

    logds("Controls-listening routine running!");

};

routine_t const g_routineControlsListenerImpl = impl;
routine_t g_routineControlsListenerCall = impl;
