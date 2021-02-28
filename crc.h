#ifndef CRC_H
#define CRC_H

#include <stdint.h>

uint8_t crc8(uint8_t *data, unsigned int size);
unsigned int crc32(uint8_t *message, unsigned int n);

#endif // CRC_H
