#include "Reservoir.hpp"

namespace {
constexpr unsigned long kInvalidDistanceCm = 400;
constexpr unsigned long kMaxPairDifferenceCm = 10;
constexpr uint8_t kMaxAttempts = 6;
constexpr unsigned long kInterSampleDelayMs = 60;
}  // namespace

void Reservoir::setup() {
  pinMode(_triggerPin, OUTPUT);
  pinMode(_echoPin, INPUT);
  digitalWrite(_triggerPin, LOW);
}

unsigned long Reservoir::getDistanceCm() {
  unsigned long lastValidDistance = kInvalidDistanceCm;

  for (uint8_t attempt = 0; attempt < kMaxAttempts; ++attempt) {
    const unsigned long distance1 = _getDistanceOnePulseCm();
    delay(kInterSampleDelayMs);
    const unsigned long distance2 = _getDistanceOnePulseCm();

    if (distance1 == kInvalidDistanceCm || distance2 == kInvalidDistanceCm) {
      if (distance1 != kInvalidDistanceCm) lastValidDistance = distance1;
      if (distance2 != kInvalidDistanceCm) lastValidDistance = distance2;
      continue;
    }

    const unsigned long difference =
        (distance1 >= distance2) ? (distance1 - distance2)
                                 : (distance2 - distance1);

    if (difference <= kMaxPairDifferenceCm) {
      return (distance1 + distance2) / 2UL;
    }

    lastValidDistance = distance2;
  }

  return lastValidDistance;
}

unsigned long Reservoir::_getDistanceOnePulseCm() {
  digitalWrite(_triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(_triggerPin, HIGH);
  delayMicroseconds(30);
  digitalWrite(_triggerPin, LOW);

  const unsigned long durationUs = pulseIn(_echoPin, HIGH, 30000UL);

  unsigned long distance = (durationUs / 58UL);

  return (distance == 0) ? kInvalidDistanceCm : distance;
}
