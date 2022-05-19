#ifndef ALARM_H
#define ALARM_H

#define NUM_OF_ALARMS  20

extern void SetAlarmHour(int& hour,LiquidCrystal& lcd,RTC_DS3231& rtc,IRrecv& irReceiver);
extern void SetAlarmMinute(int& minute,LiquidCrystal& lcd,RTC_DS3231& rtc,IRrecv& irReceiver);
extern void StoreAlarm(int& hour,int& minute,LiquidCrystal& lcd);
extern void CheckAlarms(LiquidCrystal& lcd,RTC_DS3231& rtc);
extern void SelectAlarmSlot(int& slot,LiquidCrystal& lcd,RTC_DS3231& rtc,IRrecv& irReceiver);
extern void DeleteAlarmSlot(int& slot,LiquidCrystal& lcd,IRrecv& irReceiver);
extern void DeleteAllAlarms(LiquidCrystal& lcd);

#endif
