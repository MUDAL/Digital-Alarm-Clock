#ifndef ALARM_H
#define ALARM_H

#define NUM_OF_ALARMS  20

extern void SetAlarmHour(int& hour,LiquidCrystal& lcd,IRrecv& irReceiver);
extern void SetAlarmMinute(int& minute,LiquidCrystal& lcd,IRrecv& irReceiver);
extern void StoreAlarm(int& hour,int& minute,LiquidCrystal& lcd);
extern void AlarmGenerator(RTC_DS3231& rtc,int slot);

#endif
