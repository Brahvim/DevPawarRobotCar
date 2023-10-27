#include <ArduinoSTL.h>

#include "../include/Api/Globals.hpp"
#include "../include/CarApi/NsCar.hpp"
#include "../include/BluetoothComms.hpp"
#include "../include/Api/DebuggingMacros.hpp"
#include "../include/RoutineDecls/BluetoothRoutine.hpp"

MAKE_TYPE_INFO(BluetoothRoutine);

// template bool NsAppRoutines::removeRoutine<BluetoothRoutine>();
// template NsAppRoutines::AppRoutineAdditionError NsAppRoutines::addRoutine<BluetoothRoutine>();

void BluetoothRoutine::setup() {
	DEBUG_PRINTLN("The bluetooth routine has been set up.");
}

void BluetoothRoutine::loop() {
	// DEBUG_PRINTLN("The bluetooth routine is executing!");

	// Unconventional, but accounts for bad cases without `<=`.
	// Also, faster! :>
	if (Serial.available() < 1)
		return;

	const String receivedStr = Serial.readStringUntil(BLUETOOTH_COMMS_TERMINATOR);

	if (!receivedStr.startsWith(BLUETOOTH_COMMS_PREFIX))
		return; // Not something we need to deal with, apparently!

	DEBUG_PRINT(BLUETOOTH_COMMS_PREFIX "Received: ");
	DEBUG_WRITELN(receivedStr);

	switch ('\n') { // Stub!
		case 'F':
		NsCar::moveForward();
		break;

		case 'B':
		NsCar::moveBackward();
		break;

		case 'L':
		NsCar::moveRight();
		break;

		case 'R':
		NsCar::moveLeft();
		break;

		case 'S':
		NsCar::stop();
		break;

		default:
		ERROR_PRINTLN("Received an unknown character on the bluetooth stream.");
		break;
	}
}
