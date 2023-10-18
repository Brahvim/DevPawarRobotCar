#define ENABLE_DEBUG_LOGS

#include "../DebuggingMacros.hpp"
#include "../Globals.hpp"

class BluetoothRoutine : public NsAppRoutines::AppRoutine {
	void loop() override {
		DEBUG_PRINTLN("Yo!");
	}
};

MAKE_TYPE_INFO(BluetoothRoutine);
