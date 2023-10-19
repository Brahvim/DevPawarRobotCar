#define ENABLE_DEBUG_LOGS

#pragma region Includes.
#include "DebuggingMacros.hpp"
#include "Globals.hpp" // Has more `#include` directives!
#include "NsAppRoutines.hpp"
#include "NsCar.hpp"

#include <AFMotor.h>
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
	while (!Serial)
		;
	Serial.begin(ARDUINO_SERIAL_BAUD_RATE); // Macro in `Globals.hpp`.

	// Make sure we can talk with the ultrasonic sensor:
	pinMode(PIN_ULTRASONIC_ECHO, INPUT);
	pinMode(PIN_ULTRASONIC_TRIG, OUTPUT);

	g_servo.attach(PIN_SERVO);

	NsCar::dcMotors[1].setSpeed(WHEEL_SPEED);
	NsCar::dcMotors[2].setSpeed(WHEEL_SPEED);
	NsCar::dcMotors[3].setSpeed(WHEEL_SPEED);
	NsCar::dcMotors[4].setSpeed(WHEEL_SPEED);

	DEBUG_PRINTLN("Calling `start()`.");
	start();
}

void loop() {
	for (auto it = s_routinesToClassNamesMap.begin(); it != s_routinesToClassNamesMap.end(); it++) {
		// DEBUG_PRINT("Size of vector: ");
		// DEBUG_WRITELN(s_routinesToClassNamesMap.size());
		const auto routine = it->second;
		routine->loop();
	}

	// obstacleRoutine();
	// voiceControlRoutine(); // Should come after `bluetoothControlRoutine()`...?
	// bluetoothControlRoutine();
}

void bluetoothControlRoutine() {
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

void obstacleRoutine() {
	const int dist = NsUltrasonic::read(); // Could use this info later!
	DEBUG_PRINTLN("Distance: " + dist);
	delay(100);

	if (dist > 12) {
		NsCar::moveForward();
		return;
	}

	NsCar::stop();
	NsCar::moveBackward();

	delay(100);
	NsCar::stop();

	const int leftVal = NsUltrasonic::lookLeft();
	g_servo.write(SERVO_POINT);

	delay(800);

	const int rightVal = NsUltrasonic::lookRight();
	g_servo.write(SERVO_POINT);

	if (leftVal < rightVal)
		NsCar::moveRight();
	else if (leftVal > rightVal)
		NsCar::moveLeft();

	delay(500);
	NsCar::stop();

	// Is this because of a race condition?
	delay(200);
	delay(500);

	NsCar::stop();
	delay(200);
}

void voiceControlRoutine() {
	if (Serial.available() < 1)
		return;

	char receivedValue = Serial.read();
	DEBUG_PRINTLN("Received voice control: " + receivedValue);

	switch (receivedValue) {
		case '^':
			NsCar::moveForward();
			break;

		case '-':
			NsCar::moveBackward();
			break;

		case '<':
			const int leftVal = NsUltrasonic::lookLeft();
			g_servo.write(SERVO_POINT);

			if (leftVal >= 10) {
				NsCar::moveLeft();
				delay(500);
				NsCar::stop();
			} else if (leftVal < 10)
				NsCar::stop(); // Let's not worry about having an extra condition here!
			break;

		case '>':
			const int rightVal = NsUltrasonic::lookRight();
			g_servo.write(SERVO_POINT);
			if (rightVal >= 10) {
				NsCar::moveRight();
				delay(500);
				NsCar::stop();
			} else if (rightVal < 10) {
				NsCar::stop();
			}
			break;

		case '*':
			NsCar::stop();
			break;

		default:
			// TODO Make some error routine!
			break;
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

			return NsAppRoutines::AppRoutineAdditionError::ROUTINE_ALREADY_EXISTS;
		}

		// Older check. No longer needed!:
		// for (const auto &obj : s_routinesToClassNamesMap)
		// 	if (strcmp(obj.first, TYPE_NAME(RoutineT))) {
		// 		DEBUG_PRINT("Routine of type: `");
		// 		DEBUG_WRITE(TYPE_NAME(RoutineT));
		// 		DEBUG_WRITELN("` already exists. Didn't add it.");
		// 	}

		NsAppRoutines::AppRoutine *routine = new RoutineT();
		s_routinesToClassNamesMap[TYPE_NAME(RoutineT)] = routine;
		routine->setup();

		DEBUG_PRINT("Added routine of type: `");
		DEBUG_WRITE(TYPE_NAME(RoutineT));
		DEBUG_WRITELN("`.");

		return NsAppRoutines::AppRoutineAdditionError::NO_ERROR;
	}

	template <class RoutineT>
	bool removeRoutine() {
		for (auto it = s_routinesToClassNamesMap.begin(); it != s_routinesToClassNamesMap.end(); it++) {
			if (it->first == TYPE_NAME(RoutineT)) {
				NsAppRoutines::AppRoutine *routine = &(it->second);
				routine->out();
				delete routine;

				s_routinesToClassNamesMap.erase(it);

				DEBUG_PRINT("Removed routine of type: `");
				DEBUG_WRITE(TYPE_NAME(RoutineT));
				DEBUG_WRITELN("`.");

				// DEBUG_PRINT("Size of vector: ");
				// DEBUG_WRITELN(s_routinesToClassNamesMap.size());

				return true;
			}
		}

		DEBUG_PRINT("Found no removable routine of type: `");
		DEBUG_WRITE(TYPE_NAME(RoutineT));
		DEBUG_WRITELN("`.");

		return false;
	}
}
