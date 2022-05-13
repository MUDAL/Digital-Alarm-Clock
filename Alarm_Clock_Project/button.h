#ifndef BUTTON_H
#define BUTTON_H

typedef enum
{
  UP_BUTTON = 0,
  SEL_BUTTON,
  DOWN_BUTTON
}hmiButton_t;

extern void InitHMIButtons(void);
extern bool IsPressed(hmiButton_t button);
extern bool LongPress(hmiButton_t button);

#endif
