#pragma once

#define PIN_BUZZER 2
#define BUZZER_INTERVAL_NO_PATH 500
#define BUZZER_INTERVAL_BACK_MUSIC 250
#define BUZZER_INTERVAL_ULTRASONIC_BROKE 25

namespace NsBuzzer {

	/** @brief Ends the car's "SOS beep cycle". */
	void buzzerStopAsyncBeeps();

	bool buzzerIsDoingAsyncBeeps();

	unsigned long buzzerGetAsyncBeepsInterval();

	void buzzerDoSyncBeep(unsigned long duration);

	/** @brief Starts the car's "SOS beep cycle". */
	void buzzerStartAsyncBeeps(unsigned long beepInterval);


}
