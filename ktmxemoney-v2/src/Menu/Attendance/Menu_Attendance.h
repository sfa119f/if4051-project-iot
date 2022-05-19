#include <functional>

#include "../Template/Menu.h"

class Menu_Attendance : public Menu
{
public:
  void display(void);
  uint8_t loop(void);
  int button1();
  int button2();
  int button3();
  int getCursor();
};
