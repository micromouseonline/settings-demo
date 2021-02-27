/***********************************************************************
 * Created by Peter Harrison on 2019-06-10.
 * Copyright (c) 2019 Peter Harrison
 *
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without l> imitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************/

#include "settings.h"

#include <Arduino.h>

// create arrays holding the details of each setting
const Configuration defaults PROGMEM = {CONFIG_PARAMETERS(MAKE_DEFAULTS)};

/**
 * The configuration structure is a system wide global in RAM
 */
Configuration config = defaults;

/**
 * The name of each variable should go into flash
 */
CONFIG_PARAMETERS(MAKE_STRINGS);
const char *const variableString[] PROGMEM = {

    CONFIG_PARAMETERS(MAKE_NAMES)

};
// MAKE_STRINGS(a,b,c,d);

/**
 * The pointer to each variable is const so it can live in flash also
 */
void *const variablePointers[] PROGMEM = {CONFIG_PARAMETERS(MAKE_POINTERS)};

const PROGMEM TypeName variableType[] = {CONFIG_PARAMETERS(MAKE_TYPES)};

const int getRegisterCount()
{
    return sizeof(variableType) / sizeof(variableType[0]);
}

void printRegister(int i)
{
    Serial.print('$');
    Serial.print(i);

    Serial.print('=');
    void *ptr = (void *)pgm_read_word_near(variablePointers + i);
    switch (pgm_read_byte_near(variableType + i))
    {
        case T_float:
            Serial.print(*reinterpret_cast<float *>(ptr));
            break;
        case T_bool:
            Serial.print((*reinterpret_cast<bool *>(ptr)) ? "true" : "false");
            break;
        case T_char:
            Serial.print(*reinterpret_cast<char *>(ptr));
            break;
        case T_int:
        default:
            Serial.print(*reinterpret_cast<int *>(ptr));
            break;
    }
    char buffer[30];
    Serial.print(" (");
    strcpy_P(buffer, (char *)pgm_read_word(&(variableString[i]))); // Necessary casts and dereferencing, just copy.
    Serial.print(buffer);
    Serial.print(')');
    Serial.println();
}

int setRegister(const int i, const char *valueString)
{
    void *ptr = (void *)pgm_read_word_near(variablePointers + i);
    switch (pgm_read_byte_near(variableType + i))
    {
        case T_float:
            *reinterpret_cast<float *>(ptr) = (float)atof(valueString);
            break;
        case T_bool:
            *reinterpret_cast<bool *>(ptr) = atoi(valueString) ? true : false;
            break;
        case T_char:
            *reinterpret_cast<char *>(ptr) = valueString[0];
            break;
        case T_int:
        default:
            *reinterpret_cast<int *>(ptr) = atoi(valueString);
            break;
    }
    return 0;
}

int restoreDefaultConfig()
{
    memcpy_P(&config, &defaults, sizeof(defaults));
    return 0;
}

uint8_t crc8(uint8_t *data, unsigned int size)
{
    uint8_t checksum = 0;
    while (size--)
    {
        checksum = (checksum << 1) | (checksum >> 7);
        checksum += *data;
        data++;
    }
    return checksum;
}

unsigned int crc32(uint8_t *message, unsigned int n)
{
    const uint32_t Polynomial = 0xEDB88320;
    uint32_t crc = 0xFFFFFFFF;
    for (unsigned int i = 0; i < n; i++)
    {
        uint8_t byte = message[i];
        crc = crc ^ byte;
        for (int j = 0; j < 8; j++)
        {
            uint32_t mask = -(crc & 1);
            crc = (crc >> 1) ^ (Polynomial & mask);
        }
    }
    return ~crc;
}
