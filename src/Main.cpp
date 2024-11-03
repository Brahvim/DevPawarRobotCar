#include <Wire.h>

#include "CarApi/NsCar.hpp"
#include "CarApi/NsServo.hpp"
#include "CarApi/NsBuzzer.hpp"
#include "CarApi/NsUltrasonic.hpp"

#include "Api/Main.hpp"
#include "Api/Globals.hpp"
#include "Api/DebuggingMacros.hpp"

#include "RoutineDecls/CRoutineBuzzer.hpp"
#include "RoutineDecls/CRoutineObstacleHandling.hpp"

void setup() {
	// "iS mY bOWl oF cErEAl hERe yET?!?1!1/":
	while (!Serial)
		;
	// (For some reason, NOT attaching the USB cable still allows this.)

	Wire.begin();
	Wire.setWireTimeout(5);
	Serial.begin(ARDUINO_SERIAL_BAUD_RATE); // Macro in `Globals.hpp`.

	// Make sure we can talk with the ultrasonic sensor:
	pinMode(PIN_ULTRASONIC_TRIG, OUTPUT); // This guy triggers the sensor,
	pinMode(PIN_ULTRASONIC_ECHO, INPUT);  // ...This guy reports the distance back.
	pinMode(PIN_BUZZER, OUTPUT);

	// Set the motors up! All of 'em !:
	NsServo::servo.attach(PIN_SERVO);

	// `AF_DCMotor::setSpeed()` goes through a WHOLE `switch` over
	// the motor number to set some addresses to `WHEEL_SPEED`... *sad*.
	// ...At least that's what VSCode highlightion showed.
	// ...For the Arduino Uno.

	// ...Let's not be pathetic, then!:
	/* NsCar::motors[1].setSpeed(WHEEL_SPEED); */ OCR2A = WHEEL_SPEED;
	/* NsCar::motors[2].setSpeed(WHEEL_SPEED); */ OCR2B = WHEEL_SPEED;
	/* NsCar::motors[3].setSpeed(WHEEL_SPEED); */ OCR0A = WHEEL_SPEED;
	/* NsCar::motors[4].setSpeed(WHEEL_SPEED); */ OCR0B = WHEEL_SPEED;


	NsRoutines::addRoutine<CRoutineBuzzer>();
	NsRoutines::addRoutine<CRoutineObstacleHandling>();

	DEBUG_PRINTLN("Beginning Arduino loop.");
}

void loop() {
	// DEBUG_WRITELN("In Arduino loop.");
	// DEBUG_PRINT("Size of vector: ");
	// DEBUG_WRITELN(g_routinesToClassNamesMap.size());

	// ifu (Serial.available() > 1)
	// 	DEBUG_PRINTLN("Received something on the serial line!");

	// So we... iterate over 'em all, and...
	// ...yeah, you get the point!:
	for (auto it = g_routinesToClassNamesMap.begin(); it != g_routinesToClassNamesMap.end(); ++it) {
		// DEBUG_PRINT("Running routine `");
		// DEBUG_WRITE(it->first);
		// DEBUG_WRITELN("`.");
		it->second->loop();
	}
}
