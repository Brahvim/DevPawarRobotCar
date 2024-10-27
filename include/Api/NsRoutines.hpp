#pragma once

#include <ArxContainer.h>

namespace NsRoutines {

	/**
	 * @brief Base class for `CRoutine` to allow using CRTP *and* base class pointers.
	 */
	class CRoutineBase {

	public:
		virtual ~CRoutineBase() = default;

		virtual void callSetup();

		virtual void callLoop();

		virtual void callOut();

	};

	/**
	 * @brief A class to allow many tasks to take place at once, and be added or removed easily.
	 * All data is maintained privately, in a single implementation file.
	 *
	 * The default implementations call `DEBUG_PRINTLN()` to remind about missing overrides.
	 */
	template <class TChildClassCrtpCall>
	class CRoutine : public CRoutineBase {

	public:
		/** @brief `virtual` destructor so `-Wdelete-non-virtual-dtor` is happy. Typical OO slow-thing. Sorry I'm not writing data-oriented C yet... */
		virtual ~CRoutine() = default;

		/** @brief Calls `setup()` from your derived class when this routine starts. */
		void callSetup() override final {
			static_cast<TChildClassCrtpCall*>(this)->setup();
		}

		/** @brief Calls `loop()` from your derived class in Arduino's `loop()` after this routine has started. */
		void callLoop() override final {
			static_cast<TChildClassCrtpCall*>(this)->loop();
		}

		/** @brief Calls `out()` from your derived class when this routine has been requested to be removed from the list of currently active routines. */
		void callOut() override final {
			static_cast<TChildClassCrtpCall*>(this)->out();
		}

	};

	enum class EcRoutineAdditionError {

		NO_ERROR,
		ROUTINE_ALREADY_EXISTS,

	};

#pragma region // Methods to manage routine collections.
	/**
	 * @brief Attempts to add a routine of the given type, returning
	 * `NsRoutines::EcRoutineAdditionError::ROUTINE_ALREADY_EXISTS` if it was already added.
	 * Otherwise, the routine is added and `NsRoutines::EcRoutineAdditionError::NO_ERROR` is returned.
	 */
	template <class TRoutine>
	NsRoutines::EcRoutineAdditionError addRoutine();

	/** @brief Attempts to remove a routine, call `out()` on it, and tell if it was successful. */
	template <class TRoutine>
	bool removeRoutine();
#pragma endregion

}
