#include "ActivatorService.hpp"

void printPumpState(uint8_t index, bool state) {
  Serial.print("pump ");
  Serial.print(index);
  Serial.println(state ? " 1" : " 0");
}

void ActivatorService::setup() {
  _reservoirHasWaterLED.setup();

  for (auto& pumpRelay : _pumpRelays) pumpRelay.setup();
}

void ActivatorService::hook() {
  _reservoirHasWaterLED.toggle(!_stateService.isReservoirEmpty());

  for (uint8_t i = 0; i < Config::NUMBER_OF_PUMPS; i++) {
    bool shouldRun = _stateService.shouldPumpRun(i);
    bool pumpStateChanged = _pumpRelays[i].toggle(shouldRun);
    if (pumpStateChanged) {
      printPumpState(i, shouldRun);

      if (shouldRun) _stateService.setSensorsToRefreshNow();
    }
  }
}