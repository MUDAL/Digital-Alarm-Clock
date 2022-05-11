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

void DisplayMenu(int currentRow)
{
  char time[] = "  Time: ";
  char alarm[] = "  Alarm";
  char game[] = "  Game";
  char song[] = "  Song";

  switch(currentRow)
  {
    case 0:
      time[0] = '>';
      break;
    case 1:
      alarm[0] = '>';
      break;
    case 2:
      game[0] = '>';
      break;
    case 3:
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

void Scroll(scroll_t dir,int* param,int limit)
{
  if(*param != limit)
  {
    switch(dir)
    {
      case SCROLL_UP:
        (*param)--;
        break;
      case SCROLL_DOWN:
        (*param)++;
        break;
    }
  }  
}

void SelectMenuRow(int* row,int* state)
{
  switch((*row))
  {
    case 0:
      *state = STATE_SETTIME;
      break;
    case 1:
      *state = STATE_SETALARM;
      break;
    case 2:
      *state = STATE_PLAYGAME;
      break;
    case 3:
      *state = STATE_PLAYSONG;
      break;
  }
  lcd.clear();  
}

irRecv_t GetIRRemoteVal(void)
{
  decode_results irResult;
  irRecv_t irValue = NO_KEY;
  if(irReceiver.decode(&irResult))
  {
    irValue = irResult.value;
    irReceiver.resume();
  }
  return irValue;
}

void DisplayTimeScreen(int currentRow,int t_hour,int t_minute)
{
  char hour[] = "  Hour: ";
  char minute[] = "  Minute: ";
  char back[] = "  Back ";

  switch(currentRow)
  {
    case 0:
      hour[0] = '>';
      break;
    case 1:
      minute[0] = '>';
      break;
    case 2:
      back[0] = '>';
      break;
  }

  lcd.setCursor(0,0);
  lcd.print(hour);
  lcd.print(t_hour);
  lcd.setCursor(0,1);
  lcd.print(minute);
  lcd.print(t_minute);
  lcd.setCursor(0,2);
  lcd.print(back); 
}

void SetTime(time_t t,int* val)
{
  int row;
  int col; //for hour/minute's value on LCD screen
  while(1)
  {
    DateTime dateTime = rtc.now();
    irRecv_t irValue = GetIRRemoteVal();
    switch(t)
    {
      case HOUR:
        row = 0;
        col = 8;
        (*val) %= 24; //24-hour format (00-23)
        break;
      case MINUTE:
        row = 1;
        col = 10;
        (*val) %= 60; //60-minutes (00-59)
        break;
    }
    lcd.setCursor(1,row);
    lcd.print('>');
    lcd.setCursor(col,row);
    DisplayAlignedTime((*val));
    if(LongPress(UP_BUTTON) || (irValue == KEY_UP))
    {
      delay(200);
      (*val)++;
    }
    if(LongPress(DOWN_BUTTON) || (irValue == KEY_DOWN))
    {
      delay(200);
      (*val)--;
      if((*val) < 0)
      {
        switch(t)
        {
          case HOUR:
            (*val) = 23;
            break;
          case MINUTE:
            (*val) = 59;
            break;
        }
      }
    }
    if(IsPressed(SEL_BUTTON) || (irValue == KEY_OK))
    {
      switch(t)
      {
        case HOUR:
          //set new hour (current value of 'val')
          rtc.adjust(DateTime(dateTime.year(),dateTime.month(),dateTime.day(),
                             (*val),dateTime.minute(),dateTime.second()));
          break;
        case MINUTE:
          //set new minute (current value of 'val')
          rtc.adjust(DateTime(dateTime.year(),dateTime.month(),dateTime.day(),
                              dateTime.hour(),(*val),dateTime.second()));
          break;
      }
      break; //exit the loop
    }  
  }
}

