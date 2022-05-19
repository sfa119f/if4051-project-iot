#include <functional>

#ifndef MENU_H
#define MENU_H

class Menu
{
public:
  virtual void display() = 0;
  virtual uint8_t loop() = 0;
  virtual int button1() = 0;
  virtual int button2() = 0;
  virtual int button3() = 0;
  virtual int getCursor() = 0;
};

#endif
