#ifndef _OW_BIT_FUNCTIONS_H_
#define _OW_BIT_FUNCTIONS_H_

#include <avr/io.h>

#define OW_PORT PORTC   //!< 1-Wire PORT Data register.
#define OW_PIN  PINC    //!< 1-Wire Input pin register.
#define OW_DDR  DDRC    //!< 1-Wire Data direction register.

#define OW_PULL_BUS_LOW(bitMask) \
            OW_DDR |= bitMask; OW_PORT &= ~bitMask;

#define OW_RELEASE_BUS(bitMask) \
            OW_DDR &= ~bitMask; OW_PORT &= ~bitMask;

#define __save_interrupt() SREG
#define __restore_interrupt(var) SREG = (var)
#define __disable_interrupt() cli()
#define __enable_interrupt() sei()

#define OW_DELAY_A 6
#define OW_DELAY_B 64
#define OW_DELAY_C 60
#define OW_DELAY_D 10
#define OW_DELAY_E 9
#define OW_DELAY_F 55
#define OW_DELAY_H 480
#define OW_DELAY_I 70
#define OW_DELAY_J 410

void    ow_init(uint8_t pins);
void    ow_write_bit1(uint8_t pins);
void    ow_write_bit0(uint8_t pins);
uint8_t ow_read_bit(uint8_t pins);
uint8_t ow_detect_presence(uint8_t pins);

#endif