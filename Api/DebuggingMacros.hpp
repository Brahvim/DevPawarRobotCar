// Debugging macros!:

#ifdef ENABLE_DEBUG_LOGS

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
