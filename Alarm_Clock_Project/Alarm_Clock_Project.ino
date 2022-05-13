/*
 * Alarm clock project (Dami's birthday gift)
 * Pinouts:
 * RTC (SDA: A4, SCL: A5)
 * IR receiver (A0)
 * Reset button (2)
 * Button1 (A2)
 * Button2 (A3)
 * Button3 (A1)
 * LCD (10,4,5,6,7,8)
 * Buzzer (11)
 * RTC SQW pin (3)
 * 
 * Credits (for buzzer music):
 * 1.https://www.youtube.com/watch?v=d-WkHkuYSPQ
 * 2.https://create.arduino.cc/projecthub/GeneralSpud/passive-buzzer-song-take-on-me-by-a-ha-0f04a8
 * 
 * Additional info:
 * In order to prevent conflict between the tone and IRremote libraries, 
 * the IRremote library (boarddefs.h) was modified to use TIMER1 instead of TIMER2.
 * (TIMER2 is already used by the tone library)
 * 
*/
#include "app.h"

#define IR_RECEIVER   A0
#define RESET_BUTTON  2

LiquidCrystal lcd(10,4,5,6,7,8);
IRrecv irReceiver(IR_RECEIVER);
RTC_DS3231 rtc;

//ISR (asynchronous halt) [Stop music, stop alarm]
void ISR_Halt(void)
{
  //false trigger occurs due to power cycle
  static bool isCorrectTrigger;
  switch(isCorrectTrigger)
  {
    case false:
      isCorrectTrigger = true;
      break;
    case true:
      StopMusic(true);
      break;
  }
}

void setup(void) 
{
  Serial.begin(9600);
  pinMode(RESET_BUTTON,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(RESET_BUTTON),ISR_Halt,FALLING);
  InitHMIButtons();
  irReceiver.enableIRIn();
  rtc.begin();
  lcd.begin(20,4);
  //EEPROM Test
  //WriteEEPROM(0,55);
  //byte rcvData = ReadEEPROM(0);
  //Serial.print("data = ");
  //Serial.println(rcvData,DEC);
}

void loop(void) 
{
  /*if(!MusicStopped())
  {
    PlaySong_Birthday();
  }*/
  static int state = STATE_MAINMENU;
  static int hour;
  static int minute;
  irRecv_t irValue = GetIRRemoteVal();

  switch(state)
  {
    case STATE_MAINMENU:
      StateFunc_MainMenu(state,irValue,hour,minute);
      break;
    case STATE_TIMEMENU:
      StateFunc_TimeMenu(state,irValue,hour,minute);
      break;
    case STATE_ALARMMENU:
      StateFunc_AlarmMenu(state,irValue);
      break;
    case STATE_SETALARM:
      StateFunc_SetAlarm(state,irValue);
      break;
    case STATE_DELETEALARM:
      StateFunc_DeleteAlarm(state,irValue);
      break;
    case STATE_GAMEMENU:
      StateFunc_GameMenu(state);
      break;
    case STATE_SONGMENU:
      StateFunc_SongMenu(state);
      break;
  }
}
