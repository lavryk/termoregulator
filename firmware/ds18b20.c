#include "ds18b20.h"
#include "ow_crc.h"

uint8_t ds18b20_read_temperature(uint8_t bus, uint8_t *id, uint32_t *temperature) {
  uint8_t scratchpad[9];
  uint8_t i;

  ow_detect_presence(bus);
  ow_match_rom(id, bus);
  ow_send_byte(DS18B20_CONVERT_T, bus);

  while(!ow_read_bit(bus));

  ow_detect_presence(bus);
  ow_match_rom(id, bus);
  ow_send_byte(DS18B20_READ_SCRATCHPAD, bus);
  for(i = 0; i <= 8; i++) {
    scratchpad[i] = ow_receive_byte(bus);
  }

  if(ow_check_scratch_pad_crc(scratchpad) != OW_CRC_OK) {
    return READ_CRC_ERROR;
  }

  *temperature = (uint32_t) scratchpad[0];
  *temperature |= ((uint32_t) scratchpad[1] << 8);
  *temperature *= 0.0625;
  return READ_SUCCESSFUL;
}