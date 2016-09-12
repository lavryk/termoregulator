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

#define ERR0 0x6103 // Search device crc error
#define ERR1 0x619F // Read temperature crc error
#define ERR2 0x6125 // Temperature > 99
#define ERR3 0x610D // Temperature < -9

//#define MENU_P0   0x3102
#define MENU_P1   0x309F
#define MENU_P0UP 0x8330
#define MENU_P0DW 0x8512
#define MENU_P1UP 0x8231
#define MENU_P1DW 0x8413

#define MINUS 0xFD

#define print_err print_with_index

static const uint8_t DIGITS[] PROGMEM = {0x03, 0x9F, 0x25, 0x0D, 0x99, 0x49, 0x41, 0x1F, 0x01, 0x09};

void initLED();
void print_num(int16_t number, uint8_t index);

void print_with_index(uint16_t code, uint8_t index);

void print_bits(uint16_t number);

#endif