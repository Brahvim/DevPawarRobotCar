#include <memory>

#include "Api/Globals.hpp"
#include "Api/DebuggingMacros.hpp"

#include "CarApi/NsCar.hpp"

#include "Shared/ProtocolCarControls.hpp"

#include "RoutineDecls/CRoutineControlsListener.hpp"

MAKE_TYPE_INFO(CRoutineControlsListener);

using namespace NsControls;

static void awaitBytes(long const p_bytes) {
	while (Wire.available() < p_bytes)
		/* Waiting... */;
}

static EspCamMessageType parseMessageType(void *p_data) {
	EspCamMessageType type;
	memcpy(&type, p_data, sizeof(EspCamMessageType));
	return type;
}

static void readBytes(long const p_bytes, uint8_t *const p_buffer) {
	for (int i = 0; i < p_bytes; ++i) {
		p_buffer[i] = Wire.read(); // Compiler won't unroll this :(
	}
}

static void sendResponse(ArduinoMessageType const p_message) {
	char resultMessageTypeData[sizeof(ArduinoMessageType)];

	memcpy(resultMessageTypeData, &p_message, sizeof(ArduinoMessageType));
	Wire.beginTransmission(I2C_ADDR_ESP_CAM);
	Wire.write(resultMessageTypeData, sizeof(ArduinoMessageType));
	Wire.endTransmission();
}

static void sendResponse(ArduinoMessageType const p_message, int const p_size, void *p_buffer) {
	char resultMessageTypeData[sizeof(ArduinoMessageType)];

	memcpy(resultMessageTypeData, &p_message, sizeof(ArduinoMessageType));
	Wire.beginTransmission(I2C_ADDR_ESP_CAM);
	Wire.write(resultMessageTypeData, sizeof(ArduinoMessageType));
	Wire.write((char*) p_buffer, p_size);
	Wire.endTransmission();
}

void CRoutineControlsListener::loop() {
	Wire.requestFrom(I2C_ADDR_ESP_CAM, sizeof(EspCamMessageType));
	awaitBytes(sizeof(EspCamMessageType));

	uint8_t typeData[sizeof(EspCamMessageType)];
	readBytes(sizeof(EspCamMessageType), typeData);

	EspCamMessageType const type = parseMessageType(typeData);

	switch (type) {

		default: {

		} break;

		case EspCamMessageType::STOP: {
			NsCar::stop();
			sendResponse(ArduinoMessageType::MOVE_OK);
		} break;

		case EspCamMessageType::START: {
			sendResponse(ArduinoMessageType::START_OK);
		} break;

		case EspCamMessageType::MOVE_LEFT: {
			NsCar::moveLeftAsync();
			sendResponse(ArduinoMessageType::MOVE_OK);
		} break;

		case EspCamMessageType::MOVE_RIGHT: {
			NsCar::moveRightAsync();
			sendResponse(ArduinoMessageType::MOVE_OK);
		} break;

		case EspCamMessageType::MOVE_FORWARD: {
			NsCar::moveForwardAsync();
			sendResponse(ArduinoMessageType::MOVE_OK);
		} break;

		case EspCamMessageType::MOVE_BACKWARD: {
			NsCar::moveBackwardAsync();
			sendResponse(ArduinoMessageType::MOVE_OK);
		} break;

	}
}
