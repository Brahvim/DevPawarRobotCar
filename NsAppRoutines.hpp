#pragma once

namespace NsAppRoutines {

class AppRoutine {
protected:
  /** @brief  Called when this routine starts. */
  virtual void setup() = 0;

  /** @brief  Called in `loop()` after this routine has started. */
  virtual void loop() = 0;
};

void setRoutine();
void setInitialRoutine();

}
