#pragma once

#include "../Config.hpp"
#include "Arduino.h"
#include "IOService.hpp"
#include "SoilSensor.hpp"
#include "StateService.hpp"

class HumidityService : public IOService {
 public:
  HumidityService(StateService& stateService) : _stateService(stateService) {}

  void setup() override;
  void hook() override;

 private:
  StateService& _stateService;
  unsigned long _lastReadMs = -(Config::SENSOR_READ_INTERVAL_SEC * 1000UL);
  SoilSensor _sensors[Config::NUMBER_OF_SENSORS] = {
      SoilSensor(Config::PIN_SOIL_SENSOR_1, Config::SOIL_SENSOR_1_TARGET),
      SoilSensor(Config::PIN_SOIL_SENSOR_2, Config::SOIL_SENSOR_2_TARGET),
      SoilSensor(Config::PIN_SOIL_SENSOR_3, Config::SOIL_SENSOR_3_TARGET),
      SoilSensor(Config::PIN_SOIL_SENSOR_4, Config::SOIL_SENSOR_4_TARGET),
      SoilSensor(Config::PIN_SOIL_SENSOR_5, Config::SOIL_SENSOR_5_TARGET),
      SoilSensor(Config::PIN_SOIL_SENSOR_6, Config::SOIL_SENSOR_6_TARGET),
  };
};
