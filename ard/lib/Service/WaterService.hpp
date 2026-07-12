#pragma once

#include "Button.hpp"
#include "IOService.hpp"
#include "Pump.hpp"
#include "SoilSensor.hpp"

class WaterService : public IOService {
 public:
  void hook() override;

 private:
  Button armingButton = Button(2);
  Relay armedIndicatorLed = Relay(13);
  Pump pumps[3] = {
      Pump("kukurice_1", 3, 7),
      Pump("dyne", 4, 8),
      Pump("kukurice_2", 5, 9),
  };

  SoilSensor sensors[6] = {
      SoilSensor("kukurice_1", A1), SoilSensor("kukurice_2", A2),
      SoilSensor("dyne", A3),       SoilSensor("kukurice_3", A4),
      SoilSensor("kukurice_4", A5), SoilSensor("stromecek", A6),
  };
};
