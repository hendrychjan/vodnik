#pragma once

#include "Arduino.h"

namespace Config {

static constexpr long SENSOR_READ_INTERVAL_SEC = 10;
static constexpr unsigned long BUTTON_DEBOUNCE_MS = 50;

static constexpr uint8_t NUMBER_OF_PUMPS = 3;
static constexpr uint8_t NUMBER_OF_SENSORS = 6;

static constexpr uint8_t PIN_BUTTON_MODE = 2;
static constexpr uint8_t PIN_BUTTON_PUMP_1_OVERRIDE = 3;
static constexpr uint8_t PIN_BUTTON_PUMP_2_OVERRIDE = 4;
static constexpr uint8_t PIN_BUTTON_PUMP_3_OVERRIDE = 5;
static constexpr uint8_t PIN_AUTOMATIC_LED = 13;
static constexpr uint8_t PIN_RELAY_PUMP_1 = 7;
static constexpr uint8_t PIN_RELAY_PUMP_2 = 8;
static constexpr uint8_t PIN_RELAY_PUMP_3 = 9;
static constexpr uint8_t PIN_SOIL_SENSOR_1 = A1;
static constexpr uint8_t PIN_SOIL_SENSOR_2 = A2;
static constexpr uint8_t PIN_SOIL_SENSOR_3 = A3;
static constexpr uint8_t PIN_SOIL_SENSOR_4 = A4;
static constexpr uint8_t PIN_SOIL_SENSOR_5 = A5;
static constexpr uint8_t PIN_SOIL_SENSOR_6 = A6;

static constexpr uint8_t SOIL_SENSOR_1_TARGET = 500;
static constexpr uint8_t SOIL_SENSOR_2_TARGET = 500;
static constexpr uint8_t SOIL_SENSOR_3_TARGET = 500;
static constexpr uint8_t SOIL_SENSOR_4_TARGET = 500;
static constexpr uint8_t SOIL_SENSOR_5_TARGET = 500;
static constexpr uint8_t SOIL_SENSOR_6_TARGET = 500;

}  // namespace Config
