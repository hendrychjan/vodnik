#include "Button.hpp"

#define DEBOUNCE_MS 50

bool Button::didActivate() {
  static bool initialized = false;
  static int lastRawReadingByPin[NUM_DIGITAL_PINS];
  static int stableStateByPin[NUM_DIGITAL_PINS];
  static unsigned long lastChangeMsByPin[NUM_DIGITAL_PINS];

  if (!initialized) {
    for (uint8_t i = 0; i < NUM_DIGITAL_PINS; ++i) {
      lastRawReadingByPin[i] = HIGH;
      stableStateByPin[i] = HIGH;
      lastChangeMsByPin[i] = 0;
    }
    initialized = true;
  }

  if (_pin >= NUM_DIGITAL_PINS) {
    return false;
  }

  const int reading = digitalRead(_pin);
  const unsigned long now = millis();

  if (reading != lastRawReadingByPin[_pin]) {
    lastChangeMsByPin[_pin] = now;
    lastRawReadingByPin[_pin] = reading;
  }

  if (((now - lastChangeMsByPin[_pin]) >= DEBOUNCE_MS) &&
      (reading != stableStateByPin[_pin])) {
    stableStateByPin[_pin] = reading;

    return stableStateByPin[_pin] == LOW;
  }

  return false;
}
