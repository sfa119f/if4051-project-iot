#include <SPI.h>
#include <MFRC522.h>

#define RFID_RST 34
#define RFID_SS 5

void rfidInit();
int rfidLoop(int, byte[16]);
