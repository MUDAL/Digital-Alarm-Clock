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
  static int menuParam = TIME;
  static int state = STATE_MENU;
  switch(state)
  {
    case STATE_MENU:
      Display(menuParam);
      Scroll(UP_BUTTON,&menuParam,TIME);
      Scroll(DOWN_BUTTON,&menuParam,SONG); 
      if(IsPressed(SEL_BUTTON))
      {
        switch(menuParam)
        {
          case TIME:
            state = STATE_SETTIME;
            break;
          case ALARM:
            state = STATE_SETALARM;
            break;
          case GAME:
            state = STATE_PLAYGAME;
            break;
          case SONG:
            state = STATE_PLAYSONG;
            break;
        }
      }
      break;

    case STATE_SETTIME:
      Serial.println("Setting time");
      break;
      
    case STATE_SETALARM:
      Serial.println("Setting alarm");
      break;
      
    case STATE_PLAYGAME:
      Serial.println("Playing game");
      break;
      
    case STATE_PLAYSONG:
      Serial.println("Playing song");
      break;
  }
}
