#include "Api/Globals.hpp"
#include "Api/DebuggingMacros.hpp"
#include "RoutineDecls/RoutineStoppedForever.hpp"
#include "RoutineDecls/RoutineObstacleHandling.hpp"

#include "CarApi/NsCar.hpp"
#include "CarApi/NsServo.hpp"
#include "CarApi/NsBuzzer.hpp"
#include "CarApi/NsUltrasonic.hpp"

MAKE_TYPE_INFO(RoutineObstacleHandling);

// template bool NsAppRoutines::removeRoutine<RoutineObstacleHandling>();
// template NsAppRoutines::AppRoutineAdditionError NsAppRoutines::addRoutine<RoutineObstacleHandling>();

void RoutineObstacleHandling::loop() {
	int forwardDist = NsUltrasonic::read();

	// DEBUG_PRINT("Distance: ");
	// DEBUG_WRITELN(forwardDist);

	ifu(forwardDist > LEAST_DISTANCE_FOR_OBSTACLES_CM) {
		NsCar::moveForwardAsync();
		return;
	}

	DEBUG_PRINTLN("Car is moving backwards...");
	NsCar::stop(300);
	NsCar::moveBackward(500);
	NsCar::stop();

labelCheckAgain:
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
		NsCar::moveRight(1500);
		NsCar::stop();

		DEBUG_PRINTLN("No obstacles, reading distance...");
		forwardDist = NsUltrasonic::read();
		ifu(forwardDist > LEAST_DISTANCE_FOR_OBSTACLES_CM) {
			DEBUG_PRINTLN("Obstacle too far, continuing...");
			return;
		} else {
			DEBUG_PRINTLN("Obstacle may be in range, checking again...");
			goto labelCheckAgain;
		}
	} else ifu(leftBlocked && rightBlocked) { // U-turn if there is no path ahead!:
		NsBuzzer::buzzerStartAsyncBeeps(BUZZER_INTERVAL_NO_PATH);
		NsAppRoutines::removeRoutine<RoutineObstacleHandling>();
		RoutineStoppedForever::reason = "No path ahead car!";
		NsAppRoutines::addRoutine<RoutineStoppedForever>();
		DEBUG_PRINTLN("No path!");
		NsCar::stop();
	} else ifl(leftBlocked) {
		DEBUG_PRINTLN("Left blocked...");
		NsCar::moveRight(1500);
	} else ifl(rightBlocked) {
		DEBUG_PRINTLN("Right blocked...");
		NsCar::moveLeft(1500);
	} else {
		DEBUG_PRINTLN("Nothing was blocked. But also was everything. *You shouldn't see be seeing this log!*");
	}

	NsCar::stop(900);
}
