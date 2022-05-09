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
  TIME = 0,
  ALARM,
  GAME,
  SONG
}MenuParam_t;

//Variables
extern LiquidCrystal lcd;
extern IRrecv irReceiver;
extern RTC_DS3231 rtc;

//Functions
extern void DisplayMenu(MenuParam_t param);

#endif
