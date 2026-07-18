#pragma once

#include "Arduino.h"

namespace Const {

static constexpr unsigned long BUTTON_DEBOUNCE_MS = 50;
static constexpr int BUTTON_ANALOG_PRESS_THRESHOLD = 700;
static constexpr uint8_t MUX_SELECT_SIZE = 4;
static constexpr uint8_t MUX_CHANNEL_SIZE = MUX_SELECT_SIZE * MUX_SELECT_SIZE;

}