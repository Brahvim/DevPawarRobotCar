#include "RoutineDecls/BluetoothRoutine.hpp"

class BluetoothRoutine : public NsAppRoutines::AppRoutine {
public:
	void loop() override {
		if (Serial.available() < 1)
			return;

		// Unconventional, but accounts for bad cases without `<=`.
		// Also, faster! :>

		switch (Serial.read()) {
			case 'F':
				NsCar::moveForward();
				break;

			case 'B':
				NsCar::moveBackward();
				break;

			case 'L':
				NsCar::moveLeft();
				break;

			case 'R':
				NsCar::moveRight();
				break;

			case 'S':
				NsCar::stop();
				break;

			default:
				// TODO Make some error routine!
				break;
		}
	}
};
