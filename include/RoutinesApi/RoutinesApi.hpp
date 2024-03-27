#include <vector>

namespace RoutinesApi {

	/** @brief Please call this in your Arduino code's `setup()`. Anywhere in there. */
	void setup();

	/** @brief Please call this in your Arduino code's `loop()`. Anywhere in there. */
	void loop();

	/** @brief Abstract class representing a routine object. */
	class IRoutine {
	public:

		/** Called when this routine is first called. */
		virtual void setup() { };

		/** Called in yor sketch's `loop()` along with other `IRoutine` instances's `loop()` method,
		 *  in the order of your routines list. */
		virtual void loop() { };

		/** Called when the routines list has been changed. */
		virtual void out() { };

	};

	/**
	 * @brief Simple type-definition to avoid typing too much.
	 * This is to be used as the return type for `supplyRoutines()`.
	 * Make sure to allocate this on the heap!
	 */
	typedef std::vector<RoutinesApi::IRoutine*> FixedSizeRoutinesList;

}

/** @brief Write an implementation for this to supply `RoutinesApi::IRoutine` instances. */
RoutinesApi::FixedSizeRoutinesList supplyRoutines();
