#pragma once

#include "Api/NsRoutines.hpp"

// See `NsBuzzer.cpp` for implementation.
class CRoutineBuzzer : public NsRoutines::CRoutine<CRoutineBuzzer> {

public:
	void setup();
	void loop();
	void out();

};
