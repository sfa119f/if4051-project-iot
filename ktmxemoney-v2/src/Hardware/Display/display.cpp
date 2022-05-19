#include "display.h"

TFT_eSPI tft = TFT_eSPI();

void tftInit()
{
  Serial.print("TFT TEST");
  tft.init();
  tftClear();
}

void tftClear()
{
  tft.fillScreen(DISP_BACKGROUND_COLOR);
}

void tftPrintText(String text, int sz, uint16_t color, bool bg_f, uint16_t bg_color)
{
  if (bg_f)
  {
    tft.setTextColor(color, bg_color);
  }
  else
  {
    tft.setTextColor(color, 0);
  }
  tft.setTextSize(sz);
  tft.println(text.c_str());
}

void tftSetCursor(uint16_t r, uint16_t c)
{
  tft.setCursor(r, c);
}