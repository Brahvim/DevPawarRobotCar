#define ENABLE_DEBUG_LOGS // Used by `DebuggingMacros.hpp`.

#include "Api/CustomSetup.hpp"
#include "RoutineDecls/BluetoothRoutine.hpp"
#include "RoutineDecls/ObstacleHandlingRoutine.hpp"
#include "RoutineDecls/VoiceControlRoutine.hpp"

void start() {
	// Order to add routines in:
	// obstacleRoutine();
	// voiceControlRoutine(); // Should come after `bluetoothControlRoutine()`...?
	// bluetoothControlRoutine();

	NsAppRoutines::addRoutine<BluetoothRoutine>();
	NsAppRoutines::addRoutine<VoiceControlRoutine>();
	NsAppRoutines::addRoutine<ObstacleHandlingRoutine>();
}
