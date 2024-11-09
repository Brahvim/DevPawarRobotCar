#include "CarApi/NsCar.hpp"
#include "CarApi/NsServo.hpp"
#include "CarApi/NsBuzzer.hpp"
#include "CarApi/NsUltrasonic.hpp"

#include "Api/Globals.hpp"
#include "Api/DebuggingMacros.hpp"
#include "RoutineDecls/CRoutineStoppedForever.hpp"
#include "RoutineDecls/CRoutineObstacleHandling.hpp"

MAKE_TYPE_INFO(CRoutineObstacleHandling);

void CRoutineObstacleHandling::loop() {
	int forwardDist = NsUltrasonic::read();

	DEBUG_PRINT("Forward distance: ");
	DEBUG_WRITELN(forwardDist);

	ifu(forwardDist > LEAST_DISTANCE_FOR_OBSTACLES_CM) {
		NsCar::moveForwardAsync();
		return;
	}

	DEBUG_PRINTLN("Car is moving backwards...");
	NsCar::stop(300);
	NsCar::moveBackward(500);
	NsCar::stop();

labelCheckAgain:
	DEBUG_PRINT("Looking left... ");
	NsServo::servo.write(180);
	delay(800);

	int const cmLeft = NsUltrasonic::read();
	NsServo::servo.write(SERVO_STRAIGHT_ANGLE);
	DEBUG_WRITE("Distance: ");
	DEBUG_WRITELN(cmLeft);

	delay(800);

	DEBUG_PRINT("Looking right... ");
	NsServo::servo.write(20);
	delay(800);

	int const cmRight = NsUltrasonic::read();
	NsServo::servo.write(SERVO_STRAIGHT_ANGLE);
	DEBUG_WRITE("Distance: ");
	DEBUG_WRITELN(cmRight);

	bool
		isBlockedLeft = cmLeft < LEAST_DISTANCE_FOR_OBSTACLES_CM,
		isBlockedRight = cmRight < LEAST_DISTANCE_FOR_OBSTACLES_CM;

	ifu(isBlockedLeft || isBlockedRight) { // For all blockages.
		DEBUG_PRINTLN("Car is moving backwards...");
		NsCar::stop(300);
		NsCar::moveBackward(500);
		NsCar::stop();
	}

	ifu(!(isBlockedLeft || isBlockedRight)) { // No blockages...

		DEBUG_PRINTLN("No obstacles, going right...");
		NsCar::moveRight(1500); // "ALWAYS GO FOR RIGHT!" - Dev.
		NsCar::stop();

		DEBUG_PRINTLN("Re-reading...");
		forwardDist = NsUltrasonic::read();

		ifu(forwardDist > LEAST_DISTANCE_FOR_OBSTACLES_CM) {
			DEBUG_PRINTLN("Obstacle too far, continuing...");
			return;
		} else {
			DEBUG_PRINTLN("Obstacle may be in range, checking again...");
			goto labelCheckAgain;
		}

	} else ifu(isBlockedLeft && isBlockedRight) { // U-turn if there is no path ahead!:
		CRoutineStoppedForever::reason = EcRoutineStoppedForeverCallReason::PATH;
		NsBuzzer::buzzerStartAsyncBeeps(BUZZER_INTERVAL_NO_PATH);
		NsRoutines::removeRoutine<CRoutineObstacleHandling>();
		NsRoutines::addRoutine<CRoutineStoppedForever>();
		DEBUG_PRINTLN("No path!");
		NsCar::stop();
	} else ifl(isBlockedLeft) {
		DEBUG_PRINTLN("Left blocked...");
		NsCar::moveRight(1500);
	} else ifl(isBlockedRight) {
		DEBUG_PRINTLN("Right blocked...");
		NsCar::moveLeft(1500);
	} else {
		DEBUG_PRINTLN("Nothing was blocked. But also was everything. *You shouldn't see be seeing this log!*");
	}

	NsCar::stop(900);
}
