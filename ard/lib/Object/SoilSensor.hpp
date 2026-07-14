#pragma once

#include "Arduino.h"
#include "IOObject.hpp"

class SoilSensor : public IOObject {
 public:
  SoilSensor(uint8_t pin)
      : _pin(pin) {}

  void setup() override;

  int getValue();

 private:
  uint8_t _pin;
};
