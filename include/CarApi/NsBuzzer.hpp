#pragma once

#define PIN_BUZZER 2
#define BUZZER_INTERVAL 500

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
     * @brief Call this in your routine's `loop()`!
     */
    void buzzerStart();

    /**
     * @brief Call this in your routine's `loop()`!
     */
    void buzzerStop();

    bool buzzerIsBeeping();

}
