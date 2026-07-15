#include "StateService.hpp"

#include <limits.h>

void StateService::setup() { _lastHookMs = millis(); }

void StateService::hook() {
  unsigned long nowMs = millis();
  unsigned long elapsedMs = nowMs - _lastHookMs;

  if (elapsedMs == 0) return;

  _lastHookMs = nowMs;

  _subtractElapsed(_reservoirTimeToRefreshMs, elapsedMs);
  _subtractElapsed(_soilSensorsTimeToRefreshMs, elapsedMs);

  if (_activePumpIndex >= 0) {
    _subtractElapsed(_pumpsTimeQueuedMs[_activePumpIndex], elapsedMs);

    if (_pumpsTimeQueuedMs[_activePumpIndex] == 0) {
      _activePumpIndex = -1;
    }
  }

  _promoteHighestPriorityPumpIfIdle();
}

void StateService::_subtractElapsed(unsigned long& value,
                                    unsigned long elapsedMs) {
  if (value <= elapsedMs) {
    value = 0;
    return;
  }

  value -= elapsedMs;
}

const bool StateService::isReservoirEmpty() { return _isReservoirEmpty; }

const void StateService::setReservoirEmpty(bool isEmpty) {
  if (isEmpty == _isReservoirEmpty) return;  // No state change

  if (isEmpty) clearAllPumpsTimeQueued();

  _isReservoirEmpty = isEmpty;
}

void StateService::clearAllPumpsTimeQueued() {
  for (uint8_t i = 0; i < Config::NUMBER_OF_PUMPS; i++) {
    _pumpsTimeQueuedMs[i] = 0;
  }

  _activePumpIndex = -1;
}

void StateService::setSensorsToRefreshNow() {
  _reservoirTimeToRefreshMs = 0;
  _soilSensorsTimeToRefreshMs = 0;
}

bool StateService::shouldReservoirSensorRefresh() {
  bool refreshNow = _reservoirTimeToRefreshMs == 0;

  if (refreshNow) {
    unsigned long timeToNextRefreshSec =
        (shouldAnyPumpRun())
            ? Config::RESERVOIR_SENSOR_READ_INTERVAL_SEC_DURING_CYCLE
            : Config::RESERVOIR_SENSOR_READ_INTERVAL_SEC_OUTSIDE_CYCLE;
    _reservoirTimeToRefreshMs = timeToNextRefreshSec * 1000;
  }

  return refreshNow;
}

bool StateService::shouldSoilSensorsRefresh() {
  bool refreshNow = _soilSensorsTimeToRefreshMs == 0;

  if (refreshNow)
    _soilSensorsTimeToRefreshMs = Config::SOIL_SENSOR_READ_INTERVAL_SEC * 1000;

  return refreshNow;
}

const bool StateService::shouldAnyPumpRun() {
  return _activePumpIndex >= 0;
}

const bool StateService::shouldPumpRun(uint8_t index) {
  if (index >= Config::NUMBER_OF_PUMPS) {
    Serial.print("err StateService::shouldPumpRun Pump index ");
    Serial.print(index);
    Serial.println(" is out of bounds");

    return false;
  }

  return (_activePumpIndex == static_cast<int8_t>(index)) &&
         (_pumpsTimeQueuedMs[index] > 0);
}

void StateService::queuePumpCycle(uint8_t index) {
  unsigned long timeToAddMs = Config::PUMP_CYCLE_SIZE_SEC[index] * 1000;

  _queuePumpTime(index, timeToAddMs);
}

void StateService::queuePumpInfiniteCycle(uint8_t index) {
  _queuePumpTime(index, ULONG_MAX);
}

void StateService::_queuePumpTime(uint8_t index, unsigned long timeToAddMs) {
  if (index >= Config::NUMBER_OF_PUMPS) {
    Serial.print("err StateService::_queuePumpTime Pump index ");
    Serial.print(index);
    Serial.println(" is out of bounds");

    return;
  }

  if (_isReservoirEmpty) {
    Serial.println(
        "err StateService::_queuePumpTime Unable to queue pump time, "
        "reservoir is empty.");
    return;
  }

  if (ULONG_MAX - _pumpsTimeQueuedMs[index] < timeToAddMs) {
    _pumpsTimeQueuedMs[index] = ULONG_MAX;
  } else {
    _pumpsTimeQueuedMs[index] += timeToAddMs;
  }

  _promoteHighestPriorityPumpIfIdle();
}

void StateService::clearPumpTimeQueued(uint8_t index) {
  if (index >= Config::NUMBER_OF_PUMPS) {
    Serial.print("err StateService::clearPumpTimeQueued Pump index ");
    Serial.print(index);
    Serial.println(" is out of bounds");

    return;
  }

  _pumpsTimeQueuedMs[index] = 0;

  if (_activePumpIndex == static_cast<int8_t>(index)) {
    _activePumpIndex = -1;
  }

  _promoteHighestPriorityPumpIfIdle();
}

void StateService::_promoteHighestPriorityPumpIfIdle() {
  if (_activePumpIndex >= 0) return;
  if (_isReservoirEmpty) return;

  for (uint8_t i = 0; i < Config::NUMBER_OF_PUMPS; i++) {
    if (_pumpsTimeQueuedMs[i] == 0) continue;

    _activePumpIndex = static_cast<int8_t>(i);
    return;
  }
}
