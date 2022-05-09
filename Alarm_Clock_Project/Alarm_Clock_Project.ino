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
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(RESET_BUTTON,INPUT_PULLUP);
  InitHMIButtons();
  irReceiver.enableIRIn();
  rtc.begin();
  lcd.begin(20,4);
}

void loop(void) 
{
  // put your main code here, to run repeatedly:
  DisplayMenu(TIME);
  if(IsPressed(UP_BUTTON))
  {
    Serial.println("Up pressed");
  }    
  if(IsPressed(SEL_BUTTON))
  {
    Serial.println("Select pressed");
  }
  if(IsPressed(DOWN_BUTTON))
  {
    Serial.println("Down pressed");
  }
}
