#include "../ObstacleHandlingRoutine.hpp"

class ObstacleHandlingRoutine : public NsAppRoutines::AppRoutine {
public:
	void loop() override {
		const int dist = NsUltrasonic::read(); // Could use this info later!
		DEBUG_PRINTLN("Distance: " + dist);
		delay(100);

		if (dist > 12) {
			NsCar::moveForward();
			return;
		}

		NsCar::stop();
		NsCar::moveBackward();

		delay(100);
		NsCar::stop();

		const int leftVal = NsUltrasonic::lookLeft();
		g_servo.write(SERVO_POINT);

		delay(800);

		const int rightVal = NsUltrasonic::lookRight();
		g_servo.write(SERVO_POINT);

		if (leftVal < rightVal)
			NsCar::moveRight();
		else if (leftVal > rightVal)
			NsCar::moveLeft();

		delay(500);
		NsCar::stop();

		// Is this because of a race condition?
		delay(200);
		delay(500);

		NsCar::stop();
		delay(200);
	}
};
