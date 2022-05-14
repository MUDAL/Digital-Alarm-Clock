#ifndef DISPLAY_H
#define DISPLAY_H

typedef enum
{
  SCROLL_UP = 0,
  SCROLL_DOWN
}scroll_t;

extern void Scroll(scroll_t dir,int& param,int limit);
extern void DisplayAlignedTime(LiquidCrystal& lcd,int t,char separator = '\0');
extern void DisplayMainMenu(LiquidCrystal& lcd,int currentRow,RTC_DS3231& rtc);
extern void DisplayTimeMenu(LiquidCrystal& lcd,int currentRow,int t_hour,int t_minute);
extern void DisplayAlarmMenu(LiquidCrystal& lcd,int currentRow);
extern void DisplayAlarmSetting(LiquidCrystal& lcd,int currentRow);

extern void DisplayGameMenu(LiquidCrystal& lcd,int currentRow);
extern void DisplayPlayGame(LiquidCrystal& lcd,int currentRow);
extern void DisplayHowToPlay(LiquidCrystal& lcd);
extern void DisplaySongMenu(LiquidCrystal& lcd,int currentRow);

#endif
