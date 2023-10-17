#pragma once

#include "NsUltrasonic.hpp"

namespace NsCar {

	void forward() {
		g_dcMotors[1].run(FORWARD);
		g_dcMotors[2].run(FORWARD);
		g_dcMotors[3].run(FORWARD);
		g_dcMotors[4].run(FORWARD);
	}

	void backward() {
		g_dcMotors[1].run(BACKWARD);
		g_dcMotors[2].run(BACKWARD);
		g_dcMotors[3].run(BACKWARD);
		g_dcMotors[4].run(BACKWARD);
	}

	void right() {
		g_dcMotors[1].run(BACKWARD);
		g_dcMotors[2].run(BACKWARD);
		g_dcMotors[3].run(FORWARD);
		g_dcMotors[4].run(FORWARD);
	}

	void left() {
		g_dcMotors[1].run(FORWARD);
		g_dcMotors[2].run(FORWARD);
		g_dcMotors[3].run(BACKWARD);
		g_dcMotors[4].run(BACKWARD);
	}

	void stop() {
		g_dcMotors[1].run(RELEASE);
		g_dcMotors[2].run(RELEASE);
		g_dcMotors[3].run(RELEASE);
		g_dcMotors[4].run(RELEASE);
	}

	int lookRight() {
		g_servo.write(20);
		delay(800);
		return NsUltrasonic::read();
	}

	int lookLeft() {
		g_servo.write(180);
		delay(800);
		return NsUltrasonic::read();
	}
}
