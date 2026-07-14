#include "SensorService.hpp"

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

void SensorService::setup() {
  for (auto& sensor : _soilSensors) sensor.setup();
}

void SensorService::hook() {
  if (_stateService.shouldReservoirSensorRefresh()) {
    unsigned long distanceCm = _reservoir.getDistanceCm();
    printReservoirDistance(distanceCm);
    _stateService.setReservoirEmpty(distanceCm >= Config::RESERVOIR_EMPTY_CM);
  }

  if (_stateService.shouldSoilSensorsRefresh()) {
    for (uint8_t i = 0; i < Config::NUMBER_OF_SENSORS; i++) {
      int sensorValue = _soilSensors[i].getValue();
      printSoilSensorValue(i, sensorValue);
    }
  }
}