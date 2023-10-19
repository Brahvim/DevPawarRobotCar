#pragma once

namespace NsAppRoutines {

	class AppRoutine {
	public:
		/** @brief  Called when this routine starts. */
		virtual void setup() {
		} /* = 0; */

		/** @brief  Called in `loop()` after this routine has started. */
		virtual void loop() {
		} /* = 0; */

		/**
		 * @brief  Called when this routine has been requested to be removed
		 * from the list of currently active routines.
		 */
		virtual void out() {
		} /* = 0; */
	};

	enum AppRoutineAdditionError {
		NO_ERROR,
		ROUTINE_ALREADY_EXISTS,
	};

	/**
	 * @brief Attempts to add a routine of the given type, returning
	 * `NsAppRoutines::AppRoutineAdditionError::ROUTINE_ALREADY_EXISTS` if it was already added.
	 * Otherwise, the routine is added and `NsAppRoutines::AppRoutineAdditionError::NO_ERROR` is returned.
	 */
	template <class RoutineT>
	NsAppRoutines::AppRoutineAdditionError addRoutine();

	/** Attempts to remove a routine, then tell if it was successful. */
	template <class RoutineT>
	bool removeRoutine();

}
