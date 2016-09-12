#include "ow_rom_functions.h"
#include "ow_crc.h"

void ow_send_byte(uint8_t data, uint8_t pin) {
  uint8_t i;
  for(i = 0; i < 8; i++) {
    if(data & 0x01) {
      ow_write_bit1(pin);
    } else {
      ow_write_bit0(pin);
    }
    data >>= 1;
  }
}

uint8_t ow_receive_byte(uint8_t pin) {
  uint8_t data;
  uint8_t i;

  data = 0x00;

  for(i = 0; i < 8; i++) {
    data >>= 1;
    if(ow_read_bit(pin)) {
      data |= 0x80;
    }
  }
  return data;
}

void ow_match_rom(uint8_t *rom_value, uint8_t pin) {
  uint8_t bytes_left = 8;

  ow_send_byte(OW_ROM_MATCH, pin);

  while(bytes_left-- > 0) {
    ow_send_byte(*rom_value++, pin);
  }
}

uint8_t ow_search_rom(uint8_t *bit_pattern, uint8_t last_deviation, uint8_t pin) {

  uint8_t current_bit   = 1;
  uint8_t new_deviation = 0;
  uint8_t bit_mask      = 0x01;
  uint8_t bit_a;
  uint8_t bit_b;

  ow_send_byte(OW_ROM_SEARCH, pin);

  while(current_bit <= 64) {
    bit_a = ow_read_bit(pin);
    bit_b = ow_read_bit(pin);

    if(bit_a && bit_b) {
      return SEARCH_ERROR;
    } else if(bit_a ^ bit_b) {
      if(bit_a) {
        (*bit_pattern) |= bit_mask;
      } else {
        (*bit_pattern) &= ~bit_mask;
      }
    } else {
      if(current_bit == last_deviation) {
        (*bit_pattern) |= bit_mask;
      } else if(current_bit > last_deviation) {
        (*bit_pattern) &= ~bit_mask;
        new_deviation = current_bit;
      } else if(!(*bit_pattern & bit_mask)) {
        new_deviation = current_bit;
      } else {
      }
    }

    if((*bit_pattern) & bit_mask) {
      ow_write_bit1(pin);
    } else {
      ow_write_bit0(pin);
    }

    current_bit++;

    bit_mask <<= 1;
    if(!bit_mask) {
      bit_mask = 0x01;
      bit_pattern++;
    }
  }
  return new_deviation;
}

uint8_t ow_search_devices(OW_device *devices, uint8_t num_devices, uint8_t pin, uint8_t *num) {
  uint8_t i, j;
  uint8_t *new_id;
  uint8_t *current_id;
  uint8_t last_deviation;
  uint8_t num_found_devices;
  uint8_t flag = SEARCH_SUCCESSFUL;

  for(i = 0; i < num_devices; i++) {
    for(j = 0; j < 8; j++) {
      devices[i].id[j] = 0x00;
    }
  }

  num_found_devices = 0;
  new_id            = devices[0].id;
  last_deviation    = 0;
  current_id        = new_id;

  do {
    memcpy(new_id, current_id, 8);
    if(!ow_detect_presence(pin)) {
      return SEARCH_ERROR;
    };
    last_deviation = ow_search_rom(new_id, last_deviation, pin);
    current_id     = new_id;
    num_found_devices++;
    new_id = devices[num_found_devices].id;
  } while(last_deviation != OW_ROM_SEARCH_FINISHED);


  for(i = 0; i < num_found_devices; i++) {
    if(ow_check_rom_crc(devices[i].id) != OW_CRC_OK) {
      flag = SEARCH_CRC_ERROR;
    } else {
      (*num)++;
    }
  }
  return flag;
}

