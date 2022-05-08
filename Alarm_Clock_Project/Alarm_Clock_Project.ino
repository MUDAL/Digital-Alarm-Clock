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
#define BUTTON0       A2
#define BUTTON1       A3
#define BUTTON2       2

LiquidCrystal lcd(3,4,5,6,7,8);
IRrecv irReceiver(IR_RECEIVER);
RTC_DS3231 rtc;

//Previous button states
bool prevState[3] = {0};

//Functions
bool IsDebounced(int buttonPin)
{
  if(!digitalRead(buttonPin))
  {
    delay(15); //de-bounce delay
    if(!digitalRead(buttonPin))
    {
      return true;
    }
  }
  return false;
}

bool IsPressed(int buttonPin,int index)
{
  if(IsDebounced(buttonPin) && !prevState[index])
  {
    prevState[index] = true;
    return true;
  }
  else if(!IsDebounced(buttonPin) && prevState[index])
  {
    prevState[index] = false;
  }
  return false;
}

void DisplayMenu(void)
{
  DateTime currentTime = rtc.now();
  lcd.setCursor(2,0);
  lcd.print("Time: ");
  if(currentTime.hour() < 10)
  {
    lcd.print('0');
    lcd.print(currentTime.hour());
  }
  else
  {
    lcd.print(currentTime.hour());
  }
  
  lcd.print(':');
  if(currentTime.minute() < 10)
  {
    lcd.print('0');
    lcd.print(currentTime.minute());
  }
  else
  {
    lcd.print(currentTime.minute());
  }
    
  lcd.print(':');
  if(currentTime.second() < 10)
  {
    lcd.print('0');
    lcd.print(currentTime.second());
  }
  else
  {
    lcd.print(currentTime.second());
  }
  lcd.setCursor(2,1);
  lcd.print("Alarm");
  lcd.setCursor(2,2);
  lcd.print("Game");
  lcd.setCursor(2,3);
  lcd.print("Song");  
}

void setup(void) 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(RESET_BUTTON,INPUT_PULLUP);
  pinMode(BUTTON0,INPUT_PULLUP);
  pinMode(BUTTON1,INPUT_PULLUP);
  pinMode(BUTTON2,INPUT_PULLUP);
  irReceiver.enableIRIn();
  rtc.begin();
  lcd.begin(20,4);
  DisplayMenu();
}

void loop(void) 
{
  // put your main code here, to run repeatedly:
  DisplayMenu();
  if(IsPressed(BUTTON0,0))
  {
    Serial.println("Button 0 -> pressed");
  }    
  if(IsPressed(BUTTON1,1))
  {
    Serial.println("Button 1 -> pressed");
  }
  if(IsPressed(BUTTON2,2))
  {
    Serial.println("Button 2 -> pressed");
  }
}
