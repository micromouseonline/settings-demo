/*
 * File: settings-test.ino                                                               *
 * Project: settings-test                                                                *
 * File Created: Tuesday, 2nd March 2021 3:38:49 pm                                      *
 * Author: Peter Harrison                                                                *
 * -----                                                                                 *
 * Last Modified: Thursday, 4th March 2021 1:03:25 pm                                    *
 * Modified By: Peter Harrison                                                           *
 * -----                                                                                 *
 * Copyright 2017 - 2021 Peter harrison, Micromouseonline                                *
 * -----                                                                                 *
 * MIT License                                                                           *
 *                                                                                       *
 * Copyright (c) 2021 Peter harrison                                                     *
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

#include "settings.h"
#include "stopwatch.h"
#include "system-commands.h"
#include <Arduino.h>
#include <util/crc16.h>

char line_buffer[64];
int index = 0;

void prompt() {
    Serial.print('O');
    Serial.print('K');
    Serial.print('>');
    Serial.print(' ');
}

void process_incoming_serial() {
    while (Serial.available()) {
        char c = Serial.read();
        Serial.print(c);
        switch (c) {
            case '\r':
                break;
            // TODO: add backspace handling
            case '\n': {
                line_buffer[index] = '\0'; // ensure terminated string
                if (line_buffer[0] == '$') {
                    int err = execute_settings_command(line_buffer);
                    if (err) {
                        Serial.print(F("ERROR: "));
                        Serial.print(err);
                        Serial.print(' ');
                        Serial.print(line_buffer);
                        Serial.println();
                    }
                } else {
                    Serial.println(F("Some other command perhaps"));
                }
                index = 0;
                prompt();
            } break;

            default:
                // keep grabbing characters as long as there is room
                if (index < 64) {
                    line_buffer[index++] = c;
                }
                break;
        }
    }
}

void show_some_samples() {
    execute_settings_command(line_buffer);
    Serial.println(F("Default settings:"));
    dump_settings();

    write_setting(3, 98);
    write_setting(7, false);

    settings.int_var = 100;
    Serial.println(settings.int_var);

    Serial.println();
    Serial.println(F("Modified settings:"));
    dump_settings();

    Serial.println();
    Serial.println(F("Restored defaults:"));
    restore_default_settings();
    dump_settings(4);

    settings.float_var = 999999;
    Serial.println();
    Serial.println(F("Loaded settings:"));
    load_settings_from_eeprom();
    dump_settings();
}

void initilise_settings() {
    Serial.println();
    Serial.print(F("There are "));
    Serial.print(get_settings_count());
    Serial.print(F(" settings, using "));
    Serial.print(sizeof(Settings));
    Serial.print(F(" bytes"));
    Serial.println();
    load_settings_from_eeprom(true);
}
void setup() {
    Serial.begin(115200);
    initilise_settings();
    Serial.println(hash16("Benny and the jets"));
    prompt();
}

void loop() {
    process_incoming_serial();
}

// int main(){
//   setup();
//   loop();

// };