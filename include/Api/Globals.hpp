#pragma once

#define TO_STRING(x)	 	(#x)
#define JOIN_TOKENS(x, y)	(x##y)

#define ifu(x)	if (__builtin_expect(x, 0))
#define ifl(x)	if (__builtin_expect(x, 1))

#pragma region // Compile-time type information! (Thanks to [ https://arduino.stackexchange.com/a/3080 ].)
template <typename TType>
struct TypeInfo {

	static const char *name;

}; // Can't be kept in `PROGMEM`...

template <typename TType>
const char *TypeInfo<TType>::name = "Unknown";

#define TYPE_NAME(p_var) TypeInfo<typeof(p_var)>::name

#define MAKE_TYPE_INFO(p_type)	\
	template <>					\
	const char *TypeInfo<p_type>::name = #p_type;
#pragma endregion
