#include "../include/Api/Globals.hpp"
#include "../include/Api/DebuggingMacros.hpp"

#include "../include/RoutineDecls/ObstacleHandlingRoutine.hpp"

#include "../include/CarApi/NsCar.hpp"
#include "../include/CarApi/NsServo.hpp"
#include "../include/CarApi/NsUltrasonic.hpp"

MAKE_TYPE_INFO(ObstacleHandlingRoutine);

// template bool NsAppRoutines::removeRoutine<ObstacleHandlingRoutine>();
// template NsAppRoutines::AppRoutineAdditionError NsAppRoutines::addRoutine<ObstacleHandlingRoutine>();

void ObstacleHandlingRoutine::loop() {
	// DEBUG_PRINTLN("The obstacle handling routine is executing!");

	const int distance = NsUltrasonic::read();

	// DEBUG_PRINT("Distance: ");
	// DEBUG_WRITELN(dist);
	// delay(100); // Do we not, not need this?

	if (distance > LEAST_DISTANCE_FOR_OBSTACLES) {
		NsCar::moveForward();
		return;
	}

	NsCar::stop(500);
	NsCar::moveBackward(500);
	NsCar::stop(500);

	int leftDist = NsUltrasonic::lookLeft();
	NsServo::servo.write(SERVO_STRAIGHT_ANGLE);

	delay(800);

	int rightDist = NsUltrasonic::lookRight();
	NsServo::servo.write(SERVO_STRAIGHT_ANGLE);

	const bool
		leftBlocked = leftDist < LEAST_DISTANCE_FOR_OBSTACLES,
		rightBlocked = rightDist < LEAST_DISTANCE_FOR_OBSTACLES;

	if (!(leftBlocked || rightBlocked)) {
		leftDist = NsUltrasonic::lookLeft();
		NsServo::servo.write(SERVO_STRAIGHT_ANGLE);

		delay(800);

		rightDist = NsUltrasonic::lookRight();
		NsServo::servo.write(SERVO_STRAIGHT_ANGLE);

		goto lastCase;
	}

	// U-turn if there is no path ahead!:
	if (leftBlocked && rightBlocked) {
		// Dev's idea: ALWAYS go for right.
		// Scan again, if there's room on the any side, go there.
		// Else, go back, go left, BUZZ!

		

		/*
		bool leftHasLessRoom = leftDist <= rightDist;

		if (leftHasLessRoom)
			NsCar::moveRight(2500);
		else
			NsCar::moveLeft(2500);

		NsCar::stop(500);

		// Re-do!:
		leftDist = NsUltrasonic::lookLeft();
		NsServo::servo.write(SERVO_STRAIGHT_ANGLE);

		delay(800);

		rightDist = NsUltrasonic::lookRight();
		NsServo::servo.write(SERVO_STRAIGHT_ANGLE);

		leftHasLessRoom = leftDist <= rightDist;

		if (leftHasLessRoom)
			NsCar::moveRight(2500);
		else
			NsCar::moveLeft(2500);

		delay(2500);

		*/

	} else if (leftBlocked)
		NsCar::moveRight(1500);
	else if (rightBlocked)
		NsCar::moveLeft(1500);
	else {

	}

	// if (leftVal < rightVal)
	// 	NsCar::moveLeft();
	// else if (leftVal > rightVal)
	// 	NsCar::moveRight();

lastCase:
	NsCar::stop(900);

}
