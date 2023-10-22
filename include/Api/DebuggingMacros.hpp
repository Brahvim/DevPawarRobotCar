// Debugging macros!:

#ifdef ENABLE_DEBUG_LOGS
#include <Arduino.h>

/** @brief Logs without "[DEBUG] " prefixed. */
#define DEBUG_WRITE(...) Serial.print(__VA_ARGS__)

/** @brief Logs without "[DEBUG] " prefixed, with a new-line at the end. */
#define DEBUG_WRITELN(...) Serial.println(__VA_ARGS__)

/** @brief Logs with "[DEBUG] " prefixed. */
#define DEBUG_PRINT(...)         \
	Serial.print(F("[DEBUG] ")); \
	Serial.print(__VA_ARGS__)

/** @brief Logs with "[DEBUG] " prefixed, with a new-line at the end. */
#define DEBUG_PRINTLN(...)       \
	Serial.print(F("[DEBUG] ")); \
	Serial.println(__VA_ARGS__)

#else // Define these as empty!:

#define DEBUG_WRITE(...)
#define DEBUG_PRINT(...)
#define DEBUG_WRITELN(...)
#define DEBUG_PRINTLN(...)

#endif

/** @brief Logs without "[ERROR] " prefixed. */
#define ERROR_WRITE(...) Serial.print(__VA_ARGS__)

/** @brief Logs without "[ERROR] " prefixed, with a new-line at the end. */
#define ERROR_WRITELN(...) Serial.println(__VA_ARGS__)

/** @brief Logs with "[ERROR] " prefixed. */
#define ERROR_PRINT(...)         \
	Serial.print(F("[ERROR] ")); \
	Serial.print(__VA_ARGS__)

/** @brief Logs with "[ERROR] " prefixed, with a new-line at the end. */
#define ERROR_PRINTLN(...)       \
	Serial.print(F("[ERROR] ")); \
	Serial.println(__VA_ARGS__)
