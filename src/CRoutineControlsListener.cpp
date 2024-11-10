#include <memory>
#include <Arduino.h>

#include "Api/Main.hpp"
#include "Api/Globals.hpp"
#include "Api/DebuggingMacros.hpp"

#include "CarApi/NsCar.hpp"
#include "CarApi/NsI2c.hpp"

#include "RoutineDecls/CRoutineControlsListener.hpp"

MAKE_TYPE_INFO(CRoutineControlsListener);

using namespace NsControls;

void CRoutineControlsListener::loop() {
	pinMode(A5, INPUT);
	pinMode(A4, INPUT);

	int const readingA4 = analogRead(A4); // Steering.
	int const readingA5 = analogRead(A5); // Forwards/Backwards movement via [-1, 1] values.

	if (readingA4 == 0 || readingA5 == 0)
		return;

	// DEBUG_PRINT("[Steer, Gear] read: ");
	// DEBUG_APPEND(readingA4); DEBUG_APPEND(" "); DEBUG_APPENDLN(readingA5);

	// NsCar::motors[0].setSpeed(127 + (uint8_t) ((readingA4 * WHEEL_SPEED) / 1024));
	// NsCar::motors[1].setSpeed(-127 + (uint8_t) ((readingA4 * WHEEL_SPEED) / 1024));
	// NsCar::motors[2].setSpeed(-127 + (uint8_t) ((readingA4 * WHEEL_SPEED) / 1024));
	// NsCar::motors[3].setSpeed(127 + (uint8_t) ((readingA4 * WHEEL_SPEED) / 1024));

	bool const
		inRangeBackwards = readingA5 < 450,
		inRangeForwards = readingA5 > 550,
		inRangeStop = !(inRangeBackwards || inRangeForwards);

	ifl(inRangeForwards) {

		NsCar::moveForwardAsync();
		DEBUG_PRINTLN("Car will go forwards.");

	} else ifl(inRangeBackwards) {

		NsCar::moveBackwardAsync();
		DEBUG_PRINTLN("Car will go backwards.");

	} else ifu(inRangeStop) {

		NsCar::stop();
		DEBUG_PRINTLN("Car has stopped.");

	}

}
