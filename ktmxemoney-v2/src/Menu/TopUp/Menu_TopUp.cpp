#include "Menu_TopUp.h"
#include "../../Hardware/Display/display.h"

void Menu_TopUp::display()
{

  tftSetCursor(0, 0);
  tftPrintText("TopUp");
  // tftPrintText("1. TopUp", 1, DISP_TEXT_COLOR, (cursor == 0), DISP_CURSOR_COLOR);
  // tftPrintText("2. Payment", 1, DISP_TEXT_COLOR, (cursor == 1), DISP_CURSOR_COLOR);
  // tftPrintText("3. Top Up", 1, DISP_TEXT_COLOR, (cursor == 2), DISP_CURSOR_COLOR);
  // tftPrintText("4. TopUp", 1, DISP_TEXT_COLOR, (cursor == 3), DISP_CURSOR_COLOR);
}

uint8_t topup_status = 1;

uint8_t Menu_TopUp::loop()
{
  return topup_status;
}

int Menu_TopUp::button1() { return 0; }
int Menu_TopUp::button2() { return 0; }
int Menu_TopUp::button3() { return -1; }
int Menu_TopUp::getCursor() { return -1; }