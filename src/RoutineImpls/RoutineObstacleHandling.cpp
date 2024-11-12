#include "Ifs.h"
#include "Car.h"
#include "Main.h"
#include "LoggingProjectWide.h"

static void impl();
static routine_t s_implCall = g_routineNullImpl;

static void impl() {
	unsigned long forwardDist = carSensorUltrasonicRead();

	// DEBUG_PRINT("Forward distance: ");
	// DEBUG_APPENDLN(forwardDist);

	ifu(forwardDist > CAR_LEAST_DISTANCE_CM) {
		carMoveForwards();
		return;
	}

	logis("Car is moving backwards...");
	carMoveStop(300);
	carMoveBackwards(500);
	carMoveStop();

labelCheckAgain:
	logis("Looking left...");
	g_carServo.write(180);
	delay(800);

	unsigned long const cmLeft = carSensorUltrasonicRead();
	logi("Left distance: `%ld`.", cmLeft);
	g_carServo.write(CAR_SERVO_ANGLE_STRAIGHT);

	delay(800);

	logis("Looking right...");
	g_carServo.write(20);
	delay(800);

	unsigned long const cmRight = carSensorUltrasonicRead();
	logi("Right distance: `%ld`.", cmRight);
	g_carServo.write(CAR_SERVO_ANGLE_STRAIGHT);

	bool
		isBlockedLeft = cmLeft < CAR_LEAST_DISTANCE_CM,
		isBlockedRight = cmRight < CAR_LEAST_DISTANCE_CM;

	ifu(isBlockedLeft || isBlockedRight) { // For all blockages.
		logis("Car is moving backwards...");
		carMoveStop(300);
		carMoveBackwards(500);
		carMoveStop();
	}

	ifu(!(isBlockedLeft || isBlockedRight)) { // No blockages...

		logis("No obstacles, going right...");
		carMoveRight(1500); // "ALWAYS GO FOR RIGHT!" - Dev.
		carMoveStop();

		logis("Re-reading...");
		forwardDist = carSensorUltrasonicRead();

		ifu(forwardDist > CAR_LEAST_DISTANCE_CM) {
			logis("Obstacle too far, continuing...");
			return;
		} else {
			logis("Obstacle may be in range, checking again...");
			goto labelCheckAgain;
		}

	} else ifu(isBlockedLeft && isBlockedRight) { // U-turn if there is no path ahead!:

		// CRoutineStoppedForever::reason = EcRoutineStoppedForeverCallReason::PATH;
		// NsBuzzer::buzzerStartAsyncBeeps(CAR_BUZZER_INTERVAL_NO_PATH);
		// NsRoutines::removeRoutine<CRoutineObstacleHandling>();
		// NsRoutines::addRoutine<CRoutineStoppedForever>();
		loges("No path!");
		carMoveStop();

	} else ifl(isBlockedLeft) {

		logis("Going right, left blocked...");
		carMoveRight(1500);

	} else ifl(isBlockedRight) {

		logis("Going left, right blocked...");
		carMoveLeft(1500);

	} else {

		loges("Nothing was blocked. But also was everything. *You shouldn't see be seeing this log!*");

	}

	carMoveStop(900);
};

void routineObstacleHandlingRun() {
	s_implCall();
}

void routineObstacleHandlingEnable() {
	s_implCall = impl;
}

void routineObstacleHandlingDisable() {
	s_implCall = g_routineNullImpl;
}

bool routineObstacleHandlingIsRunning() {
	return s_implCall == impl;
}
