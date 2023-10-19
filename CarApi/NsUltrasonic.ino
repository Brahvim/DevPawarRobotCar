#include "NsUltrasonic.hpp"

namespace NsUltrasonic {

	int read() {
		// Lower TRIG for `4` microseconds as an error check:
		digitalWrite(PIN_ULTRASONIC_TRIG, LOW);
		delayMicroseconds(4); // ...We'll also wait this out.

		// From the HC-SR04 datasheet:
		// Set TRIG for `10` microseconds:
		digitalWrite(PIN_ULTRASONIC_TRIG, HIGH);
		delayMicroseconds(10);

		// Set it low again for next use! ...things go wrong, okay!?
		digitalWrite(PIN_ULTRASONIC_TRIG, LOW);

		// Giving the ultrasonic sensor a duration gets us a reading:
		long pulseDur = pulseIn(PIN_ULTRASONIC_ECHO, HIGH); // Pulse duration.
		pulseDur = pulseDur / 29 / 2;						// Time-to-centimeters conversion.
		// pulseDur = sqrt(pulseDur);                        // This is
		// important. Weirdly, the datasheet doesn't mention it.
		return pulseDur;
	}

	int lookLeft() {
		g_servo.write(180);
		delay(800);
		return NsUltrasonic::read();
	}

	int lookRight() {
		g_servo.write(20);
		delay(800);
		return NsUltrasonic::read();
	}

}
