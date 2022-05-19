#include <Arduino.h>
#include <LiquidCrystal.h>
#include <IRremote.h>
#include "pitches.h"
#include "RTClib.h"
#include "button.h"
#include "i2c_eeprom.h"
#include "display.h"
#include "remote.h"
#include "alarm.h"
#include "song.h"

#define ALARMSLOT_EEPROMADDR  100
#define EMPTY_EEPROM          255

static void AlarmGenerator(LiquidCrystal& lcd,RTC_DS3231& rtc,int slot)
{
  DateTime dateTime = rtc.now();
  int currentHour = dateTime.hour();
  int currentMinute = dateTime.minute();
  int currentSecond = dateTime.second();
  int alarmHour = ReadEEPROM(slot*2);
  int alarmMinute = ReadEEPROM(1 + (slot*2));
  if((currentHour == alarmHour)&&(currentMinute == alarmMinute)&&(currentSecond == 0))
  {
    tone(BUZZER_PIN,250); //250Hz alarm sound  
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Hey, there's work");
    lcd.setCursor(0,1);
    lcd.print("to do!!!!!");
    while(1){} //loop breaks due to reset button
  }
}

void SetAlarmHour(int& hour,LiquidCrystal& lcd,RTC_DS3231& rtc,IRrecv& irReceiver)
{
  lcd.setCursor(1,0);
  lcd.print('>');
  while(1)
  {
    CheckAlarms(lcd,rtc);
    irRecv_t irValue = GetIRRemoteVal(irReceiver);
    hour %= 24; //24-hour format (00-23)
    lcd.setCursor(8,0);
    DisplayAlignedValue(lcd,hour);
    if(LongPress(UP_BUTTON) || (irValue == KEY_UP))
    {
      delay(150);
      hour++;
    }
    if(LongPress(DOWN_BUTTON) || (irValue == KEY_DOWN))
    {
      delay(150);
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

void SetAlarmMinute(int& minute,LiquidCrystal& lcd,RTC_DS3231& rtc,IRrecv& irReceiver)
{
  lcd.setCursor(1,1);
  lcd.print('>');
  while(1)
  {
    CheckAlarms(lcd,rtc);
    irRecv_t irValue = GetIRRemoteVal(irReceiver);
    minute %= 60; //60-minutes (00-59)
    lcd.setCursor(10,1);
    DisplayAlignedValue(lcd,minute);
    if(LongPress(UP_BUTTON) || (irValue == KEY_UP))
    {
      delay(150);
      minute++;
    }
    if(LongPress(DOWN_BUTTON) || (irValue == KEY_DOWN))
    {
      delay(150);
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
  //Find and store free sub-slot for next alarm
  for(int i = 0; i < (2*NUM_OF_ALARMS); i+=2)
  {
    if(ReadEEPROM(i) == EMPTY_EEPROM)
    {
      WriteEEPROM(ALARMSLOT_EEPROMADDR,i);
      break;
    }
  }
  byte unusedsubSlot = ReadEEPROM(ALARMSLOT_EEPROMADDR);
  //To accomodate 20 alarms (1 alarm = hour + minute)
  //1 alarm takes up 2 sub-slots [1 slot = 2 sub-slots]
  unusedsubSlot %= (2*NUM_OF_ALARMS); 
  WriteEEPROM(unusedsubSlot,hour);
  WriteEEPROM((unusedsubSlot+1),minute);
  WriteEEPROM(ALARMSLOT_EEPROMADDR,(unusedsubSlot+2)); //move to next free sub-slot
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Alarm stored in");
  lcd.setCursor(0,1);
  lcd.print("slot ");
  lcd.print(1+(unusedsubSlot / 2));
  delay(2500);
}

void CheckAlarms(LiquidCrystal& lcd,RTC_DS3231& rtc)
{
  for(int alarm = 0; alarm < NUM_OF_ALARMS; alarm++)
  {
    AlarmGenerator(lcd,rtc,alarm);  
  }  
}

void SelectAlarmSlot(int& slot,LiquidCrystal& lcd,RTC_DS3231& rtc,IRrecv& irReceiver)
{
  lcd.setCursor(1,0);
  lcd.print('>');
  int prevSlot = 0;
  while(1)
  {
    CheckAlarms(lcd,rtc);
    irRecv_t irValue = GetIRRemoteVal(irReceiver);
    slot %= NUM_OF_ALARMS;
    if(prevSlot != slot)
    {
      lcd.setCursor(8,0);
      //clear reset of the line
      for(int i = 8; i < 20; i++)
      {
        lcd.print(" ");
      }
    }
    lcd.setCursor(8,0);
    DisplayAlignedValue(lcd,1+slot);
    //Display alarm hour and minute for current slot by.. 
    //reading the required sub-slots
    int hour = ReadEEPROM(slot*2);
    int minute = ReadEEPROM(1+(slot*2));
    lcd.setCursor(11,0);
    lcd.print('[');
    if((hour == EMPTY_EEPROM) || (minute == EMPTY_EEPROM))
    {
      lcd.print("Nil]    "); //Nil] with 4 spaces afterwards
    }
    else
    {
      DisplayAlignedValue(lcd,hour,':'); //hour
      DisplayAlignedValue(lcd,minute); //minute 
      lcd.print(']');
    }
    
    if(LongPress(UP_BUTTON) || (irValue == KEY_UP))
    {
      delay(150);
      slot++;
      prevSlot = slot;
    }
    if(LongPress(DOWN_BUTTON) || (irValue == KEY_DOWN))
    {
      delay(150);
      slot--;
      if(slot < 0)
      {
        slot = (NUM_OF_ALARMS - 1);
      }
      prevSlot = slot;
    }
    if(IsPressed(SEL_BUTTON) || (irValue == KEY_OK))
    {
      break; //exit the loop
    }     
  }
}

void DeleteAlarmSlot(int& slot,LiquidCrystal& lcd,IRrecv& irReceiver)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Deleting alarm");
  lcd.setCursor(0,1);
  lcd.print("at slot ");
  lcd.print(slot+1);
  //Clear current slot (both sub-slots)
  WriteEEPROM((2*slot),EMPTY_EEPROM); //hour sub-slot
  WriteEEPROM((1+(2*slot)),EMPTY_EEPROM); //minute sub-slot
  //Find smallest empty slot
  for(int i = 0; i < (2*NUM_OF_ALARMS); i+=2)
  {
    if(ReadEEPROM(i) == EMPTY_EEPROM)
    {
      WriteEEPROM(ALARMSLOT_EEPROMADDR,i);
      break;
    }
  }
  delay(2000);
}

void DeleteAllAlarms(LiquidCrystal& lcd)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Deleting all alarms");
  //Clear all slots
  for(int i = 0; i < (2*NUM_OF_ALARMS); i++)
  {
    WriteEEPROM(i,EMPTY_EEPROM);
  }
  //Store sub-slot 0 
  WriteEEPROM(ALARMSLOT_EEPROMADDR,0);
  delay(2000);
}

