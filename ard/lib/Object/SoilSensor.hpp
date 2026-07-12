#pragma once

#include "Arduino.h"

class SoilSensor {
 public:
  SoilSensor(const char* name, uint8_t pin) : pin(pin), name(name) {
    pinMode(pin, INPUT);
  }

  float getHumidityPercent(bool print);

 private:
  const char* name;
  float humidityPercent = 100.;
  uint8_t pin;
};
