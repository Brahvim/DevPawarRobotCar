#define ENABLE_DEBUG_LOGS

#include "../DebuggingMacros.hpp"
#include "../Globals.hpp"
#include "../NsAppRoutines.hpp"

class BluetoothRoutine : public NsAppRoutines::AppRoutine {
public:
	void setup() override {
		pinMode(LED_BUILTIN, OUTPUT);
		Serial.println("Setup done!");
	}

	void loop() override {
		digitalWrite(LED_BUILTIN, LOW);
		delay(150);
		digitalWrite(LED_BUILTIN, HIGH);
		delay(150);

		Serial.println("Yo!");
	}

	void out() override {
		Serial.println("Alrighty, I'm out!");
	}
};

MAKE_TYPE_INFO(BluetoothRoutine);
