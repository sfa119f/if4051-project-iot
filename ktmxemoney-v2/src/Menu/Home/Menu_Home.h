#include <functional>

#include "../Template/Menu.h"

// const int menu_size = 4;
// const String menu_item[] = {
//     "1. Attendance",
//     "2. Payment",
//     "3. Top Up",
//     "4. Register"};

class Menu_Home : public Menu
{
private:
  int cursor = 0;
  const int menu_size = 4;

public:
  void display(void);
  uint8_t loop(void);
  int button1();
  int button2();
  int button3();
  int getCursor();
};
