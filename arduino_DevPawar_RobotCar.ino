#pragma region Includes.
#include "Globals.hpp" // Has more `#include` directives!
#include "NsCar.hpp"

#include <Vector.h>
#pragma endregion

// #pragma region Static declarations.
static Vector<NsAppRoutines::AppRoutine> s_routinesVector;
// #pragma endregion

namespace NsAppRoutines {
	// Apparently references are always non-`nullptr`!
	NsAppRoutines::AppRoutineAdditionError addRoutine(const NsAppRoutines::AppRoutine &p_routine) {
		for (const VectorIterator<NsAppRoutines::AppRoutine> it = s_routinesVector.begin();
			 it != s_routinesVector.end(); it++) {
			auto obj = *it;
			if (TYPE_NAME(p_routine) == TYPE_NAME(obj))
				return NsAppRoutines::AppRoutineAdditionError::ROUTINE_ALREADY_EXISTS;
		}

		s_routinesVector.push_back(p_routine);
		return NsAppRoutines::AppRoutineAdditionError::NO_ERROR;
	}

	void removeRoutine(const NsAppRoutines::AppRoutine &p_routine) {
		for (const VectorIterator<NsAppRoutines::AppRoutine> it = s_routinesVector.begin();
			 it != s_routinesVector.end(); it++)
			;
	}
}

void setup() {
	while (!Serial)
		;

	Serial.begin(ARDUINO_SERIAL_BAUD_RATE); // Macro in `Globals.hpp`.

	// Make sure we can talk with the ultrasonic sensor:
	pinMode(PIN_ULTRASONIC_ECHO, INPUT);
	pinMode(PIN_ULTRASONIC_TRIG, OUTPUT);

	g_servo.attach(PIN_SERVO);

	g_dcMotors[1].setSpeed(WHEEL_SPEED);
	g_dcMotors[2].setSpeed(WHEEL_SPEED);
	g_dcMotors[3].setSpeed(WHEEL_SPEED);
	g_dcMotors[4].setSpeed(WHEEL_SPEED);

	start();
}

void loop() {
	obstacleRoutine();
	voiceControlRoutine(); // Should come after `bluetoothControlRoutine()`...?
	bluetoothControlRoutine();
}

void bluetoothControlRoutine() {
	if (Serial.available() < 1)
		return;

	// Unconventional, but accounts for bad cases without `<=`.
	// Also, faster! :>

	switch (Serial.read()) {
		case 'F':
			NsCar::forward();
			break;

		case 'B':
			NsCar::backward();
			break;

		case 'L':
			NsCar::left();
			break;

		case 'R':
			NsCar::right();
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
		NsCar::forward();
		return;
	}

	NsCar::stop();
	NsCar::backward();

	delay(100);
	NsCar::stop();

	const int leftVal = NsCar::lookLeft();
	g_servo.write(SERVO_POINT);

	delay(800);

	const int rightVal = NsCar::lookRight();
	g_servo.write(SERVO_POINT);

	if (leftVal < rightVal)
		NsCar::right();
	else if (leftVal > rightVal)
		NsCar::left();

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
			NsCar::forward();
			break;

		case '-':
			NsCar::backward();
			break;

		case '<':
			const int leftVal = NsCar::lookLeft();
			g_servo.write(SERVO_POINT);

			if (leftVal >= 10) {
				NsCar::left();
				delay(500);
				NsCar::stop();
			} else if (leftVal < 10)
				NsCar::stop(); // Let's not worry about having an extra condition here!
			break;

		case '>':
			const int rightVal = NsCar::lookRight();
			g_servo.write(SERVO_POINT);
			if (rightVal >= 10) {
				NsCar::right();
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
