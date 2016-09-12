#ifndef _RELAY_H_
#define _RELAY_H_

#include <avr/io.h>
#include <avr/eeprom.h>

/*
 * Cooler 0 B0
 * Cooler 1 B1
 * Heater 0 B2
 * Heater 1 B3
 */

#define DISABLE_COOLER(index) \
          DDRB &= ~_BV(index); \
          PORTB &= ~_BV(index);

#define DISABLE_HEATER(index) \
          DDRB &= ~_BV(index + 2); \
          PORTB &= ~_BV(index + 2);

#define ENABLE_COOLER(index) \
          DISABLE_HEATER(index); \
          DDRB |= _BV(index); \
          PORTB |= _BV(index);

#define ENABLE_HEATER(index) \
          DISABLE_COOLER(index); \
          DDRB |= _BV(index + 2); \
          PORTB |= _BV(index + 2);

void adjustTemperature(int32_t temperature, uint8_t index);
void turnOffRelays();

#endif

