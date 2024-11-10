#include <ArxContainer.h>

#include "Api/Globals.hpp"
#include "Api/NsRoutines.hpp"
#include "Api/DebuggingMacros.hpp"

#include "RoutineDecls/CRoutineBuzzer.hpp"
#include "RoutineDecls/CRoutineStoppedForever.hpp"
#include "RoutineDecls/CRoutineObstacleHandling.hpp"
#include "RoutineDecls/CRoutineControlsListener.hpp"

arx::map<const char*, NsRoutines::CRoutine*> g_routinesToClassNamesMap;

#pragma region // Template instances.
template bool NsRoutines::removeRoutine<CRoutineBuzzer>();
template bool NsRoutines::removeRoutine<CRoutineStoppedForever>();
template bool NsRoutines::removeRoutine<CRoutineObstacleHandling>();
template bool NsRoutines::removeRoutine<CRoutineControlsListener>();

template NsRoutines::EcRoutineAdditionError NsRoutines::addRoutine<CRoutineBuzzer>();
template NsRoutines::EcRoutineAdditionError NsRoutines::addRoutine<CRoutineStoppedForever>();
template NsRoutines::EcRoutineAdditionError NsRoutines::addRoutine<CRoutineObstacleHandling>();
template NsRoutines::EcRoutineAdditionError NsRoutines::addRoutine<CRoutineControlsListener>();
#pragma endregion

namespace NsRoutines {

	void CRoutine::out() { }

	void CRoutine::loop() { }

	void CRoutine::setup() { }

	template <class TRoutine>
	NsRoutines::EcRoutineAdditionError addRoutine() {
		// If an object of this class already exists,
		ifu(g_routinesToClassNamesMap.find(TYPE_NAME(TRoutine)) != g_routinesToClassNamesMap.end()) {
			DEBUG_PRINT("Routine of type `");
			DEBUG_APPEND(TYPE_NAME(TRoutine));
			DEBUG_APPENDLN("` already exists. Didn't add another.");

			// Yeah, we ain't adding another (for now! ..should this change later?! ..indexed instances?!):
			return NsRoutines::EcRoutineAdditionError::ROUTINE_ALREADY_EXISTS;
		}

		// Okay, here we go! Roll the callback!:
		NsRoutines::CRoutine *routine = static_cast<NsRoutines::CRoutine*>(new TRoutine()); // Fun fact: Object slicing ruined me here for DAYS 🤣
		g_routinesToClassNamesMap[TYPE_NAME(TRoutine)] = routine;
		routine->setup();

		DEBUG_PRINT("Added routine of type: `");
		DEBUG_APPEND(TYPE_NAME(TRoutine));
		DEBUG_APPENDLN("`.");

		return NsRoutines::EcRoutineAdditionError::NO_ERROR;
	}

	template <class TRoutine>
	bool removeRoutine() {
		// Check if a routine of the same class name exists :
		for (auto it = g_routinesToClassNamesMap.begin(); it != g_routinesToClassNamesMap.end(); ++it) {
			// If the name of the class isn't the same, keep looking (yes, this is a guard clause!):
			ifu(it->first != TYPE_NAME(TRoutine))
				continue;

			// If we've found one, we dispatch the callback and de-allocate memory:
			NsRoutines::CRoutine *routine = it->second;
			routine->out();
			delete routine;

			// ...As well as remove our object from our map:
			g_routinesToClassNamesMap.erase(it);

			DEBUG_PRINT("Removed routine of type: `");
			DEBUG_APPEND(TYPE_NAME(TRoutine));
			DEBUG_APPENDLN("`.");

			// DEBUG_PRINT("Size of vector: ");
			// DEBUG_APPENDLN(g_routinesToClassNamesMap.size());

			return true;
		}

		DEBUG_PRINT("Found no removable routine of type: `");
		DEBUG_APPEND(TYPE_NAME(TRoutine));
		DEBUG_APPENDLN("`.");

		return false;
	}

}
