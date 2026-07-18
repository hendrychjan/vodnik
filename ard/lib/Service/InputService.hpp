#pragma once

#include "../Config.hpp"
#include "Arduino.h"
#include "Button.hpp"
#include "IOService.hpp"
#include "Mux.hpp"
#include "Reservoir.hpp"
#include "StateService.hpp"

/// @brief Adds event hooks for physical buttons and updates states in
/// StateService upon button press
class InputService : public IOService {
 public:
  InputService(StateService& stateService) : _stateService(stateService) {}

  void setup() override;
  void hook() override;

 private:
  StateService& _stateService;

  Button _stopAllPumpsButton{Config::PIN_BUTTON_STOP_PUMPS};
  Button _refreshSensorsButton{Config::PIN_BUTTON_REFRESH_SENSORS};
  Reservoir _reservoir{Config::PIN_DIST_ECHO, Config::PIN_DIST_TRIG};
  Mux _mux{Config::PIN_MUX_SELECT, Config::PIN_MUX_DATA,
           Config::PIN_MUX_ENABLE};
};
