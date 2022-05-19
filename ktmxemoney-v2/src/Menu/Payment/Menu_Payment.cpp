#include "Menu_Payment.h"
#include "../../Hardware/Display/display.h"

void Menu_Payment::display()
{

  tftSetCursor(0, 0);
  tftPrintText("Payment");
  // tftPrintText("1. Payment", 1, DISP_TEXT_COLOR, (cursor == 0), DISP_CURSOR_COLOR);
  // tftPrintText("2. Payment", 1, DISP_TEXT_COLOR, (cursor == 1), DISP_CURSOR_COLOR);
  // tftPrintText("3. Top Up", 1, DISP_TEXT_COLOR, (cursor == 2), DISP_CURSOR_COLOR);
  // tftPrintText("4. Register", 1, DISP_TEXT_COLOR, (cursor == 3), DISP_CURSOR_COLOR);
}

uint8_t Menu_Payment::loop()
{
  return 0;
}

int Menu_Payment::button1() { return 0; }
int Menu_Payment::button2() { return 0; }
int Menu_Payment::button3() { return -1; }
int Menu_Payment::getCursor() { return -1; }