#include "routine.hpp"

enum app_routines {

	APP_ROUTINE_OBSTACLES,
	APP_ROUTINE_BLUETOOTH,
	APP_ROUTINE_STOPPED,
	APP_ROUTINE_BUZZER,
	APP_ROUTINE_COUNT

};

// This is `struct routine` as a structure-of-arrays:
static routine_out_fn_t s_out_calls[APP_ROUTINE_COUNT];
static routine_loop_fn_t s_loop_calls[APP_ROUTINE_COUNT];
static routine_setup_fn_t s_setup_calls[APP_ROUTINE_COUNT];

static struct routines_collection s_routines_collection = {

	.out = s_out_calls,
	.loop = s_loop_calls,
	.setup = s_setup_calls,

};

void routine_call_all_setups() {
	for (unsigned long i = 0; i < APP_ROUTINE_COUNT; ++i)
		s_setup_calls[i]();
}

void routine_call_all_loops() {
	for (unsigned long i = 0; i < APP_ROUTINE_COUNT; ++i)
		s_loop_calls[i]();
}

void routine_call_all_outs() {
	for (unsigned long i = 0; i < APP_ROUTINE_COUNT; ++i)
		s_out_calls[i]();
}

void app_routines_setup() {

}
