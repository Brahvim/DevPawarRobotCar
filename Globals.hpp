#pragma once

#pragma region Value macros.
#define WHEEL_SPEED				 170
#define SERVO_POINT				 103
#define ARDUINO_SERIAL_BAUD_RATE 9600

// Ultrasonic pins:
#define PIN_ULTRASONIC_ECHO A0
#define PIN_ULTRASONIC_TRIG A1

// Misc. Pins:
#define PIN_SERVO 10
#pragma endregion

#pragma region Functional macros.
// Compile-time type information! (Thanks to ):
template <typename TypeT>
struct TypeInfo {
	static const char *name;
}; // Can't go into `PROGMEM`...
template <typename TypeT>
const char *TypeInfo<TypeT>::name = "Unknown";

#define TYPE_NAME(var) TypeInfo<typeof(var)>::name
#define MAKE_TYPE_INFO(type) \
	template <>              \
	const char *TypeInfo<type>::name = #type;
#pragma endregion

// #pragma region Global values.
// extern const g_servo;
// extern const g_dcMotors[4];
// #pragma endregion

#pragma region Global functions.
void start();
void (*restart)(void) = 0;
#pragma endregion
