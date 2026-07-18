#include "SoilSensor.hpp"

void SoilSensor::setup() { pinMode(_pin, INPUT); }

int SoilSensor::getValue() { 
  analogRead(_pin); // Dummy read for values to settle
  return analogRead(_pin); 
}
