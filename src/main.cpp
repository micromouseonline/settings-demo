#include "settings.h"
#include <Arduino.h>

void printList()
{
    Serial.println();
    for (int i = 0; i < getRegisterCount(); i++)
    {
        printRegister(i);
    }
}

void setup()
{
    Serial.begin(115200);
    Serial.println();
    Serial.print(F(" Config uses "));
    Serial.print(sizeof(Configuration));
    Serial.print(F(" bytes"));
    Serial.println();
    setRegister(0, "900.654");
    printList();
    config.MaxAccel = 100;
    restoreDefaultConfig();
    printList();
}

void loop()
{
    // put your main code here, to run repeatedly:
}

// int main(){
//   setup();
//   loop();

// };