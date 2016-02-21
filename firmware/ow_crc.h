#ifndef _OW_CRC_H_
#define _OW_CRC_H_

#include <avr/io.h>

#define   OW_CRC_OK     0x00
#define   OW_CRC_ERROR  0x01

uint8_t ow_compute_crc8(uint8_t data, uint8_t seed);
uint8_t ow_check_rom_crc(uint8_t *rom_value);
uint8_t ow_check_scratch_pad_crc(uint8_t *scratchpad);

#endif