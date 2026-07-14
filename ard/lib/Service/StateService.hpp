#pragma once

#include "../Config.hpp"
#include "Arduino.h"

class StateService {
 public:
  bool isReservoirEmpty = false;
  bool pumpsActivated[Config::NUMBER_OF_PUMPS] = {
      false,
      false,
      false,
  };

  bool pumpsCycleQueued[Config::NUMBER_OF_PUMPS] = {
      false,
      false,
      false,
  };

 private:
  void _clearPumpCycles();
};
