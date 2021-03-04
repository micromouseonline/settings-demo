/*
 * File: system-commands.cpp                                                             *
 * Project: settings-test                                                                *
 * File Created: Tuesday, 2nd March 2021 12:33:55 pm                                     *
 * Author: Peter Harrison                                                                *
 * -----                                                                                 *
 * Last Modified: Thursday, 4th March 2021 2:48:31 pm                                    *
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

#include "system-commands.h"
#include "read-number.h"
#include "settings.h"
#include "stopwatch.h"
#include <Arduino.h>

int execute_settings_command(char *line) {
    // we already know that line[0] == '$'
    if (line[1] == '\0') {
        return T_OK;
    }
    if (line[2] == '\0') { // one of the single character commands
        switch (line[1]) {
            case '$':
                dump_settings(5);
                return T_OK;
                break;
            case '#':
                restore_default_settings();
                return T_OK;
                break;
            case '@':
                load_settings_from_eeprom();
                return T_OK;
                break;
            case '!':
                save_settings_to_eeprom();
                return T_OK;
                break;
            case '?':
                // could be used by host to populate its data structures
                // list the settings names and types?
                // or send them as a C declaration?
                // or a JSON object ...

                for (int i = 0; i < get_settings_count(); i++) {
                    print_setting_details(i);
                    Serial.println(';');
                }
                return T_OK;
                break;
        }
    }

    //OK - so it must be a parameter fetch/update
    uint8_t pos = 1; // the first character [0] is already known
    // get the parameter index
    int index;
    if (!read_integer(line, &pos, &index)) {
        // This could be the place to trigger a string search
        return T_UNEXPECTED_TOKEN;
    }
    if (index < 0 or index >= get_settings_count()) {
        return T_OUT_OF_RANGE;
    }

    // There is a parameter index, now see if this is an assignment
    if (line[pos++] != '=') {
        print_setting(index, 3); // no, just report the value
        Serial.println();
        return T_OK;
    }

    // It was an assignment so get the value
    float value;
    if (!read_float(line, &pos, &value)) {
        return T_OUT_OF_RANGE;
    }
    // Any remaining characters are ignored

    // Everything must have worked. Woot!
    write_setting(index, value);
    return T_OK;
}
