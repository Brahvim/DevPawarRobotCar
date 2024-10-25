#pragma once

#include "../Api/NsAppRoutines.hpp"

// See `NsBuzzer.cpp` for implementation.
class BuzzerRoutine : public NsAppRoutines::AppRoutine {

public:
	void loop();
	void setup();

};
