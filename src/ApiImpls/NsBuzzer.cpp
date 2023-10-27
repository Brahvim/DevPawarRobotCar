#include "../../include/CarApi/NsBuzzer.hpp"
#include "../../include/Api/DebuggingMacros.hpp"

namespace NsBuzzer {

    static int buzzerPrevState;
    static bool buzzerShouldBeep;
    static unsigned long nextBeepMillis;

    void buzzerSetup() {
        pinMode(2, OUTPUT);
    }

    void beepRoutine() {
        if (!NsBuzzer::buzzerShouldBeep)
            return;

        if (millis() > NsBuzzer::nextBeepMillis) {
            digitalWrite(PIN_BUZZER,
                NsBuzzer::buzzerPrevState == HIGH ? LOW : HIGH);
            NsBuzzer::nextBeepMillis = millis() + BUZZER_INTERVAL;
        }
    }

    void buzzerStart() {
        NsBuzzer::buzzerShouldBeep = true;
        NsBuzzer::nextBeepMillis = millis() + BUZZER_INTERVAL;
    }

    void buzzerStop() {
        NsBuzzer::buzzerShouldBeep = false;
    }

    bool isBeeping() {
        return NsBuzzer::buzzerShouldBeep;
    }

}


