#include "Menu_Attendance.h"
#include "../../Hardware/Display/display.h"

void Menu_Attendance::display()
{

  tftSetCursor(0, 0);
  tftPrintText("Attendance");
  // tftPrintText("1. Attendance", 1, DISP_TEXT_COLOR, (cursor == 0), DISP_CURSOR_COLOR);
  // tftPrintText("2. Payment", 1, DISP_TEXT_COLOR, (cursor == 1), DISP_CURSOR_COLOR);
  // tftPrintText("3. Top Up", 1, DISP_TEXT_COLOR, (cursor == 2), DISP_CURSOR_COLOR);
  // tftPrintText("4. Register", 1, DISP_TEXT_COLOR, (cursor == 3), DISP_CURSOR_COLOR);
}

uint8_t attendance_status = 1;

uint8_t Menu_Attendance::loop()
{
  return attendance_status;
}

int Menu_Attendance::button1() { return 0; }
int Menu_Attendance::button2() { return 0; }
int Menu_Attendance::button3() { return -1; }
int Menu_Attendance::getCursor() { return -1; }