#include "Api/Main.hpp"
#include "Api/Globals.hpp"

#include "CarApi/NsBuzzer.hpp"

#include "Api/CustomSetup.hpp"
#include "Api/NsAppRoutines.hpp"
#include "Api/DebuggingMacros.hpp"

#include "RoutineDecls/BuzzerRoutine.hpp"
#include "RoutineDecls/BluetoothRoutine.hpp"
#include "RoutineDecls/ObstacleHandlingRoutine.hpp"

void sideTest() {
	delay(500);
	NsCar::moveLeft(1000);

	delay(500);
	NsCar::moveRight(1000);
}

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

void start() {
	NsAppRoutines::addRoutine<ObstacleHandlingRoutine>();
	// // NsAppRoutines::addRoutine<BluetoothRoutine>();
	NsAppRoutines::addRoutine<BuzzerRoutine>();
}
