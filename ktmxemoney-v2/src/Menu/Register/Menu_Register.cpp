#include "Menu_Register.h"
#include "../../Hardware/Display/display.h"

void Menu_Register::display()
{

  tftSetCursor(0, 0);
  tftPrintText("Register");
  // tftPrintText("1. Register", 1, DISP_TEXT_COLOR, (cursor == 0), DISP_CURSOR_COLOR);
  // tftPrintText("2. Payment", 1, DISP_TEXT_COLOR, (cursor == 1), DISP_CURSOR_COLOR);
  // tftPrintText("3. Top Up", 1, DISP_TEXT_COLOR, (cursor == 2), DISP_CURSOR_COLOR);
  // tftPrintText("4. Register", 1, DISP_TEXT_COLOR, (cursor == 3), DISP_CURSOR_COLOR);
}

uint8_t Menu_Register::loop()
{
  return 0;
}

int Menu_Register::button1() { return 0; }
int Menu_Register::button2() { return 0; }
int Menu_Register::button3() { return -1; }
int Menu_Register::getCursor() { return -1; }