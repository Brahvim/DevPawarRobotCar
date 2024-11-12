#include "Car.h"
#include "Ifs.h"
#include "Main.h"
#include "LoggingProjectWide.h"
#include "ProtocolCarControls.h"

void setup() {
	logSetupLogging();

	pinMode(PIN_ANALOG_ULTRASONIC_TRIGGER, OUTPUT); // This guy triggers a sound wave,
	pinMode(PIN_ANALOG_ULTRASONIC_ECHO, INPUT);  // ...This girl reports that it arrived back.
	pinMode(PIN_ANALOG_BUZZER, OUTPUT);
	// pinMode(PIN_DIGITAL_SERVO, OUTPUT);

	g_carServo.attach(PIN_DIGITAL_SERVO);

	g_routineStoppedCall = g_routineNullImpl;
	g_routineControlsListenerCall = g_routineNullImpl;

	attachInterrupt(digitalPinToInterrupt(PIN_DIGITAL_ARDUINO_1), carModeCbck, CHANGE);

	g_carMotors[0].setSpeed(CAR_WHEEL_SPEED);
	g_carMotors[1].setSpeed(CAR_WHEEL_SPEED);
	g_carMotors[2].setSpeed(CAR_WHEEL_SPEED);
	g_carMotors[3].setSpeed(CAR_WHEEL_SPEED);
}

void loop() {
	g_routineBuzzerCall();
	g_routineStoppedCall();
	g_routineControlsListenerCall();
	g_routineObstacleHandlingCall();
}
