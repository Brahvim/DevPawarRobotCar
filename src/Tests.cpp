#include <Arduino.h>

#include "CarApi/NsCar.hpp"

#include "Api/DebuggingMacros.hpp"

void textSide() {
	delay(500);
	NsCar::moveLeft(1000);

	delay(500);
	NsCar::moveRight(1000);
}

void textWheel() {
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
