#include <memory>

#include "Api/Globals.hpp"
#include "Api/DebuggingMacros.hpp"

#include "CarApi/NsCar.hpp"

#include "Shared/ProtocolCarControls.hpp"

#include "RoutineDecls/CRoutineControlsListener.hpp"

MAKE_TYPE_INFO(CRoutineControlsListener);

using namespace NsControls;

void awaitBytes(long const p_bytes) {
	while (Wire.available() < p_bytes)
		/* Waiting... */;
}

MessageType parseMessageType(void *p_data) {
	MessageType type;
	memcpy(&type, p_data, g_szMessageType);
	return type;
}

void readBytes(long const p_bytes, uint8_t *const p_buffer) {
	for (int i = 0; i < p_bytes; ++i) {
		p_buffer[i] = Wire.read(); // Compiler won't unroll this :(
	}
}

void sendResponse(MessageType const p_message) {
	char resultMessageTypeData[g_szMessageType];

	memcpy(resultMessageTypeData, &p_message, g_szMessageType);
	Wire.beginTransmission(I2C_ADDR_ESP_CAM);
	Wire.write(resultMessageTypeData, g_szMessageType);
	Wire.endTransmission();
}

void sendResponse(MessageType const p_message, int const p_size, void *p_buffer) {
	char resultMessageTypeData[g_szMessageType];

	memcpy(resultMessageTypeData, &p_message, g_szMessageType);
	Wire.beginTransmission(I2C_ADDR_ESP_CAM);
	Wire.write(resultMessageTypeData, g_szMessageType);
	Wire.write((char*) p_buffer, p_size);
	Wire.endTransmission();
}

void CRoutineControlsListener::loop() {
	Wire.requestFrom(I2C_ADDR_ESP_CAM, g_szMessageType);
	awaitBytes(g_szMessageType);

	uint8_t typeData[g_szMessageType];
	readBytes(g_szMessageType, typeData);

	MessageType const type = parseMessageType(typeData);

	switch (type) {

		default: {

		} break;

		case MessageType::START: {
			sendResponse(MessageType::START_OK);
		} break;

		case MessageType::MOVE_FORWARD: {
			NsCar::moveForwardAsync();
			sendResponse(MessageType::MOVE_OK);
		} break;

		case MessageType::MOVE_BACKWARD: {
			NsCar::moveBackwardAsync();
			sendResponse(MessageType::MOVE_OK);
		} break;

	}
}
