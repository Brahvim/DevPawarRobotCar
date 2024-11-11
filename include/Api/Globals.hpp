#pragma once

#define TO_STRING(x)	 	(#x)
#define JOIN_TOKENS(x, y)	(x##y)

#define ifu(x)	if (__builtin_expect(x, 0))
#define ifl(x)	if (__builtin_expect(x, 1))

#pragma region // Compile-time type information! (Thanks to [ https://arduino.stackexchange.com/a/3080 ].)
template <typename TType>
struct TypeInfo {
	static char const *name;
}; // Can't be kept in `PROGMEM`...

template <typename TypeT>
char const *TypeInfo<TypeT>::name = "Unknown";

#define TYPE_NAME(var) TypeInfo<typeof(var)>::name
#define MAKE_TYPE_INFO(type) \
	template <>              \
	char const *TypeInfo<type>::name = #type;
