#include "ds18b20.h"
#include "ow_crc.h"
#include "display.h"

uint8_t search_flag = SEARCH_SENSORS;

void initDS18B20() {
  ow_init(BUS);
}

uint8_t ds18b20_search_devices() {
  uint8_t num_devices = MAX_DEVICES;
  if(search_flag == SEARCH_SENSORS) {
    num_devices      = 0;
    uint8_t crc_flag = ow_search_devices(all_devices, MAX_DEVICES, BUS, &num_devices);
    if(crc_flag == SEARCH_CRC_ERROR) {
      print_err(ERR0, num_devices);
      _delay_us(1000);
    } else if(num_devices == MAX_DEVICES) {
      search_flag = SENSORS_FOUND;
    }
  }

  return num_devices;
}

uint8_t ds18b20_read_temperature(uint8_t index, int32_t *temperature) {
  uint8_t scratchpad[9];
  uint8_t i;

  ow_detect_presence(BUS);
  ow_match_rom(all_devices[index].id, BUS);
  ow_send_byte(DS18B20_CONVERT_T, BUS);

  while(!ow_read_bit(BUS));

  ow_detect_presence(BUS);
  ow_match_rom(all_devices[index].id, BUS);
  ow_send_byte(DS18B20_READ_SCRATCHPAD, BUS);
  for(i = 0; i <= 8; i++) {
    scratchpad[i] = ow_receive_byte(BUS);
  }

  if(ow_check_scratch_pad_crc(scratchpad) != OW_CRC_OK) {
    print_err(ERR1, index);
    _delay_us(1000);
    search_flag = SEARCH_SENSORS;
    return READ_CRC_ERROR;
  }

  *temperature = (int16_t) scratchpad[0];
  *temperature |= ((int16_t) scratchpad[1] << 8);
  *temperature *= 0.0625;
  return READ_SUCCESSFUL;
}