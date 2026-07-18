#include "Mux.hpp"

void Mux::setup() {
  // Set the enable pin mode and initially disable MUX
  pinMode(_enablePin, OUTPUT);
  digitalWrite(_enablePin, HIGH);
  
  // Set pinMode for mux select pins
  for (uint8_t i = 0; i < Const::MUX_SELECT_SIZE; i++)
  pinMode(_selectPins[i], OUTPUT);
  
  // Set the pinMode for mux data pin
  _selectDevice(0);
  pinMode(_dataPin, INPUT);
}

bool Mux::_selectDevice(uint8_t index) {
  if (index >= Const::MUX_CHANNEL_SIZE) {
    Serial.print("err Mux::selectDevice Channel index ");
    Serial.print(index);
    Serial.println(" is out of bounds");

    return false;
  }
  
  // Disable mux before switching channels
  digitalWrite(_enablePin, HIGH);

  for (uint8_t i = 0; i < Const::MUX_SELECT_SIZE; i++) {
    digitalWrite(_selectPins[i], bitRead(index, i) ? HIGH : LOW);
  }

  // Re-enable mux after switching channels
  digitalWrite(_enablePin, LOW);
  delayMicroseconds(5);
  
  return true; // Channels switch succesfully
}

int Mux::getSoilValue(uint8_t pin) {
  if (!_selectDevice(pin)) return -1;

  return _soilSensorDummy.getValue();
}

bool Mux::didButtonActivate(uint8_t index) {
  if (!_selectDevice(index)) return false;

  const bool isPressed = _buttonDummy.isPressed();

  if (isPressed != _buttonLastRawState[index]) {
    _buttonLastDebounceMs[index] = millis();
    _buttonLastRawState[index] = isPressed;
  }

  if (millis() - _buttonLastDebounceMs[index] < Const::BUTTON_DEBOUNCE_MS) {
    return false;
  }

  if (isPressed == _buttonWasPressed[index]) {
    return false;
  }

  _buttonWasPressed[index] = isPressed;

  return isPressed;
}
