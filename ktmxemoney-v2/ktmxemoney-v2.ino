#include "src/Hardware/Display/display.h"
#include "src/Hardware/Keypad/keypad.h"
#include "src/Hardware/RFID/rfid.h"
#include "src/Hardware/Fingerprint/finger.h"
//#include "cursor.h"
#include "src/Menu/Menu_Controller.h"
#include "src/Utils/Conn/Conn.h"

// Task Variables
TaskHandle_t TaskMain, TaskConnection;

void setup()
{
  Serial.begin(9600);
  tftInit();
  buttonInit();
  rfidInit();
  fingerInit();
  controller_display();

  // Create task to handle connection at core 0
  xTaskCreatePinnedToCore(
    connectionFunc,
    "connection",
    10000,
    NULL,
    1,
    &TaskConnection,
    0);
  delay(500);

  xTaskCreatePinnedToCore(
    mainFunc,
    "main",
    10000,
    NULL,
    1,
    &TaskMain,
    1);
  delay(500);

}

void loop()
{
}

void connectionFunc(void *pvParameters){
  connection_init();

  for(;;){
    connection_loop();
  }
}

void mainFunc(void *pvParameters){
  controller_display();

  for(;;){
    controller_loop();
  }
}
