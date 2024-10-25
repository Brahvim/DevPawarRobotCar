#pragma once

#include "../Api/NsRoutines.hpp"

class CRoutineBluetooth : public NsRoutines::CRoutine {

public:
	void loop();
	void setup();

private:
	String customReadStringUntil(char terminator);

};
