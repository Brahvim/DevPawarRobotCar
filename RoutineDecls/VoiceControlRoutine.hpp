#pragma once
#define ENABLE_DEBUG_LOGS

#include "../Api/DebuggingMacros.hpp"
#include "../Api/Globals.hpp"
#include "../Api/NsAppRoutines.hpp"

class VoiceControlRoutine : public NsAppRoutines::AppRoutine {};

MAKE_TYPE_INFO(VoiceControlRoutine);
