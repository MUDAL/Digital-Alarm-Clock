#ifndef APP_H
#define APP_H

#include <IRremote.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include "RTClib.h" //Version 1.3.3

#include "button.h"
#include "i2c_eeprom.h"
#include "display.h"
#include "song.h"
#include "remote.h"
#include "game.h"
#include "alarm.h"

enum States
{
  STATE_MAINMENU = 0,
  STATE_TIMEMENU,
  STATE_ALARMMENU,
  STATE_SETALARM,
  STATE_CHECKALARM,
  STATE_DELETEALARM,
  STATE_GAMEMENU,
  STATE_PLAYGAME,
  STATE_SONGMENU
};

//State functions
extern void StateFunc_MainMenu(int& state,irRecv_t& irValue,LiquidCrystal& lcd,
                               RTC_DS3231& rtc,int& hour,int& minute);
extern void StateFunc_TimeMenu(int& state,irRecv_t& irValue,LiquidCrystal& lcd,
                               RTC_DS3231& rtc,IRrecv& irReceiver,
                               int& hour,int& minute);
extern void StateFunc_AlarmMenu(int& state,irRecv_t& irValue,LiquidCrystal& lcd);
extern void StateFunc_SetAlarm(int& state,irRecv_t& irValue,LiquidCrystal& lcd,IRrecv& irReceiver);
extern void StateFunc_CheckAlarm(int& state,irRecv_t& irValue,LiquidCrystal& lcd);
extern void StateFunc_DeleteAlarm(int& state,irRecv_t& irValue,LiquidCrystal& lcd);
extern void StateFunc_GameMenu(int& state,irRecv_t& irValue,LiquidCrystal& lcd);
extern void StateFunc_PlayGame(int& state,irRecv_t& irValue,LiquidCrystal& lcd,IRrecv& irReceiver);
extern void StateFunc_SongMenu(int& state,irRecv_t& irValue,LiquidCrystal& lcd);

#endif
