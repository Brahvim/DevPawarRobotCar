#include <stdint.h>

#include <Wire.h>

#define I2C_ADDR_ARDUINO 0x01
#define I2C_ADDR_ESP_CAM 0x02

namespace NsControls {

	enum class MessageType : uint8_t {

#pragma region // Movement stuff.
		STOP,
		MOVE_OK,
		MOVE_LEFT,
		MOVE_RIGHT,
		MOVE_FORWARD,
		MOVE_BACKWARD,
#pragma endregion

#pragma region // Protocol management.
		START,
		START_OK,
		START_ERROR,
		END_NO_PATH,
		END_SENSOR_BROKE,
#pragma endregion

		NUM_MESSAGE_TYPES

	};

	struct Packet {

		enum MessageType const type;
		void *data;

	};

	constexpr int g_szMessageType = sizeof(NsControls::MessageType);

	const int g_szPackets[] = {

		0, // `STOP`,
		0, // `LEFT`,
		0, // `RIGHT`,
		0, // `FORWARD`,
		0, // `BACKWARD`,
		0, // `BEGIN`,
		0, // `END_NO_PATH`,
		0, // `END_SENSOR_BROKE`,

	};

}
