#include "app.h"

static void DisplayAlignedTime(int t,char separator = '\0')
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

void DisplayMenu(MenuParam_t param)
{
  char time[] = "  Time: ";
  char alarm[] = "  Alarm";
  char game[] = "  Game";
  char song[] = "  Song";

  switch(param)
  {
    case TIME:
      time[0] = '>';
      break;
    case ALARM:
      alarm[0] = '>';
      break;
    case GAME:
      game[0] = '>';
      break;
    case SONG:
      song[0] = '>';
      break;
  }
  
  lcd.setCursor(0,0);
  lcd.print(time);
  DateTime currentTime = rtc.now();
  DisplayAlignedTime(currentTime.hour(),':');
  DisplayAlignedTime(currentTime.minute());
  lcd.setCursor(0,1);
  lcd.print(alarm);
  lcd.setCursor(0,2);
  lcd.print(game);
  lcd.setCursor(0,3);
  lcd.print(song);  
}
