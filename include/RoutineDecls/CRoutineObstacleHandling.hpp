#pragma once

#include "Api/NsRoutines.hpp"

class CRoutineObstacleHandling : public NsRoutines::CRoutine < CRoutineObstacleHandling> {

public:
	void setup();
	void loop();
	void out();

};
