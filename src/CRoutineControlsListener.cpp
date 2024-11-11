#include <memory>
#include <Arduino.h>

#include "Api/Main.hpp"
#include "Api/Globals.hpp"
#include "Api/DebuggingMacros.hpp"

#include "CarApi/NsCar.hpp"

#include "Shared/ProtocolCarControls.hpp"

#include "RoutineDecls/CRoutineSwitchActuator.hpp"
#include "RoutineDecls/CRoutineControlsListener.hpp"
#include "RoutineDecls/CRoutineObstacleHandling.hpp"

MAKE_TYPE_INFO(CRoutineControlsListener);

void CRoutineControlsListener::loop() {
	pinMode(PIN_CAR_ARDUINO_1, INPUT);
	pinMode(PIN_CAR_ARDUINO_2, INPUT);
	// pinMode(PIN_CAR_ARDUINO_STEER, INPUT);

	int const reading1 = digitalRead(PIN_CAR_ARDUINO_1);
	int const reading2 = digitalRead(PIN_CAR_ARDUINO_2);
	int const readingSteer = analogRead(PIN_CAR_ARDUINO_STEER);

	// Steering:

	// uint8_t const steering = map(readingSteer, 0, 1023, 0, 255); // `int` to `char`.
	uint8_t const steering = readingSteer; // Should be in [0, 255].
	DEBUG_PRINT("Steering read: `");
	DEBUG_APPEND(steering);
	DEBUG_APPEND("`. ");

	NsCar::motors[0].setSpeed(steering); // Right.
	NsCar::motors[1].setSpeed(1023 - steering); // Left.
	NsCar::motors[2].setSpeed(1023 - steering); // Left.
	NsCar::motors[3].setSpeed(steering); // Right.

	bool const
		gearStop = !(reading1 && reading2), // Does routine stuff.
		gearNeutral = reading1 && reading2,
		gearForwards = reading1 && !reading2,
		gearBackwards = !reading1 && reading2;

	ifl(gearForwards) {

		NsCar::moveForwardAsync();
		DEBUG_PRINTLN("Car gear forwards.");

	} else ifl(gearBackwards) {

		NsCar::moveBackwardAsync();
		DEBUG_PRINTLN("Car gear backwards.");

	} else ifu(gearNeutral) {

		NsCar::stop();
		DEBUG_PRINTLN("Car gear neutral.");

	} else ifu(gearStop) {

		NsCar::stop();
		DEBUG_PRINTLN("Car now in obstacle avoidance mode.");

		NsRoutines::addRoutine<CRoutineSwitchActuator>();
		NsRoutines::addRoutine<CRoutineObstacleHandling>();

		NsRoutines::removeRoutine<CRoutineControlsListener>();

		pinMode(PIN_CAR_ARDUINO_1, INPUT_PULLUP);
		pinMode(PIN_CAR_ARDUINO_2, INPUT_PULLUP);
		// pinMode(PIN_CAR_ARDUINO_STEER, INPUT_PULLUP);

	}
}
