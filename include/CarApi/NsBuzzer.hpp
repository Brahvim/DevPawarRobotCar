#pragma once

#define PIN_BUZZER 9
#define BUZZER_INTERVAL 500

namespace NsBuzzer {

    /**
     * @brief Call this in this `start()`.
     */
    void buzzerSetup();

    /**
     * @brief Call this in your routine's `loop()`!
     */
    void beepRoutine();

    /**
     * @brief Call this in your routine's `loop()`!
     */
    void beepStart();

    /**
     * @brief Call this in your routine's `loop()`!
     */
    void beepStop();

}
