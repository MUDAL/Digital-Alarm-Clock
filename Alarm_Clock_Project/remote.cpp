#include <Arduino.h>
#include <IRremote.h>
#include "remote.h"

irRecv_t GetIRRemoteVal(IRrecv& irReceiver)
{
  decode_results irResult;
  irRecv_t irValue = NO_KEY;
  if(irReceiver.decode(&irResult))
  {
    irValue = irResult.value;
    irReceiver.resume();
  }
  return irValue;
}

char GetIRKeyPress(irRecv_t& irValue)
{
  static irRecv_t irArray[] = 
  {
    KEY_1,KEY_2,KEY_3,
    KEY_4,KEY_5,KEY_6,
    KEY_7,KEY_8,KEY_9
  };
  static char ch[] = 
  {
    '1','2','3',
    '4','5','6',
    '7','8','9'
  };
  for(int i = 0; i < 9; i++)
  {
    if(irValue == irArray[i])
    {
      return ch[i];
    }
  }
  return '\0';
}

