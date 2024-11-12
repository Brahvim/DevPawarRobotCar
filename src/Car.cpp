#include "Car.h"

Servo g_carServo;
AF_DCMotor g_carMotors[4] = {

    /*

    L293D motor numbers:
    ```
    2 1
    3 4
    ```

    As array indices:
    ```
    1 0
    2 3
    ```

    */

    AF_DCMotor(1),
    AF_DCMotor(2),
    AF_DCMotor(3),
    AF_DCMotor(4),

};
