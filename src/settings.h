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

#ifndef SETTINGS_H
#define SETTINGS_H

#include <Arduino.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum  TypeName : uint8_t
{
    T_float,
    T_int,
    T_bool,
    T_char
};

typedef struct
{
    const uint8_t type;
    void *ptr;
} ConfigEntry;

// clang-format off
#define CONFIG_PARAMETERS(ACTION)                  \
  ACTION( 0, float,       MaxSpeed,    123.45)     \
  ACTION( 1, float,       MaxAccel,     23.456)    \
  ACTION( 2, float,       MaxOmega,     34.567)    \
  ACTION( 3, float,       MinOmega,     34.567)    \
  ACTION( 4, int,         RunCount,    452)        \
  ACTION( 5, bool,        JapanRules,  true)       \
  ACTION( 6, char,        Revision,    'e')        \
\

/*
 * Macros derived from
 * https://stackoverflow.com/questions/201593/is-there-a-simple-way-to-convert-c-enum-to-string/238157#238157
 */
#define MAKE_STRINGS(        INDEX, CTYPE,  VAR,   VALUE) const PROGMEM char s_##VAR[] = #VAR;
#define MAKE_NAMES(          INDEX, CTYPE,  VAR,   VALUE) s_##VAR,
#define MAKE_TYPES(          INDEX, CTYPE,  VAR,   VALUE) T_##CTYPE,
#define MAKE_DEFAULTS(       INDEX, CTYPE,  VAR,   VALUE) .VAR = VALUE,
#define MAKE_STRUCT(         INDEX, CTYPE,  VAR,   VALUE) CTYPE VAR;
#define MAKE_POINTERS(       INDEX, CTYPE,  VAR,   VALUE) reinterpret_cast<void *>(&config.VAR),
#define MAKE_CONFIG_ENTRY(   INDEX, CTYPE,  VAR,   VALUE) {#VAR,T_##CTYPE,reinterpret_cast<void *>(&config.VAR)},

// clang-format on

/***
 * Builds a structure definition
 */
typedef struct
{
    CONFIG_PARAMETERS(MAKE_STRUCT)
} Configuration;

extern Configuration config;

extern const Configuration defaults;
extern void *const variablePointers[];
extern const TypeName variableType[];

const int getRegisterCount();

int restoreDefaultConfig();
uint8_t crc8(uint8_t *data, unsigned int size);
unsigned int crc32(uint8_t *message, unsigned int n);

const char *getNameString(int index);
void printRegister(const int i);
int setRegister(const int i, const char *valueString);

#endif //UNTITLED2_CONFIG_H
