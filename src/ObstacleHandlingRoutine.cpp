#include "Api/Globals.hpp"
#include "Api/DebuggingMacros.hpp"
#include "RoutineDecls/ObstacleHandlingRoutine.hpp"

#include "CarApi/NsCar.hpp"
#include "CarApi/NsServo.hpp"
#include "CarApi/NsBuzzer.hpp"
#include "CarApi/NsUltrasonic.hpp"

MAKE_TYPE_INFO(ObstacleHandlingRoutine);

// template bool NsAppRoutines::removeRoutine<ObstacleHandlingRoutine>();
// template NsAppRoutines::AppRoutineAdditionError NsAppRoutines::addRoutine<ObstacleHandlingRoutine>();

void ObstacleHandlingRoutine::loop() {
	ifu(this->stoppedForever) { // Set to be *unlikely* so that the upcoming stuff is speculatively executed.
		DEBUG_PRINTLN("Stopped forever...");
		return;
	}

	// ...
	// ...These boards surely *don't* have spec-ex! No way!
	// Yet I use `__builtin_expect()`. *Anyway*.

	// DEBUG_PRINTLN("The obstacle handling routine is executing!");

	// DEBUG_PRINTLN("Performing routinely distance check...");
	int forwardDist = NsUltrasonic::read();

	// DEBUG_PRINT("Distance: ");
	// DEBUG_WRITELN(forwardDist);
	// delay(100); // Do we not, not* need this?

	ifu(forwardDist > LEAST_DISTANCE_FOR_OBSTACLES_CM) {
		NsCar::moveForwardAsync();
		return;
	}

	DEBUG_PRINTLN("Car is moving backwards...");
	NsCar::stop(300);
	NsCar::moveBackward(500);
	NsCar::stop();

checkAgain:
	DEBUG_PRINTLN("Looking left...");
	int leftDist = NsUltrasonic::lookLeft();
	NsServo::servo.write(SERVO_STRAIGHT_ANGLE);

	delay(800);

	DEBUG_PRINTLN("Looking right...");
	int rightDist = NsUltrasonic::lookRight();
	NsServo::servo.write(SERVO_STRAIGHT_ANGLE);

	bool
		leftBlocked = leftDist < LEAST_DISTANCE_FOR_OBSTACLES_CM,
		rightBlocked = rightDist < LEAST_DISTANCE_FOR_OBSTACLES_CM;

	ifu(!(leftBlocked || rightBlocked)) {
		DEBUG_PRINTLN("No obstacles, going right...");
		// "ALWAYS GO FOR RIGHT!" - Dev.
		NsCar::moveRightOnSpot(1500);
		NsCar::stop();

		DEBUG_PRINTLN("No obstacles, reading distance...");
		forwardDist = NsUltrasonic::read();
		ifu(forwardDist > LEAST_DISTANCE_FOR_OBSTACLES_CM) {
			DEBUG_PRINTLN("Obstacle too far, continuing...");
			return;
		} else {
			DEBUG_PRINTLN("Obstacle may be in range, checking again...");
			goto checkAgain;
		}
	} else ifu(leftBlocked && rightBlocked) { // U-turn if there is no path ahead!:
		DEBUG_PRINTLN("No path! Starting buzzer...");
		NsBuzzer::buzzerStart(BUZZER_INTERVAL_NO_PATH);
		NsCar::stop();
		this->stoppedForever = true;
	} else ifl(leftBlocked) {
		DEBUG_PRINTLN("Left blocked...");
		NsCar::moveRightOnSpot(1500);
	} else ifl(rightBlocked) {
		DEBUG_PRINTLN("Right blocked...");
		NsCar::moveLeftOnSpot(1500);
	} else {
		DEBUG_PRINTLN("Nothing was blocked. But also was everything. *You shouldn't see be seeing this log!*");
	}

	NsCar::stop(900);
}
