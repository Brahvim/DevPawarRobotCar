#include "Ifs.h"
#include "Car.h"
#include "Main.h"
#include "LoggingProjectWide.h"

static void impl() {
	logds("Obstacle-handling routine running!");

};

routine_t const g_routineObstacleHandlingImpl = impl;
routine_t g_routineObstacleHandlingCall = impl;
