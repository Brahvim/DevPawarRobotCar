#include <ArduinoSTL.h>

#include "Api/Globals.hpp"
#include "CarApi/NsCar.hpp"
#include "BluetoothComms.hpp"
#include "Api/DebuggingMacros.hpp"
#include "RoutineDecls/BluetoothRoutine.hpp"

MAKE_TYPE_INFO(BluetoothRoutine);

// template bool NsAppRoutines::removeRoutine<BluetoothRoutine>();
// template NsAppRoutines::AppRoutineAdditionError NsAppRoutines::addRoutine<BluetoothRoutine>();

void BluetoothRoutine::setup() {
	DEBUG_PRINTLN("The bluetooth routine has been set up.");
}

String BluetoothRoutine::customReadStringUntil(char p_term) {
	String result = "";
	char c;
	while ((c = Serial.read()) != p_term) {
		result += c;
	}
	// Include the terminator character in the resulting string
	result += p_term;
	return result;
}

void BluetoothRoutine::loop() {
	// DEBUG_PRINTLN("The bluetooth routine is executing!");

	// Unconventional, but accounts for bad cases without `<=`.
	// Also, faster! :>
	if (Serial.available() < 1)
		return;

	// const String receivedStr = Serial.readString();

	// if (!receivedStr.startsWith(BLUETOOTH_COMMS_REMOTE_PREFIX))
	// 	return; // Not something we need to deal with, apparently!

	// BLUETOOTH_PRINT("Hey! You sent this: ");
	// BLUETOOTH_WRITELN(receivedStr);

	// const String receivedStr = Serial.readString();
	const String receivedStr = this->customReadStringUntil(BLUETOOTH_COMMS_TERMINATOR_CHAR);

	if (!receivedStr.startsWith(BLUETOOTH_COMMS_REMOTE_PREFIX)) {
		DEBUG_WRITELN("Skipping this from serial:");
		DEBUG_WRITELN(receivedStr);
		return; // Not something we need to deal with, apparently!
	}

	int start = receivedStr.indexOf(BLUETOOTH_COMMS_REMOTE_PREFIX) + BLUETOOTH_COMMS_REMOTE_PREFIX_LENGTH;
	int end = receivedStr.indexOf('\n', start);

	String intStr = receivedStr.substring(start, end);
	const int receivedInt = intStr.toInt();

	BLUETOOTH_PRINT("Hey! You sent this: ");
	BLUETOOTH_WRITELN(receivedStr);

	BLUETOOTH_PRINT("Is this the INT?: ");
	BLUETOOTH_WRITELN(intStr);

	BLUETOOTH_PRINT("Parsed INT: ");
	BLUETOOTH_WRITELN(receivedInt);

}
