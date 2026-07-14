#include "Reservoir.hpp"

void Reservoir::setup() {
  pinMode(_triggerPin, OUTPUT);
  pinMode(_echoPin, INPUT);
  digitalWrite(_triggerPin, LOW);
}

unsigned long Reservoir::getDistanceCm() {
  digitalWrite(_triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(_triggerPin, HIGH);
  delayMicroseconds(30);
  digitalWrite(_triggerPin, LOW);

  const unsigned long durationUs = pulseIn(_echoPin, HIGH, 30000UL);

  return (durationUs / 58UL);
}
