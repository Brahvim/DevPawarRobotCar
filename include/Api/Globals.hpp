#pragma once

#pragma region Value macros.
// Speeds and angles!...:
#define WHEEL_SPEED				 170
#define SERVO_POINT				 103
#define ARDUINO_SERIAL_BAUD_RATE 9600

// Pins:
#define PIN_SERVO			10
#define PIN_ULTRASONIC_ECHO A0
#define PIN_ULTRASONIC_TRIG A1
#pragma endregion

#pragma region Functional macros.
#define STRINGIZE(x)	  (#x)
#define TO_STRING(x)	  STRINGIZE(x)
#define JOIN_TOKENS(x, y) (x##y)

// Compile-time type information! (Thanks to [ https://arduino.stackexchange.com/a/3080 ].)

template <typename TypeT>
struct TypeInfo {
	static const char *name;
}; // Can't be kept in `PROGMEM`...

template <typename TypeT>
const char *TypeInfo<TypeT>::name = "Unknown";

#define TYPE_NAME(var) TypeInfo<typeof(var)>::name
#define MAKE_TYPE_INFO(type) \
	template <>              \
	const char *TypeInfo<type>::name = #type;
#pragma endregion

#pragma region Global function declarations.
// void (*restart)(void) = 0;
#pragma endregion
