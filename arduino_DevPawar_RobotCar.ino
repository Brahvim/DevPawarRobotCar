#pragma region  // Global declarations!
#include <Servo.h>
#include <AFMotor.h>
#include "AppRoutine.hpp"

#define PIN_ULTRASONIC_ECHO A0
#define PIN_ULTRASONIC_TRIG A1
#define PIN_MOTOR 10
#define WHEEL_SPEED 170
#define SERVO_POINT 103

int g_left = 0;
int g_right = 0;
int g_L1 = 0;
int g_R1 = 0;

Servo g_servo;

AF_DCMotor g_dcMotors[4] = {
  AF_DCMotor(1),
  AF_DCMotor(2),
  AF_DCMotor(3),
  AF_DCMotor(4),
};
#pragma endregion

void (*restart)(void) = 0;

void setup() {
  Serial.begin(9600);

  pinMode(PIN_ULTRASONIC_ECHO, INPUT);
  pinMode(PIN_ULTRASONIC_TRIG, OUTPUT);

  g_servo.attach(PIN_MOTOR);

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
  const int dist = ultrasonicRead();  // Could use this info later!
  // Serial.println("Distance: " + dist);
  delay(100);

  if (dist > 12) {
    forward();
    return;
  }

  stop();
  backward();

  delay(100);
  stop();

  g_left = lookLeft();
  g_servo.write(SERVO_POINT);

  delay(800);

  g_right = lookRight();
  g_servo.write(SERVO_POINT);

  if (g_left < g_right)
    right();
  else if (g_left > g_right)
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
  Serial.println(receivedValue);

  switch (receivedValue) {
    case '^':
    forward();
    break;

    case '-':
    backward();
    break;

    case '<':
    g_left = lookLeft();
    g_servo.write(SERVO_POINT);

    if (g_left >= 10) {
      left();
      delay(500);
      stop();
    } else if (g_left < 10)
      stop();  // Let's not worry about having an extra condition here!
    break;

    case '>':
    g_right = lookRight();
    g_servo.write(SERVO_POINT);
    if (g_right >= 10) {
      right();
      delay(500);
      stop();
    } else if (g_right < 10) {
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

int ultrasonicRead() {
  // Lower TRIG for `4` microseconds as an error check:
  digitalWrite(PIN_ULTRASONIC_TRIG, LOW);
  delayMicroseconds(4);  // ...We'll also wait this out.

  // From the HC-SR04 datasheet:
  // Set TRIG for `10` microseconds:
  digitalWrite(PIN_ULTRASONIC_TRIG, HIGH);
  delayMicroseconds(10);

  // Set it low again for next use! ...things go wrong, okay!?
  digitalWrite(PIN_ULTRASONIC_TRIG, LOW);

  // Giving the ultrasonic sensor a duration gets us a reading:
  long pulseDur = pulseIn(PIN_ULTRASONIC_ECHO, HIGH);  // Pulse duration.
  pulseDur = pulseDur / 29 / 2;                        // Time-to-centimeters conversion.
  pulseDur = sqrt(pulseDur);                           // This is important.
  return pulseDur;
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
  return ultrasonicRead();
}

int lookLeft() {
  g_servo.write(180);
  delay(800);
  return ultrasonicRead();
}