#pragma once

#include "Api/NsRoutines.hpp"

class CRoutineBluetooth : public NsRoutines::CRoutine {

public:
	void setup();
	void loop();
	void out();

private:
	String customReadStringUntil(char terminator);

};
