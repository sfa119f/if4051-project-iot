#include "finger.h"

#define mySerial Serial2

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
uint8_t id;

void fingerInit()
{
  finger.begin(57600);

  if (finger.verifyPassword())
  {
    Serial.println("Found fingerprint sensor!");
  }
  else
  {
    Serial.println("Did not find fingerprint sensor :(");
    while (1)
    {
      delay(1);
    }
  }
}

int fingerLoop()
{
  int p = -1;
  Serial.print("Waiting for valid finger");
  p = finger.getImage();
  switch (p)
  {
  case FINGERPRINT_OK:
    Serial.println("Image taken");
    break;
  case FINGERPRINT_NOFINGER:
    Serial.println(".");
    break;
  case FINGERPRINT_PACKETRECIEVEERR:
    Serial.println("Communication error");
    break;
  case FINGERPRINT_IMAGEFAIL:
    Serial.println("Imaging error");
    break;
  default:
    Serial.println("Unknown error");
    break;
  }

  if (p != FINGERPRINT_OK)
    return -1;

  p = finger.image2Tz(1);
  switch (p)
  {
  case FINGERPRINT_OK:
    Serial.println("Image converted");
    break;
  case FINGERPRINT_IMAGEMESS:
    Serial.println("Image too messy");
    break;
    // return p;
  case FINGERPRINT_PACKETRECIEVEERR:
    Serial.println("Communication error");
    break;
    // return p;
  case FINGERPRINT_FEATUREFAIL:
    Serial.println("Could not find fingerprint features");
    break;
    // return p;
  case FINGERPRINT_INVALIDIMAGE:
    Serial.println("Could not find fingerprint features");
    break;
    // return p;
  default:
    Serial.println("Unknown error");
    break;
    // return p;
  }

  Serial.println("Remove finger");
  delay(2000);
  // p = 0;
  // while (p != FINGERPRINT_NOFINGER)
  // {
  //   p = finger.getImage();
  // }
  return 0;
}
