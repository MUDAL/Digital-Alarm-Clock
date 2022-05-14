#ifndef I2C_EEPROM_H
#define I2C_EEPROM_H

extern void WriteEEPROM(int address,byte data);
extern byte ReadEEPROM(int address);

#endif

