#define ENABLE_DEBUG_LOGS

#include "../include/Api/Globals.hpp"
#include "../include/Api/DebuggingMacros.hpp"
#include "../include/RoutineDecls/VoiceControlRoutine.hpp"

#include "../include/CarApi/NsServo.hpp"
#include "../include/CarApi/NsCar.hpp"
#include "../include/CarApi/NsUltrasonic.hpp"

MAKE_TYPE_INFO(VoiceControlRoutine);

// template bool NsAppRoutines::removeRoutine<VoiceControlRoutine>();
// template NsAppRoutines::AppRoutineAdditionError NsAppRoutines::addRoutine<VoiceControlRoutine>();

void VoiceControlRoutine::loop() {
	DEBUG_PRINTLN("The voice control routine is executing!");

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

		case '<': {
			const int leftVal = NsUltrasonic::lookLeft();
			NsServo::servo.write(SERVO_POINT);

			if (leftVal >= 10) {
				NsCar::moveLeft();
				delay(500);
				NsCar::stop();
			} else if (leftVal < 10)
				NsCar::stop(); // Let's not worry about having an extra condition here!
		}
				break;

		case '>': {
			const int rightVal = NsUltrasonic::lookRight();
			NsServo::servo.write(SERVO_POINT);
			if (rightVal >= 10) {
				NsCar::moveRight();
				delay(500);
				NsCar::stop();
			} else if (rightVal < 10) {
				NsCar::stop();
			}
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
