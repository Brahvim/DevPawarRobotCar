#include "Api/Main.hpp"
#include "Api/Globals.hpp"

#include "CarApi/NsBuzzer.hpp"

#include "Api/CustomSetup.hpp"
#include "Api/NsAppRoutines.hpp"
#include "Api/DebuggingMacros.hpp"

#include "RoutineDecls/BuzzerRoutine.hpp"
#include "RoutineDecls/BluetoothRoutine.hpp"
#include "RoutineDecls/ObstacleHandlingRoutine.hpp"

void start() {
	NsAppRoutines::addRoutine<ObstacleHandlingRoutine>();
	// NsAppRoutines::addRoutine<BluetoothRoutine>();
	NsAppRoutines::addRoutine<BuzzerRoutine>();
}
