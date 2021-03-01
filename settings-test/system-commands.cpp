#include "system-commands.h"
#include "settings.h"
#include "stopwatch.h"
#include <Arduino.h>

enum {
    T_OK,
    T_OUT_OF_RANGE,
    T_UNEXPECTED_TOKEN,
};

/////////////////////////////////////////////////////////////////////////////

// floats have no more than 8 significant digits
#define MAX_DIGITS 8
/***
 * Scan a character array for an integer.
 * Begin scn at line[pos]
 * Assumes no leading spaces.
 * Stops at first non-digit.
 * MODIFIES pos so that it points to the first non-digit
 * MODIFIES value ONLY IF a valid integer is converted
 * RETURNS  boolean status indicating success or error
 *
 * optimisations are possible but may not be worth the effort
 */
uint8_t read_integer(const char *line, uint8_t *pos, int *value) {
    char *ptr = (char *)line + *pos;
    char c = *ptr++;
    bool is_minus = false;
    uint8_t digits = 0;
    if (c == '-') {
        is_minus = true;
        c = *ptr++;
    }
    int32_t number = 0;
    while (c >= '0' and c <= '9') {
        if (digits++ < MAX_DIGITS) {
            number = 10 * number + (c - '0');
        }
        c = *ptr++;
    }
    *pos = ptr - line - 1;
    if (digits > 0) {

        *value = is_minus ? -number : number;
    }
    return digits;
}
/////////////////////////////////////////////////////////////////////////////

/***
 * Scan a character array for a float.
 * This is a much simplified and limited version of the library function atof()
 * It will not convert exponents and has a limited range of valid values.
 * They should be more than adequate for the robot parameters however.
 * Begin scan at line[pos]
 * Assumes no leading spaces.
 * Only scans MAX_DIGITS characters
 * Stops at first non-digit, or decimal point.
 * MODIFIES pos so that it points to the first character after the number
 * MODIFIES value ONLY IF a valid float is converted
 * RETURNS  boolean status indicating success or error
 *
 * optimisations are possible but may not be worth the effort
 */
uint8_t read_float(const char *line, uint8_t *pos, float *value) {

    char *ptr = (char *)line + *pos;
    char c = *ptr++;
    uint8_t digits = 0;

    bool is_minus = false;
    if (c == '-') {
        is_minus = true;
        c = *ptr++;
    }

    uint32_t a = 0.0;
    int exponent = 0;
    while (c >= '0' and c <= '9') {
        if (digits++ < MAX_DIGITS) {
            a = a * 10 + (c - '0');
        }
        c = *ptr++;
    };
    if (c == '.') {
        c = *ptr++;
        while (c >= '0' and c <= '9') {
            if (digits++ < MAX_DIGITS) {
                a = a * 10 + (c - '0');
                exponent = exponent - 1;
            }
            c = *ptr++;
        }
    }

    *pos = ptr - line - 1;
    float b = a;
    while (exponent < 0) {
        b *= 0.1;
        exponent++;
    }
    if (digits > 0) {
        *value = is_minus ? -b : b;
    }
    return digits;
}

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
                return T_OK;
                break;
        }
    }

    //OK - so it must be a parameter fetch/update
    uint8_t pos = 1; // the first character [0] is already known
    // get the parameter index
    int index;
    Stopwatch sw;
    if (!read_integer(line, &pos, &index)) {
        // This could be the place to trigger a string search
        return T_UNEXPECTED_TOKEN;
    }
    Serial.print('[');
    Serial.print(sw.split());
    Serial.print(']');
    Serial.println();
    if (index < 0 or index >= get_settings_count()) {
        return T_OUT_OF_RANGE;
    }

    // There is a parameter index, now see if this is an assignment
    if (line[pos++] != '=') {
        print_setting(index, 3); // no, just report the value
        return T_OK;
    }

    // It was an assignment so get the value
    float value;
    sw.start();
    if (!read_float(line, &pos, &value)) {
        return T_OUT_OF_RANGE;
    }
    Serial.print('[');
    Serial.print(sw.split());
    Serial.print(']');
    Serial.println();
    // Any remaining characters are ignored

    // Everything must have worked. Woot!
    write_setting(index, value);
    return T_OK;
}
