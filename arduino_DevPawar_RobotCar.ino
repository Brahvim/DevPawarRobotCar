#define DEBUG  // Used by `Globals.hpp`.

#pragma region Includes.
#include <Servo.h>
#include <AFMotor.h>
#include <Vector.h>

#include "NsCar.hpp"
#include "Globals.hpp"  // Includes more stuff!
#include "NsUltrasonic.hpp"
#pragma endregion

// #pragma region Static declarations.
static Vector<NsAppRoutines::AppRoutine *> s_routinesArray;
// #pragma endregion

namespace NsAppRoutines {
void setRoutine(const AppRoutine &p_ptrAppRoutine) {
}
}

void setup() {
  while (!Serial) {}
  Serial.begin(ARDUINO_SERIAL_BAUD_RATE);

  pinMode(PIN_ULTRASONIC_ECHO, INPUT);
  pinMode(PIN_ULTRASONIC_TRIG, OUTPUT);

  g_servo.attach(PIN_SERVO);

  g_dcMotors[1].setSpeed(WHEEL_SPEED);
  g_dcMotors[2].setSpeed(WHEEL_SPEED);
  g_dcMotors[3].setSpeed(WHEEL_SPEED);
  g_dcMotors[4].setSpeed(WHEEL_SPEED);
}

void loop() {
  obstacleRoutine();
  bluetoothControlRoutine();
  voiceControlRoutine();
}

void bluetoothControlRoutine() {
  if (Serial.available() < 1)
    return;

  // Unconventional, but accounts for bad cases without `<=`.
  // Also, faster! :>

  switch (Serial.read()) {
    case 'F':
      forward();
      break;

    case 'B':
      backward();
      break;

    case 'L':
      left();
      break;

    case 'R':
      right();
      break;

    case 'S':
      stop();
      break;

    default:
      // TODO Make some error routine!
      break;
  }
}

void obstacleRoutine() {
  const int dist = NsUltrasonic::read();  // Could use this info later!
  DEBUG_PRINT("Distance: " + dist);
  delay(100);

  if (dist > 12) {
    forward();
    return;
  }

  stop();
  backward();

  delay(100);
  stop();

  const int leftVal = lookLeft();
  g_servo.write(SERVO_POINT);

  delay(800);

  const int rightVal = lookRight();
  g_servo.write(SERVO_POINT);

  if (leftVal < rightVal)
    right();
  else if (leftVal > rightVal)
    left();


  delay(500);
  stop();

  // Is this because of a race condition?
  delay(200);
  delay(500);

  stop();
  delay(200);
}

void voiceControlRoutine() {
  if (Serial.available() < 1)
    return;

  char receivedValue = Serial.read();
  DEBUG_PRINT(receivedValue);

  switch (receivedValue) {
    case '^':
      forward();
      break;

    case '-':
      backward();
      break;

    case '<':
      const int leftVal = lookLeft();
      g_servo.write(SERVO_POINT);

      if (leftVal >= 10) {
        left();
        delay(500);
        stop();
      } else if (leftVal < 10)
        stop();  // Let's not worry about having an extra condition here!
      break;

    case '>':
      const int rightVal = lookRight();
      g_servo.write(SERVO_POINT);
      if (rightVal >= 10) {
        right();
        delay(500);
        stop();
      } else if (rightVal < 10) {
        stop();
      }
      break;

    case '*':
      stop();
      break;

    default:
      // TODO Make some error routine!
      break;
  }
}

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
