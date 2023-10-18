#define ENABLE_DEBUG_LOGS

#pragma region Includes.
#include "DebuggingMacros.hpp"
#include "Globals.hpp" // Has more `#include` directives!
#include "NsAppRoutines.hpp"
#include "NsCar.hpp"

#include <AFMotor.h>
#include <Servo.h>
#include <Vector.h>
#pragma endregion

#pragma region Global definitions.
const Servo g_servo;
#pragma endregion

#pragma region Static declarations.
static NsAppRoutines::AppRoutine s_routineStorage[10];

// This library automatically uses references in the type specified:
static Vector<NsAppRoutines::AppRoutine> s_routinesVector;
#pragma endregion

void setup() {
	while (!Serial)
		;
	Serial.begin(ARDUINO_SERIAL_BAUD_RATE); // Macro in `Globals.hpp`.

	s_routinesVector.setStorage(s_routineStorage);

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

	DEBUG_PRINT("Size of vector: ");
	DEBUG_WRITELN(s_routinesVector.size());
}

void loop() {
	for (const auto &r : s_routinesVector) {
		r.loop();
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
		for (const auto &obj : s_routinesVector)
			if (TYPE_NAME(obj) == TYPE_NAME(RoutineT))
				return NsAppRoutines::AppRoutineAdditionError::ROUTINE_ALREADY_EXISTS;

		const AppRoutine *routine = new RoutineT();
		s_routinesVector.push_back(*routine);

		DEBUG_PRINT("Added routine of type: `");
		DEBUG_WRITE(TYPE_NAME(RoutineT));
		DEBUG_WRITELN("`.");

		return NsAppRoutines::AppRoutineAdditionError::NO_ERROR;
	}

	template <class RoutineT>
	bool removeRoutine() {
		// Checking against a method call here since... threads.
		// Yeah. On a completely serial order device too!:
		for (size_t i = 0; i < s_routinesVector.size(); i++) {
			const auto &obj = s_routinesVector[i];
			if (TYPE_NAME(obj) == TYPE_NAME(RoutineT)) {
				DEBUG_PRINT("Removed routine of type: `");
				DEBUG_WRITE(TYPE_NAME(RoutineT));
				DEBUG_WRITELN("`.");

				s_routinesVector.remove(i);
				return true;
			}
		}
		return false;
	}

}
