#include "crc.h"
#include <stdint.h>

uint8_t crc8(uint8_t *data, unsigned int size) {
    uint8_t checksum = 0;
    while (size--) {
        checksum = (checksum << 1) | (checksum >> 7);
        checksum += *data;
        data++;
    }
    return checksum;
}

unsigned int crc32(uint8_t *message, unsigned int n) {
    const uint32_t Polynomial = 0xEDB88320;
    uint32_t crc = 0xFFFFFFFF;
    for (unsigned int i = 0; i < n; i++) {
        uint8_t byte = message[i];
        crc = crc ^ byte;
        for (int j = 0; j < 8; j++) {
            uint32_t mask = -(crc & 1);
            crc = (crc >> 1) ^ (Polynomial & mask);
        }
    }
    return ~crc;
}