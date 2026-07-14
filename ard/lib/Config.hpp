#pragma once

#include "Arduino.h"

namespace Config {

static constexpr unsigned long BUTTON_DEBOUNCE_MS = 50;
static constexpr unsigned long SOIL_SENSOR_READ_INTERVAL_SEC = 10;
static constexpr unsigned long RESERVOIR_SENSOR_READ_INTERVAL_SEC = 10;
static constexpr unsigned long PUMP_CYCLE_SIZE_SEC[NUMBER_OF_PUMPS] = {
    10,
    10,
    10,
};

static constexpr uint8_t NUMBER_OF_PUMPS = 3;
static constexpr uint8_t NUMBER_OF_SENSORS = 6;

static constexpr uint8_t PIN_BUTTON_STOP_PUMPS = 2;
static constexpr uint8_t PIN_BUTTON_REFRESH_SENSORS = 3;
static constexpr uint8_t PIN_BUTTON_PUMP_1_OVERRIDE = 4;
static constexpr uint8_t PIN_BUTTON_PUMP_2_OVERRIDE = 5;
static constexpr uint8_t PIN_BUTTON_PUMP_3_OVERRIDE = 6;
static constexpr uint8_t PIN_RESERVOIR_HAS_WATER_LED = 13;
static constexpr uint8_t PIN_RELAY_PUMP_1 = 7;
static constexpr uint8_t PIN_RELAY_PUMP_2 = 8;
static constexpr uint8_t PIN_RELAY_PUMP_3 = 9;
static constexpr uint8_t PIN_DIST_ECHO = 12;
static constexpr uint8_t PIN_DIST_TRIG = 11;
static constexpr uint8_t PIN_SOIL_SENSOR_1 = A1;
static constexpr uint8_t PIN_SOIL_SENSOR_2 = A2;
static constexpr uint8_t PIN_SOIL_SENSOR_3 = A3;
static constexpr uint8_t PIN_SOIL_SENSOR_4 = A4;
static constexpr uint8_t PIN_SOIL_SENSOR_5 = A5;
static constexpr uint8_t PIN_SOIL_SENSOR_6 = A6;

static constexpr uint8_t RESERVOIR_EMPTY_CM = 100;

}  // namespace Config
