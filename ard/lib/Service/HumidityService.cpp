#include "HumidityService.hpp"

void printSensorValue(uint8_t index, int value) {
  Serial.print("soil ");
  Serial.print(index);
  Serial.print(" ");
  Serial.println(value);
}

void HumidityService::setup() {
  for (auto& sensor : _sensors) sensor.setup();
}

void HumidityService::hook() {
  const unsigned long now = millis();
  if (now - _lastReadMs < Config::SENSOR_READ_INTERVAL_SEC * 1000UL) return;
  _lastReadMs = now;

  for (uint8_t i = 0; i < Config::NUMBER_OF_SENSORS; i++) {
    if (_sensors[i].refresh()) {
      _stateService.pumpsCycleQueued[i] = true;
    }

    printSensorValue(i, _sensors[i].getValueCached());
  }
}