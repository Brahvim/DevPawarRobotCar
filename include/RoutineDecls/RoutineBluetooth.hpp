#pragma once

#include "../Api/NsAppRoutines.hpp"

class RoutineBluetooth : public NsAppRoutines::AppRoutine {

public:
	void loop();
	void setup();

private:
	String customReadStringUntil(char terminator);

};
