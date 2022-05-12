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
  //EEPROM Test [Thanks to DroneBot Workshop and https://github.com/cyberp/AT24Cx/tree/master/AT24CX_search_IC]
  //WriteEEPROM(0,55);
  //byte rcvData = ReadEEPROM(0);
  //Serial.print("data = ");
  //Serial.println(rcvData,DEC);
}

void loop(void) 
{
  static int state = STATE_MAINMENU;
  static int hour;
  static int minute;
  irRecv_t irValue = GetIRRemoteVal();

  switch(state)
  {
    case STATE_MAINMENU:
      StateFunction_MainMenu(state,irValue,hour,minute);
      break;
    case STATE_TIMEMENU:
      StateFunction_TimeMenu(state,irValue,hour,minute);
      break;
    case STATE_ALARMMENU:
      StateFunction_AlarmMenu(state,irValue);
      break;
    case STATE_GAMEMENU:
      break;
    case STATE_SONGMENU:
      break;
  }
}
