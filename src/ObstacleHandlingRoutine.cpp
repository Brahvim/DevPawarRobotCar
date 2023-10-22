#define ENABLE_DEBUG_LOGS

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

	const int dist = NsUltrasonic::read(); // Could use this info later!
	// DEBUG_PRINT("Distance: ");
	DEBUG_WRITELN(dist);
	delay(100);

	if (dist > 12) {
		NsCar::moveForward();
		return;
	}

	NsCar::stop();
	NsCar::moveBackward();

	delay(100);
	NsCar::stop();

	const int leftVal = NsUltrasonic::lookLeft();
	NsServo::servo.write(SERVO_POINT);

	delay(800);

	const int rightVal = NsUltrasonic::lookRight();
	NsServo::servo.write(SERVO_POINT);

	if (leftVal < rightVal)
		NsCar::moveRight();
	else if (leftVal > rightVal)
		NsCar::moveLeft();

	delay(500);
	NsCar::stop();

	// Is this because of a race condition?
	delay(200);
	delay(500);

	NsCar::stop();
	delay(200);
}
