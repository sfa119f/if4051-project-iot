#include "rfid.h"

MFRC522 mfrc522(RFID_SS, RFID_RST);
MFRC522::MIFARE_Key rfid_key;
byte rfid_uid_sector = 1;
byte rfid_uid_blockAddr = 4;

void rfidInit()
{
  SPI.begin();
  mfrc522.PCD_Init();
  for (byte i = 0; i < 6; i++)
  {
    rfid_key.keyByte[i] = 0xFF;
  }
  delay(20);                         // Optional delay. Some board do need more time after init to be ready, see Readme
  mfrc522.PCD_DumpVersionToSerial(); // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void readCardID(MFRC522::StatusCode *read_status, byte *id_buffer, byte buffer_len)
{
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);

  // Check for compatibility
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI && piccType != MFRC522::PICC_TYPE_MIFARE_1K && piccType != MFRC522::PICC_TYPE_MIFARE_4K)
  {
    Serial.println(F("This sample only works with MIFARE Classic cards."));
    return;
  }

  mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid)); // dump some details about the card

  *read_status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, rfid_uid_blockAddr, &rfid_key, &(mfrc522.uid));
  if (*read_status != MFRC522::STATUS_OK)
  {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(*read_status));
    return;
  }

  *read_status = mfrc522.MIFARE_Read(rfid_uid_blockAddr, id_buffer, &buffer_len);
  if (*read_status != MFRC522::STATUS_OK)
  {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(*read_status));
    return;
  }

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

void writeCardID(MFRC522::StatusCode *write_status, byte *id_buffer, byte buffer_len)
{
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);

  // Check for compatibility
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI && piccType != MFRC522::PICC_TYPE_MIFARE_1K && piccType != MFRC522::PICC_TYPE_MIFARE_4K)
  {
    Serial.println(F("This sample only works with MIFARE Classic cards."));
    return;
  }

  mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid)); // dump some details about the card

  *write_status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, rfid_uid_blockAddr, &rfid_key, &(mfrc522.uid));
  if (*write_status != MFRC522::STATUS_OK)
  {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(*write_status));
    return;
  }

  *write_status = mfrc522.MIFARE_Write(rfid_uid_blockAddr, id_buffer, buffer_len);
  if (*write_status != MFRC522::STATUS_OK)
  {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(*write_status));
    return;
  }

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

void dump_byte_array(byte *buffer, byte bufferSize)
{
  for (byte i = 0; i < bufferSize; i++)
  {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

String bytetostring(byte *buffer, byte bufferSize)
{
  String text = "";
  for (byte i = 0; i < bufferSize; i++)
  {
    text += (buffer[i] < 0x10 ? "0" : "");
    text += String(buffer[i], HEX);
  }
  return text;
}

void getRandomID(byte *buffer, byte bufferSize)
{
  for (byte i = 0; i < bufferSize; i++)
  {
    buffer[i] = byte(random(0, 256));
  }
}

int rfidLoop(int cursor, byte uid[16])
{
  if (!mfrc522.PICC_IsNewCardPresent())
  {
    delay(1);
    return 1;
  }
  Serial.println("NEW CARD");
  if (!mfrc522.PICC_ReadCardSerial())
  {
    delay(1);
    return 2;
  }
  Serial.println("Reading card..");

  byte id_buffer[18];
  byte len = 18;
  MFRC522::StatusCode _status;

  switch (cursor)
  {
  case 0:
    readCardID(&_status, id_buffer, len);
    break;
  case 1:
    readCardID(&_status, id_buffer, len);
    break;
  case 2:
    readCardID(&_status, id_buffer, len);
    break;
  case 3:
  {
    len = 16;
    getRandomID(id_buffer, len);
    writeCardID(&_status, id_buffer, len);
    break;
  }
  default:
    readCardID(&_status, id_buffer, len);
    break;
  }

  if (_status == MFRC522::STATUS_OK)
  {
    Serial.print(F("ID: "));
    dump_byte_array(id_buffer, 16);
    memcpy(uid, id_buffer, 16);
    Serial.println();
    return 0;
  }
  return -1;
}
