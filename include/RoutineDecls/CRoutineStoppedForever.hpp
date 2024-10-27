#pragma once

#include "Api/NsRoutines.hpp"

class CRoutineStoppedForever : public NsRoutines::CRoutine<CRoutineStoppedForever> {

public:
	static String reason;

	void setup();
	void loop();
	void out();

};
