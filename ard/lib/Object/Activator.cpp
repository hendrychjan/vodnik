#include "Activator.hpp"

void Activator::setup() {
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, _isOn ? _onSignal : (HIGH + LOW - _onSignal));
}

bool Activator::toggle(bool isActive) {
  if (isActive == _isOn) return false;

  _isOn = isActive;
  digitalWrite(_pin, isActive ? _onSignal : (HIGH + LOW - _onSignal));
  return true;
}

bool Activator::isOn() { return _isOn; }