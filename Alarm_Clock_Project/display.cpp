#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include "RTClib.h" //Version 1.3.3
#include "display.h"

static void HighlightRow(int currentRow,int numOfRows,char** rowHeading)
{
  for(int i = 0; i < numOfRows; i++)
  {
    if(currentRow == i)
    {
      rowHeading[i][0] = '-';
      break;
    }
  }
}

static void DisplayRowHeadings(LiquidCrystal& lcd,char** rowHeading,int numOfRows)
{
  for(int i = 0; i < numOfRows; i++)
  {
    lcd.setCursor(0,i);
    lcd.print(rowHeading[i]);
  }
}

void Scroll(scroll_t dir,int& param,int limit)
{
  if(param != limit)
  {
    switch(dir)
    {
      case SCROLL_UP:
        param--;
        break;
      case SCROLL_DOWN:
        param++;
        break;
    }
  }  
}

void DisplayAlignedValue(LiquidCrystal& lcd,int t,char separator)
{
  //t = unaligned value
  if(t < 10)
  {
    lcd.print('0');
    lcd.print(t);
  }
  else
  {
    lcd.print(t);
  }
  if(separator != '\0')
  {
    lcd.print(separator);
  }  
}

void DisplayMainMenu(LiquidCrystal& lcd,int currentRow,RTC_DS3231& rtc)
{
  static byte smiley[8] = 
  {
    B00000,
    B10001,
    B00000,
    B00000,
    B10001,
    B01110,
    B00000,
  };
  char time[] = "  Time: ";
  char alarm[] = "  Alarm";
  char game[] = "  Game";
  char song[] = "  Songs";
  char* rowHeading[] = {time,alarm,game,song};
  HighlightRow(currentRow,4,rowHeading);
  DisplayRowHeadings(lcd,rowHeading,4);
  //Display time
  lcd.setCursor(8,0);
  DateTime currentTime = rtc.now();
  DisplayAlignedValue(lcd,currentTime.hour(),':');
  DisplayAlignedValue(lcd,currentTime.minute());
  //Display logo for main menu
  for(int i = 0; i < 4; i++)
  {
    lcd.setCursor(14,i);
    lcd.print('|');
  }
  lcd.createChar(0,smiley);
  lcd.setCursor(15,0);
  lcd.print("DAMI");
  lcd.write(byte(0)); //display smiley face
  lcd.setCursor(15,1);
  lcd.print("****");
  lcd.setCursor(15,2);
  lcd.print("MAIN");
  lcd.setCursor(15,3);
  lcd.print("MENU");
}

void DisplayTimeMenu(LiquidCrystal& lcd,int currentRow,int t_hour,int t_minute)
{
  char hour[] = "  Hour: ";
  char minute[] = "  Minute: ";
  char back[] = "  Back ";
  char* rowHeading[] = {hour,minute,back};
  HighlightRow(currentRow,3,rowHeading);
  DisplayRowHeadings(lcd,rowHeading,3);
  //Display hour and minute
  lcd.setCursor(8,0);
  lcd.print(t_hour);
  lcd.setCursor(10,1);
  lcd.print(t_minute);
}

void DisplayAlarmMenu(LiquidCrystal& lcd,int currentRow)
{
  char setAlarm[] = "  Set alarm ";
  char delAlarm[] = "  Delete alarm";
  char back[] = "  Back";
  char* rowHeading[] = {setAlarm,delAlarm,back};
  HighlightRow(currentRow,3,rowHeading);
  DisplayRowHeadings(lcd,rowHeading,3);
}

void DisplayAlarmSetting(LiquidCrystal& lcd,int currentRow,int t_hour,int t_minute)
{
  char hour[] = "  Hour: ";
  char minute[] = "  Minute: ";
  char store[] = "  Store [Max of 20]";
  char back[] = "  Back"; 
  char* rowHeading[] = {hour,minute,store,back}; 
  HighlightRow(currentRow,4,rowHeading);
  DisplayRowHeadings(lcd,rowHeading,4);
  //Display hour and minute
  lcd.setCursor(8,0);
  lcd.print(t_hour);
  lcd.setCursor(10,1);
  lcd.print(t_minute);
}

void DisplayAlarmDeletion(int& alarmSlot,LiquidCrystal& lcd,int currentRow)
{
  char slot[] = "  Slot: ";
  char deleteSlot[] = "  Delete slot";
  char deleteAll[] = "  Delete all";
  char back[] = "  Back";
  char* rowHeading[] = {slot,deleteSlot,deleteAll,back};
  HighlightRow(currentRow,4,rowHeading);
  DisplayRowHeadings(lcd,rowHeading,4);
  //Display current slot
  lcd.setCursor(8,0);
  lcd.print(alarmSlot+1);
}

void DisplayGameMenu(LiquidCrystal& lcd,int currentRow)
{
  char gameName[] = "  Tic-Tac-Toe";
  char back[] = "  Back";
  char* rowHeading[] = {gameName,back}; 
  HighlightRow(currentRow,2,rowHeading);
  DisplayRowHeadings(lcd,rowHeading,2);
  //Display Game Hint
  lcd.setCursor(0,2);
  lcd.print("[Use the remote");
  lcd.setCursor(0,3);
  lcd.print("to play the game]");
}

void DisplayPlayGame(LiquidCrystal& lcd,int currentRow)
{
  char play[] = "  Play";
  char howToPlay[] = "  How to play";
  char back[] = "  Back";
  char* rowHeading[] = {play,howToPlay,back};
  HighlightRow(currentRow,3,rowHeading);
  DisplayRowHeadings(lcd,rowHeading,3);
}

void DisplayHowToPlay(LiquidCrystal& lcd)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("1. Player 1 = X");
  lcd.setCursor(0,1);
  lcd.print("Player 2 = O");
  lcd.setCursor(0,2);
  lcd.print("Take turns to play");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("2. Use keys 1-9");
  lcd.setCursor(0,1);
  lcd.print("on the remote to");
  lcd.setCursor(0,2);
  lcd.print("place X or O");
  lcd.setCursor(0,3);
  lcd.print("on the game board");
  delay(3000);
}

void DisplaySongMenu(LiquidCrystal& lcd,int currentRow)
{
  char song1[] = "  Take on me by a-ha";
  char song2[] = "  Happy birthday";
  char song3[] = "  Star wars";
  char back[] = "  Back";
  char* rowHeading[] = {song1,song2,song3,back};
  HighlightRow(currentRow,4,rowHeading);
  DisplayRowHeadings(lcd,rowHeading,4);
}

