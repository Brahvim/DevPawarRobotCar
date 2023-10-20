#define ENABLE_DEBUG_LOGS

#pragma region Includes.
#include "CarApi/NsCar.hpp"
#include "CarApi/NsUltrasonic.hpp"
#include "CustomSetup.hpp"
#include "DebuggingMacros.hpp"
#include "Globals.hpp"
#include "NsAppRoutines.hpp"

#include <Arduino.h>
#include <ArxContainer.h>
#include <Servo.h>
#pragma endregion

#pragma region Global definitions.
const Servo g_servo;
#pragma endregion

#pragma region Static declarations.
static arx::map<const char *, NsAppRoutines::AppRoutine *> s_routinesToClassNamesMap;
#pragma endregion

void setup() {
	// "iS mY bOWl oF cErEAl hERe yET?!?1!1/":
	while (!Serial)
		;

	Serial.begin(ARDUINO_SERIAL_BAUD_RATE); // Macro in `Globals.hpp`.

	// Make sure we can talk with the ultrasonic sensor:
	pinMode(PIN_ULTRASONIC_TRIG, OUTPUT); // This guy triggers the sensor,
	pinMode(PIN_ULTRASONIC_ECHO, INPUT);  // ...This guy reports the distance back.

	// Set the motors up! All of 'em !:
	g_servo.attach(PIN_SERVO);

	NsCar::dcMotors[1].setSpeed(WHEEL_SPEED);
	NsCar::dcMotors[2].setSpeed(WHEEL_SPEED);
	NsCar::dcMotors[3].setSpeed(WHEEL_SPEED);
	NsCar::dcMotors[4].setSpeed(WHEEL_SPEED);

	DEBUG_PRINT("Calling `");
	DEBUG_WRITE(STRINGIZE(START_FXN_NAME));
	DEBUG_WRITELN("()`.");

	// Start!:
	START_FXN_NAME();
}

void loop() {
	// So we... iterate over 'em all, and...
	// ...yeah, you get the point!:
	for (auto it = s_routinesToClassNamesMap.begin(); it != s_routinesToClassNamesMap.end(); it++) {
		DEBUG_PRINT("Size of vector: ");
		DEBUG_WRITELN(s_routinesToClassNamesMap.size());

		// Have this variable just in case. Dunno when the big iterations are gunna be here!:
		const auto routine = it->second;
		routine->loop();
	}
}

namespace NsAppRoutines {

	template <class RoutineT>
	NsAppRoutines::AppRoutineAdditionError addRoutine() {
		// If an object of this class already exists,
		if (s_routinesToClassNamesMap.find(TYPE_NAME(RoutineT)) != s_routinesToClassNamesMap.end()) {
			DEBUG_PRINT("Routine of type `");
			DEBUG_WRITE(TYPE_NAME(RoutineT));
			DEBUG_WRITELN("` already exists. Didn't add another.");

			// Yeah, we ain't adding another (for now! ..should this change later?! ..indexed instances?!):
			return NsAppRoutines::AppRoutineAdditionError::ROUTINE_ALREADY_EXISTS;
		}

		// Okay, here we go! Roll the callback!:
		NsAppRoutines::AppRoutine *routine = new RoutineT(); // Fun fact: Object slicing ruined me here for DAYS 🤣
		s_routinesToClassNamesMap[TYPE_NAME(RoutineT)] = routine;
		routine->setup();

		DEBUG_PRINT("Added routine of type: `");
		DEBUG_WRITE(TYPE_NAME(RoutineT));
		DEBUG_WRITELN("`.");

		return NsAppRoutines::AppRoutineAdditionError::NO_ERROR;
	}

	template <class RoutineT>
	bool removeRoutine() {
		// Check if a routine of the same class name exists:
		for (auto it = s_routinesToClassNamesMap.begin(); it != s_routinesToClassNamesMap.end(); it++) {
			// If the name of the class isn't the same, keep looking (yes, this is a guard clause!):
			if (it->first != TYPE_NAME(RoutineT))
				continue;

			// If we've found one, we dispatch the callback and de-allocate memory:
			NsAppRoutines::AppRoutine *routine = &(it->second);
			routine->out();
			delete routine;

			// ...As well as remove our object from our map:
			s_routinesToClassNamesMap.erase(it);

			DEBUG_PRINT("Removed routine of type: `");
			DEBUG_WRITE(TYPE_NAME(RoutineT));
			DEBUG_WRITELN("`.");

			// DEBUG_PRINT("Size of vector: ");
			// DEBUG_WRITELN(s_routinesToClassNamesMap.size());

			return true;
		}

		DEBUG_PRINT("Found no removable routine of type: `");
		DEBUG_WRITE(TYPE_NAME(RoutineT));
		DEBUG_WRITELN("`.");

		return false;
	}
}
