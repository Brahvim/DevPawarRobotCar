#include "Api/Globals.hpp"
#include "Api/DebuggingMacros.hpp"
#include "RoutineDecls/CRoutineStoppedForever.hpp"

MAKE_TYPE_INFO(CRoutineStoppedForever);

String CRoutineStoppedForever::reason = "";

void CRoutineStoppedForever::loop() {
	ERROR_PRINT("Stopped forever... Reason: ");
	ERROR_WRITELN(CRoutineStoppedForever::reason);
}
