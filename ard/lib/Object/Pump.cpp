#include "Pump.hpp"

void Pump::toggleOn() {
  if (relay.isOn()) return;

  relay.toggleOn();

  Serial.print("pump ");
  Serial.print(title);
  Serial.println(" 1");
}

void Pump::toggleOff() {
  if (!relay.isOn()) return;

  relay.toggleOff();

  Serial.print("pump ");
  Serial.print(title);
  Serial.println(" 0");
}

void Pump::toggle() {
  if (relay.isOn())
    toggleOff();
  else
    toggleOn();
}

bool Pump::isOn() {
  return relay.isOn();
}
