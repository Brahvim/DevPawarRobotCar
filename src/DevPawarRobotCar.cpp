#define ENABLE_DEBUG_LOGS // Used by `DebuggingMacros.hpp`.

#include "../include/Api/Main.hpp"
#include "../include/Api/Globals.hpp"
#include "../include/Api/CustomSetup.hpp"
#include "../include/Api/NsAppRoutines.hpp"
#include "../include/RoutineDecls/BluetoothRoutine.hpp"
#include "../include/RoutineDecls/VoiceControlRoutine.hpp"
#include "../include/RoutineDecls/ObstacleHandlingRoutine.hpp"

void start() {
	// Order to add routines in:
	// obstacleRoutine();
	// voiceControlRoutine(); // Should come after `bluetoothControlRoutine()`...?
	// bluetoothControlRoutine();

	NsAppRoutines::addRoutine<ObstacleHandlingRoutine>();
	NsAppRoutines::addRoutine<VoiceControlRoutine>();
	NsAppRoutines::addRoutine<BluetoothRoutine>();
}
