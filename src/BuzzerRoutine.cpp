#include "Api/Globals.hpp"
#include "Api/DebuggingMacros.hpp"

#include "CarApi/NsBuzzer.hpp"
#include "RoutineDecls/BuzzerRoutine.hpp"

void BuzzerRoutine::setup() {
    NsBuzzer::buzzerSetup();
}

void BuzzerRoutine::loop() {
    NsBuzzer::buzzerRoutine();
}
