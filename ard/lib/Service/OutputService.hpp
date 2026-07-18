#pragma once

#include "../Config.hpp"
#include "Activator.hpp"
#include "IOService.hpp"
#include "StateService.hpp"

class OutputService : public IOService {
 public:
  OutputService(StateService& stateService) : _stateService(stateService) {}

  void setup() override;
  void hook() override;

 private:
  StateService& _stateService;

  Activator _reservoirHasWaterLED{Config::PIN_RESERVOIR_HAS_WATER_LED, true};
  Activator _pumpRelays[Config::NUMBER_OF_PUMPS] = {
      Activator(Config::PIN_PUMP_RELAY[0], false, LOW),
      Activator(Config::PIN_PUMP_RELAY[1], false, LOW),
  };
};
