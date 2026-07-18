#include "InputService.hpp"

void printSoilSensorValue(uint8_t index, int value) {
  Serial.print("soil ");
  Serial.print(index);
  Serial.print(" ");
  Serial.println(value);
}

void printReservoirDistance(unsigned long distanceCm) {
  Serial.print("reservoir ");
  Serial.println(distanceCm);
}

void InputService::setup() {
  _mux.setup();
  _reservoir.setup();
  _stopAllPumpsButton.setup();
  _refreshSensorsButton.setup();
}

void InputService::hook() {
  // Check stop button
  if (_stopAllPumpsButton.didActivate()) {
    _stateService.clearAllPumpsTimeQueued();
  }

  // Check refresh button
  if (_refreshSensorsButton.didActivate()) {
    _stateService.setSensorsToRefreshNow();
  }

  // Check pump override buttons
  for (uint8_t i = 0; i < Config::NUMBER_OF_PUMPS; i++) {
    if (_mux.didButtonActivate(Config::MUX_PIN_BUTTON_PUMP_OVERRIDE[i])) {
      if (_stateService.shouldPumpRun(i))
        _stateService.clearPumpTimeQueued(i);
      else
        _stateService.queuePumpInfiniteCycle(i);
    }
  }

  // Read soils sensors if this is refresh loop
  if (_stateService.shouldSoilSensorsRefresh()) {
    for (uint8_t i = 0; i < Config::NUMBER_OF_SENSORS; i++) {
      int sensorValue = _mux.getSoilValue(Config::MUX_PIN_SOIL_SENSOR[i]);
      printSoilSensorValue(i, sensorValue);
    }
  }

  // Read reservoir sensor if this is refresh loop
  if (_stateService.shouldReservoirSensorRefresh()) {
    unsigned long distanceCm = _reservoir.getDistanceCm();
    printReservoirDistance(distanceCm);
    _stateService.setReservoirEmpty(distanceCm >= Config::RESERVOIR_EMPTY_CM);
  }
}