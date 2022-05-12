#include <Arduino.h>
#include "i2c_eeprom.h"

#define EEPROM_ADDRESS 0x57 //AT24C32

void WriteEEPROM(int address,byte data)
{
  Wire.beginTransmission(EEPROM_ADDRESS);
  //Send memory as two bytes
  Wire.write((int)(address >> 8)); //MSB
  Wire.write((int)(address & 0xFF)); //LSB
  Wire.write(data);
  Wire.endTransmission();
  delay(5);
}

byte ReadEEPROM(int address)
{
  //Define byte for received data
  byte rcvData = 0xFF;
  Wire.beginTransmission(EEPROM_ADDRESS);
  //Send memory as two bytes
  Wire.write((int)(address >> 8)); //MSB
  Wire.write((int)(address & 0xFF)); //LSB
  Wire.endTransmission();
  //Request 1 byte of data at current memory address
  Wire.requestFrom(EEPROM_ADDRESS,1);
  //Read the data
  rcvData = Wire.read();
  return rcvData;
}

