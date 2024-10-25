#pragma once

#include "../Api/NsRoutines.hpp"

class CRoutineStoppedForever : public NsRoutines::CRoutine {

public:
	static String reason;
	void loop(); // Why, oh *why* did I go with virtual calls thinking `sizeof(class)` is smaller than a function pointer's?

};
