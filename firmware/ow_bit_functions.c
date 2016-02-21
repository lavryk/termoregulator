#include <util/delay.h>
#include <avr/interrupt.h>
#include "ow_bit_functions.h"

void ow_init(uint8_t pins) {
  OW_RELEASE_BUS(pins);
  _delay_us(OW_DELAY_H);
}

void ow_write_bit1(uint8_t pins) {

  uint8_t int_state;

  int_state = __save_interrupt();
  __disable_interrupt();

  OW_PULL_BUS_LOW(pins);
  _delay_us(OW_DELAY_A);

  OW_RELEASE_BUS(pins);
  _delay_us(OW_DELAY_B);

  __restore_interrupt(int_state);
}

void ow_write_bit0(uint8_t pins) {
  uint8_t int_state;

  int_state = __save_interrupt();
  __disable_interrupt();

  OW_PULL_BUS_LOW(pins);
  _delay_us(OW_DELAY_C);

  OW_RELEASE_BUS(pins);
  _delay_us(OW_DELAY_D);

  __restore_interrupt(int_state);
}

uint8_t ow_read_bit(uint8_t pins) {
  uint8_t int_state;
  uint8_t bits_read;

  int_state = __save_interrupt();
  __disable_interrupt();

  OW_PULL_BUS_LOW(pins);
  _delay_us(OW_DELAY_A);

  OW_RELEASE_BUS(pins);
  _delay_us(OW_DELAY_E);

  bits_read = OW_PIN & pins;
  _delay_us(OW_DELAY_F);
  __restore_interrupt(int_state);

  return bits_read;
}

uint8_t ow_detect_presence(uint8_t pins) {
  uint8_t int_state;
  uint8_t presence_detected;

  int_state = __save_interrupt();
  __disable_interrupt();

  OW_PULL_BUS_LOW(pins);
  _delay_us(OW_DELAY_H);

  OW_RELEASE_BUS(pins);
  _delay_us(OW_DELAY_I);

  presence_detected = ((~OW_PIN) & pins);
  _delay_us(OW_DELAY_J);

  __restore_interrupt(int_state);

  return presence_detected;
}
