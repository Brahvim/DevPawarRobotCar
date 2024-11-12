#pragma once

void buzzerPlayStartupBeeps();

/** @brief Ends the car's "SOS beep cycle". */
void buzzerStopAsyncBeeps();

bool buzzerIsDoingAsyncBeeps();

unsigned long buzzerGetAsyncBeepsInterval();

void buzzerDoSyncBeep(unsigned long durationMs);

/** @brief Starts the car's "SOS beep cycle". */
void buzzerStartAsyncBeeps(unsigned long beepInterval);
