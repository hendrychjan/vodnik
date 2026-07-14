#pragma once

#include "../Config.hpp"
#include "Arduino.h"
#include "IOService.hpp"
#include "SoilSensor.hpp"
#include "Reservoir.hpp"
#include "StateService.hpp"

class SensorService : public IOService {
 public:
  SensorService(StateService& stateService) : _stateService(stateService) {}

  void setup() override;
  void hook() override;

 private:
  StateService& _stateService;
  Reservoir _reservoir{Config::PIN_DIST_ECHO, Config::PIN_DIST_TRIG};
  SoilSensor _soilSensors[Config::NUMBER_OF_SENSORS] = {
      SoilSensor(Config::PIN_SOIL_SENSOR_1),
      SoilSensor(Config::PIN_SOIL_SENSOR_2),
      SoilSensor(Config::PIN_SOIL_SENSOR_3),
      SoilSensor(Config::PIN_SOIL_SENSOR_4),
      SoilSensor(Config::PIN_SOIL_SENSOR_5),
      SoilSensor(Config::PIN_SOIL_SENSOR_6),
  };
};
