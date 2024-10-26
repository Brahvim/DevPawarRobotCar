#include "CarApi/NsCar.hpp"
#include "CarApi/NsBuzzer.hpp"

#include "Api/Main.hpp"
#include "Api/Globals.hpp"
#include "Api/NsRoutines.hpp"
#include "Api/CustomSetup.hpp"
#include "Api/DebuggingMacros.hpp"

#include "RoutineDecls/CRoutineBuzzer.hpp"
#include "RoutineDecls/CRoutineBluetooth.hpp"
#include "RoutineDecls/CRoutineObstacleHandling.hpp"

void wheelTest() {
	delay(2000);
	NsCar::stop();
	NsCar::motors[0].run(FORWARD);

	delay(2000);
	NsCar::stop();
	NsCar::motors[1].run(FORWARD);

	delay(2000);
	NsCar::stop();
	NsCar::motors[2].run(FORWARD);

	delay(2000);
	NsCar::stop();
	NsCar::motors[3].run(FORWARD);
}

void sideTest() {
	delay(500);
	NsCar::moveLeft(1000);

	delay(500);
	NsCar::moveRight(1000);
}

void start() {
	NsRoutines::addRoutine<CRoutineBuzzer>();
	// NsRoutines::addRoutine<CRoutineBluetooth>();
	NsRoutines::addRoutine<CRoutineObstacleHandling>();
}
