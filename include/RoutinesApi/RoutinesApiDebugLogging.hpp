#ifdef ROUTINES_API_ENABLE_DEBUG_LOGS
#define DEBUG_LOGS_PREFIX "[RoutinesApi] "
#include "PerFileLogging/DebugLogging.hpp"
#endif

// ...Try it out!

/*
// Code example!:

```cpp
DEBUG_PRINT_NOPRE_NOPM("Hello, world!");
DEBUG_PRINT_NOPRE("Greetings!");
DEBUG_PRINT_NOPRE_LN_NOPM("Goodbye, world!");
DEBUG_PRINT_NOPRE_LN("See you later!");
DEBUG_PRINT_NOPM("Important message!");
DEBUG_PRINT_LN_NOPM("Time for a line break!");
DEBUG_PRINT_LN("Final words.");

Serial.println("It's done!");
```

// Output from said code example 😂:

```log
Hello, world!Greetings!Goodbye, world!
See you later!
[RoutinesApi] Important message![RoutinesApi] Time for a line break!
[RoutinesApi] Final words.
It's done!
```

*/
