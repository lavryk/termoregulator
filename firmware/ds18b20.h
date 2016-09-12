// http://www.atmel.com/images/doc2579.pdf
//http://hardisoft.ru/hard/samodelkin/poisk-ustrojstv-na-shine-1-wire-na-assemblere-dlya-mikrokontrollerov-avr-firmy-atmel/

#ifndef _DS18B20_H_
#define _DS18B20_H_

#include <avr/io.h>
#include <util/delay.h>
#include "ow_rom_functions.h"

#define MAX_DEVICES       0x02

#define DS18B20_CONVERT_T 0x44

#define BUS OW_PIN_0

#define SEARCH_SENSORS 0x00
#define SENSORS_FOUND  0xff

#define READ_SUCCESSFUL   0x00
#define READ_CRC_ERROR    0x01

#define DS18B20_READ_SCRATCHPAD          0xbe

OW_device all_devices[MAX_DEVICES];

void initDS18B20();

uint8_t ds18b20_read_temperature(uint8_t index, int32_t *temperature);

uint8_t ds18b20_search_devices();

#endif
