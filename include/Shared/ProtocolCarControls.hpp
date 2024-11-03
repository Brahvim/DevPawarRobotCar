#include <stdint.h>
#include <Wire.h>

#define I2C_ADDR_ARDUINO 0x01
#define I2C_ADDR_ESP_CAM 0x02

namespace NsControls {

	enum class ArduinoMessageType : uint8_t {

		MOVE_OK,
		START_OK,
		START_ERROR,
		STOP_NO_PATH,
		STOP_SENSOR_BROKE,

	};

	enum class EspCamMessageType : uint8_t {

		STOP,
		START,
		MOVE_LEFT,
		MOVE_RIGHT,
		MOVE_FORWARD,
		MOVE_BACKWARD,

	};

}
