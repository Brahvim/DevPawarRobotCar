#pragma once

namespace NsAppRoutines {

    class AppRoutine {
    protected:
        /** @brief  Called when this routine starts. */
        virtual void setup(){
            // <Sigh>.....  ^ Arduino IDE formatting!...
        };

        /** @brief  Called in `loop()` after this routine has started. */
        virtual void loop(){

        };

        /**
         * @brief  Called when this routine has been requested to be removed
         * from the list of currently active routines.
         */
        virtual void out(){

        };
    };

    enum AppRoutineError {
      ROUTINE_ALREADY_EXISTS,
    };

    /** Adds a routine. */
    void addRoutine(const NsAppRoutines::AppRoutine &routine);

    /** Removes a routine. */
    void removeRoutine(const NsAppRoutines::AppRoutine &routine);

}
