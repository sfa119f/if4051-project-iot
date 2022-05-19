#include "Menu_Controller.h"

#include "Home/Menu_Home.h"
#include "Attendance/Menu_Attendance.h"
#include "Payment/Menu_Payment.h"
#include "Register/Menu_Register.h"
#include "TopUp/Menu_TopUp.h"

#include "../Hardware/Keypad/keypad.h"
#include "../Hardware/Display/display.h"
#include "../Utils/Auth/Authentication.h"
#include "../Utils/Conn/Conn.h"
#include "../Utils/Payload/payload.h"

Menu_Home home;
Menu_Attendance attendance;
Menu_Payment payment;
Menu_Register regist;
Menu_TopUp topup;
Menu *currMenu = &home;

Authentication auth;
int changeAuthStatus = -1;

void controller_display()
{
  // connection_init();
  tftClear();
  currMenu->display();
  if (auth.getActiveStatus() == 0)
  {
    switch (changeAuthStatus)
    {
    case 1:
      tftPrintText("Place your Card");
      break;
    case 2:
      tftPrintText("Place your Finger");
      break;
    default:
      break;
    }
    tftPrintText("Go Back", 1, DISP_TEXT_COLOR, 1, DISP_CURSOR_COLOR);
  }
}

void controller_loop()
{
  int p = buttonLoop();
  if (p >= 0)
  {
    if (p == 0)
    {
      currMenu->button1();
    }
    else if (p == 1)
    {
      currMenu->button2();
    }
    else if (p == 2)
    {
      int cursor = currMenu->button3();
      switch (cursor)
      {
      case -1:
        currMenu = &home;
        auth.clear();
        break;
      case 0:
        currMenu = &attendance;
        auth.start(cursor);
        break;
      case 1:
        currMenu = &payment;
        auth.start(cursor);
        break;
      case 2:
        currMenu = &topup;
        auth.start(cursor);
        break;
      case 3:
        currMenu = &regist;
        auth.start(cursor);
        break;
      default:
        currMenu = &home;
        auth.clear();
        break;
      }
    }
    controller_display();
    currMenu->loop();
  }
  if (changeAuthStatus != auth.loop())
  {
    changeAuthStatus = auth.getAuthStatus();
    if (changeAuthStatus == 0)
    {
      changeAuthStatus = -1;
      char payload[128];
      byte authId[16];
      auth.getAuthId(authId);
      createPayload(payload, authId, auth.getActiveCursor());
      sendPayload(payload);
      auth.clear();
      currMenu = &home;
    }
    controller_display();
  };
}
