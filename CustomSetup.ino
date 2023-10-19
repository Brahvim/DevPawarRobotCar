#define ENABLE_DEBUG_LOGS // Used by `Globals.hpp`.

#include "CustomRoutines/BluetoothRoutine.hpp"
#include "DebuggingMacros.hpp"
#include "Globals.hpp"

void start() {
	NsAppRoutines::addRoutine<BluetoothRoutine>();
}
