#include "Authentication.h"

#include "../../Hardware/RFID/rfid.h"
#include "../../Hardware/Fingerprint/finger.h"

int Authentication::loop()
{
  if (this->activeStatus != 0)
    return -1;

  if (this->activeStatus == 0 && this->rfidStatus != 0)
    this->rfidStatus = rfidLoop(this->activeCursor, this->authId);
  if (this->activeStatus == 0 && this->rfidStatus == 0)
    this->fingerStatus = fingerLoop();

  if (this->rfidStatus == 0)
  {
    if (this->fingerStatus > 0)
    {
      this->authStatus = 0;
      this->activeStatus = -1;
    }
    else
    {
      this->authStatus = 2;
    }
  }
  else
  {
    this->authStatus = 1;
  }

  return this->authStatus;
}

void Authentication::clear()
{
  this->activeStatus = -1;
  this->activeCursor = -1;
  this->rfidStatus = -1;
  this->fingerStatus = -1;
  this->authStatus = -1;
}

int Authentication::start(int cursor)
{
  this->activeStatus = 0;
  this->activeCursor = cursor;
  return 0;
}

int Authentication::getAuthStatus()
{
  return this->authStatus;
}

int Authentication::getRfidStatus()
{
  return this->rfidStatus;
}

int Authentication::getFingerStatus()
{
  return this->fingerStatus;
}

int Authentication::getActiveStatus()
{
  return this->activeStatus;
}

int Authentication::getActiveCursor()
{
  return this->activeCursor;
}

int Authentication::getAuthId(byte authId[16])
{
  memcpy(authId, this->authId, 16);
  return 0;
}
