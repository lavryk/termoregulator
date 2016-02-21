#include "display.h"

void init_led() {
  DDRC |= _BV(DS_PIN) | _BV(ST_CP_PIN) | _BV(SH_CP_PIN);
  PORTC |= 0b00000000;
}

void print_num(uint8_t number, uint8_t index) {
  uint16_t code = ((pgm_read_byte(&DIGITS[number / 10]) << 8) | pgm_read_byte(&DIGITS[number % 10]));
  print_with_index(code, index);
}

void print_err(uint16_t code, uint8_t index) {
  print_with_index(pgm_read_byte(&ERR[code]), index);
}

void print_with_index(uint16_t code, uint8_t index) {
  print_bits(code & ~_BV(index * 8));
}

void print_bits(uint16_t bits) {
  SH_CP_low();
  ST_CP_low();
  int i;
  for(i = 0; i < 16; i++) {
    if(bits & _BV(i))
      DS_high();
    else
      DS_low();

    SH_CP_high();
    SH_CP_low();
  }
  ST_CP_high();
}