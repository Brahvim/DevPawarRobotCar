#include "Api/Globals.hpp"
#include "Api/DebuggingMacros.hpp"
#include "RoutineDecls/StoppedForeverRoutine.hpp"

MAKE_TYPE_INFO(StoppedForeverRoutine);

String StoppedForeverRoutine::reason = "";

void StoppedForeverRoutine::loop() {
	ERROR_PRINT("Stopped forever... Reason: ");
	ERROR_WRITELN(StoppedForeverRoutine::reason);
}
