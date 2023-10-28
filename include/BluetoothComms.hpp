#pragma once

#define BLUETOOTH_COMMS_CAR_PREFIX "1"
#define BLUETOOTH_COMMS_REMOTE_PREFIX "0"
#define BLUETOOTH_COMMS_TERMINATOR_CHAR '\n'

#define BLUETOOTH_COMMS_CAR_PREFIX_LENGTH (sizeof(BLUETOOTH_COMMS_CAR_PREFIX) / sizeof(char))
#define BLUETOOTH_COMMS_REMOTE_PREFIX_LENGTH (sizeof(BLUETOOTH_COMMS_REMOTE_PREFIX) / sizeof(char))
#define BLUETOOTH_COMMS_TERMINATOR_CHAR_LENGTH (sizeof(BLUETOOTH_COMMS_TERMINATOR_CHAR) / sizeof(char))

enum BluetoothMessage {
	BT_STOP,
	BT_LEFT,
	BT_RIGHT,
	BT_FORWARDS,
	BT_BACKWARDS,
	BT_AUTO_PILOT,
};

#pragma region // Communication macros:
/** @brief Logs without "[BLUETOOTH] " prefixed. */
#define BLUETOOTH_WRITE(...) Serial.print(__VA_ARGS__)

/** @brief Logs without "[BLUETOOTH] " prefixed, with a new-line at the end. */
#define BLUETOOTH_WRITELN(...) Serial.println(__VA_ARGS__)

/** @brief Logs with "[BLUETOOTH] " prefixed. */
#define BLUETOOTH_PRINT(...)        	\
	Serial.print(F(BLUETOOTH_COMMS_CAR_PREFIX)); 	\
	Serial.print(__VA_ARGS__)

/** @brief Logs with "[BLUETOOTH] " prefixed, with a new-line at the end. */
#define BLUETOOTH_PRINTLN(...)       	\
	Serial.print(F(BLUETOOTH_COMMS_CAR_PREFIX)); 	\
	Serial.println(__VA_ARGS__)
#pragma endregion
