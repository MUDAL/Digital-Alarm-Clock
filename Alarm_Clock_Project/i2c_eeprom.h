#ifndef I2C_EEPROM_H
#define I2C_EEPROM_H

#include <Wire.h>
extern void WriteEEPROM(int address,byte data);
extern byte ReadEEPROM(int address);

#endif

