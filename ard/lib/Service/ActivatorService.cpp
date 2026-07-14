#include "ActivatorService.hpp"

void printPumpState(uint8_t index, bool state) {
  Serial.print("pump ");
  Serial.print(index);
  Serial.println(state ? " 1" : " 0");
}

void ActivatorService::setup() {
  _isAutomaticEnabledLED.setup();

  for (auto& pumpRelay : _pumpRelays) pumpRelay.setup();
}

void ActivatorService::hook() {
  _isAutomaticEnabledLED.toggle(_stateService.getMode() == AUTOMATIC);

  for (uint8_t i = 0; i < Config::NUMBER_OF_PUMPS; i++) {
    bool shouldActivate = _stateService.pumpsActivated[i];
    bool pumpStateChanged = _pumpRelays[i].toggle(shouldActivate);
    if (pumpStateChanged) printPumpState(i, shouldActivate);
  }
}