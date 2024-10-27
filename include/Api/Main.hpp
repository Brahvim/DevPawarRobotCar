#pragma once

#include <Arduino.h>
#include <ArxContainer.h>

#include "Api/NsRoutines.hpp"

#define WHEEL_SPEED				 	 170
#define ARDUINO_SERIAL_BAUD_RATE 	9600

#pragma region // Global declarations.
extern arx::map<const char*, NsRoutines::CRoutine*> g_routinesToClassNamesMap; // See `NsAppRoutines.cpp` for definition.
#pragma endregion

extern void setup();

extern void loop();
