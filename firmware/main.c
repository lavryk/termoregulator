#include <avr/interrupt.h>
#include <util/delay.h>

#include "display.h"
#include "ds18b20.h"


int main(void) {
  uint32_t temperature = 0;
  uint8_t  search_flag = SEARCH_SENSORS;
  uint8_t  num_devices = 0;
  uint8_t  crc_flag    = 0;

  init_led();
  ow_init(BUS);

  while(1) {

    if(search_flag == SEARCH_SENSORS) {
      num_devices = 0;
      crc_flag    = ow_search_devices(all_devices, MAX_DEVICES, BUS, &num_devices);
      if(crc_flag == SEARCH_CRC_ERROR) {
        print_err(ERR0, num_devices);
      } else if(num_devices == MAX_DEVICES) {
        search_flag = SENSORS_FOUND;
      }
    }

    uint8_t index;
    for(index = 0; index < MAX_DEVICES; index++) {
      crc_flag = ds18b20_read_temperature(BUS, all_devices[index].id, &temperature);
      if(crc_flag == READ_CRC_ERROR) {
        print_err(ERR1, index);
      } else {
        print_num(temperature, index);
        search_flag = SEARCH_SENSORS;
      }
      _delay_us(500);
    }

    _delay_ms(500);

  }
  return 0;   /* never reached */
}

