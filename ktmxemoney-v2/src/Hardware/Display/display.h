#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>

#define DISP_BACKGROUND_COLOR TFT_BLACK
#define DISP_CURSOR_COLOR 0x4040
#define DISP_TEXT_COLOR TFT_WHITE

void tftInit();
void tftClear();
void tftPrintText(String text, int sz = 1, uint16_t color = DISP_TEXT_COLOR, bool bg_f = 0, uint16_t bg_color = DISP_CURSOR_COLOR);
void tftSetCursor(uint16_t r, uint16_t c);