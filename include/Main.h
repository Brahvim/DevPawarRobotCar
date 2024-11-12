#pragma once

#include "Car.h"
#include "Routines.h"

void routineBuzzerRun();
void routineStoppedRun();
void routineControlsListenerRun();
void routineObstacleHandlingRun();

bool routineBuzzerIsRunning();
bool routineStoppedIsRunning();
bool routineControlsListenerIsRunning();
bool routineObstacleHandlingIsRunning();

void routineBuzzerEnable(); void routineBuzzerDisable();
void routineControlsListenerEnable(); void routineControlsListenerDisable();
void routineObstacleHandlingEnable(); void routineObstacleHandlingDisable();
void routineStoppedEnable(CarStopReason const reason); void routineStoppedDisable();
