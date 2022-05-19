#include "keypad.h"

bool button_state[3];
bool button_curr[3];

void buttonInit()
{
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_CONFIRM, INPUT_PULLUP);
  button_state[0] = digitalRead(BUTTON_UP);
  button_state[1] = digitalRead(BUTTON_DOWN);
  button_state[2] = digitalRead(BUTTON_CONFIRM);
}

int buttonLoop()
{
  int p = -1;

  button_curr[0] = digitalRead(BUTTON_UP);
  button_curr[1] = digitalRead(BUTTON_DOWN);
  button_curr[2] = digitalRead(BUTTON_CONFIRM);

  // debounce
  if (button_curr[0] == HIGH && button_state[0] == LOW)
  {
    Serial.println("BUTTON 1");
    p = 0;
  }
  if (button_curr[1] == HIGH && button_state[1] == LOW)
  {
    Serial.println("BUTTON 2");
    p = 1;
  }
  if (button_curr[2] == HIGH && button_state[2] == LOW)
  {
    Serial.println("BUTTON 3");
    p = 2;
  }

  button_state[0] = digitalRead(BUTTON_UP);
  button_state[1] = digitalRead(BUTTON_DOWN);
  button_state[2] = digitalRead(BUTTON_CONFIRM);
  return p;
}
