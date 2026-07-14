#pragma once

#include "../Config.hpp"
#include "Arduino.h"
#include "Button.hpp"
#include "IOService.hpp"
#include "StateService.hpp"

/// @brief Adds event hooks for physical buttons and updates states in
/// StateService upon button press
class ButtonService : public IOService {
 public:
  ButtonService(StateService& stateService) : _stateService(stateService) {}

  void setup() override;
  void hook() override;

 private:
  StateService& _stateService;

  Button _modeSwitchButton{Config::PIN_BUTTON_MODE};
  Button _pumpOverrideButtons[Config::NUMBER_OF_PUMPS] = {
      Button(Config::PIN_BUTTON_PUMP_1_OVERRIDE),
      Button(Config::PIN_BUTTON_PUMP_2_OVERRIDE),
      Button(Config::PIN_BUTTON_PUMP_3_OVERRIDE),
  };
};