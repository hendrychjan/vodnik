#include "Arduino.h"
#include "StateService.hpp"
#include "ButtonService.hpp"
#include "ActivatorService.hpp"
#include "HumidityService.hpp"
#include "SerialService.hpp"
#include "Reservoir.hpp"

StateService stateService;
SerialService serialService(stateService);
ButtonService buttonService(stateService);
HumidityService humidityService(stateService);
ActivatorService activatorService(stateService);

Reservoir reservoir(12, 11, 40);

void setup() {
  Serial.begin(9600);
  reservoir.setup();

  // serialService.setup();
  // buttonService.setup();
  // humidityService.setup();
  // activatorService.setup();
}

void loop() {
  delay(1000);

  reservoir.refresh();
  
  Serial.println(reservoir.getDistanceCached());

  // serialService.hook();
  // buttonService.hook();
  // humidityService.hook();
  // activatorService.hook();
}
