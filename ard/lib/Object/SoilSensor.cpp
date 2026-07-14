#include "SoilSensor.hpp"

void SoilSensor::setup() { pinMode(_pin, INPUT); }

int SoilSensor::getValueCached() { return _value; }

void SoilSensor::refresh() { _value = analogRead(_pin); }

bool SoilSensor::isBelowTarget() { return _value < _targetValue; }