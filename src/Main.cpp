#include "Car.h"
#include "Ifs.h"
#include "Main.h"
#include "LoggingProjectWide.h"
#include "ProtocolCarControls.h"

void setup() {
	logSetupLogging();

	pinMode(PIN_ANALOG_ULTRASONIC_TRIGGER, OUTPUT); // This guy triggers the sensor,
	pinMode(PIN_ANALOG_ULTRASONIC_ECHO, INPUT);  // ...This girl reports the distance back.
	pinMode(PIN_ANALOG_BUZZER, OUTPUT);

	// pinMode(PIN_DIGITAL_SERVO, OUTPUT);

	g_carServo.attach(PIN_DIGITAL_SERVO);

	g_routineStoppedCall = g_routineNullImpl;
	g_routineControlsListenerCall = g_routineNullImpl;

	attachInterrupt(digitalPinToInterrupt(PIN_DIGITAL_CAR_ARDUINO_1), carModeCbck, CHANGE);
}

void loop() {
	g_routineBuzzerCall();
	g_routineStoppedCall();
	g_routineControlsListenerCall();
	g_routineObstacleHandlingCall();
}

void carModeCbck() {
	ifu(g_routineControlsListenerCall == g_routineNullImpl) {
		g_routineObstacleHandlingCall = g_routineNullImpl;
		g_routineControlsListenerCall = g_routineControlsListenerImpl;
	} else {
		g_routineObstacleHandlingCall = g_routineObstacleHandlingImpl;
		g_routineControlsListenerCall = g_routineNullImpl;
	}
}
