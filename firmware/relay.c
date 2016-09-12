#include "relay.h"

int32_t maxTemperatureFor(uint8_t index) {
//TODO: Get from eeprom
  return 7;
}

int32_t minTemperatureFor(uint8_t index) {
  return 4;
}

void adjustTemperature(int32_t temperature, uint8_t index) {

  if(temperature > maxTemperatureFor(index)) {
    ENABLE_COOLER(index);
  } else if(temperature < minTemperatureFor(index)) {
    ENABLE_HEATER(index);
  } else {
    DISABLE_COOLER(index);
    DISABLE_HEATER(index)
  }
}

void turnOffRelays() {
  DISABLE_COOLER(0);
  DISABLE_COOLER(1);
  DISABLE_HEATER(0);
  DISABLE_HEATER(1);
}