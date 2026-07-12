#pragma once

#include "Arduino.h"
#include "IOService.hpp"
#include "StateService.hpp"

class SerialService : public IOService {
 public:
  SerialService(StateService stateService) : _stateService(stateService) {
    Serial.begin(9600);
  }

  void hook() override;

 private:
  StateService _stateService;
};
