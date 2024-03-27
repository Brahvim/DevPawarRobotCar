#include "Api/DebuggingMacros.hpp"
#include "Api/Globals.hpp"
#include "Api/NsAppRoutines.hpp"

#include "RoutineDecls/BuzzerRoutine.hpp"
#include "RoutineDecls/BluetoothRoutine.hpp"
#include "RoutineDecls/ObstacleHandlingRoutine.hpp"

#include "ArxContainer.h"

arx::map<const char *, NsAppRoutines::AppRoutine *> g_routinesToClassNamesMap;

// template bool NsAppRoutines::removeRoutine<BluetoothRoutine>();
template NsAppRoutines::AppRoutineAdditionError NsAppRoutines::addRoutine<BluetoothRoutine>();

// template bool NsAppRoutines::removeRoutine<ObstacleHandlingRoutine>();
template NsAppRoutines::AppRoutineAdditionError NsAppRoutines::addRoutine<ObstacleHandlingRoutine>();

// template bool NsAppRoutines::removeRoutine<BuzzerRoutine>();
template NsAppRoutines::AppRoutineAdditionError NsAppRoutines::addRoutine<BuzzerRoutine>();

namespace NsAppRoutines {

	void AppRoutine::setup() {
		// DEBUG_PRINTLN(F("Looks like somebody forgot to override `setup()`!"));
	}

	void AppRoutine::loop() {
		// DEBUG_PRINTLN(F("Looks like somebody forgot to override `loop()`!"));
	}

	void AppRoutine::out() {
		// DEBUG_PRINTLN(F("Looks like somebody forgot to override `out()`!"));
	}

	template <class RoutineT>
	NsAppRoutines::AppRoutineAdditionError addRoutine() {
		// If an object of this class already exists,
		if (g_routinesToClassNamesMap.find(TYPE_NAME(RoutineT)) != g_routinesToClassNamesMap.end()) {
			DEBUG_PRINT("Routine of type `");
			DEBUG_WRITE(TYPE_NAME(RoutineT));
			DEBUG_WRITELN("` already exists. Didn't add another.");

			// Yeah, we ain't adding another (for now! ..should this change later?! ..indexed instances?!):
			return NsAppRoutines::AppRoutineAdditionError::ROUTINE_ALREADY_EXISTS;
		}


		// Okay, here we go! Roll the callback!:
		NsAppRoutines::AppRoutine *routine = new RoutineT(); // Fun fact: Object slicing ruined me here for DAYS 🤣
		g_routinesToClassNamesMap[TYPE_NAME(RoutineT)] = routine;
		routine->setup();

		DEBUG_PRINT("Added routine of type: `");
		DEBUG_WRITE(TYPE_NAME(RoutineT));
		DEBUG_WRITELN("`.");

		return NsAppRoutines::AppRoutineAdditionError::NO_ERROR;
	}

	template <class RoutineT>
	bool removeRoutine() {
		// Check if a routine of the same class name exists :
		for (auto it = g_routinesToClassNamesMap.begin(); it != g_routinesToClassNamesMap.end(); it++) {
			// If the name of the class isn't the same, keep looking (yes, this is a guard clause!):
			if (it->first != TYPE_NAME(RoutineT))
				continue;

			// If we've found one, we dispatch the callback and de-allocate memory:
			NsAppRoutines::AppRoutine *routine = it->second;
			routine->out();
			delete routine;

			// ...As well as remove our object from our map:
			g_routinesToClassNamesMap.erase(it);

			DEBUG_PRINT("Removed routine of type: `");
			DEBUG_WRITE(TYPE_NAME(RoutineT));
			DEBUG_WRITELN("`.");

			// DEBUG_PRINT("Size of vector: ");
			// DEBUG_WRITELN(g_routinesToClassNamesMap.size());

			return true;
		}

		DEBUG_PRINT("Found no removable routine of type: `");
		DEBUG_WRITE(TYPE_NAME(RoutineT));
		DEBUG_WRITELN("`.");

		return false;
	}

}
