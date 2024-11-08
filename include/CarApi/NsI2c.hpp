#pragma once

#include "Shared/ProtocolCarControls.hpp"

char const* wireStatusToString(uint8_t const status);

void i2cSendResponse(NsControls::MessageTypeArduino const message);
void i2cSendResponse(NsControls::MessageTypeArduino const message, size_t const size, void *buffer);

void i2cReadEspCam(size_t const bytes, uint8_t *const buffer);
void i2cAwaitEspCam(int const bytes, size_t const interval_millis = 1, size_t const interval_count = 100);
NsControls::MessageTypeEspCam i2cAwaitMessageEspCam(size_t const interval_millis = 1, size_t const interval_count = 100);
