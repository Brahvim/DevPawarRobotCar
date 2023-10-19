#define ENABLE_DEBUG_LOGS // Used by `Globals.hpp`.

#include "CustomRoutines/BluetoothRoutine.hpp"
#include "CustomRoutines/ObstacleHandlingRoutine.hpp"
#include "CustomRoutines/VoiceControlRoutine.hpp"
#include "DebuggingMacros.hpp"
#include "Globals.hpp"

void start() {
	// Order to add routines in:
	// obstacleRoutine();
	// voiceControlRoutine(); // Should come after `bluetoothControlRoutine()`...?
	// bluetoothControlRoutine();

	NsAppRoutines::addRoutine<BluetoothRoutine>();
	NsAppRoutines::addRoutine<VoiceControlRoutine>();
	NsAppRoutines::addRoutine<ObstacleHandlingRoutine>();
}
