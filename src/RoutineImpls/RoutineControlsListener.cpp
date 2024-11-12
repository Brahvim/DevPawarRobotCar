#include "Ifs.h"
#include "Main.h"
#include "LoggingProjectWide.h"
#include "ProtocolCarControls.h"

static void impl();
static int readingSteerPrevious = 0;
static routine_t s_implCall = g_routineNullImpl;

static void impl() {
	pinMode(CAR_PIN_DIGITAL_ARDUINO_1, INPUT);
	pinMode(CAR_PIN_DIGITAL_ARDUINO_2, INPUT);
	// pinMode(CAR_PIN_ANALOG_ARDUINO_STEER, INPUT);

	int const reading1 = digitalRead(CAR_PIN_DIGITAL_ARDUINO_1);
	int const reading2 = digitalRead(CAR_PIN_DIGITAL_ARDUINO_2);
	int const readingSteer = analogRead(CAR_PIN_ANALOG_ARDUINO_STEER);

	// Steering:

	// uint8_t const steering = map(readingSteer, 0, 1023, 0, 255); // `int` to `char`.
	uint8_t const steering = readingSteer; // Should be in [0, 255].

	if (readingSteerPrevious != readingSteer) {
		logd("Steering read: `%c`.", steering);

		g_carMotors[0].setSpeed(steering); // Right.
		g_carMotors[1].setSpeed(1023 - steering); // Left.
		g_carMotors[2].setSpeed(1023 - steering); // Left.
		g_carMotors[3].setSpeed(steering); // Right.
	}

	bool const
		gearStop = !(reading1 && reading2), // Does routine stuff.
		gearNeutral = reading1 && reading2,
		gearForwards = reading1 && !reading2,
		gearBackwards = !reading1 && reading2;

	ifl(gearForwards) {

		carMoveForwards();
		logds("Car gear forwards.");

	} else ifl(gearBackwards) {

		carMoveBackwards();
		logds("Car gear backwards.");

	} else ifu(gearNeutral) {

		carMoveStop();
		logds("Car gear neutral.");

	} else ifu(gearStop) {

		carMoveStop();
		carModeSetObstacleAvoidance();
		logds("Car now in obstacle avoidance mode.");

		pinMode(CAR_PIN_DIGITAL_ARDUINO_1, INPUT_PULLUP);
		pinMode(CAR_PIN_DIGITAL_ARDUINO_2, INPUT_PULLUP);
		// pinMode(CAR_PIN_ANALOG_ARDUINO_STEER, INPUT_PULLUP);

	}
};

void routineControlsListenerRun() {
	s_implCall();
}

void routineControlsListenerEnable() {
	s_implCall = impl;
}

void routineControlsListenerDisable() {
	s_implCall = g_routineNullImpl;
}

bool routineControlsListenerIsRunning() {
	return s_implCall == impl;
}
