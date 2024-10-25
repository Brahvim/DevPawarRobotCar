#pragma once

#define PIN_BUZZER 2
#define BUZZER_INTERVAL_NO_PATH 500
#define BUZZER_INTERVAL_BACK_MUSIC 250
#define BUZZER_INTERVAL_ULTRASONIC_BROKE 50

namespace NsBuzzer {

	/**
	 * @brief Call this in this `start()`.
	 */
	void buzzerSetup();

	/**
	 * @brief Call this in your routine's `loop()`!
	 */
	void buzzerRoutine();

	/**
	 * @brief Starts the car's "SOS beep cycle".
	 */
	void buzzerStart(unsigned long beepInterval);

	/**
	 * @brief Ends the car's "SOS beep cycle".
	 */
	void buzzerStop();

	bool buzzerIsBeeping();

	unsigned long buzzerGetBeepInterval();

}
