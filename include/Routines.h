#pragma once

#define routineSourceGlobalCallDecl(p_name) routine_t g_routine ## p_name ## Call
#define routineSourceGlobalImplDecl(p_name) routine_t g_routine ## p_name ## Impl
#define routineSourceStaticFunctionName(p_name) routine ## p_name ## Impl

#define routineDeclare(p_name)							\
	extern routineSourceGlobalCallDecl(p_name);			\
	extern const routineSourceGlobalImplDecl( p_name);	\

#define routineDefine(p_name, p_impl)                                                   \
static void routineSourceStaticFunctionName(p_name)() p_impl                            \
routineSourceGlobalCallDecl(p_name) = routineSourceStaticFunctionName(p_name);          \
const routineSourceGlobalImplDecl(p_name) = routineSourceStaticFunctionName(p_name);    \

typedef void (*routine_t)();
