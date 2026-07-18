#include "Button.hpp"

void Button::setup() { pinMode(_pin, INPUT); }

bool Button::isPressed() {
  // External resistor wiring only: analog read is the raw signal source.
  return analogRead(_pin) >= Const::BUTTON_ANALOG_PRESS_THRESHOLD;
}

bool Button::didActivate() {
  const bool pressed = isPressed();

  if (pressed != _lastRawState) {
    _lastDebounceMs = millis();
    _lastRawState = pressed;
  }

  if (millis() - _lastDebounceMs < Const::BUTTON_DEBOUNCE_MS) {
    return false;
  }

  if (pressed == _wasPressed) {
    return false;
  }

  _wasPressed = pressed;

  return pressed;
}