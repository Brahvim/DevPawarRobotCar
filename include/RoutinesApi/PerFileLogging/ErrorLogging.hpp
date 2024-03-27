#pragma once

#ifdef ERROR_LOGS_PREFIX
#include <Arduino.h>

#pragma region // Logging without a prefix.
/** @brief Simply logs whatever is passed. */
#define ERROR_PRINT_NOPRE_NOPM(...)             \
Serial.print(__VA_ARGS__)

/** @brief Logs whatever is passed, storing the input into flash memory using `F()`. */
#define ERROR_PRINT_NOPRE(string)               \
Serial.print(F(string))

/** @brief Logs whatever is passed, with a new-line at the end. */
#define ERROR_PRINT_NOPRE_LN_NOPM(...)          \
Serial.println(__VA_ARGS__)

/** @brief Logs whatever is passed, with a new-line at the end, storing the input into flash memory using `F()`. */
#define ERROR_PRINT_NOPRE_LN(string)            \
Serial.println(F(string))
#pragma endregion

#pragma region // Logging with a prefix.
/** @brief Logs with the prefix, and a new-line at the end, storing the input into flash memory using `F()`. */
#define ERROR_PRINT_LN(string)		              \
  Serial.print(F(ERROR_LOGS_PREFIX));	          \
  Serial.println(F(string))

/** @brief Simply logs whatever is passed with the prefix. */
#define ERROR_PRINT_NOPM(...)                   \
    Serial.print(ERROR_LOGS_PREFIX);            \
    Serial.print(__VA_ARGS__)

/** @brief Logs with the prefix, storing the input into flash memory using `F()`. */
#define ERROR_PRINT(string)                     \
    Serial.print(F(ERROR_LOGS_PREFIX));         \
    Serial.print(F(string))

/** @brief Logs with the prefix, and a new-line at the end. */
#define ERROR_PRINT_LN_NOPM(...)		            \
  Serial.print(F(ERROR_LOGS_PREFIX));	          \
  Serial.println(__VA_ARGS__)
#pragma endregion

#else // Else, we define these as empty:

// Without a prefix:
#define ERROR_PRINT_NOPRE_NOPM(...)
#define ERROR_PRINT_NOPRE(string)
#define ERROR_PRINT_NOPRE_LN_NOPM(...)
#define ERROR_PRINT_NOPRE_LN(string)

// With a prefix:
#define ERROR_PRINT_NOPM(...)
#define ERROR_PRINT(string)
#define ERROR_PRINT_LN_NOPM(...)
#define ERROR_PRINT_LN(string)

#endif
