#include "SoilSensor.hpp"

void SoilSensor::setup() { pinMode(_pin, INPUT); }

int SoilSensor::getValue() { return analogRead(_pin); }
