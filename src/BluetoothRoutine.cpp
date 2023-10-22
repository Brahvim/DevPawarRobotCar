#define ENABLE_DEBUG_LOGS

#include "../include/CarApi/NsCar.hpp"
#include "../include/RoutineDecls/BluetoothRoutine.hpp"

#include "../include/Api/Globals.hpp"
#include "../include/Api/DebuggingMacros.hpp"

MAKE_TYPE_INFO(BluetoothRoutine);

// template bool NsAppRoutines::removeRoutine<BluetoothRoutine>();
// template NsAppRoutines::AppRoutineAdditionError NsAppRoutines::addRoutine<BluetoothRoutine>();

void BluetoothRoutine::setup() {
	DEBUG_PRINTLN("The bluetooth routine has been set up.");
}

void BluetoothRoutine::loop() {
	DEBUG_PRINTLN("The bluetooth routine is executing!");

	if (Serial.available() < 1)
		return;

	// Unconventional, but accounts for bad cases without `<=`.
	// Also, faster! :>

	switch (Serial.read()) {
		case 'F':
		NsCar::moveForward();
		break;

		case 'B':
		NsCar::moveBackward();
		break;

		case 'L':
		NsCar::moveLeft();
		break;

		case 'R':
		NsCar::moveRight();
		break;

		case 'S':
		NsCar::stop();
		break;

		default:
		// TODO Make some error routine!
		break;
	}
}
