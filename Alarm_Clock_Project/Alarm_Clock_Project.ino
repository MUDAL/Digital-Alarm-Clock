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
 * 
 * Credits (for buzzer music):
 * 1.https://www.youtube.com/watch?v=d-WkHkuYSPQ
 * 2.https://create.arduino.cc/projecthub/GeneralSpud/passive-buzzer-song-take-on-me-by-a-ha-0f04a8
 * 3.https://forum.arduino.cc/t/halloween-and-star-wars-on-two-push-botton-and-buzzer/630316
 * 4.https://docs.arduino.cc/built-in-examples/digital/toneMelody
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

//ISR (asynchronous halt) [Stop music/alarm]
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
      noTone(BUZZER_PIN);
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
}

void loop(void) 
{
  static int state = STATE_MAINMENU;
  static int hour;
  static int minute;
  irRecv_t irValue = GetIRRemoteVal(irReceiver);
  //Checking for alarm
  CheckAlarms(rtc);  
  //Executing state machine
  switch(state)
  {
    case STATE_MAINMENU:
      StateFunc_MainMenu(state,irValue,lcd,rtc,hour,minute);
      break;
    case STATE_TIMEMENU:
      StateFunc_TimeMenu(state,irValue,lcd,rtc,irReceiver,hour,minute);
      break;
    case STATE_ALARMMENU:
      StateFunc_AlarmMenu(state,irValue,lcd);
      break;
    case STATE_SETALARM:
      StateFunc_SetAlarm(state,irValue,lcd,rtc,irReceiver);
      break;
    case STATE_DELETEALARM:
      StateFunc_DeleteAlarm(state,irValue,lcd,rtc,irReceiver);
      break;
    case STATE_GAMEMENU:
      StateFunc_GameMenu(state,irValue,lcd);
      break;
    case STATE_PLAYGAME:
      StateFunc_PlayGame(state,irValue,lcd,rtc,irReceiver);
      break;
    case STATE_SONGMENU:
      StateFunc_SongMenu(state,irValue,lcd);
      break;
  }
}
