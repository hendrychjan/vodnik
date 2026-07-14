#include "Button.hpp"

void Button::setup() { pinMode(_pin, INPUT_PULLUP); }

bool Button::didActivate() {
  const bool isPressed = digitalRead(_pin) == LOW;

  if (isPressed != _lastRawState) {
    _lastDebounceMs = millis();
    _lastRawState = isPressed;
  }

  if (millis() - _lastDebounceMs < Config::BUTTON_DEBOUNCE_MS) {
    return false;
  }

  const bool activated = isPressed && !_wasPressed;
  _wasPressed = isPressed;

  return activated;
}