#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <avr/io.h>
#include <avr/pgmspace.h>

#define DS_PORT PORTC
#define DS_PIN 1
#define ST_CP_PORT PORTC
#define ST_CP_PIN 2
#define SH_CP_PORT PORTC
#define SH_CP_PIN 3

#define DS_low() DS_PORT&=~_BV(DS_PIN)
#define DS_high() DS_PORT|=_BV(DS_PIN)
#define ST_CP_low() ST_CP_PORT&=~_BV(ST_CP_PIN)
#define ST_CP_high() ST_CP_PORT|=_BV(ST_CP_PIN)
#define SH_CP_low() SH_CP_PORT&=~_BV(SH_CP_PIN)
#define SH_CP_high() SH_CP_PORT|=_BV(SH_CP_PIN)

#define ERR0 0b0110000100000011
#define ERR1 0b0110000110011111
#define ERR2 0b0110000100100101
#define ERR3 0b0110000100001101

#define MINUS 0b11111101

static const uint8_t DIGITS[] PROGMEM = {
  0b00000011, // 0
  0b10011111, // 1
  0b00100101, // 2
  0b00001101, // 3
  0b10011001, // 4
  0b01001001, // 5
  0b01000001, // 6
  0b00011111, // 7
  0b00000001, // 8
  0b00001001  // 9
};

void init_led();
void print_num(char number, uint8_t index);
void print_err(uint16_t code, uint8_t index);
void print_with_index(uint16_t code, uint8_t index);
void print_bits(uint16_t number);

#endif