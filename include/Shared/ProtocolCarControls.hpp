#pragma once

#include <stdint.h>

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
