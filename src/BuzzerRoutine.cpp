#include "../include/Api/Globals.hpp"
#include "../include/Api/DebuggingMacros.hpp"

#include "../include/CarApi/NsBuzzer.hpp"
#include "../include/RoutineDecls/BuzzerRoutine.hpp"

void BuzzerRoutine::setup() {
    NsBuzzer::buzzerSetup();
}

void BuzzerRoutine::loop() {
    NsBuzzer::beepRoutine();
}
