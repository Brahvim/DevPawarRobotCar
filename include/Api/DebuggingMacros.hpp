#include <Arduino.h>

#define ENABLE_DEBUG_LOGS

// Debugging macros!:

#ifdef ENABLE_DEBUG_LOGS

/** @brief Logs without "[DEBUG] " prefixed. */
#define DEBUG_APPEND(...) Serial.print(__VA_ARGS__)

/** @brief Logs without "[DEBUG] " prefixed, and a new-line at the end. */
#define DEBUG_APPENDLN(...) Serial.println(__VA_ARGS__)

/** @brief Logs with "[DEBUG] " prefixed. */
#define DEBUG_PRINT(...)			\
	Serial.print(F("[DEBUG] "));	\
	Serial.print(__VA_ARGS__)

/** @brief Logs with "[DEBUG] " prefixed, and a new-line at the end. */
#define DEBUG_PRINTLN(...)		\
  Serial.print(F("[DEBUG] "));	\
  Serial.println(__VA_ARGS__)

#else // Else, we define these as empty:

#define DEBUG_PRINT(...)
#define DEBUG_APPEND(...)

#define DEBUG_PRINTLN(...)
#define DEBUG_APPENDLN(...)

#endif

#pragma region // Error macros:
/** @brief Logs without "[ERROR] " prefixed. */
#define ERROR_APPEND(...) Serial.print(__VA_ARGS__)

/** @brief Logs without "[ERROR] " prefixed, with a new-line at the end. */
#define ERROR_APPENDLN(...) Serial.println(__VA_ARGS__)

/** @brief Logs with "[ERROR] " prefixed. */
#define ERROR_PRINT(...)        	\
	Serial.print(F("[ERROR] ")); 	\
	Serial.print(__VA_ARGS__)

/** @brief Logs with "[ERROR] " prefixed, with a new-line at the end. */
#define ERROR_PRINTLN(...)       	\
	Serial.print(F("[ERROR] ")); 	\
	Serial.println(__VA_ARGS__)
#pragma endregion
