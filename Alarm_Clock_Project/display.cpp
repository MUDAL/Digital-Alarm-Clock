#include <Arduino.h>
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

static void DisplayRowHeadings(char** rowHeading,int numOfRows)
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

void DisplayAlignedTime(int t,char separator)
{
  //t = unaligned time
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

void DisplayMainMenu(int currentRow)
{
  byte smiley[8] = 
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
  DisplayRowHeadings(rowHeading,4);
  //Display time
  lcd.setCursor(8,0);
  DateTime currentTime = rtc.now();
  DisplayAlignedTime(currentTime.hour(),':');
  DisplayAlignedTime(currentTime.minute());
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

void DisplayTimeMenu(int currentRow,int t_hour,int t_minute)
{
  char hour[] = "  Hour: ";
  char minute[] = "  Minute: ";
  char back[] = "  Back ";
  char* rowHeading[] = {hour,minute,back};
  HighlightRow(currentRow,3,rowHeading);
  DisplayRowHeadings(rowHeading,3);
  //Display hour and minute
  lcd.setCursor(8,0);
  lcd.print(t_hour);
  lcd.setCursor(10,1);
  lcd.print(t_minute);
}

void DisplayAlarmMenu(int currentRow)
{
  char setAlarm[] = "  Set alarm ";
  char delAlarm[] = "  Delete alarm";
  char back[] = "  Back";
  char* rowHeading[] = {setAlarm,delAlarm,back};
  HighlightRow(currentRow,3,rowHeading);
  DisplayRowHeadings(rowHeading,3);
}

void DisplayAlarmSetting(int currentRow)
{
  char alarmSlot[] = "  Alarm slot: ";
  char hour[] = "  Hour: ";
  char minute[] = "  Minute: ";
  char back[] = "  Back"; 
  char* rowHeading[] = {alarmSlot,hour,minute,back}; 
  HighlightRow(currentRow,4,rowHeading);
  DisplayRowHeadings(rowHeading,4);
}

void DisplayGameMenu(int currentRow)
{
  char gameName[] = "  Tic-Tac-Toe";
  char back[] = "  Back";
  char* rowHeading[] = {gameName,back}; 
  HighlightRow(currentRow,2,rowHeading);
  DisplayRowHeadings(rowHeading,2);
}

void DisplaySongMenu(int currentRow)
{
  char song1[] = "  Take on me by a-ha";
  char song2[] = "  Happy birthday";
  char song3[] = "  Star wars";
  char back[] = "  Back";
  char* rowHeading[] = {song1,song2,song3,back};
  HighlightRow(currentRow,4,rowHeading);
  DisplayRowHeadings(rowHeading,4);
}

