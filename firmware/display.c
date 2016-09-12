#include <stdlib.h>
#include "display.h"

void initLED() {
  DDRC |= _BV(DS_PIN) | _BV(ST_CP_PIN) | _BV(SH_CP_PIN);
  PORTC |= 0x0;
}

void print_num(int16_t number, uint8_t index) {
  if(number > 99) {
    print_err(ERR2, index);
    return;
  }

  if(number < -9) {
    print_err(ERR3, index);
    return;
  }

  uint8_t num0;
  uint8_t num1;
  if(number < 0) {
    num0 = pgm_read_byte(&DIGITS[abs(number) % 10]);
    num1 = MINUS;
  } else {
    num0 = pgm_read_byte(&DIGITS[number % 10]);
    num1 = pgm_read_byte(&DIGITS[number / 10]);
  }

  print_with_index(((num1 << 8) | num0), index);
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