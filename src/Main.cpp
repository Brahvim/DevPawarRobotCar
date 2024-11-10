#include "CarApi/NsCar.hpp"
#include "CarApi/NsServo.hpp"
#include "CarApi/NsBuzzer.hpp"
#include "CarApi/NsUltrasonic.hpp"

#include "Api/Main.hpp"
#include "Api/Tests.hpp"
#include "Api/Globals.hpp"
#include "Api/DebuggingMacros.hpp"

#include "Shared/ProtocolCarControls.hpp"

#include "RoutineDecls/CRoutineBuzzer.hpp"
#include "RoutineDecls/CRoutineObstacleHandling.hpp"
#include "RoutineDecls/CRoutineControlsListener.hpp"

void setup() {
	// "iS mY bOWl oF cErEAl hERe yET?!?1!1/":
	while (!Serial)// (For some reason, NOT attaching the USB cable still allows this.)
		;

	Serial.begin(ARDUINO_SERIAL_BAUD_RATE); // Macro in `Globals.hpp`.
	// Wire.setClock(100000);
	// Wire.begin(I2C_ADDR); // Macro in `ProtocolCarControls.hpp`.

	// Make sure we can talk with the ultrasonic sensor:
	pinMode(PIN_ULTRASONIC_TRIG, OUTPUT); // This guy triggers the sensor,
	pinMode(PIN_ULTRASONIC_ECHO, INPUT);  // ...This guy reports the distance back.
	pinMode(PIN_BUZZER, OUTPUT);

	// Set the motors up! All of 'em !:
	NsServo::servo.attach(PIN_SERVO);

	NsCar::motors[0].setSpeed(WHEEL_SPEED);
	NsCar::motors[1].setSpeed(WHEEL_SPEED);
	NsCar::motors[2].setSpeed(WHEEL_SPEED);
	NsCar::motors[3].setSpeed(WHEEL_SPEED);

	NsRoutines::addRoutine<CRoutineBuzzer>();
	NsRoutines::addRoutine<CRoutineObstacleHandling>();
	// NsRoutines::addRoutine<CRoutineControlsListener>();

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
