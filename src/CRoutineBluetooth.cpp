#include <ArduinoSTL.h>

#include "Api/Globals.hpp"
#include "CarApi/NsCar.hpp"
#include "BluetoothComms.hpp"
#include "Api/DebuggingMacros.hpp"
#include "RoutineDecls/CRoutineBluetooth.hpp"

MAKE_TYPE_INFO(CRoutineBluetooth);

// template bool NsRoutines::removeRoutine<CRoutineBluetooth>();
// template NsRoutines::EcRoutineAdditionError NsRoutines::addRoutine<CRoutineBluetooth>();

void CRoutineBluetooth::setup() {
	DEBUG_PRINTLN("The bluetooth routine has been set up.");
}

void CRoutineBluetooth::loop() {
	// DEBUG_PRINTLN("The bluetooth routine is executing!");

	// Unconventional, but accounts for bad cases without `<=`.
	// Also, faster! :>

	ifl(Serial.available() < 1)
		return;

	// String const receivedStr = Serial.readString();

	// if (!receivedStr.startsWith(BLUETOOTH_COMMS_REMOTE_PREFIX))
	// 	return; // Not something we need to deal with, apparently!

	// BLUETOOTH_PRINT("Hey! You sent this: ");
	// BLUETOOTH_WRITELN(receivedStr);

	// String const receivedStr = Serial.readString();
	String const receivedStr = this->customReadStringUntil(BLUETOOTH_COMMS_TERMINATOR_CHAR);

	ifl(!receivedStr.startsWith(BLUETOOTH_COMMS_REMOTE_PREFIX)) {
		DEBUG_WRITELN("Skipping this from serial:");
		DEBUG_WRITELN(receivedStr);
		return; // Not something we need to deal with, apparently!
	}

	int start = receivedStr.indexOf(BLUETOOTH_COMMS_REMOTE_PREFIX) + BLUETOOTH_COMMS_REMOTE_PREFIX_LENGTH;
	int end = receivedStr.indexOf('\n', start);

	String intStr = receivedStr.substring(start, end);
	int const receivedInt = intStr.toInt();

	BLUETOOTH_PRINT("Hey! You sent this: ");
	BLUETOOTH_WRITELN(receivedStr);

	BLUETOOTH_PRINT("Is this the INT?: ");
	BLUETOOTH_WRITELN(intStr);

	BLUETOOTH_PRINT("Parsed INT: ");
	BLUETOOTH_WRITELN(receivedInt);
}

String CRoutineBluetooth::customReadStringUntil(char p_term) {
	char c;
	String result = "";

	while ((c = Serial.read()) != p_term) {
		result += c;
	}

	// Include the terminator character in the resulting string
	result += p_term;
	return result;
}
