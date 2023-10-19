#pragma once

#include "../Globals.hpp"

#include <Servo.h>

extern const Servo g_servo;

namespace NsUltrasonic {

	int read();

	int lookLeft();

	int lookRight();

}
