#include <stdio.h>
#include "rfid.h"
#include "../../Utils/Encrypt/rijndael.h"

MFRC522 mfrc522(RFID_SS, RFID_RST);
MFRC522::MIFARE_Key rfid_key;
byte rfid_uid_sector = 1;
byte rfid_uid_blockAddr = 4;
byte rfid_balance_sector = 1;
byte rfid_balance_blockAddr = 5;
String key = "randomid";

bool debug = true;

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

uint32_t bytearrtouint32t(byte *buffer, byte bufferSize)
{
  uint32_t val = 0;
  for (byte i = 0; i < bufferSize; i++)
  {
    val += buffer[i] << ((bufferSize - 1 - i) * 8);
  }
  return val;
}

void uint32ttobytearr(byte *buffer, byte bufferSize, byte padding, uint32_t value)
{
  for (byte i = 0; i < bufferSize; i++)
  {
    buffer[i] = byte(value >> ((bufferSize - 1 - i) * 8));
  }
  for (byte i = 0; i < padding; i++)
  {
    buffer[bufferSize + i] = byte(0);
  }
}

void getRandomID(byte *buffer, byte bufferSize)
{
  for (byte i = 0; i < bufferSize; i++)
  {
    buffer[i] = byte(random(0, 256));
  }
}

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

void rfidAuth(MFRC522::StatusCode *status, int blockAddr)
{
  *status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockAddr, &rfid_key, &(mfrc522.uid));
  if (*status != MFRC522::STATUS_OK)
  {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(*status));
    return;
  }
}

void rfidEnd()
{
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

void rfidRead(MFRC522::StatusCode *status, byte addr, byte *buffer, byte buffer_len)
{
  rfidAuth(status, addr);
  *status = mfrc522.MIFARE_Read(addr, buffer, &buffer_len);
  if (*status != MFRC522::STATUS_OK)
  {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(*status));
    return;
  }
}

void rfidWrite(MFRC522::StatusCode *status, byte addr, byte *buffer, byte buffer_len)
{
  rfidAuth(status, addr);
  *status = mfrc522.MIFARE_Write(addr, buffer, buffer_len);
  if (*status != MFRC522::STATUS_OK)
  {
    Serial.print(F("Writing failed: "));
    Serial.println(mfrc522.GetStatusCodeName(*status));
    return;
  }
}

void readWriteCardBalance(MFRC522::StatusCode *status, byte *buffer, byte len, uint32_t *value, bool operation, uint32_t delta)
{
  byte buffer_len = 18;
  byte id_buffer_len = 16;
  byte id_buffer[buffer_len];
  byte balance_buffer_len = 4;
  byte padded_balance_buffer_len = 16;
  byte balance_buffer[buffer_len];
  byte crypt_buffer[17];
  uint32_t balance;

  rfidRead(status, rfid_uid_blockAddr, id_buffer, buffer_len);
  if (*status != MFRC522::STATUS_OK)
  {
    return;
  }

  decrypt(id_buffer, id_buffer_len, key, crypt_buffer);
  memcpy(buffer, crypt_buffer, len);

  rfidRead(status, rfid_balance_blockAddr, balance_buffer, buffer_len);
  if (*status != MFRC522::STATUS_OK)
  {
    return;
  }

  balance = bytearrtouint32t(balance_buffer, balance_buffer_len);
  if (operation)
  {
    balance += delta;
    *value = balance;
  }
  else
  {
    balance -= delta;
    *value = balance;
  }

  uint32ttobytearr(balance_buffer, balance_buffer_len, 12, balance);
  rfidWrite(status, rfid_balance_blockAddr, balance_buffer, padded_balance_buffer_len);
  if (*status != MFRC522::STATUS_OK)
  {
    return;
  }
}

void genCard(MFRC522::StatusCode *status, byte *buffer, byte len)
{
  byte buffer_len = 18;
  byte id_buffer_len = 16;
  byte id_buffer[buffer_len];
  byte balance_buffer_len = 4;
  byte padded_balance_buffer_len = 16;
  byte balance_buffer[buffer_len];
  byte crypt_buffer[17];
  uint32_t default_balance = 50000;

  getRandomID(id_buffer, id_buffer_len);
  memcpy(buffer, id_buffer, len);
  encrypt(id_buffer, id_buffer_len, key, crypt_buffer);

  rfidWrite(status, rfid_uid_blockAddr, id_buffer, id_buffer_len);
  if (*status != MFRC522::STATUS_OK)
  {
    return;
  }

  uint32ttobytearr(balance_buffer, balance_buffer_len, 12, default_balance);
  rfidWrite(status, rfid_balance_blockAddr, balance_buffer, padded_balance_buffer_len);
  if (*status != MFRC522::STATUS_OK)
  {
    return;
  }
}

void dumpIdBalance()
{
  MFRC522::StatusCode status;
  byte buffer_len = 18;
  byte id_buffer_len = 16;
  byte id_buffer[buffer_len];
  byte balance_buffer_len = 4;
  byte padded_balance_buffer_len = 16;
  byte balance_buffer[buffer_len];
  byte crypt_buffer[17];
  uint32_t balance;

  Serial.println("Reading ID... ");

  rfidRead(&status, rfid_uid_blockAddr, id_buffer, buffer_len);
  if (status != MFRC522::STATUS_OK)
  {
    return;
  }

  decrypt(id_buffer, id_buffer_len, key, crypt_buffer);
  Serial.print("Enc ID: ");
  dump_byte_array(id_buffer, id_buffer_len);
  Serial.println();

  Serial.print("Dec ID: ");
  dump_byte_array(crypt_buffer, id_buffer_len);
  Serial.println();

  Serial.println("Reading balance...");
  rfidRead(&status, rfid_balance_blockAddr, balance_buffer, buffer_len);
  if (status != MFRC522::STATUS_OK)
  {
    return;
  }

  Serial.print("Balance: ");
  dump_byte_array(balance_buffer, padded_balance_buffer_len);
  Serial.println();

  Serial.print("Balance: ");
  Serial.println(bytearrtouint32t(balance_buffer, balance_buffer_len));
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
  uint32_t balance;
  uint32_t delta;

  switch (cursor)
  {
  case 0:
    readCardID(&_status, id_buffer, len);

    if (debug)
    {
      Serial.println("Card");
      dumpIdBalance();
    }
    break;
  case 1:
    if (debug)
    {
      Serial.println("Prev Card");
      dumpIdBalance();
    }

    delta = 3000;
    readWriteCardBalance(&_status, id_buffer, len, &balance, false, delta);

    if (debug)
    {
      Serial.println("New Card");
      dumpIdBalance();
    }
    break;
  case 2:
    if (debug)
    {
      Serial.println("Prev Card");
      dumpIdBalance();
    }

    delta = 5000;
    readWriteCardBalance(&_status, id_buffer, len, &balance, true, delta);

    if (debug)
    {
      Serial.println("New Card");
      dumpIdBalance();
    }
    break;
  case 3:
  {
    if (debug)
    {
      Serial.println("Prev Card");
      dumpIdBalance();
    }

    genCard(&_status, id_buffer, len);

    if (debug)
    {
      Serial.println("New Card");
      dumpIdBalance();
    }
    break;
  }
  default:
    readCardID(&_status, id_buffer, len);
    break;
  }

  rfidEnd();

  if (_status == MFRC522::STATUS_OK)
  {
    memcpy(uid, id_buffer, len);
    return 0;
  }
  return 3;
}
