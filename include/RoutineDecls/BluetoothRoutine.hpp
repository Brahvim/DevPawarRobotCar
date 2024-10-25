#pragma once

#include "../Api/NsAppRoutines.hpp"

class BluetoothRoutine : public NsAppRoutines::AppRoutine {

public:
	void loop();
	void setup();

private:
	String customReadStringUntil(char terminator);

};
