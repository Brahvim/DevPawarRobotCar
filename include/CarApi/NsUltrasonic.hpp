#pragma once

#define PIN_ULTRASONIC_ECHO			A0
#define PIN_ULTRASONIC_TRIG			A1
#define ULTRASONIC_MAX_ZERO_READS 	5

namespace NsUltrasonic {

	extern volatile int g_countingSemaphoreZeroReads;

	int read();

	int lookLeft();

	int lookRight();

}
