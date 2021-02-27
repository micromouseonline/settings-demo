#include "settings.h"
#include "stopwatch.h"
#include <Arduino.h>

void setup() {
    Stopwatch sw;
    Serial.begin(115200);
    Serial.println();
    Serial.print(F("Settings object uses "));
    Serial.print(sizeof(Settings));
    Serial.print(F(" bytes"));
    Serial.println();

    Serial.println(F("Default settings:"));
    dump_settings();

    write_setting(2, "900.654");
    write_setting(3, 98);

    settings.MaxAccel = 100;
    Serial.println(settings.RunCount);
    settings.RunCount = 100;
    Serial.println(settings.RunCount);

    Serial.println();
    Serial.println(F("Modified settings:"));
    dump_settings();

    Serial.println();
    Serial.println(F("Restored defaults:"));
    restore_default_settings();
    dump_settings(4);

    settings.MaxAccel = 999999;
    Serial.println();
    Serial.println(F("Loaded settings:"));
    load_settings_from_eeprom();
    dump_settings();
}

void loop() {
    // put your main code here, to run repeatedly:
}

// int main(){
//   setup();
//   loop();

// };