#pragma once

typedef void(*routine_out_fn_t)(void);
typedef void(*routine_loop_fn_t)(void);
typedef void(*routine_setup_fn_t)(void);

struct routines_collection {

	routine_out_fn_t *out;
	routine_loop_fn_t *loop;
	routine_setup_fn_t *setup;

};

void routine_out_stub_implementation();
void routine_loop_stub_implementation();
void routine_setup_stub_implementation();

void routine_call_all_outs(struct routines_collection *routines);
void routine_call_all_loops(struct routines_collection *routines);
void routine_call_all_setups(struct routines_collection *routines);

void routine_remove_out(struct routines_collection *routines, int routine);
void routine_remove_loop(struct routines_collection *routines, int routine);
void routine_remove_setup(struct routines_collection *routines, int routine);
