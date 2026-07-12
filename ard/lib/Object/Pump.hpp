#pragma once

#include "Arduino.h"
#include "Button.hpp"
#include "Activator.hpp"

class Pump {
 public:
  const char* title;
  Button toggleButton;
  Activator relay;

  Pump(const char* title, uint8_t buttonPin, uint8_t relayPin)
      : title(title), toggleButton(buttonPin), relay(relayPin) {}

  void toggleOn();
  void toggleOff();
  void toggle();
  bool isOn();
};
