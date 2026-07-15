#pragma once

#include "../Config.hpp"
#include "Arduino.h"
#include "IOObject.hpp"

class Reservoir : public IOObject {
 public:
  Reservoir(uint8_t echoPin, uint8_t triggerPin)
      : _echoPin(echoPin), _triggerPin(triggerPin) {}

  void setup() override;

  unsigned long getDistanceCm();

 private:
  uint8_t _echoPin;
  uint8_t _triggerPin;

  unsigned long _getDistanceOnePulseCm();
};
