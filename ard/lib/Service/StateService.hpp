#pragma once

#include "../Config.hpp"
#include "Arduino.h"
#include "IOService.hpp"

class StateService : public IOService {
 public:
  void setup() override;
  void hook() override;

  const bool isReservoirEmpty();
  const void setReservoirEmpty(bool isEmpty);

  void setSensorsToRefreshNow();
  bool shouldReservoirSensorRefresh();
  bool shouldSoilSensorsRefresh();

  const bool shouldAnyPumpRun();
  void clearAllPumpsTimeQueued();
  void clearPumpTimeQueued(uint8_t index);
  const bool shouldPumpRun(uint8_t index);
  void queuePumpCycle(uint8_t index);
  void queuePumpInfiniteCycle(uint8_t index);

 private:
  void _subtractElapsed(unsigned long& value, unsigned long elapsedMs);

  void _queuePumpTime(uint8_t index, unsigned long time);
  void _promoteHighestPriorityPumpIfIdle();

  bool _isReservoirEmpty = false;
  unsigned long _lastHookMs = 0;

  unsigned long _reservoirTimeToRefreshMs =
      Config::RESERVOIR_OUT_CYCLE_INTERVAL_SEC * 1000;
  unsigned long _soilSensorsTimeToRefreshMs =
      Config::SOIL_SENSOR_READ_INTERVAL_SEC * 1000;

  unsigned long _pumpsTimeQueuedMs[Config::NUMBER_OF_PUMPS] = {
      0,
      0,
  };

  int8_t _activePumpIndex = -1;
};
