#pragma once

#include "../Config.hpp"
#include "Activator.hpp"
#include "IOService.hpp"
#include "StateService.hpp"

class ActivatorService : public IOService {
 public:
  ActivatorService(StateService& stateService) : _stateService(stateService) {}

  void setup() override;
  void hook() override;

 private:
  StateService& _stateService;

  Activator _reservoirHasWaterLED{Config::PIN_RESERVOIR_HAS_WATER_LED, true};
  Activator _pumpRelays[Config::NUMBER_OF_PUMPS] = {
      Activator(Config::PIN_RELAY_PUMP_1, false),
      Activator(Config::PIN_RELAY_PUMP_2, false),
      Activator(Config::PIN_RELAY_PUMP_3, false),
  };
};
