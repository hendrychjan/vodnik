#include "WaterService.hpp"

void WaterService::setup() {

  // Initialize the armed indicator LED
  armedIndicatorLed.setup();
  armedIndicatorLed.toggleOn();  // By default automatic is armed

  // Initialize pump hw
  for (auto& pump : pumps) {
    pump.setup();
  }
}

void WaterService::hook() {
  if (armingButton.didActivate()) {
    // TODO: Stop any ongoing automations
    if (isPumpActive)
      for (auto& pump : pumps)
        if (pump.isOn()) pump.toggleOff();

    isPumpActive = false;
    isArmed = !isArmed;
    armedIndicatorLed.toggle();

    Serial.print("armed ");
    Serial.println(isArmed ? " 1" : " 0");
  }

  // Check for manual pump activation
  if (!isArmed)
    for (auto& pump : pumps)
      if (pump.toggleButton.didActivate()) {
        // Pump toggled manually
        if (pump.isOn()) { // Turning off
          pump.toggleOff();
          isPumpActive = false;
        } else { // Turning on
          if (isPumpActive) continue; // Only one pump can be active at a time

          pump.toggleOn();
          isPumpActive = true;
        }
      }
}
