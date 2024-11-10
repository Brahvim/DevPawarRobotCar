#include <memory>
#include <Arduino.h>

#include "Api/Main.hpp"
#include "Api/Globals.hpp"
#include "Api/DebuggingMacros.hpp"

#include "CarApi/NsCar.hpp"
#include "CarApi/NsI2c.hpp"

#include "RoutineDecls/CRoutineControlsListener.hpp"

MAKE_TYPE_INFO(CRoutineControlsListener);

using namespace NsControls;

char const* wireStatusToString(uint8_t const p_status) {
	/*

	`Wire.cpp` line `432`:
	"""
	https://www.arduino.cc/reference/en/language/functions/communication/wire/endtransmission/
	endTransmission() returns:
	0: success.
	1: data too long to fit in transmit buffer.
	2: received NACK on transmit of address.
	3: received NACK on transmit of data.
	4: other error.
	5: timeout
	"""

	PS The URL has changed to [ https://docs.arduino.cc/language-reference/en/functions/communication/Wire/endTransmission/ ].

	*/

	switch (p_status) {

		case 0: { return "Success"; } break;
		case 1: { return "Data written too large to fit in transmit buffer"; } break;
		case 2: { return "Received NACK when transmitting I2C address"; } break;
		case 3: { return "Received NACK when transmitting I2C data"; } break;
		case 4: { return "Other error"; } break;
		case 5: { return "I2C timeout"; } break;

		default: { return "Unknown error"; } break;

	}
}

#pragma region // `sendResponse()` overloads.
void i2cSendResponse(MessageTypeArduino const p_message) {
	char resultMessageTypeData[sizeof(MessageTypeArduino)];

	memcpy(resultMessageTypeData, &p_message, sizeof(MessageTypeArduino));
	Wire.beginTransmission(I2C_ADDR);
	size_t const bytes_sent = Wire.write(resultMessageTypeData, sizeof(MessageTypeArduino));
	uint8_t const wire_status = Wire.endTransmission(false);

	ifu(bytes_sent != sizeof(MessageTypeEspCam)) {
		DEBUG_PRINTLN("Arduino `Wire`/I2C transmission didn't send all bytes for message transaction.");
	}

	DEBUG_PRINT("Arduino `Wire`/I2C transmission wrote `");
	DEBUG_WRITE(bytes_sent);
	DEBUG_WRITELN("` bytes.");

	ifu(!wire_status) {
		DEBUG_PRINT("Arduino `Wire`/I2C message transmission failure:");
		DEBUG_WRITELN(wireStatusToString(wire_status));
	}
}

void i2cSendResponse(MessageTypeArduino const p_message, size_t const p_size, void *p_buffer) {
	char resultMessageTypeData[sizeof(MessageTypeArduino)];

	memcpy(resultMessageTypeData, &p_message, sizeof(MessageTypeArduino));
	Wire.beginTransmission(I2C_ADDR);

	size_t bytes_sent = 0;

	bytes_sent += Wire.write(resultMessageTypeData, sizeof(MessageTypeArduino));
	bytes_sent += Wire.write((char*) p_buffer, p_size);

	uint8_t const wire_status = Wire.endTransmission(false);

	ifu(bytes_sent != sizeof(MessageTypeEspCam)) {
		DEBUG_PRINTLN("Arduino `Wire`/I2C transmission didn't send all bytes for message transaction.");
	}

	DEBUG_PRINT("Arduino `Wire`/I2C transmission wrote `");
	DEBUG_WRITE(bytes_sent);
	DEBUG_WRITELN("` bytes.");

	ifu(!wire_status) {
		DEBUG_PRINT("Arduino `Wire`/I2C message transmission failure:");
		DEBUG_WRITELN(wireStatusToString(wire_status));
	}
}
#pragma endregion

MessageTypeEspCam i2cAwaitMessageEspCam(size_t const p_interval_millis, size_t const p_interval_count) {
	MessageTypeEspCam toRet;

	i2cAwaitEspCam(sizeof(MessageTypeEspCam), p_interval_millis, p_interval_count);
	i2cReadEspCam(sizeof(MessageTypeEspCam), (uint8_t*) &toRet);

	return toRet;
}

void i2cReadEspCam(size_t const p_bytes, uint8_t *const p_buffer) {
	for (size_t i = 0; i < p_bytes; ++i) {
		p_buffer[i] = Wire.read(); // Compiler won't unroll this :(
	}
}

void i2cAwaitEspCam(int const p_bytes, size_t const p_interval_millis = 1, size_t const p_interval_count = 100) {
	uint8_t const bytes = Wire.requestFrom(I2C_ADDR, sizeof(MessageTypeArduino));

	// DEBUG_PRINT("Received `");
	// DEBUG_WRITE(bytes);
	// DEBUG_WRITELN("` bytes from ESP32-CAM.");

	for (size_t i = p_interval_count; i < 1 || Wire.available() > p_bytes; --i) {
		delay(p_interval_millis);
	}
}

void loopI2c() {
	// DEBUG_PRINTLN("Attempting to receive I2C messages...");

	MessageTypeEspCam const message = i2cAwaitMessageEspCam();

	/*

		- L293D motor numbers (as array indices):
			```
			1 0
			2 3
			```

		- `AF_DCMotor::setSpeed()`-set registers (in place of array indices):
			```
			OCR2B OCR2A
			OCR0A OCR0B
			```

	*/

	// DEBUG_PRINTLN("Should've received an I2C message by now!...");

	switch (message) {

		default: {

		} break;

		case MessageTypeEspCam::PING: {
			i2cSendResponse(MessageTypeArduino::PONG);
		} break;

		case MessageTypeEspCam::STOP: {
			DEBUG_PRINTLN("I2C request: stop.");
			NsCar::stop();
			i2cSendResponse(MessageTypeArduino::STOP_OK);
		} break;

		case MessageTypeEspCam::STEER: {
			DEBUG_PRINTLN("I2C request: steer.");
			Wire.requestFrom(I2C_ADDR, sizeof(MessageSteer));
			i2cAwaitEspCam(sizeof(MessageSteer));

			char buf[sizeof(MessageSteer)];
			i2cReadEspCam(sizeof(MessageSteer), (uint8_t*) buf);

			uint8_t const value = ((MessageSteer*) buf)->steer_normal;

			if (value < 0) {
				OCR2B = -value; // NsCar::motors[1].setSpeed(-value);
				OCR0A = -value;	// NsCar::motors[2].setSpeed(-value);
			} else {
				OCR2A = value; // NsCar::motors[0].setSpeed(value);
				OCR0B = value; // NsCar::motors[3].setSpeed(value);
			}

			i2cSendResponse(MessageTypeArduino::STEER_OK);
		} break;

		case MessageTypeEspCam::GEAR_FORWARD: {
			DEBUG_PRINTLN("I2C request: forward.");
			NsCar::moveForwardAsync();
			i2cSendResponse(MessageTypeArduino::GEAR_OK);
		} break;

		case MessageTypeEspCam::GEAR_BACKWARD: {
			DEBUG_PRINTLN("I2C request: backwards.");
			NsCar::moveBackwardAsync();
			i2cSendResponse(MessageTypeArduino::GEAR_OK);
		} break;

	}
}

void CRoutineControlsListener::loop() {
	pinMode(A5, INPUT);
	pinMode(A4, INPUT);

	int const readingA4 = analogRead(A4); // Steering.
	int const readingA5 = analogRead(A5); // Forwards/Backwards movement via [-1, 1] values.

	if (readingA4 == 0 || readingA5 == 0)
		return;

	// No writes. No more.
	// pinMode(A5, OUTPUT);
	// pinMode(A4, OUTPUT);

	// FP operations suck on AVR, apparently:

	// NsCar::motors[0].setSpeed((uint8_t) (((float) readingA4 / 1024.0f) * WHEEL_SPEED));
	// NsCar::motors[1].setSpeed((uint8_t) (((float) readingA4 / 1024.0f) * WHEEL_SPEED));
	// NsCar::motors[2].setSpeed((uint8_t) (((float) readingA4 / 1024.0f) * WHEEL_SPEED));
	// NsCar::motors[3].setSpeed((uint8_t) (((float) readingA4 / 1024.0f) * WHEEL_SPEED));

	NsCar::motors[0].setSpeed(127 + (uint8_t) ((readingA4 * WHEEL_SPEED) / 1024));

	NsCar::motors[1].setSpeed(-127 + (uint8_t) ((readingA4 * WHEEL_SPEED) / 1024));
	NsCar::motors[2].setSpeed(-127 + (uint8_t) ((readingA4 * WHEEL_SPEED) / 1024));

	NsCar::motors[3].setSpeed(127 + (uint8_t) ((readingA4 * WHEEL_SPEED) / 1024));

	// analogWrite(14, (uint8_t) MessageTypeArduino::STEER_OK);

	DEBUG_PRINT("[Steer, Gear] read: ");
	DEBUG_WRITE(readingA4); DEBUG_WRITE(" "); DEBUG_WRITELN(readingA5);

	bool const
		inRangeBackwards = readingA5 < 450,
		inRangeForwards = readingA5 > 550,
		inRangeStop = !(inRangeBackwards || inRangeForwards);

	ifl(inRangeForwards) {
		NsCar::moveForwardAsync();
		DEBUG_PRINTLN("Car will go forwards.");
		// analogWrite(15, (uint8_t) MessageTypeArduino::GEAR_OK);
	} else ifl(inRangeBackwards) {
		NsCar::moveBackwardAsync();
		DEBUG_PRINTLN("Car will go backwards.");
		// analogWrite(15, (uint8_t) MessageTypeArduino::GEAR_OK);
	} else ifu(inRangeStop) {
		NsCar::stop();
		DEBUG_PRINTLN("Car has stopped.");
		// analogWrite(15, (uint8_t) MessageTypeArduino::GEAR_OK);
	}

}
