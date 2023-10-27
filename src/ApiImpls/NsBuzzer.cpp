#include "../../include/CarApi/NsBuzzer.hpp"
#include "../../include/Api/DebuggingMacros.hpp"

namespace NsBuzzer {

    bool buzzerShouldBeep;

    void buzzerSetup() {
        pinMode(2, OUTPUT);
    }

    void beepRoutine() {

        if (NsBuzzer::buzzerShouldBeep) {

        }

    }

}


