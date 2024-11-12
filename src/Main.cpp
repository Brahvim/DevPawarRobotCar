#include "Car.h"
#include "Ifs.h"
#include "Main.h"
#include "Buzzer.h"
#include "LoggingProjectWide.h"
#include "ProtocolCarControls.h"

void setup() {
	logSetupLogging();

	pinMode(CAR_PIN_ANALOG_ULTRASONIC_TRIGGER, OUTPUT); // This guy triggers a sound wave,
	pinMode(CAR_PIN_ANALOG_ULTRASONIC_ECHO, INPUT);  // ...This girl reports that it arrived back.
	pinMode(CAR_PIN_ANALOG_BUZZER, OUTPUT);
	// pinMode(CAR_PIN_DIGITAL_SERVO, OUTPUT);

	g_carServo.attach(CAR_PIN_DIGITAL_SERVO);

	routineBuzzerEnable();
	routineObstacleHandlingEnable();

	attachInterrupt(digitalPinToInterrupt(CAR_PIN_DIGITAL_ARDUINO_1), carCbckMode, CHANGE);

	g_carMotors[0].setSpeed(CAR_WHEEL_SPEED);
	g_carMotors[1].setSpeed(CAR_WHEEL_SPEED);
	g_carMotors[2].setSpeed(CAR_WHEEL_SPEED);
	g_carMotors[3].setSpeed(CAR_WHEEL_SPEED);

	logis("Car started! Beeping to notify.");
	buzzerPlayStartupBeeps();
}

void loop() {
	routineBuzzerRun();
	routineStoppedRun();
	routineControlsListenerRun();
	routineObstacleHandlingRun();
}
