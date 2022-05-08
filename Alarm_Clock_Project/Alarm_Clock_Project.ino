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
#include <IRremote.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include "RTClib.h" //Version 1.3.3

#define IR_RECEIVER   A0
#define RESET_BUTTON  A1
#define BUTTON1       A2
#define BUTTON2       A3
#define BUTTON3       2

LiquidCrystal lcd(3,4,5,6,7,8);
IRrecv irrecv(IR_RECEIVER);
RTC_DS3231 rtc;

void setup(void) 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(RESET_BUTTON,INPUT_PULLUP);
  pinMode(BUTTON1,INPUT_PULLUP);
  pinMode(BUTTON2,INPUT_PULLUP);
  pinMode(BUTTON3,INPUT_PULLUP);
  lcd.begin(20,4);
  lcd.print("Welcome");
  irrecv.enableIRIn();
  rtc.begin();
}

void loop(void) 
{
  // put your main code here, to run repeatedly:
  if(!digitalRead(RESET_BUTTON))
  {
    Serial.println("Reset button pressed");
  }
  if(!digitalRead(BUTTON1))
  {
    Serial.println("Button 1 pressed");
  }
  if(!digitalRead(BUTTON2))
  {
    Serial.println("Button 2 pressed");
  }
  if(!digitalRead(BUTTON3))
  {
    Serial.println("Button 3 pressed");
  }      
}
