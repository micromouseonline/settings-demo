# settings-demo

## How to use configuration settings in an arduino project.

Projects often benefit from keeping any configuration settings together in a single, manageable entity. It is also useful to be able to keep those settings in EEPROM so that they can survive a processor reset. 

This project illustrates one way to do that. There are extensive comments in the code. The idea is that all the project settings (so ling as they are numeric types) are held in a structure called settings. The code will automatically create this structure in RAM along with a set of defaults and a table of identifier names in Flash. The only RAM used is that needed to store the current working settings.

Functions are provided to allow current settings to be reset to the compiled-in defaults, load settings from EEPROM and store settings in EEPROM.

On program startup, the EEPROM is checked to see if it has a configuration compatible with the current definition and, if so, load it into RAM. If the current configuration is not compatible, then the programmed-in defalts are loaded and then saved to EEPROM.

Changes to working settings are not automatically save to EEPROM so that, at any time, changes can be reversed.

There is a facility to dump the settings to the Serial device so that they can easily be stored on a host. Replaying that list to the controller will make the relevant changes.

## Arduino IDE users

This project should build directly in the classic Arduino IDE if you open the directory settings-test


