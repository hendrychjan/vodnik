#pragma once

#include "../Config.hpp"
#include "Activator.hpp"
#include "IOService.hpp"
#include "StateService.hpp"

/// @brief Enables digital output devices (LEDs, relays, ...) based on flags in
/// StateService
class ActivatorService : public IOService {
 public:
  ActivatorService(StateService& stateService) : _stateService(stateService) {}

  void setup() override;
  void hook() override;

 private:
  StateService& _stateService;

  Activator _isAutomaticEnabledLED{Config::PIN_AUTOMATIC_LED, true};
  Activator _pumpRelays[Config::NUMBER_OF_PUMPS] = {
      Activator(Config::PIN_RELAY_PUMP_1, false),
      Activator(Config::PIN_RELAY_PUMP_2, false),
      Activator(Config::PIN_RELAY_PUMP_3, false),
  };
};
