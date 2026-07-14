#include "StateService.hpp"

const Mode StateService::getMode() { return _mode; }

void StateService::setMode(Mode mode) {
  _mode = mode;
  _clearPumpCycles();

  Serial.println(mode == AUTOMATIC ? "mode 1" : "mode 2");
}

void StateService::_clearPumpCycles() {
  for (uint8_t i = 0; i < Config::NUMBER_OF_PUMPS; i++) {
    pumpsActivated[i] = false;
    pumpsCycleQueued[i] = false;
  }
}
