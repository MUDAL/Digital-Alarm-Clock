#include <Arduino.h>
#include <LiquidCrystal.h>
#include <IRremote.h>
#include "RTClib.h"
#include "button.h"
#include "i2c_eeprom.h"
#include "display.h"
#include "remote.h"
#include "alarm.h"
#include "song.h"

#define ALARMSLOT_EEPROMADDR  100

void SetAlarmHour(int& hour,LiquidCrystal& lcd,IRrecv& irReceiver)
{
  while(1)
  {
    irRecv_t irValue = GetIRRemoteVal(irReceiver);
    hour %= 24; //24-hour format (00-23)
    lcd.setCursor(1,0);
    lcd.print('>');
    lcd.setCursor(8,0);
    DisplayAlignedTime(lcd,hour);
    if(LongPress(UP_BUTTON) || (irValue == KEY_UP))
    {
      delay(200);
      hour++;
    }
    if(LongPress(DOWN_BUTTON) || (irValue == KEY_DOWN))
    {
      delay(200);
      hour--;
      if(hour < 0)
      {
        hour = 23;
      }
    }
    if(IsPressed(SEL_BUTTON) || (irValue == KEY_OK))
    {
      break; //exit the loop
    }  
  }  
}

void SetAlarmMinute(int& minute,LiquidCrystal& lcd,IRrecv& irReceiver)
{
  while(1)
  {
    irRecv_t irValue = GetIRRemoteVal(irReceiver);
    minute %= 60; //60-minutes (00-59)
    lcd.setCursor(1,1);
    lcd.print('>');
    lcd.setCursor(10,1);
    DisplayAlignedTime(lcd,minute);
    if(LongPress(UP_BUTTON) || (irValue == KEY_UP))
    {
      delay(200);
      minute++;
    }
    if(LongPress(DOWN_BUTTON) || (irValue == KEY_DOWN))
    {
      delay(200);
      minute--;
      if(minute < 0)
      {
        minute = 59;
      }
    }
    if(IsPressed(SEL_BUTTON) || (irValue == KEY_OK))
    {
      break; //exit the loop
    }  
  }   
}

void StoreAlarm(int& hour,int& minute,LiquidCrystal& lcd)
{
  byte unusedSlot = ReadEEPROM(ALARMSLOT_EEPROMADDR);
  //To accomodate 20 alarms (1 alarm = hour + minute)
  //1 alarm takes up 2 slots
  unusedSlot %= 40; 
  WriteEEPROM(unusedSlot,hour);
  WriteEEPROM((unusedSlot+1),minute);
  WriteEEPROM(ALARMSLOT_EEPROMADDR,(unusedSlot+2));
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Alarm stored in");
  lcd.setCursor(0,1);
  lcd.print("slot ");
  lcd.print(unusedSlot / 2);
  delay(2500);
}

void AlarmGenerator(RTC_DS3231& rtc,int slot)
{
  DateTime dateTime = rtc.now();
  int currentHour = dateTime.hour();
  int currentMinute = dateTime.minute();
  int currentSecond = dateTime.second();
  int alarmHour = ReadEEPROM(slot * 2);
  int alarmMinute = ReadEEPROM(1 + (slot*2));
  if((currentHour == alarmHour)&&(currentMinute == alarmMinute)&&(currentSecond == 0))
  {
    tone(BUZZER_PIN,300); //300Hz alarm sound  
  }
}
