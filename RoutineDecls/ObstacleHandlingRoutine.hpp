#pragma once
#define ENABLE_DEBUG_LOGS

#include "../Api/DebuggingMacros.hpp"
#include "../Api/Globals.hpp"
#include "../Api/NsAppRoutines.hpp"

class ObstacleHandlingRoutine : public NsAppRoutines::AppRoutine {};

MAKE_TYPE_INFO(ObstacleHandlingRoutine);
