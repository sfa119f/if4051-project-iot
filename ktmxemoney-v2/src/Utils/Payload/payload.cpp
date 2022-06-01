#include "payload.h"
#include "../Conn/Conn.h"

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

void createPayload(char payload_buff[JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(8)], byte uid[16], int kind)
{
  time_t now;
  struct tm timeinfo;
  getLocalTime(&timeinfo);
  time(&now);

  const size_t capacity = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(8);

  DynamicJsonDocument doc(capacity);
  doc["timestamp"] = ((unsigned long long)now) * 1000;
  JsonObject payload = doc.createNestedObject("payload");
  payload["device"] = WiFi.macAddress();
  payload["uid"] = byte_to_string(uid, 16);
  payload["mode"] = kind;

  serializeJson(doc, payload_buff, capacity);
}

void getPayload()
{
  // const size_t capacity = JSON_OBJECT_SIZE(10);
  // DynamicJsonDocument doc(capacity);
  // deserializeJson(doc, lastPayload);
  // Serial.println(doc["timestamp"]);
}