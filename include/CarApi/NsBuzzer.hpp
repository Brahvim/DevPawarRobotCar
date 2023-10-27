#pragma once

#define PIN_BUZZER 9

namespace NsBuzzer {

    /**
     * @brief Call this in your `start()`.
     */
    void buzzerSetup();

    /**
     * @brief Call this in your routine's `loop()`!
     */
    void beepRoutine();

    void beepStart();

    void beepStop();

}
