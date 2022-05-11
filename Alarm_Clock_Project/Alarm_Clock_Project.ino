/*
 * Alarm clock project (Dami's birthday gift)
 * Pinouts:
 * RTC (SDA: A4, SCL: A5)
 * IR receiver (A0)
 * Reset button (A1)
 * Button1 (A2)
 * Button2 (A3)
 * Button3 (2)
 * LCD (3,4,5,6,7,8)
 * Buzzer (11)
 * RTC SQW pin (9)
*/
#include "app.h"

#define IR_RECEIVER   A0
#define RESET_BUTTON  A1

LiquidCrystal lcd(3,4,5,6,7,8);
IRrecv irReceiver(IR_RECEIVER);
RTC_DS3231 rtc;

void setup(void) 
{
  Serial.begin(9600);
  pinMode(RESET_BUTTON,INPUT_PULLUP);
  InitHMIButtons();
  irReceiver.enableIRIn();
  rtc.begin();
  lcd.begin(20,4);
}

void loop(void) 
{
  static int state = STATE_MENU;
  static int hour;
  static int minute;
  irRecv_t irValue = GetIRRemoteVal();

  if(state == STATE_MENU)
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
      Scroll(SCROLL_UP,&currentRow,minRow);
    }
    if(IsPressed(DOWN_BUTTON) || (irValue == KEY_DOWN))
    {
      Scroll(SCROLL_DOWN,&currentRow,maxRow); 
    }
    if(IsPressed(SEL_BUTTON) || (irValue == KEY_OK))
    {
      SelectMenuRow(&currentRow,&state);
    }
  }
  
  else if(state == STATE_SETTIME)
  {
    const int minRow = 0;
    const int maxRow = 2;
    static int currentRow;
    
    DisplayTimeScreen(currentRow,hour,minute);
    if(IsPressed(UP_BUTTON) || (irValue == KEY_UP))
    {
      Scroll(SCROLL_UP,&currentRow,minRow);
    }
    if(IsPressed(DOWN_BUTTON) || (irValue == KEY_DOWN))
    {
      Scroll(SCROLL_DOWN,&currentRow,maxRow); 
    }
    if(IsPressed(SEL_BUTTON) || (irValue == KEY_OK))
    {
      switch(currentRow)
      {
        case 0:
          SetTime(HOUR,&hour);
          break;
        case 1:
          SetTime(MINUTE,&minute);
          break;
        case 2:
          state = STATE_MENU;
          break;
      }
      lcd.clear(); 
    }
  }
  
  else if(state == STATE_SETALARM)
  {
    static int currentRow;
  }
  
  else if(state == STATE_PLAYGAME)
  {
    static int currentRow;
  }
  
  else if(state == STATE_PLAYSONG)
  {
    static int currentRow;
  }
}
