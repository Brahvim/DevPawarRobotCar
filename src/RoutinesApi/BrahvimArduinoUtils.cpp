#include "BrahvimArduinoUtils.hpp"

#include <Arduino.h>

#ifdef __AVR__
#include <avr/sleep.h>
#endif

namespace BrahvimArduinoUtils {


#ifdef __AVR__
    namespace AvrOnly {

        void arduinoSleep() {

            // Arduino sleep modes as explained by ChatGPT:
            /*
            `SLEEP_MODE_IDLE`:
                In this mode, the CPU is stopped while the peripherals and interrupts remain active.
                It's the mode with the least power savings, as the CPU is only halted, but other components continue to operate.

            `SLEEP_MODE_ADC`:
                This mode is similar to `SLEEP_MODE_IDLE` but with the added feature that the ADC
                (Analog-to-Digital Converter) is turned off. It's useful when you don't need ADC conversions during sleep.

            `SLEEP_MODE_PWR_DOWN`:
                This is a deeper sleep mode where the CPU and all other peripherals are turned off,
                except for asynchronous timers and external interrupts. The device is in the lowest power consumption state.
                To wake up, an external interrupt, a Watchdog Timer interrupt, or a pin change interrupt can be used.

            `SLEEP_MODE_PWR_SAVE`:
                This mode is similar to `SLEEP_MODE_PWR_DOWN` but allows the asynchronous timer (Timer/Counter2) to
                continue running. It provides a compromise between power saving and the ability to maintain timing functions.

            `SLEEP_MODE_STANDBY`:
                In this mode, the crystal/resonator oscillator is running, providing a faster wake-up time than
                `SLEEP_MODE_PWR_DOWN`. The CPU is halted, and all other peripherals are turned off.
                Like `SLEEP_MODE_PWR_DOWN`, external interrupts, pin change interrupts, or a Watchdog Timer interrupt can wake
                up the device.

            `SLEEP_MODE_EXT_STANDBY`:
                This is a more extended version of `SLEEP_MODE_STANDBY`.
                It provides an even faster wake-up time by keeping the external oscillator running.
        */

            set_sleep_mode(SLEEP_MODE_PWR_DOWN);
            sleep_enable();
            sleep_mode();
        }
    }
#else
#endif

}

