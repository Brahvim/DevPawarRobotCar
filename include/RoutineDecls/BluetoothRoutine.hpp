#pragma once

#include "../Api/NsAppRoutines.hpp"

#define BLUETOOTH_MESSAGE_TERMINATOR '\n'

class BluetoothRoutine : public NsAppRoutines::AppRoutine {
	void loop();
	void setup();
};
