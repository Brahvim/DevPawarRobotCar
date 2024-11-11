#pragma once

#include "Api/NsRoutines.hpp"

enum class EcRoutineStoppedForeverCallReason : uint8_t {

	PATH,
	SENSOR,
	UNKNOWN,

};

class CRoutineStoppedForever : public NsRoutines::CRoutine {

public:
	static EcRoutineStoppedForeverCallReason reason;

	void loop();

};
