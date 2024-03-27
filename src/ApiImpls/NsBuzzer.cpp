#include "CarApi/NsBuzzer.hpp"
#include "Api/DebuggingMacros.hpp"

namespace NsBuzzer {

    static int buzzerPrevState;
    static bool buzzerShouldBeep;
    static unsigned long nextCheckMillis;

    void buzzerSetup() {
        pinMode(PIN_BUZZER, OUTPUT);
    }

    void buzzerRoutine() {
        if (!NsBuzzer::buzzerShouldBeep)
            return;

        if (millis() > NsBuzzer::nextCheckMillis) {
            if (digitalRead(PIN_BUZZER) == HIGH)
                digitalWrite(PIN_BUZZER, LOW);
            else
                digitalWrite(PIN_BUZZER, HIGH);

            NsBuzzer::nextCheckMillis = millis() + BUZZER_INTERVAL;
        }
    }

    void buzzerStart() {
        NsBuzzer::buzzerShouldBeep = true;
        NsBuzzer::nextCheckMillis = millis() + BUZZER_INTERVAL;
        digitalWrite(PIN_BUZZER, HIGH);
    }

    void buzzerStop() {
        NsBuzzer::buzzerShouldBeep = false;
        digitalWrite(PIN_BUZZER, LOW);
    }

    bool buzzerIsBeeping() {
        return NsBuzzer::buzzerShouldBeep;
    }

}


