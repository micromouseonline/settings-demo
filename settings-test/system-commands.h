/*
 * File: system-commands.h                                                               *
 * Project: settings-test                                                                *
 * File Created: Tuesday, 2nd March 2021 12:33:55 pm                                     *
 * Author: Peter Harrison                                                                *
 * -----                                                                                 *
 * Last Modified: Wednesday, 3rd March 2021 10:55:28 am                                  *
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

#ifndef SYSTEM_COMMANDS_H
#define SYSTEM_COMMANDS_H

#include <Arduino.h>

int execute_settings_command(char *line);

#endif