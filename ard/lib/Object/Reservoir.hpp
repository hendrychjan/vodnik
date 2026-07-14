#pragma once

#include "Arduino.h"
#include "IOObject.hpp"

class Reservoir : public IOObject {
 public:
  Reservoir(uint8_t echoPin, uint8_t triggerPin, int emptyDistanceCm)
      : _echoPin(echoPin),
        _triggerPin(triggerPin),
        _emptyDistanceCm(emptyDistanceCm),
        _distanceCm(0) {}

  void setup() override;

  void refresh();
  int getDistanceCached();
  bool isEmpty();

 private:
  uint8_t _echoPin;
  uint8_t _triggerPin;
  int _emptyDistanceCm;
  int _distanceCm;
};
