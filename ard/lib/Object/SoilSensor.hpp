#pragma once

#include "Arduino.h"
#include "IOObject.hpp"

class SoilSensor : public IOObject {
 public:
  SoilSensor(uint8_t pin, int targetValue)
      : _pin(pin), _targetValue(targetValue), _value(0) {}

  void setup() override;

  void refresh();
  int getValueCached();
  bool isBelowTarget();

 private:
  uint8_t _pin;
  int _targetValue;
  int _value;
};
