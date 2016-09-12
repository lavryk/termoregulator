#include <avr/interrupt.h>

#include <util/delay.h>

#include <avr/pgmspace.h>
#include <avr/io.h>
#include <stdio.h>

#include "display.h"
#include "ds18b20.h"
#include "relay.h"
//#include "micro_menu.h"


int main(void) {
  int32_t temperature = -1;

  initLED();
  initDS18B20();

  while(1) {
    uint8_t index;
    for(index = 0; index < ds18b20_search_devices(); index++) {
      if(ds18b20_read_temperature(index, &temperature) == READ_SUCCESSFUL) {
        print_num(temperature, index);
        adjustTemperature(temperature, index);
        _delay_ms(200);
      } else {
        turnOffRelays();
      }
    }
    _delay_ms(200);
  }
  return 0;   /* never reached */
}


