#include <Arduino.h>

#include "LoggingProjectWide.h"

void setup() {
	Serial.begin(9600);
	fdevopen([](char const p_char, FILE *p_stream) -> int { return Serial.write(p_char); }, 0);
}

void loop() {
	logds("Debugging!");
}
