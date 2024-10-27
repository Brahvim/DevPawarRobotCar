#include "Api/DebuggingMacros.hpp"
#include "CarApi/NsUltrasonic.hpp"
#include "routine.hpp"
#include "app.hpp"

void routine_out_stub_implementation() { }

void routine_loop_stub_implementation() { }

void routine_setup_stub_implementation() { }

typedef void(*routine_stopped_forever_loop_fn_t)(void);
typedef void(*routine_obstacle_handling_loop_fn_t)(void);

static routine_obstacle_handling_loop_fn_t s_routine_obstacle_handling_loop_fn = routine_stopped_forever_loop;
static routine_stopped_forever_loop_fn_t s_routine_stopped_forever_loop_fn = [] { };

const char* g_stopped_forever_reason = "Unknown.";

// Arduino `loop()`:
void loop() {
	s_routine_stopped_forever_loop_fn();
	s_routine_obstacle_handling_loop_fn();
}

void routine_stopped_forever_loop() {
	ERROR_PRINT("Stopped forever... Reason: ");
	ERROR_WRITELN(g_stopped_forever_reason);
}

void routine_obstacle_handling_loop() {
	ifu(NsUltrasonic::read() == 0) { // Sensor failed, stop forever!
		s_routine_stopped_forever_loop_fn = routine_stopped_forever_loop;
		s_routine_obstacle_handling_loop_fn = [] { };
	}
}
