#include "Menu_Home.h"
#include "../../Hardware/Display/display.h"

void Menu_Home::display()
{
  tftSetCursor(0, 0);
  tftPrintText("Home");
  tftPrintText("1. Attendance", 1, DISP_TEXT_COLOR, (cursor == 0), DISP_CURSOR_COLOR);
  tftPrintText("2. Payment", 1, DISP_TEXT_COLOR, (cursor == 1), DISP_CURSOR_COLOR);
  tftPrintText("3. Top Up", 1, DISP_TEXT_COLOR, (cursor == 2), DISP_CURSOR_COLOR);
  tftPrintText("4. Register", 1, DISP_TEXT_COLOR, (cursor == 3), DISP_CURSOR_COLOR);
}

uint8_t home_status = 1;

uint8_t Menu_Home::loop()
{
  return home_status;
}

int Menu_Home::button1()
{
  this->cursor--;
  if (this->cursor < 0)
  {
    this->cursor = 0;
  }
  Serial.println("up");
  return 0;
}

int Menu_Home::button2()
{
  this->cursor++;
  if (this->cursor > this->menu_size - 1)
  {
    this->cursor = this->menu_size - 1;
  }
  Serial.println("down");
  return 0;
}

int Menu_Home::button3()
{
  Serial.println("confirm");
  return this->getCursor();
}

int Menu_Home::getCursor()
{
  return this->cursor;
}
