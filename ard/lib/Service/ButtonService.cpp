#include "ButtonService.hpp"

void ButtonService::setup() {
  _modeSwitchButton.setup();

  for (auto& pumpOverrideButton : _pumpOverrideButtons)
    pumpOverrideButton.setup();
}

void ButtonService::hook() {
  if (_modeSwitchButton.didActivate()) {
    Mode newMode = _stateService.getMode() == AUTOMATIC ? OVERRIDE : AUTOMATIC;
    _stateService.setMode(newMode);
  }

  if (_stateService.getMode() == OVERRIDE) {
    for (uint8_t i = 0; i < Config::NUMBER_OF_PUMPS; i++) {
      if (_pumpOverrideButtons[i].didActivate()) {
        _stateService.pumpsActivated[i] = !_stateService.pumpsActivated[i];
      }
    }
  }
}