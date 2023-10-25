#pragma once

#define BLUETOOTH_COMMS_PREFIX "[BLUETOOTH] "
#define BLUETOOTH_COMMS_TERMINATOR '\n'

#pragma region // Communication macros:
/** @brief Logs without "[BLUETOOTH] " prefixed. */
#define BLUETOOTH_WRITE(...) Serial.print(__VA_ARGS__)

/** @brief Logs without "[BLUETOOTH] " prefixed, with a new-line at the end. */
#define BLUETOOTH_WRITELN(...) Serial.println(__VA_ARGS__)

/** @brief Logs with "[BLUETOOTH] " prefixed. */
#define BLUETOOTH_PRINT(...)        	\
	Serial.print(F(BLUETOOTH_COMMS_PREFIX)); 	\
	Serial.print(__VA_ARGS__)

/** @brief Logs with "[BLUETOOTH] " prefixed, with a new-line at the end. */
#define BLUETOOTH_PRINTLN(...)       	\
	Serial.print(F(BLUETOOTH_COMMS_PREFIX)); 	\
	Serial.println(__VA_ARGS__)
#pragma endregion
