#pragma once

#include "Arduino.h"
#include "Const.hpp"

namespace Config {

#pragma region HW definition
static constexpr uint8_t NUMBER_OF_PUMPS = 2;
static constexpr uint8_t NUMBER_OF_SENSORS = 2;
#pragma endregion

#pragma region Intervals
static constexpr unsigned long SOIL_SENSOR_READ_INTERVAL_SEC = 10;
static constexpr unsigned long RESERVOIR_IN_CYCLE_INTERVAL_SEC = 1;
static constexpr unsigned long RESERVOIR_OUT_CYCLE_INTERVAL_SEC = 10;
static constexpr unsigned long PUMP_CYCLE_SIZE_SEC[NUMBER_OF_PUMPS] = {
    10,
    10,
};
#pragma endregion

#pragma region Pins
static constexpr uint8_t PIN_RESERVOIR_HAS_WATER_LED = 13;
static constexpr uint8_t PIN_BUTTON_REFRESH_SENSORS = A6;
static constexpr uint8_t PIN_BUTTON_STOP_PUMPS = A7;

static constexpr uint8_t PIN_MUX_SELECT[Const::MUX_SELECT_SIZE] = {
    A0,
    A1,
    A2,
    A3,
};
static constexpr uint8_t PIN_MUX_DATA = A5;
static constexpr uint8_t PIN_MUX_ENABLE = A4;

static constexpr uint8_t MUX_PIN_BUTTON_PUMP_OVERRIDE[NUMBER_OF_PUMPS] = {
    14,
    15,
};
static constexpr uint8_t MUX_PIN_SOIL_SENSOR[NUMBER_OF_SENSORS] = {
    0,
    1,
};

static constexpr uint8_t PIN_PUMP_RELAY[NUMBER_OF_PUMPS] = {2, 3};

static constexpr uint8_t PIN_DIST_ECHO = 11;
static constexpr uint8_t PIN_DIST_TRIG = 12;
#pragma endregion

static constexpr uint8_t RESERVOIR_EMPTY_CM = 100;

}  // namespace Config
