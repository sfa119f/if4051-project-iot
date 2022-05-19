#include "payload.h"

String byte_to_string(byte *buffer, byte bufferSize)
{
  String text = "";
  for (byte i = 0; i < bufferSize; i++)
  {
    text += (buffer[i] < 0x10 ? "0" : "");
    text += String(buffer[i], HEX);
  }
  return text;
}

void createPayload(char payload[128], byte uid[16], int kind)
{
  struct tm timeinfo;
  getLocalTime(&timeinfo);
  char buf[32];
  strftime(buf, sizeof(buf), "%FT%TZ", &timeinfo);

  StaticJsonDocument<256> doc;
  doc["time"] = String(buf);
  doc["uid"] = byte_to_string(uid, 16);
  doc["kind"] = kind;

  serializeJson(doc, payload, 128);
}
