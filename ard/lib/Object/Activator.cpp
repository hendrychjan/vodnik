#include "Activator.hpp"

bool Activator::isOn() { return _isOn; }

void Activator::toggleOn() {
  if (_isOn) return;

  digitalWrite(_pin, HIGH);
  _isOn = true;
}

void Activator::toggleOff() {
  if (!_isOn) return;

  digitalWrite(_pin, LOW);
  _isOn = false;
}
