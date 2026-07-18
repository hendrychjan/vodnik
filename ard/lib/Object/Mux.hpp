#pragma once

#include "../Config.hpp"
#include "../Const.hpp"
#include "Arduino.h"
#include "Button.hpp"
#include "IOObject.hpp"
#include "SoilSensor.hpp"

class Mux : public IOObject {
 public:
  Mux(const uint8_t (&selectPins)[Const::MUX_SELECT_SIZE], uint8_t dataPin,
      uint8_t enablePin)
      : _selectPins(selectPins), _dataPin(dataPin), _enablePin(enablePin) {}

  void setup() override;

  int getSoilValue(uint8_t index);
  bool didButtonActivate(uint8_t index);

 private:
  const uint8_t (&_selectPins)[Const::MUX_SELECT_SIZE];
  uint8_t _dataPin;
  uint8_t _enablePin;

  SoilSensor _soilSensorDummy{_dataPin};
  Button _buttonDummy{_dataPin};

  // Muxed buttons keep their own per-channel debounce state because the dummy
  // Button object only provides the raw read, not channel-specific history.
  bool _buttonLastRawState[Const::MUX_CHANNEL_SIZE] = {};
  bool _buttonWasPressed[Const::MUX_CHANNEL_SIZE] = {};
  unsigned long _buttonLastDebounceMs[Const::MUX_CHANNEL_SIZE] = {};

  bool _selectDevice(uint8_t index);
};