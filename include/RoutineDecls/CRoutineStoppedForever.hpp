#pragma once

#include "Api/NsRoutines.hpp"

class CRoutineStoppedForever : public NsRoutines::CRoutine {

public:
	static String reason;

	void setup();
	void loop();
	void out();

};
