#define ENABLE_DEBUG_LOGS
#pragma once

#pragma region Includes.
#include "../CarApi/NsCar.hpp"
#include "../CarApi/NsServo.hpp"
#include "../CarApi/NsUltrasonic.hpp"
#include "CustomSetup.hpp"
#include "DebuggingMacros.hpp"
#include "Globals.hpp"
#include "NsAppRoutines.hpp"

#include <Arduino.h>
#include <ArxContainer.h>
#include <Servo.h>
#pragma endregion

// #pragma region Global definitions.
extern arx::map<const char *, NsAppRoutines::AppRoutine *> g_routinesToClassNamesMap;
// #pragma endregion

void setup() {
	// "iS mY bOWl oF cErEAl hERe yET?!?1!1/":
	while (!Serial)
		;

	Serial.begin(ARDUINO_SERIAL_BAUD_RATE); // Macro in `Globals.hpp`.

	// Make sure we can talk with the ultrasonic sensor:
	pinMode(PIN_ULTRASONIC_TRIG, OUTPUT); // This guy triggers the sensor,
	pinMode(PIN_ULTRASONIC_ECHO, INPUT);  // ...This guy reports the distance back.

	// Set the motors up! All of 'em !:
	NsServo::servo.attach(PIN_SERVO);

	NsCar::dcMotors[1].setSpeed(WHEEL_SPEED);
	NsCar::dcMotors[2].setSpeed(WHEEL_SPEED);
	NsCar::dcMotors[3].setSpeed(WHEEL_SPEED);
	NsCar::dcMotors[4].setSpeed(WHEEL_SPEED);

	DEBUG_PRINT("Calling `");
	DEBUG_WRITE(TO_STRING(START_FXN));
	DEBUG_WRITELN("()`.");

	// Start!:
	START_FXN();

	DEBUG_PRINTLN("Gunna loop now...");
}

void loop() {
	// DEBUG_WRITELN("In Arduino loop.");
	// DEBUG_PRINT("Size of vector: ");
	// DEBUG_WRITELN(g_routinesToClassNamesMap.size());

	// if (Serial.available() > 1)
	// 	DEBUG_PRINTLN("Received something on the serial line!");

	// So we... iterate over 'em all, and...
	// ...yeah, you get the point!:
	for (auto it = g_routinesToClassNamesMap.begin(); it != g_routinesToClassNamesMap.end(); it++) {
		// DEBUG_PRINT("Running routine `");
		// DEBUG_WRITE(it->first);
		// DEBUG_WRITELN("`.");

		// Have this variable just in case. Dunno when the big iterations are gunna be here!:
		const auto routine = it->second;
		routine->loop();
	}
}
