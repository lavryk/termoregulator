#ifndef _OW_ROM_FUNCTIONS_H_
#define _OW_ROM_FUNCTIONS_H_

// Used for memcpy
#include <string.h>
#include <avr/io.h>
#include "ow_bit_functions.h"

typedef struct {
    uint8_t id[8];    //!< The 64 bit identifier.
} OW_device;

#define     OW_PIN_0       0x01
#define     OW_PIN_1       0x02
#define     OW_PIN_2       0x04
#define     OW_PIN_3       0x08
#define     OW_PIN_4       0x10
#define     OW_PIN_5       0x20
#define     OW_PIN_6       0x40
#define     OW_PIN_7       0x80

#define SEARCH_SUCCESSFUL     0x00
#define SEARCH_CRC_ERROR      0x01
#define SEARCH_ERROR          0xff

#define OW_ROM_SEARCH_FINISHED     0x00

#define OW_ROM_READ    0x33
#define OW_ROM_SKIP    0xcc
#define OW_ROM_MATCH   0x55
#define OW_ROM_SEARCH  0xf0

void    ow_send_byte(uint8_t data, uint8_t pin);
uint8_t ow_receive_byte(uint8_t pin);
void    ow_skip_rom(uint8_t pin);
void    ow_read_rom(uint8_t *rom_value, uint8_t pin);
void    ow_match_rom(uint8_t *rom_value, uint8_t pin);
uint8_t ow_search_rom(uint8_t *bit_pattern, uint8_t last_deviation, uint8_t pins);
uint8_t ow_search_devices(OW_device *devices, uint8_t num_devices, uint8_t pin, uint8_t *num);


#endif