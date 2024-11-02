#pragma once

#include "Api/NsRoutines.hpp"

// See `NsBuzzer.cpp` for implementation.
class CRoutineBuzzer : public NsRoutines::CRoutine {

public:
	void setup();
	void loop();

};
