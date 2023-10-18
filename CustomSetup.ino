#define ENABLE_DEBUG_LOGS // Used by `Globals.hpp`.

const size_t g_maxRoutineCount = 9;

#include "CustomRoutines/BluetoothRoutine.hpp"
#include "DebuggingMacros.hpp"
#include "Globals.hpp"

void start() {
	NsAppRoutines::addRoutine<BluetoothRoutine>();
	// NsAppRoutines::removeRoutine<BluetoothRoutine>();
}
