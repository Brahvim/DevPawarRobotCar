#pragma once

#include <stdint.h>
#include <Wire.h>

#define I2C_ADDR_ARDUINO 0x01
#define I2C_ADDR_ESP_CAM 0x02

// From [ https://docs.arduino.cc/language-reference/en/functions/communication/Wire/ ]:
#define I2C_PIN_SDA_ARDUINO A4
#define I2C_PIN_SCL_ARDUINO A5
// These are the defaults and cannot be set, it seems. Also found in `pins_arduino.h`.

#define I2C_PIN_SDA_ESP_CAM 14
#define I2C_PIN_SCL_ESP_CAM 15

namespace NsControls {

	enum class MessageTypeArduino : uint8_t {

		// Is-alive response.
		PONG,

		GEAR_OK,
		STOP_OK,
		STEER_OK,
		BRAKE_OK,
		MAX_SPEED_OK,

		GEAR_FAILED,
		STOP_FAILED,
		STEER_FAILED,
		BRAKE_FAILED,
		MAX_SPEED_FAILED,

	};

	enum class MessageTypeEspCam : uint8_t {

		STOP,

		// Is-alive request.
		PING,

		// Make sure to send a `MessageSteer` after sending this!
		STEER,

		// Make sure to send a `MessageMaxSpeed` after sending this!
		SPEED,

		GEAR_FORWARD,
		GEAR_BACKWARD,

	};

	struct MessageSteer {

		float steer_normal; // `-1` is all left, `1` is all right.

	};

	struct MessageMaxSpeed {

		uint8_t speed; // `AF_DCMotor::setSpeed()` values, `[0, 255]`.

	};

}
