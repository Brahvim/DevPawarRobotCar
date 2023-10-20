#define ENABLE_DEBUG_LOGS // Used by `DebuggingMacros.hpp`.

#include "CustomRoutines/BluetoothRoutine.hpp"
#include "CustomRoutines/ObstacleHandlingRoutine.hpp"
#include "CustomRoutines/VoiceControlRoutine.hpp"
#include "CustomSetup.hpp"

void start() {
	// Order to add routines in:
	// obstacleRoutine();
	// voiceControlRoutine(); // Should come after `bluetoothControlRoutine()`...?
	// bluetoothControlRoutine();

	NsAppRoutines::addRoutine<BluetoothRoutine>();
	NsAppRoutines::addRoutine<VoiceControlRoutine>();
	NsAppRoutines::addRoutine<ObstacleHandlingRoutine>();
}
