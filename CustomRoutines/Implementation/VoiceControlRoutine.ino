#include "../VoiceControlRoutine.hpp"

class VoiceControlRoutine : public NsAppRoutines::AppRoutine {
public:
	void loop() override {
		if (Serial.available() < 1)
			return;

		char receivedValue = Serial.read();
		DEBUG_PRINTLN("Received voice control: " + receivedValue);

		switch (receivedValue) {
			case '^':
				NsCar::moveForward();
				break;

			case '-':
				NsCar::moveBackward();
				break;

			case '<':
				const int leftVal = NsUltrasonic::lookLeft();
				g_servo.write(SERVO_POINT);

				if (leftVal >= 10) {
					NsCar::moveLeft();
					delay(500);
					NsCar::stop();
				} else if (leftVal < 10)
					NsCar::stop(); // Let's not worry about having an extra condition here!
				break;

			case '>':
				const int rightVal = NsUltrasonic::lookRight();
				g_servo.write(SERVO_POINT);
				if (rightVal >= 10) {
					NsCar::moveRight();
					delay(500);
					NsCar::stop();
				} else if (rightVal < 10) {
					NsCar::stop();
				}
				break;

			case '*':
				NsCar::stop();
				break;

			default:
				// TODO Make some error routine!
				break;
		}
	}
};
