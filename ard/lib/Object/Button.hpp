#pragma once

#include "Arduino.h"

class Button {
 public:
  Button(uint8_t pin) : _pin(pin) { pinMode(_pin, INPUT_PULLUP); }

  bool didActivate();

 private:
  uint8_t _pin;
};