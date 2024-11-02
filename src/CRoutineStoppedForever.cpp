#include "Api/Globals.hpp"
#include "Api/DebuggingMacros.hpp"
#include "RoutineDecls/CRoutineStoppedForever.hpp"

MAKE_TYPE_INFO(CRoutineStoppedForever);

EcRoutineStoppedForeverCallReason CRoutineStoppedForever::reason = EcRoutineStoppedForeverCallReason::UNKNOWN;

static char const *s_errorMessages[] = {

	/* `PATH` */ 	"No path ahead car!",
	/* `SENSOR` */ 	"Ultrasonic sensor wiring broke!",
	/* `UNKNOWN` */ "REASON UNKNOWN!",

};

void CRoutineStoppedForever::loop() {
	ERROR_PRINT("Stopped forever... Reason: ");
	ERROR_WRITELN(s_errorMessages[(uint8_t) CRoutineStoppedForever::reason]);
}
