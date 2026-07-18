#include "Arduino.h"
#include "StateService.hpp"
#include "SerialService.hpp"
#include "InputService.hpp"
#include "OutputService.hpp"

StateService stateService;
SerialService serialService(stateService);
InputService inputService(stateService);
OutputService outputService(stateService);


void setup() {
  Serial.begin(9600);

  stateService.setup();
  serialService.setup();
  inputService.setup();
  outputService.setup();
}

void loop() {
  stateService.hook();
  serialService.hook();
  inputService.hook();
  outputService.hook();
}
