#include "../include/Api/Main.hpp"
#include "../include/Api/Globals.hpp"

#include "../include/CarApi/NsBuzzer.hpp"

#include "../include/Api/CustomSetup.hpp"
#include "../include/Api/NsAppRoutines.hpp"
#include "../include/Api/DebuggingMacros.hpp"

#include "../include/RoutineDecls/BuzzerRoutine.hpp"
#include "../include/RoutineDecls/BluetoothRoutine.hpp"
#include "../include/RoutineDecls/ObstacleHandlingRoutine.hpp"

void start() {
	NsAppRoutines::addRoutine<ObstacleHandlingRoutine>();
	// NsAppRoutines::addRoutine<BluetoothRoutine>();
	NsAppRoutines::addRoutine<BuzzerRoutine>();
}
