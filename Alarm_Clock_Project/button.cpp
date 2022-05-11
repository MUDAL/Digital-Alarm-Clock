#include <Arduino.h>
#include "button.h"
//HMI button pins
#define UP_PIN      A2
#define SELECT_PIN  A3
#define DOWN_PIN    2

static bool IsDebounced(int buttonPin)
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

void InitHMIButtons(void)
{
  pinMode(UP_PIN,INPUT_PULLUP);
  pinMode(SELECT_PIN,INPUT_PULLUP);
  pinMode(DOWN_PIN,INPUT_PULLUP);  
}

bool IsPressed(int button)
{
  //Previous state of the 3 control buttons [up,sel,down] 
  static bool prevState[3] = {0};
  const int buttonPin[3] = {UP_PIN,SELECT_PIN,DOWN_PIN}; 
  
  if(IsDebounced(buttonPin[button]) && !prevState[button])
  {
    prevState[button] = true;
    return true;
  }
  else if(!IsDebounced(buttonPin[button]) && prevState[button])
  {
    prevState[button] = false;
  }
  return false;
}

bool LongPress(int button)
{
  const int buttonPin[3] = {UP_PIN,SELECT_PIN,DOWN_PIN}; 
  if(!digitalRead(buttonPin[button]))
  {
    return true;
  }
  return false;  
}
