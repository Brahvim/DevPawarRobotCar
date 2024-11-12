#pragma once

#include "Routines.h"

extern routine_t g_routineBuzzerCall;
extern routine_t const g_routineBuzzerImpl;

extern routine_t g_routineStoppedCall;
extern routine_t const g_routineStoppedImpl;

extern routine_t g_routineControlsListenerCall;
extern routine_t const g_routineControlsListenerImpl;

extern routine_t g_routineObstacleHandlingCall;
extern routine_t const g_routineObstacleHandlingImpl;

void carModeCbck();
