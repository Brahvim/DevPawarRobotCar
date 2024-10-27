#include <Arduino.h>
#include "CarApi/NsCar.hpp"

void wheelTest() {
    delay(2000);
    NsCar::stop();
    NsCar::motors[0].run(FORWARD);

    delay(2000);
    NsCar::stop();
    NsCar::motors[1].run(FORWARD);

    delay(2000);
    NsCar::stop();
    NsCar::motors[2].run(FORWARD);

    delay(2000);
    NsCar::stop();
    NsCar::motors[3].run(FORWARD);
}

void sideTest() {
    delay(500);
    NsCar::moveLeft(1000);

    delay(500);
    NsCar::moveRight(1000);
}
