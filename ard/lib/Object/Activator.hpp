#pragma once

#include "Arduino.h"
#include "IOObject.hpp"

class Activator : public IOObject {
 public:
  Activator(uint8_t pin, bool initialState = false, uint8_t onSignal = HIGH)
      : _pin(pin), _isOn(initialState), _onSignal(onSignal) {}

  void setup() override;

  bool isOn();
  bool toggle(bool isActive);

 private:
  uint8_t _pin;
  bool _isOn;
  uint8_t _onSignal;
};
