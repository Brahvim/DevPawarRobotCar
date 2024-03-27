#include <Arduino.h>
#include "RoutinesApi.hpp"
#include "BrahvimArduinoUtils.hpp"

void setup() {
    Serial.begin(9600);
    RoutinesApi::setup();
}

void loop() {
    RoutinesApi::loop();
}

RoutinesApi::FixedSizeRoutinesList supplyRoutines() {
    class TestRoutine : public RoutinesApi::IRoutine {

        virtual void setup() {
            Serial.println("Hello, world!");
        }

    };

    static RoutinesApi::FixedSizeRoutinesList list({ new TestRoutine });
    return list;
}
