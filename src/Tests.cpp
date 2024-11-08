#include <Arduino.h>

#include "CarApi/NsCar.hpp"
#include "CarApi/NsI2c.hpp"

#include "Api/DebuggingMacros.hpp"

void testI2c() {
	NsControls::MessageTypeEspCam message = i2cAwaitMessageEspCam();
	DEBUG_PRINTLN("Received `PING` from ESP32-CAM.");

	if (message == NsControls::MessageTypeEspCam::PING) {
		DEBUG_PRINTLN("Received `PING` from ESP32-CAM.");
		i2cSendResponse(NsControls::MessageTypeArduino::PONG);
	}
}

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
