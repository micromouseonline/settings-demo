/*
 * File: crc.cpp                                                                         *
 * Project: settings-test-one                                                            *
 * File Created: Saturday, 27th February 2021 6:56:31 pm                                 *
 * Author: Peter Harrison                                                                *
 * -----                                                                                 *
 * Last Modified: Wednesday, 3rd March 2021 10:56:08 am                                  *
 * Modified By: Peter Harrison                                                           *
 * -----                                                                                 *
 * Copyright 2017 - 2021 Peter Harrison, Micromouseonline                                *
 * -----                                                                                 *
 * MIT License                                                                           *
 *                                                                                       *
 * Copyright (c) 2021 Peter Harrison                                                     *
 *                                                                                       *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of       *
 * this software and associated documentation files (the "Software"), to deal in         *
 * the Software without restriction, including without limitation the rights to          *
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies         *
 * of the Software, and to permit persons to whom the Software is furnished to do        *
 * so, subject to the following conditions:                                              *
 *                                                                                       *
 * The above copyright notice and this permission notice shall be included in all        *
 * copies or substantial portions of the Software.                                       *
 *                                                                                       *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR            *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,              *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE           *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER                *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,         *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE         *
 * SOFTWARE.                                                                             *
 */

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