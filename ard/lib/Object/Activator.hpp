#pragma once

#include "Arduino.h"

class Activator {
 public:
  Activator(uint8_t pin, bool initial = false) : _pin(pin), _isOn(initial) {
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, _isOn ? HIGH : LOW);
  }

  void toggleOn();
  void toggleOff();

  bool isOn();

 private:
  uint8_t _pin;
  bool _isOn;
};
