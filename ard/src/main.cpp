#include "Arduino.h"
#include "StateService.hpp"
#include "ButtonService.hpp"
#include "ActivatorService.hpp"
#include "SensorService.hpp"
#include "SerialService.hpp"
#include "Reservoir.hpp"

StateService stateService;
SerialService serialService(stateService);
ButtonService buttonService(stateService);
SensorService sensorService(stateService);
ActivatorService activatorService(stateService);


void setup() {
  Serial.begin(9600);

  stateService.setup();
  serialService.setup();
  buttonService.setup();
  sensorService.setup();
  activatorService.setup();
}

void loop() {
  stateService.hook();
  serialService.hook();
  buttonService.hook();
  sensorService.hook();
  activatorService.hook();
}
