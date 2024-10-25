#include "Api/Globals.hpp"
#include "Api/DebuggingMacros.hpp"
#include "RoutineDecls/RoutineStoppedForever.hpp"

MAKE_TYPE_INFO(RoutineStoppedForever);

String RoutineStoppedForever::reason = "";

void RoutineStoppedForever::loop() {
	ERROR_PRINT("Stopped forever... Reason: ");
	ERROR_WRITELN(RoutineStoppedForever::reason);
}
