/*
 * File: stopwatch.h                                                                     *
 * Project: settings-test-one                                                            *
 * File Created: Tuesday, 2nd March 2021 12:33:55 pm                                     *
 * Author: Peter Harrison                                                                *
 * -----                                                                                 *
 * Last Modified: Wednesday, 3rd March 2021 11:06:53 am                                  *
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

#ifndef _STOPWATCH_H
#define _STOPWATCH_H

#include <Arduino.h>

const uint32_t ONE_MILLISECOND = 1000;
const uint32_t ONE_SECOND = 1000 * ONE_MILLISECOND;
class Stopwatch {

public:
    Stopwatch() {
        start();
    };

    void start() {
        start_time = micros();
        stop_time = start_time;
    };

    void stop() {
        stop_time = micros();
    };

    uint32_t split() {
        return micros() - start_time;
    }

    uint32_t elapsed_time() const {
        return stop_time - start_time;
    };

private:
    uint32_t start_time;
    uint32_t stop_time;
};

#endif