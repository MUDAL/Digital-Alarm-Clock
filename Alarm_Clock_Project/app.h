#ifndef APP_H
#define APP_H

#include <IRremote.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include "RTClib.h" //Version 1.3.3
#include "button.h"

//Enums
enum MenuParams
{
  TIME = 0,
  ALARM,
  GAME,
  SONG
};

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
extern IRrecv irReceiver;
extern RTC_DS3231 rtc;

//Functions
extern void Display(int param);
extern void Scroll(int button,int* param,int limit);

#endif
