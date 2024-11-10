#include <Arduino.h>

#include "Api/Globals.hpp"
#include "Api/DebuggingMacros.hpp"

#include "Shared/ProtocolCarControls.hpp"

#include "RoutineDecls/CRoutineStoppedForever.hpp"
#include "RoutineDecls/CRoutineSwitchActuator.hpp"
#include "RoutineDecls/CRoutineControlsListener.hpp"
#include "RoutineDecls/CRoutineObstacleHandling.hpp"

MAKE_TYPE_INFO(CRoutineSwitchActuator);

void CRoutineSwitchActuator::loop() {
	ifl(digitalRead(PIN_CAR_ARDUINO_1) != HIGH)
		return;

	for (size_t i = 0; i < 25; ++i) {
		DEBUG_PRINTLN("Car now in control mode!");
	}

	delay(2000);

	NsRoutines::addRoutine<CRoutineControlsListener>();

	NsRoutines::removeRoutine<CRoutineStoppedForever>();
	NsRoutines::removeRoutine<CRoutineSwitchActuator>();
	NsRoutines::removeRoutine<CRoutineObstacleHandling>();
}
