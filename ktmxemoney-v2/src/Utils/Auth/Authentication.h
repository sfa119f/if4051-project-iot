#include <Arduino.h>

class Authentication
{
private:
  int activeStatus = -1;
  int activeCursor = -1;
  int rfidStatus = -1;
  int fingerStatus = -1;
  int authStatus = -1;
  byte authId[16];

public:
  int loop();
  void clear();
  int start(int);
  int getAuthStatus();
  int getRfidStatus();
  int getFingerStatus();
  int getActiveStatus();
  int getActiveCursor();
  int getAuthId(byte authId[16]);
};