#include "app.h"

static void SetTime(time_t t,int& time,LiquidCrystal& lcd,RTC_DS3231& rtc,IRrecv& irReceiver)
{
  int row;
  int col; //for hour/minute's value on LCD screen
  while(1)
  {
    DateTime dateTime = rtc.now();
    irRecv_t irValue = GetIRRemoteVal(irReceiver);
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
    DisplayAlignedTime(lcd,time);
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

static void LoopSong(void(*PlaySong)())
{
  StopMusic(false); //Enable music play 
  while(1)
  {
    PlaySong();
    if(MusicStopped())
    {
      //Music stopped by reset button 
      break;
    }
  }
}

//Extern functions
void StateFunc_MainMenu(int& state,irRecv_t& irValue,LiquidCrystal& lcd,
                        RTC_DS3231& rtc,int& hour,int& minute)
{
  const int minRow = 0;
  const int maxRow = 3;
  static int currentRow;
  
  DateTime dateTime = rtc.now();
  hour = dateTime.hour();
  minute = dateTime.minute();
  
  DisplayMainMenu(lcd,currentRow,rtc);
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
}

void StateFunc_TimeMenu(int& state,irRecv_t& irValue,LiquidCrystal& lcd,
                        RTC_DS3231& rtc,IRrecv& irReceiver,
                        int& hour,int& minute)
{
  const int minRow = 0;
  const int maxRow = 2;
  static int currentRow;
  
  DisplayTimeMenu(lcd,currentRow,hour,minute);
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
        SetTime(HOUR,hour,lcd,rtc,irReceiver);
        break;
      case 1:
        SetTime(MINUTE,minute,lcd,rtc,irReceiver);
        break;
      case 2:
        state = STATE_MAINMENU;
        break;
    }
    lcd.clear(); 
  }  
}

void StateFunc_AlarmMenu(int& state,irRecv_t& irValue,LiquidCrystal& lcd)
{
  const int minRow = 0;
  const int maxRow = 2;
  static int currentRow;

  DisplayAlarmMenu(lcd,currentRow);
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
        state = STATE_SETALARM;
        break;
      case 1:
        state = STATE_DELETEALARM;
        break;
      case 2:
        state = STATE_MAINMENU;
        break;
    }
    lcd.clear();
  }  
}

void StateFunc_SetAlarm(int& state,irRecv_t& irValue,LiquidCrystal& lcd)
{
  const int minRow = 0;
  const int maxRow = 3;
  static int currentRow;  

  DisplayAlarmSetting(lcd,currentRow);
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
        //Set alarm slot
        break;
      case 1:
        //Set alarm hour
        break;
      case 2:
        //Set alarm minute
        break;
      case 3:
        state = STATE_ALARMMENU;
        break;
    }
    lcd.clear(); 
  }      
}

void StateFunc_DeleteAlarm(int& state,irRecv_t& irValue,LiquidCrystal& lcd)
{
  
}

void StateFunc_GameMenu(int& state,irRecv_t& irValue,LiquidCrystal& lcd)
{
  const int minRow = 0;
  const int maxRow = 1;
  static int currentRow;

  DisplayGameMenu(lcd,currentRow);
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
        state = STATE_PLAYGAME;
        break;
      case 1:
        state = STATE_MAINMENU;
        break;
    }
    lcd.clear(); 
  }    
}

void StateFunc_PlayGame(int& state,irRecv_t& irValue,LiquidCrystal& lcd,IRrecv& irReceiver)
{
  const int minRow = 0;
  const int maxRow = 2;
  static int currentRow;

  DisplayPlayGame(lcd,currentRow);
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
        PlayGame(lcd,irReceiver);
        state = STATE_MAINMENU;
        break;
      case 1:
        DisplayHowToPlay(lcd);
        break;
      case 2:
        state = STATE_GAMEMENU;
        break;
    }
    lcd.clear(); 
  }        
}

void StateFunc_SongMenu(int& state,irRecv_t& irValue,LiquidCrystal& lcd)
{
  const int minRow = 0;
  const int maxRow = 3;
  static int currentRow;

  DisplaySongMenu(lcd,currentRow);
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
        lcd.setCursor(1,0);
        lcd.print('>');
        LoopSong(PlaySong_TakeOnMe);
        break;
      case 1:
        lcd.setCursor(1,1);
        lcd.print('>');
        LoopSong(PlaySong_Birthday);
        break;
      case 2:
        lcd.setCursor(1,2);
        lcd.print('>');
        LoopSong(PlaySong_Starwars);
        break;
      case 3:
        state = STATE_MAINMENU;
        break;
    }
    lcd.clear(); 
  }         
}

