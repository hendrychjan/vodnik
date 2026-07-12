#include "SoilSensor.hpp"

float SoilSensor::getHumidityPercent(bool print = false) {
  const int value = analogRead(pin);

  humidityPercent = 100.;

  if (print) {
    Serial.print("pot ");
    Serial.print(name);
    Serial.print(" ");
    Serial.print(humidityPercent);
  }
}
