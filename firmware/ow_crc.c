#include "ow_crc.h"

uint8_t ow_compute_crc8(uint8_t data, uint8_t seed) {
  uint8_t bits_left;
  uint8_t temp;

  for(bits_left = 8; bits_left > 0; bits_left--) {
    temp = ((seed ^ data) & 0x01);
    if(temp == 0) {
      seed >>= 1;
    } else {
      seed ^= 0x18;
      seed >>= 1;
      seed |= 0x80;
    }
    data >>= 1;
  }

  return seed;
}

uint8_t ow_check_rom_crc(uint8_t *rom_value) {
  uint8_t i;
  uint8_t crc8 = 0;

  for(i = 0; i < 7; i++) {
    crc8 = ow_compute_crc8(*rom_value, crc8);
    rom_value++;
  }
  if(crc8 == (*rom_value)) {
    return OW_CRC_OK;
  }
  return OW_CRC_ERROR;
}

uint8_t ow_check_scratch_pad_crc(uint8_t *scratchpad) {
  uint8_t i;
  uint8_t crc8 = 0;

  for(i = 0; i < 8; i++) {
    crc8 = ow_compute_crc8(*scratchpad, crc8);
    scratchpad++;
  }
  if(crc8 == (*scratchpad)) {
    return OW_CRC_OK;
  }
  return OW_CRC_ERROR;
}