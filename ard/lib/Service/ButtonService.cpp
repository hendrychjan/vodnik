#include "ButtonService.hpp"

void ButtonService::setup() {
  _stopAllPumpsButton.setup();
  _refreshSensorsButton.setup();

  for (auto& pumpOverrideButton : _pumpOverrideButtons)
    pumpOverrideButton.setup();
}

void ButtonService::hook() {
  if (_stopAllPumpsButton.didActivate()) {
    _stateService.clearAllPumpsTimeQueued();
  }

  if (_refreshSensorsButton.didActivate()) {
    _stateService.setSensorsToRefreshNow();
  }

  for (uint8_t i = 0; i < Config::NUMBER_OF_PUMPS; i++) {
    if (_pumpOverrideButtons[i].didActivate()) {
      _stateService.queuePumpCycle(i);
    }
  }
}