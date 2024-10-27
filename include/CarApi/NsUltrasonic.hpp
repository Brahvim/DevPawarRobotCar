#pragma once

#include <Arduino.h>
#include "Api/Globals.hpp"

#define PIN_ULTRASONIC_ECHO		A0
#define PIN_ULTRASONIC_TRIG 	A1

namespace NsUltrasonic {

	extern volatile int g_countingSemaphoreZeroReads;

	int read();

	int lookLeft();

	int lookRight();

}
