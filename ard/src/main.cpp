#include "Arduino.h"

#include "StateService.hpp"
#include "SerialService.hpp"

void setup() {
  Serial.begin(9600);
}

void loop() {
  for (auto* ioService : ioServices) ioService->hook();
}
