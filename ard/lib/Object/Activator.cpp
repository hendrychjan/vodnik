#include "Activator.hpp"

void Activator::setup() {
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, _isOn ? HIGH : LOW);
}

bool Activator::toggle(bool isActive) {
  if (isActive == _isOn) return false;

  _isOn = isActive;
  digitalWrite(_pin, isActive ? HIGH : LOW);
  return true;
}

bool Activator::isOn() { return _isOn; }