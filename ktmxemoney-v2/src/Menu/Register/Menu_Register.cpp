#include "Menu_Register.h"
#include "../../Hardware/Display/display.h"
#include "../../Hardware/RFID/rfid.h"
#include "../../Hardware/Fingerprint/finger.h"

void Menu_Register::display()
{

  tftSetCursor(0, 0);
  tftPrintText("Register");
  // tftPrintText("1. Register", 1, DISP_TEXT_COLOR, (cursor == 0), DISP_CURSOR_COLOR);
  // tftPrintText("2. Payment", 1, DISP_TEXT_COLOR, (cursor == 1), DISP_CURSOR_COLOR);
  // tftPrintText("3. Top Up", 1, DISP_TEXT_COLOR, (cursor == 2), DISP_CURSOR_COLOR);
  // tftPrintText("4. Register", 1, DISP_TEXT_COLOR, (cursor == 3), DISP_CURSOR_COLOR);
}

uint8_t rfid_regist_status = 1;
uint8_t finger_regist_status = 1;
byte a[16];

uint8_t Menu_Register::loop()
{
  if (rfid_regist_status != 0)
  {
    rfid_regist_status = rfidLoop(3, a);
  }

  if (rfid_regist_status == 0 && finger_regist_status != 0)
  {
    Serial.println("finger in");
    finger_regist_status = fingerReg(2);
    Serial.println("finger out");
  }

  if (rfid_regist_status == 0 && finger_regist_status == 0) {
    rfid_regist_status = 1;
    finger_regist_status = 1;
    return 0;
  }

  return 1;
}

int Menu_Register::button1() { return 0; }
int Menu_Register::button2() { return 0; }
int Menu_Register::button3()
{
  rfid_regist_status = 1;
  finger_regist_status = 1;
  return -1;
}
int Menu_Register::getCursor() { return -1; }