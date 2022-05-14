#ifndef REMOTECTRL_H
#define REMOTECTRL_H

//Enums
typedef enum
{
  NO_KEY = 0,
  KEY_UP = 0xFF629D,
  KEY_FORWARD = 0xFFC23D,
  KEY_DOWN = 0xFFA857,
  KEY_BACK = 0xFF22DD,
  KEY_OK = 0xFF02FD,
  KEY_1 = 0xFF6897,
  KEY_2 = 0xFF9867,
  KEY_3 = 0xFFB04F,
  KEY_4 = 0xFF30CF,
  KEY_5 = 0xFF18E7,
  KEY_6 = 0xFF7A85,
  KEY_7 = 0xFF10EF,
  KEY_8 = 0xFF38C7,
  KEY_9 = 0xFF5AA5,
  KEY_0 = 0xFF4AB5,
  KEY_STAR = 0xFF42BD,
  KEY_HASH = 0xFF52AD
}irRecv_t;

extern irRecv_t GetIRRemoteVal(IRrecv& irReceiver);
extern char GetIRKeyPress(irRecv_t& irValue);

#endif
