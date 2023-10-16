#pragma region  // Global declarations!
#include <Servo.h>
#include <AFMotor.h>

#define PIN_ULTRASONIC_ECHO A0
#define PIN_ULTRASONIC_TRIG A1
#define PIN_MOTOR 10
#define WHEEL_SPEED 170
#define SERVO_POINT 103

int g_left;
int g_right;
int L = 0;
int R = 0;
int L1 = 0;
int R1 = 0;

Servo g_servo;

AF_DCMotor g_dcMotors[4] = {
  AF_DCMotor(1),
  AF_DCMotor(2),
  AF_DCMotor(3),
  AF_DCMotor(4),
};
#pragma endregion

void setup() {
  Serial.begin(9600);
  pinMode(PIN_ULTRASONIC_TRIG, OUTPUT);
  pinMode(PIN_ULTRASONIC_ECHO, INPUT);
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
  char receivedValue = 0;
  if (Serial.available() > 0) {
    receivedValue = Serial.read();
    Serial.println(receivedValue);
  }

  switch (receivedValue) {
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
  }
}

void obstacleRoutine() {
  const int dist = ultrasonicRead();
  Serial.println("Distance: ", dist);
  delay(100);

  if (dist > 12) {
    forward();
    return;
  }

  stop();
  backward();

  delay(100);
  stop();

  L = lookLeft();
  g_servo.write(SERVO_POINT);

  delay(800);

  R = lookRight();
  g_servo.write(SERVO_POINT);

  if (L < R)
    right();
  else if (L > R)
    left();


  delay(500);
  stop();
  delay(200);
  delay(500);
  stop();
  delay(200);
}

void voiceControlRoutine() {
  char receivedValue = 0;
  if (Serial.available() > 0) {
    receivedValue = Serial.read();
    Serial.println(receivedValue);
    if (receivedValue == '^') {
      forward();
    } else if (receivedValue == '-') {
      backward();
    } else if (receivedValue == '<') {
      L = lookLeft();
      g_servo.write(SERVO_POINT);
      if (L >= 10) {
        left();
        delay(500);
        stop();
      } else if (L < 10) {
        stop();
      }
    } else if (receivedValue == '>') {
      R = lookRight();
      g_servo.write(SERVO_POINT);
      if (R >= 10) {
        right();
        delay(500);
        stop();
      } else if (R < 10) {
        stop();
      }
    } else if (receivedValue == '*') {
      stop();
    }
  }
}

/**
  Sends a pulse to the ultrasonic sensor, and then 
  reads the distance the ultrasonic sensor has read.
*/
int ultrasonicRead() {
  // Set the line to `LOW` (just to make sure):
  digitalWrite(PIN_ULTRASONIC_TRIG, LOW);
  delayMicroseconds(4);  // We're making a pulse, thus this little delay.

  // Set the line to `HIGH`:
  digitalWrite(PIN_ULTRASONIC_TRIG, HIGH);
  delayMicroseconds(10);  // We wait more before reading anything off of the sensor.

  // Set the pin to `LOW` again:
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