#ifndef DISPLAY_H
#define DISPLAY_H

#include <LiquidCrystal.h>
#include <Wire.h>
#include "RTClib.h" //Version 1.3.3

typedef enum
{
  SCROLL_UP = 0,
  SCROLL_DOWN
}scroll_t;

extern LiquidCrystal lcd;
extern RTC_DS3231 rtc;

extern void Scroll(scroll_t dir,int& param,int limit);
extern void DisplayAlignedTime(int t,char separator = '\0');
extern void DisplayMainMenu(int currentRow);
extern void DisplayTimeMenu(int currentRow,int t_hour,int t_minute);
extern void DisplayAlarmMenu(int currentRow);
extern void DisplayAlarmSetting(int currentRow);

#endif
