#ifndef APP_H
#define APP_H

#include <IRremote.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include "RTClib.h" //Version 1.3.3
#include "button.h"

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
  KEY_HASH = 0xFF52AD,
  KEY_LONGPRESS = 0xFFFFFFFF
}irRecv_t;

typedef enum
{
  SCROLL_UP = 0,
  SCROLL_DOWN
}scroll_t;

typedef enum
{
  HOUR = 0,
  MINUTE
}time_t;

enum States
{
  STATE_MENU = 0,
  STATE_SETTIME,
  STATE_SETALARM,
  STATE_PLAYGAME,
  STATE_PLAYSONG
};

//Variables
extern LiquidCrystal lcd;
extern RTC_DS3231 rtc;
extern IRrecv irReceiver;

//Functions
extern void DisplayMenu(int currentRow);
extern void Scroll(scroll_t dir,int* param,int limit);
extern void SelectMenuRow(int* row,int* state);
extern irRecv_t GetIRRemoteVal(void);
extern void DisplayTimeScreen(int currentRow,int t_hour,int t_minute);
extern void SetTime(time_t t,int* val);

#endif
