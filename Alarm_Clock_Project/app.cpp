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

void SelectMenuRow(int& row,int& state)
{
  switch(row)
  {
    case 0:
      state = STATE_TIMEMENU;
      break;
    case 1:
      state = STATE_ALARMMENU;
      break;
    case 2:
      state = STATE_GAMEMENU;
      break;
    case 3:
      state = STATE_SONGMENU;
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

void SetTime(time_t t,int& time)
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
        time %= 24; //24-hour format (00-23)
        break;
      case MINUTE:
        row = 1;
        col = 10;
        time %= 60; //60-minutes (00-59)
        break;
    }
    lcd.setCursor(1,row);
    lcd.print('>');
    lcd.setCursor(col,row);
    DisplayAlignedTime(time);
    if(LongPress(UP_BUTTON) || (irValue == KEY_UP))
    {
      delay(200);
      time++;
    }
    if(LongPress(DOWN_BUTTON) || (irValue == KEY_DOWN))
    {
      delay(200);
      time--;
      if(time < 0)
      {
        switch(t)
        {
          case HOUR:
            time = 23;
            break;
          case MINUTE:
            time = 59;
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
                              time,dateTime.minute(),dateTime.second()));
          break;
        case MINUTE:
          //set new minute (current value of 'val')
          rtc.adjust(DateTime(dateTime.year(),dateTime.month(),dateTime.day(),
                              dateTime.hour(),time,dateTime.second()));
          break;
      }
      break; //exit the loop
    }  
  }
}

void DisplayAlarmScreen(int currentRow)
{
  char setAlarm[] = "  Set alarm ";
  char delAlarm[] = "  Delete alarm";
  char back[] = "  Back";

  switch(currentRow)
  {
    case 0:
      setAlarm[0] = '>';
      break;
    case 1:
      delAlarm[0] = '>';
      break;
    case 2:
      back[0] = '>';
      break;
  }
  lcd.setCursor(0,0);
  lcd.print(setAlarm);
  lcd.setCursor(0,1);
  lcd.print(delAlarm);
  lcd.setCursor(0,2);
  lcd.print(back);    
}

//State functions
void StateFunction_MainMenu(int& state,irRecv_t& irValue,int& hour,int& minute)
{
  const int minRow = 0;
  const int maxRow = 3;
  static int currentRow;
  
  DateTime dateTime = rtc.now();
  hour = dateTime.hour();
  minute = dateTime.minute();
  
  DisplayMenu(currentRow);
  if(IsPressed(UP_BUTTON) || (irValue == KEY_UP))
  {
    Scroll(SCROLL_UP,currentRow,minRow);
  }
  if(IsPressed(DOWN_BUTTON) || (irValue == KEY_DOWN))
  {
    Scroll(SCROLL_DOWN,currentRow,maxRow); 
  }
  if(IsPressed(SEL_BUTTON) || (irValue == KEY_OK))
  {
    SelectMenuRow(currentRow,state);
  }  
}

void StateFunction_TimeMenu(int& state,irRecv_t& irValue,int& hour,int& minute)
{
  const int minRow = 0;
  const int maxRow = 2;
  static int currentRow;
  
  DisplayTimeScreen(currentRow,hour,minute);
  if(IsPressed(UP_BUTTON) || (irValue == KEY_UP))
  {
    Scroll(SCROLL_UP,currentRow,minRow);
  }
  if(IsPressed(DOWN_BUTTON) || (irValue == KEY_DOWN))
  {
    Scroll(SCROLL_DOWN,currentRow,maxRow); 
  }
  if(IsPressed(SEL_BUTTON) || (irValue == KEY_OK))
  {
    switch(currentRow)
    {
      case 0:
        SetTime(HOUR,hour);
        break;
      case 1:
        SetTime(MINUTE,minute);
        break;
      case 2:
        state = STATE_MAINMENU;
        break;
    }
    lcd.clear(); 
  }  
}

void StateFunction_AlarmMenu(int& state,irRecv_t& irValue)
{
  const int minRow = 0;
  const int maxRow = 2;
  static int currentRow;

  DisplayAlarmScreen(currentRow);
  if(IsPressed(UP_BUTTON) || (irValue == KEY_UP))
  {
    Scroll(SCROLL_UP,currentRow,minRow);
  }
  if(IsPressed(DOWN_BUTTON) || (irValue == KEY_DOWN))
  {
    Scroll(SCROLL_DOWN,currentRow,maxRow); 
  }
  if(IsPressed(SEL_BUTTON) || (irValue == KEY_OK))
  {
    switch(currentRow)
    {
      case 0:
        break;
      case 1:
        break;
      case 2:
        state = STATE_MAINMENU;
        break;
    }
    lcd.clear();
  }  
}
