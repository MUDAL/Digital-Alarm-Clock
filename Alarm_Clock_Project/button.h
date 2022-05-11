#ifndef BUTTON_H
#define BUTTON_H

enum Button
{
  UP_BUTTON = 0,
  SEL_BUTTON,
  DOWN_BUTTON
};

extern void InitHMIButtons(void);
extern bool IsPressed(int button);
extern bool LongPress(int button);

#endif
