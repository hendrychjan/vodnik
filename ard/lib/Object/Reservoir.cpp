#include "Reservoir.hpp"

void Reservoir::setup() {
  pinMode(_triggerPin, OUTPUT);
  pinMode(_echoPin, INPUT);
  digitalWrite(_triggerPin, LOW);
  _distanceCm = 0;
  refresh();
}

void Reservoir::refresh() {
  digitalWrite(_triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(_triggerPin, HIGH);
  delayMicroseconds(30);
  digitalWrite(_triggerPin, LOW);

  const unsigned long durationUs = pulseIn(_echoPin, HIGH, 30000UL);

  _distanceCm = static_cast<int>(durationUs / 58UL);
}

int Reservoir::getDistanceCached() { return _distanceCm; }

bool Reservoir::isEmpty() { return _distanceCm >= _emptyDistanceCm; }