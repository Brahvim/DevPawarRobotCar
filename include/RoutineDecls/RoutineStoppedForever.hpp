#pragma once

#include "../Api/NsAppRoutines.hpp"

class RoutineStoppedForever : public NsAppRoutines::AppRoutine {

public:
	static String reason;
	void loop(); // Why, oh *why* did I go with virtual calls thinking `sizeof(class)` is smaller than a function pointer's?

};
