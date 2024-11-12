#pragma once

#define ifu(p_condition) if (__builtin_expect(p_condition, 0))
#define ifl(p_condition) if (__builtin_expect(p_condition, 1))
