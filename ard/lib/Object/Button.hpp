#pragma once

#include "../Config.hpp"
#include "Arduino.h"
#include "IOObject.hpp"

class Button : public IOObject {
 public:
  Button(uint8_t pin) : _pin(pin), _wasPressed(false), _lastRawState(false) {}

  void setup() override;

  bool didActivate();

 private:
  uint8_t _pin;
  bool _wasPressed;
  bool _lastRawState;
  unsigned long _lastDebounceMs = 0;
};