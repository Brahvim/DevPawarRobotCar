#pragma once

#include "../Api/NsAppRoutines.hpp"

class BuzzerRoutine : public NsAppRoutines::AppRoutine {
	void loop();
	void setup();
};
